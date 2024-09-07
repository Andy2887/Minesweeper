//
// Created by yuanliheng on 4/15/24.
//

#ifndef MINESWEEPER_TILE_H
#define MINESWEEPER_TILE_H
#include <vector>
using namespace std;

class Tile {
private:
    vector<Tile*> adjacent_tiles;
    int num_adjacent_mine = 0;
    int r;
    int c;
    bool is_mine = false;
    bool is_flagged = false;
    bool is_revealed = false;

public:
    Tile();

    Tile(bool is_mine);

    void addAdjacentTile(Tile* adjTile);

    void flag_tile();

    void remove_flag();

    void reveal_tile();

    void set_mine();

    void increment_adj_mine_num();

    vector<Tile*> get_adjacent_tiles();

    bool get_is_flagged();

    bool get_is_revealed();

    bool get_is_mine();

    int get_num_adj_mines();

    void setRow(int r);

    int getRow();

    void setCol(int c);

    int getCol();




};


#endif //MINESWEEPER_TILE_H
