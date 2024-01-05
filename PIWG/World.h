#pragma once
#include <ctime>
#include <set>
#include "Region.h"

// The game world itself, holds all regions and manages the dynamic loading system.
class World{
    public:
        World(int seed = time(NULL), int regionSize = 10, Location renderDistance = Location(3, 3));
        ~World(){}

        // Functions which apply cellular automata and dynamic loading.
        void update(Location worldLocation);
        void generateRegions(std::set<Location> regionLocations);
        void smoothRegions(std::set<Location> regionLocations);
        void unloadRegions(std::set<Location> regionLocations);

        // Helper functions which determine which 
        // regions are to be rendered or unrendered.
        std::set<Location> renderedRegions();
        std::set<Location> unrenderedRegions();
        
        // Utility functions which look at the tiles surrounding a 
        // particular location and count how many wall tiles are present.
        int numAdjacentWalls(Location worldLocation);
        int numSurroundingWalls(Location worldLocation);

        // Math-based functions for conversion between location types.
        Location localToWorld(RelativeLocation relativeLocation);
        RelativeLocation worldToLocal(Location worldLocation);

        // Utility functions for directly dealing with tiles,
        // calls the Region class equivalent of each function.
        Tile* tileAt(Location worldLocation);
        Tile* tileAt(RelativeLocation relativeLocation);
        bool tileExistsAt(Location worldLocation);
        bool tileExistsAt(RelativeLocation relativeLocation);

        // Utility functions for locating regions.
        Region* regionAt(Location regionLocation);
        bool regionExistsAt(Location regionLocation);

        int& regionSize(){return _regionSize;}
        const int regionSize() const{return _regionSize;}
        Location& playerLocation(){return _playerLocation;}
        const Location& playerLocation() const{return _playerLocation;}
        Location& renderDistance(){return _renderDistance;}
        const Location& renderDistance() const{return _renderDistance;}
    private:
        int _regionSize;
        Location _playerLocation;
        Location _activeRegion;
        Location _renderDistance;
        std::map<Location, Region> _regions;
};