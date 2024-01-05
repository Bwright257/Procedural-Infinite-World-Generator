#include <cmath>
#include "World.h"

World::World(int seed, int regionSize, Location renderDistance) : _regionSize(regionSize), _renderDistance(renderDistance){
    srand(seed); // Seeds the random generation of the world.
    return;
}

void World::update(Location worldLocation){
    // Sets the active region and gets all regions within render distance.
    _activeRegion = worldToLocal(worldLocation).regionLocation();
    std::set<Location> regionLocations = renderedRegions();

    // Unload the old regions, generate the new regions, and finally
    // apply the cellular automata algorithm to smooth out each region.
    unloadRegions(unrenderedRegions());
    generateRegions(regionLocations);
    smoothRegions(regionLocations);
    return;
}

void World::generateRegions(std::set<Location> regionLocations){
    // Creates a region at each location.
    for (auto & regionLocation : regionLocations){
        _regions.emplace(regionLocation, Region(_regionSize));
    }

    return;
}

void World::smoothRegions(std::set<Location> regionLocations){
    std::set<Location> smoothedRegions;
    const int cycles{10}; // How many times the algorithm should loop, higher 
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

void World::unloadRegions(std::set<Location> regionLocations){
    // Currently deletes each region, TODO: load each region into storage.
    for (auto & regionLocation : regionLocations){
        _regions.erase(regionLocation);
    }

    return;
}

std::set<Location> World::renderedRegions(){
    std::set<Location> regionLocations;
    
    // Finds the location of every region within render distance of the active region.
    for (int i = _activeRegion.row() - _renderDistance.row(); i <= _activeRegion.row() + _renderDistance.row(); i++){
        for (int j = _activeRegion.column() - _renderDistance.column(); j <= _activeRegion.column() + _renderDistance.column(); j++){
            regionLocations.insert(Location(i, j));
        }
    }

    return regionLocations;
}

std::set<Location> World::unrenderedRegions(){
    std::set<Location> regionLocations;

    // Initialize the set with every loaded region.
    for (auto & region : _regions){
        regionLocations.insert(region.first);
    }

    // Subtract every region to be rendered.
    for (auto & regionLocation : renderedRegions()){
        regionLocations.erase(regionLocation);
    }

    // Result is every region to be unrendered.
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
            if (rand() % 100 > 66){
                count++;
            }
        }
    }

    return count;
}

Location World::localToWorld(RelativeLocation relativeLocation){
    return relativeLocation.localLocation() + (relativeLocation.regionLocation() * _regionSize);
}

RelativeLocation World::worldToLocal(Location worldLocation){
    Location regionLocation = Location(floor(double(worldLocation.row()) / double(_regionSize)), floor(double(worldLocation.column()) / double(_regionSize)));
    Location localLocation = (regionLocation * -_regionSize) + worldLocation;

    return RelativeLocation(regionLocation, localLocation);
}

Tile* World::tileAt(Location worldLocation){
    return tileAt( worldToLocal(worldLocation));
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