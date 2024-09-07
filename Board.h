//
// Created by yuanliheng on 4/16/24.
//

#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H
#include "Tile.h"

class Board {
private:
    int numRows;
    int numCols;
    int numTotalMine;
    int num_remaining_mine_for_user;
    int num_revealed_tiles = 0;
    bool gameWin = false;
    bool gameLose = false;
    bool gameProgressing = true;
    bool debugMode = false;
    vector<vector<Tile>> vec_Board;
public:
    Board(int rows, int cols, int num_mine);
    vector<vector<Tile>> getGameBoard();
    int getRemainingMineForUser();
    void setRemainingMineForUser(int change);
    int getNumRevealedTiles();
    int getNumTotalMine();
    void setNumRevealedTiles(int change);
    void setGameWin();
    void setGameLose();
    bool getGameWin();
    bool getGameLose();
    bool getIsMine(int r, int c);
    bool getIsRevealed(int r, int c);
    bool getIsFlagged(int r, int c);
    Tile* getTilePtr(int r, int c);
    int getNumAdjMines(int r, int c);

    void revealTile(int r, int c);
    void revealNeighbours(int r, int c);
    void flagTile(int r, int c);
    void removeFlag(int r, int c);
    void setGameProgressing();
    bool getGameProgressing();
    void setDebugMode();
    bool getDebugMode();


};


#endif //MINESWEEPER_BOARD_H
