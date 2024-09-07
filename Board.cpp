//
// Created by yuanliheng on 4/16/24.
//
#include <iostream>
#include "Board.h"

using namespace std;

Board::Board(int numRows, int numCols, int numTotalMine) {
    this->numRows = numRows;
    this->numCols = numCols;
    this->numTotalMine = numTotalMine;
    num_remaining_mine_for_user = numTotalMine;

    // create a board for our game
    vector<vector<Tile>> vec_Board(numRows, vector<Tile>(numCols));
    this->vec_Board = vec_Board;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            this->vec_Board[i][j] = Tile();
        }
    }

    // set adjacent tiles for our game
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            for (int dx = -1; dx <= 1; dx++){
                for (int dy = -1; dy <= 1; dy++){
                    int x = i + dx;
                    int y = j + dy;

                    if (x >= 0 && x < numRows && y >= 0 && y < numCols){
                        if (!(i == x && j == y)){
                            this->vec_Board[i][j].addAdjacentTile(&this->vec_Board[x][y]);
                        }
                    }
                }
            }
        }
    }


    // set mines for our game
    int mine_in_map = 0;
    int randRow;
    int randCol;
    while(mine_in_map < numTotalMine){
        randRow = (rand() % numRows);
        randCol = (rand() % numCols);
        if (!this->vec_Board[randRow][randCol].get_is_mine()){
            this->vec_Board[randRow][randCol].set_mine();
            mine_in_map += 1;
        }
    }

    // set the number of mines near a tile
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            vector<Tile*> vec_adjTiles_ptrs = this->vec_Board[i][j].get_adjacent_tiles();
            for (auto ptr : vec_adjTiles_ptrs){
                if (ptr->get_is_mine()){
                    this->vec_Board[i][j].increment_adj_mine_num();
                }
            }
        }
    }
}

vector<vector<Tile>> Board::getGameBoard(){
    return vec_Board;
}

int Board::getRemainingMineForUser() {
    return num_remaining_mine_for_user;
}

void Board::setRemainingMineForUser(int change) {
    num_remaining_mine_for_user += change;
}

int Board::getNumRevealedTiles() {
    return num_revealed_tiles;
}

int Board::getNumTotalMine(){
    return numTotalMine;
}

void Board::setNumRevealedTiles(int change) {
    num_revealed_tiles += change;
}


void Board::setGameWin() {
    gameWin = true;
}

void Board::setGameLose() {
    gameLose = true;
}

bool Board::getGameWin() {
    return gameWin;
}

bool Board::getGameLose() {
    return gameLose;
}

bool Board::getIsMine(int r, int c) {
    return vec_Board[r][c].get_is_mine();
}

bool Board::getIsRevealed(int r, int c){
    return vec_Board[r][c].get_is_revealed();
}

bool Board::getIsFlagged(int r, int c){
    return vec_Board[r][c].get_is_flagged();
}

Tile* Board::getTilePtr(int r, int c){
    return &vec_Board[r][c];
}

int Board::getNumAdjMines(int r, int c){
    return vec_Board[r][c].get_num_adj_mines();
}


void Board::revealTile(int r, int c) {
    vec_Board[r][c].reveal_tile();
    num_revealed_tiles += 1;
}

void Board::revealNeighbours(int r, int c){
    revealTile(r,c);
    if (vec_Board[r][c].get_num_adj_mines() == 0){
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                int newRow = r + dr;
                int newCol = c + dc;
                // Skip the current tile
                if (dr == 0 && dc == 0) continue;
                if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols){
                    if (!vec_Board[newRow][newCol].get_is_revealed()){
                        revealNeighbours(newRow, newCol); // Recursively reveal neighboring tiles
                    }
                }
            }
        }
    }
}

void Board::flagTile(int r, int c){
    vec_Board[r][c].flag_tile();
}

void Board::removeFlag(int r, int c){
    vec_Board[r][c].remove_flag();
}

void Board::setGameProgressing() {
    gameProgressing = !gameProgressing;
}

bool Board::getGameProgressing() {
    return gameProgressing;
}

void Board::setDebugMode() {
    debugMode = !debugMode;
}

bool Board::getDebugMode() {
    return debugMode;
}