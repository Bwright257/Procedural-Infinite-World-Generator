#include <stdlib.h>
#include "Region.h"

// Upon a region being created, it populates itself with a random noise of tiles.
Region::Region(int size) : _isComplete(false){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            createTile(Location(i, j), rand() % 2 == 0 ? Tile(TILE_WALL) : Tile(TILE_GROUND));
        }
    }

    return;
}

Tile* Region::tileAt(Location localLocation){
    if (_tiles.find(localLocation) != _tiles.end()){
        return &_tiles.find(localLocation)->second;
    }

    return nullptr;
}

Tile* Region::createTile(Location localLocation, Tile tile){
    _tiles.emplace(localLocation, tile);
    return tileAt(localLocation);
}

void Region::destroyTile(Location localLocation){
    if (tileExistsAt(localLocation)){
        _tiles.erase(localLocation);
    }
    
    return;
}

bool Region::tileExistsAt(Location localLocation){
    return _tiles.count(localLocation) > 0;
}