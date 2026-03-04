#include "Game.h"

#include <cstdlib>


void Game::placeBombs(int idx){
    if(firstClick || bombsNumber<=0){
        return;
    }

    int bombsPlaced = 0;
    int size = rows * cols;

    while(bombsPlaced < bombsNumber){
        int bomb = rand() % size;

        if(bomb == idx){
            continue;
        }

        if(grid[bomb].hasBomb){
            continue;
        }

        grid[bomb].hasBomb = true;
        bombsPlaced++;
    }

    firstClick = true;
}

int Game::bombsAround(int idx) const {
    if(grid[idx].hasBomb){
        return 0;
    }

    int r = idx / cols;
    int c = idx % cols;

    int counterBombsAround=0;

    for(int dirRows = -1; dirRows <= 1; dirRows++){
        for(int dirCols = -1; dirCols <= 1; dirCols++){

            if(dirRows == 0 && dirCols == 0){
                continue;
            }

            int newRows = r + dirRows;
            int newCols = c + dirCols;

            if(newRows >= 0 && newRows < rows){
                if(newCols >= 0 && newCols < cols){

                    int bombIdx = newRows + cols * newCols;
                    if(grid[bombIdx].hasBomb){
                        counterBombsAround++;
                    }

                }
            }
        }
    }
}


int Game::index(int r, int c) const{
    return (r * cols) + c;
}

bool Game::toggleFlag(int idx, int counter){
    if(grid[idx].isRevealed()){
        return false;
    }

    if(grid[idx].isFlagged()){
        grid[idx].setFlagged(false);
        counter++;
    }else{
        grid[idx].setFlagged(true);
        counter--;
    }

    return true;
}

bool Game::hasBomb(int idx) const {
    if(grid[idx].isBomb()){
        return true;
    }

    return false;
}

