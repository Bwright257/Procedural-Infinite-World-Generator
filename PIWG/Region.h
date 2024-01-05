#pragma once
#include <map>
#include "Tile.h"
#include "Location.h"

// Utilized by the world class, separating the world into an uniformly-sized array of regions.
// These regions each hold a uniformly-sized array of tiles.
class Region{
    public:
        Region(int size);
        ~Region(){}

        // Utility functions for directly dealing with tiles.
        Tile* tileAt(Location localLocation);
        Tile* createTile(Location localLocation, Tile tile);
        void destroyTile(Location localLocation);
        bool tileExistsAt(Location localLocation);

        // Whether this region has been generated and smoothed via cellular automata.
        // Is set by the smoothRegions function in the World class.
        bool& isComplete(){return _isComplete;}
        const bool isComplete() const{return _isComplete;}
        std::map<Location, Tile>& tiles(){return _tiles;}
        const std::map<Location, Tile>& tiles() const{return _tiles;}
    private:
        bool _isComplete;
        std::map<Location, Tile> _tiles;
};