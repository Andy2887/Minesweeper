//
// Created by yuanliheng on 4/15/24.
//

#include "Tile.h"

Tile::Tile(){

}

Tile::Tile(bool is_mine) {
    this->is_mine = is_mine;
    is_flagged = false;
    is_revealed = false;
}

void Tile::addAdjacentTile(Tile* adjTile){
    adjacent_tiles.push_back(adjTile);
}

void Tile::flag_tile(){
    is_flagged = true;
}

void Tile::remove_flag(){
    is_flagged = false;
}

void Tile::reveal_tile(){
    is_revealed = true;
}

void Tile::set_mine(){
    is_mine = true;
}

void Tile::increment_adj_mine_num(){
    num_adjacent_mine += 1;
}

vector<Tile*> Tile::get_adjacent_tiles(){
    return adjacent_tiles;
}

bool Tile::get_is_flagged(){
    return is_flagged;
}

bool Tile::get_is_revealed(){
    return is_revealed;
}

bool Tile::get_is_mine(){
    return is_mine;
}

int Tile::get_num_adj_mines(){
    return num_adjacent_mine;
}

void Tile::setRow(int r){
    this->r = r;
}

int Tile::getRow(){
    return r;
}

void Tile::setCol(int c){
    this->c = c;
}

int Tile::getCol(){
    return c;
}