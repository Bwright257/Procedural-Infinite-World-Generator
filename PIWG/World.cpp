#include <filesystem>
#include <fstream>
#include <string>
#include <cmath>
#include "World.h"

World::World(int seed, int regionSize, Location loadDistance) : _regionSize(regionSize), _loadDistance(loadDistance){
    std::filesystem::remove_all("Data/Regions/");
    std::filesystem::create_directory("Data/Regions");
    srand(seed); // Seeds the random generation of the world.
    return;
}

World::~World(){
    std::filesystem::remove_all("Data/Regions/");
    return;
}

void World::update(Location worldLocation){
    // Sets the active region based on the input location.
    _activeRegion = worldToLocal(worldLocation).regionLocation();

    // Save and then unload regions that fall out of the load distance.
    std::set<Location> unloadLocations = regionsToUnload();
    saveRegions(unloadLocations);
    unloadRegions(unloadLocations);

    std::set<Location> loadLocations = regionsToLoad();
    std::set<Location> generatedLocations;

    // If a region is saved it's loaded, otherwise it's generated.
    for (auto & regionLocation : loadLocations){
        if (isRegionSaved(regionLocation)){
            loadRegion(regionLocation);
        } else {
            generateRegion(regionLocation);
            generatedLocations.insert(regionLocation);
        }
    }
    
    // Smooth all regions that were just generated.
    smoothRegions(generatedLocations);

    return;
}

void World::generateRegion(Location regionLocation){
    // Creates a region at a location.
    _regions.emplace(regionLocation, Region(_regionSize));
    return;
}

void World::generateRegions(std::set<Location> regionLocations){
    // Creates a region at each location.
    for (auto & regionLocation : regionLocations){
        generateRegion(regionLocation);
    }

    return;
}

void World::smoothRegions(std::set<Location> regionLocations){
    std::set<Location> smoothedRegions;
    const int cycles{7}; // How many times the algorithm should loop, higher 
                          // values lead to a longer loading time but a smoother world.
    
    for (int c = 0; c < cycles; c++){
        std::map<Location, Tile> tiles; // A copy of every tile in the world, important so that the
                                        // parameters of the algorithm don't change after it's started.

        // Accumulates every tile in each region.
        for (auto & regionLocation : regionLocations){
            if (regionExistsAt(regionLocation) && !regionAt(regionLocation)->isComplete()){
                smoothedRegions.insert(regionLocation); // Flag to make sure a region isn't changed in the future.

                for (auto & tile : regionAt(regionLocation)->tiles()){
                    Location tileLocation = localToWorld(RelativeLocation(regionLocation, tile.first));
                    tiles.emplace(tileLocation, tile.second);
                }
            }
        }

        // Cellular automata algorithm, determines if a tile should change its type.
        for (auto & tile : tiles){
            if (tileExistsAt(tile.first)){
                int wallCount = numSurroundingWalls(tile.first);

                // Each tile switches type based on its surroundings.
                if (tileAt(tile.first)->type() == TILE_GROUND && wallCount >= 5){
                    tiles[tile.first].type() = TILE_WALL;
                } else if (tileAt(tile.first)->type() == TILE_WALL && wallCount < 4){
                    tiles[tile.first].type() = TILE_GROUND;
                }
            }
        }

        // Set the actual worlds tiles with their new types.
        for (auto & tile : tiles){
            if (tileExistsAt(tile.first)){
                tileAt(tile.first)->type() = tile.second.type();
            }
        }
    }
    
    // Makes sure every affected region is never touched by further cycles.
    for (auto & regionLocation : smoothedRegions){
        regionAt(regionLocation)->isComplete() = true;
    }

    return;
}

void World::saveRegion(Location regionLocation){
    std::ofstream outFile;
    outFile.open(pathToRegion(regionLocation), std::ostream::trunc);

    // Saves each tile as its location plus its icon.
    // Format appears as "(row,column) icon ".
    for (auto & tile : regionAt(regionLocation)->tiles()){
        outFile << std::to_string(tile.first.row()) + " " + std::to_string(tile.first.column()) + " " + std::to_string(tile.second.type()) + " ";
    }

    outFile.close();
    return;
}

void World::saveRegions(std::set<Location> regionLocations){
    // Saves each region in the set.
    for (auto & regionLocation : regionLocations){
        saveRegion(regionLocation);
    }

    return;
}

void World::loadRegion(Location regionLocation){
    std::string path = pathToRegion(regionLocation);

    if (isRegionSaved(regionLocation)){
        std::ifstream inFile;
        inFile.open(path);

        std::map<Location, Tile> tiles;
        std::string row, column, type;

        // Creates a new region with the tiles found in the associated region file.
        while (inFile.good()){
            inFile >> row;
            inFile >> column;
            inFile >> type;
            tiles.emplace(Location(std::stoi(row), std::stoi(column)), Tile(static_cast<TileTypes>(std::stoi(type))));
        }

        _regions.emplace(regionLocation, Region(tiles));
        inFile.close();
    }

    return;
}

void World::loadRegions(std::set<Location> regionLocations){
    // Loads each region in the set.
    for (auto & regionLocation : regionLocations){
        loadRegion(regionLocation);
    }

    return;
}

void World::unloadRegion(Location regionLocation){
    // Unloads a specific region.
    _regions.erase(regionLocation);
    return;
}

void World::unloadRegions(std::set<Location> regionLocations){
    // Unloads each region in the set.
    for (auto & regionLocation : regionLocations){
        unloadRegion(regionLocation);
    }

    return;
}

bool World::isRegionSaved(Location regionLocation){
    // Returns true if the path to a region file is valid.
    return std::filesystem::exists(pathToRegion(regionLocation));
}

std::string World::pathToRegion(Location regionLocation){
    // Gets the path to a region file, format is (row,column).
    return "Data/Regions/(" + std::to_string(regionLocation.row()) + "," + std::to_string(regionLocation.column()) + ")";
}

std::set<Location> World::regionsToLoad(){
    std::set<Location> regionLocations;
    
    // Finds the location of every region within load distance of the active region.
    for (int i = _activeRegion.row() - _loadDistance.row(); i <= _activeRegion.row() + _loadDistance.row(); i++){
        for (int j = _activeRegion.column() - _loadDistance.column(); j <= _activeRegion.column() + _loadDistance.column(); j++){
            regionLocations.insert(Location(i, j));
        }
    }

    return regionLocations;
}

std::set<Location> World::regionsToUnload(){
    std::set<Location> regionLocations;

    // Initialize the set with every loaded region.
    for (auto & region : _regions){
        regionLocations.insert(region.first);
    }

    // Subtract every region to be loaded.
    for (auto & regionLocation : regionsToLoad()){
        regionLocations.erase(regionLocation);
    }

    // Result is every region to be unloaded.
    return regionLocations;
}

int World::numAdjacentWalls(Location worldLocation){
    int count{0}; // Wall count.

    // Loops for all cardinal directions.
    for (int i = DIR_NORTH; i <= DIR_EAST; i++){
        Location target = directionalLocation(worldLocation, static_cast<Directions>(i));

        // Counts if a wall exists at the target location.
        if (tileExistsAt(target) && tileAt(target)->type() == TILE_WALL){
            count++;
        }
    }

    return count;
}

int World::numSurroundingWalls(Location worldLocation){
    int count{0}; // Wall count.
    
    // Loops for all cardinal and intermediate directions.
    for (int i = DIR_NORTH; i <= DIR_SOUTHEAST; i++){
        Location target = directionalLocation(worldLocation, static_cast<Directions>(i));

        // Counts if a wall exists at the target location.
        if (tileExistsAt(target)){
            if (tileAt(target)->type() == TILE_WALL){
                count++;
            }
        } else {
            // Any tile on the outside of the loaded regions is undetermined.
            if (rand() % 2 == 0){
                count++;
            }
        }
    }

    return count;
}

Location World::localToWorld(RelativeLocation relativeLocation){
    // Converts a local location within a region to a world location.
    return relativeLocation.localLocation() + (relativeLocation.regionLocation() * _regionSize);
}

RelativeLocation World::worldToLocal(Location worldLocation){
    // Converts a world location to a relative region and local location.
    Location regionLocation = Location(floor(double(worldLocation.row()) / double(_regionSize)), floor(double(worldLocation.column()) / double(_regionSize)));
    Location localLocation = (regionLocation * -_regionSize) + worldLocation;
    return RelativeLocation(regionLocation, localLocation);
}

Tile* World::tileAt(Location worldLocation){
    return tileAt(worldToLocal(worldLocation));
}

Tile* World::tileAt(RelativeLocation relativeLocation){
    if (tileExistsAt(relativeLocation)){
        return regionAt(relativeLocation.regionLocation())->tileAt(relativeLocation.localLocation());
    }

    return nullptr;
}

bool World::tileExistsAt(Location worldLocation){
    return tileExistsAt(worldToLocal( worldLocation));
}

bool World::tileExistsAt(RelativeLocation relativeLocation){
    if (regionExistsAt(relativeLocation.regionLocation())){
        return regionAt(relativeLocation.regionLocation())->tileExistsAt(relativeLocation.localLocation());
    }

    return false;
}

Region* World::regionAt(Location regionLocation){
    if (_regions.find(regionLocation) != _regions.end()){
        return &_regions.find(regionLocation)->second;
    }

    return nullptr;
}

bool World::regionExistsAt(Location regionLocation){
    return _regions.count(regionLocation) > 0;
}