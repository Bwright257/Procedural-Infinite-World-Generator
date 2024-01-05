#pragma once

// Represents each possible type a tile can be and its related icon.
typedef enum{TILE_GROUND = ' ', TILE_WALL = '#'} TileTypes;

// Simple holder class.
class Tile{
    public:
        Tile(TileTypes type = TILE_GROUND) : _type(type){}
        ~Tile(){}

        const char icon() const{return char(_type);}
        TileTypes& type(){return _type;}
        const TileTypes type() const{return _type;}
    private:
        TileTypes _type;
};