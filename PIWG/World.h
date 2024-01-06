#pragma once
#include <ctime>
#include <set>
#include "Region.h"

// The game world itself, holds all regions and manages generation and the dynamic loading system.
class World{
    public:
        World(int seed = time(NULL), int regionSize = 25, Location loadDistance = Location(1, 1));
        ~World();

        // Updates the world around a location, typically a player location.
        void update(Location worldLocation);

        // Functions which generate regions and apply procedural generation.
        void generateRegion(Location regionLocation);
        void generateRegions(std::set<Location> regionLocations);
        void smoothRegions(std::set<Location> regionLocations);

        // Functions which apply the dynamic loading system.
        void saveRegion(Location regionLocation);
        void saveRegions(std::set<Location> regionLocations);
        void loadRegion(Location regionLocation);
        void loadRegions(std::set<Location> regionLocations);
        void unloadRegion(Location regionLocation);
        void unloadRegions(std::set<Location> regionLocations);

        // Helper functions for the dynamic loading system.
        bool isRegionSaved(Location regionLocation);
        std::string pathToRegion(Location regionLocation);

        // Helper functions which determine which 
        // regions are to be loaded or unloaded.
        std::set<Location> regionsToLoad();
        std::set<Location> regionsToUnload();
        
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
        Location& loadDistance(){return _loadDistance;}
        const Location& loadDistance() const{return _loadDistance;}
    private:
        int _regionSize;
        Location _playerLocation;
        Location _activeRegion;
        Location _loadDistance;
        std::map<Location, Region> _regions;
};