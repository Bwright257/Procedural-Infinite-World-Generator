#pragma once
#include <map>
#include "Tile.h"
#include "Location.h"

class Region{
    public:
        Region(int size);
        ~Region(){}

        Tile* tileAt(Location localLocation);
        Tile* createTile(Location localLocation, Tile tile);
        void destroyTile(Location localLocation);
        bool tileExistsAt(Location localLocation);

        bool& isComplete(){return _isComplete;}
        const bool isComplete() const{return _isComplete;}
        std::map<Location, Tile>& tiles(){return _tiles;}
        const std::map<Location, Tile>& tiles() const{return _tiles;}
    private:
        bool _isComplete;
        std::map<Location, Tile> _tiles;
};