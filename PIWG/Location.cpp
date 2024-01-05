#include "Location.h"

bool Location::operator<(const Location& location) const{
    return _row < location.row() || (_row == location.row() && _column < location.column());
}

bool Location::operator<=(const Location& location) const{
    return _row <= location.row() && _column <= location.column();
}

bool Location::operator>(const Location& location) const{
    return _row > location.row() || (_row == location.row() && _column > location.column());
}

bool Location::operator>=(const Location& location) const{
    return _row >= location.row() && _column >= location.column();
}

bool Location::operator==(const Location& location) const{
    return _row == location.row() && _column == location.column();
}

Location& Location::operator++(){
    _row++;
    _column++;
    return *this;
}

void Location::operator++(int){
    _row += 1;
    _column += 1;
    return;
}

Location& Location::operator--(){
    _row--;
    _column--;
    return *this;
}

void Location::operator--(int){
    _row -= 1;
    _column -= 1;
    return;
}

Location Location::operator+(const int& value) const{
    return Location(_row + value, _column + value);
}

Location Location::operator+(const Location& location) const{
    return Location(_row + location.row(), _column + location.column());
}

Location  Location::operator-(const int& value) const{
    return Location(_row - value, _column - value);
}

Location Location::operator-(const Location& location) const{
    return Location(_row - location.row(), _column - location.column());
}

Location Location::operator*(const int& value) const{
    return Location(_row * value, _column * value);
}

Location Location::operator*(const Location& location) const{
    return Location(_row * location.row(), _column * location.column());
}

Location Location::operator/(const int& value) const{
    return Location(_row / value, _column / value);
}

Location Location::operator/(const Location& location) const{
    return Location(_row / location.row(), _column / location.column());
}

Location Location::operator%(const int& value) const{
    return Location(_row % value, _column % value);
}

Location Location::operator%(const Location& location) const{
    return Location(_row % location.row(), _column % location.column());
}

Location Location::getDirectionalLocation(Location location, Directions direction){
    switch (direction){
        case DIR_NORTH:
            location.row() -= 1;
            break;
        case DIR_WEST:
            location.column() -= 1;
            break;
        case DIR_SOUTH:
            location.row() += 1;
            break;
        case DIR_EAST:
            location.column() += 1;
            break;
        case DIR_NORTHEAST:
            location.row() -= 1;
            location.column() += 1;
            break;
        case DIR_NORTHWEST:
            location.row() -= 1;
            location.column() -= 1;
            break;
        case DIR_SOUTHWEST:
            location.row() += 1;
            location.column() -= 1;
            break;
        case DIR_SOUTHEAST:
            location.row() += 1;
            location.column() += 1;
            break;
        default:
            break;
    }
    
    return location;
}