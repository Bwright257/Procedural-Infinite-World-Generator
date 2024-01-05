#pragma once
#include <ctime>
#include <set>
#include "Region.h"

class World{
    public:
        World(int seed = time(NULL), int regionSize = 25, Location renderDistance = Location(1, 1));
        ~World(){}

        void update(Location worldLocation);
        void generateRegions(std::set<Location> regionLocations);
        void smoothRegions(std::set<Location> regionLocations);
        void unloadRegions(std::set<Location> regionLocations);
        std::set<Location> renderedRegions();
        std::set<Location> unrenderedRegions();
  
        int numAdjacentWalls(Location worldLocation);
        int numSurroundingWalls(Location worldLocation);

        Location localToWorld(RelativeLocation relativeLocation);
        RelativeLocation worldToLocal(Location worldLocation);

        Tile* tileAt(Location worldLocation);
        Tile* tileAt(RelativeLocation relativeLocation);
        bool tileExistsAt(Location worldLocation);
        bool tileExistsAt(RelativeLocation relativeLocation);

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