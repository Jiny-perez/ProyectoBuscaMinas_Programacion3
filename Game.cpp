#include "Game.h"

#include <cstdlib>
#include <ctime>

void Game::placeBombs(int idx){
    srand(time(0));

    if(bombsNumber<=0){
        return;
    }

    int bombsPlaced = 0;
    int size = rows * cols;

    while(bombsPlaced < bombsNumber){
        int bomb = rand() % size;

        if(bomb == idx){
            continue;
        }

        if(grid[bomb].isBomb()){
            continue;
        }

        grid[bomb].setHasBomb(true);
        bombsPlaced++;
    }

    firstClick = false;
}

int Game::bombsAround(int idx) {
    if(grid[idx].isBomb()){
        return 0;
    }

    int rowIdx = idx / cols;
    int columnIdx = idx % cols;

    int counterBombsAround=0;

    for(int dirRows = -1; dirRows <= 1; dirRows++){
        for(int dirCols = -1; dirCols <= 1; dirCols++){

            if(dirRows == 0 && dirCols == 0){
                continue;
            }

            int newRows = rowIdx + dirRows;
            int newCols = columnIdx + dirCols;

            if(newRows >= 0 && newRows < rows){
                if(newCols >= 0 && newCols < cols){

                    int bombIdx = newRows * cols + newCols;
                    if(grid[bombIdx].isBomb()){
                        counterBombsAround++;
                    }

                }
            }
        }
    }
    return counterBombsAround;
}


int Game::index(int row, int column) const{
    return (row * cols) + column;
}

bool Game::toggleFlag(int idx){
    if(grid[idx].isRevealed()){
        return false;
    }

    if(grid[idx].isFlagged()){
        grid[idx].setFlagged(false);
        flagsPlaced--;
    }else{
        grid[idx].setFlagged(true);
        flagsPlaced++;
    }

    return true;
}

const Cell& Game::getCell(int idx)
{
    return grid[idx];
}

Game::RevealResult Game::reveal(int idx)
{
    RevealResult revealResult{RevealOutcome::NA, {}};

    if (idx < 0 || idx >= rows * cols)
        return revealResult;

    if(firstClick)
    {
        placeBombs(idx);

        for(int i = 0; i < rows * cols; i++)
        {
            int adjacentBombs = bombsAround(i);
            grid[i].setBombsAround(adjacentBombs);
        }
    }

    if(grid[idx].isFlagged() || grid[idx].isRevealed())
        return revealResult;

    revealRecursive(idx, revealResult);

    if(revealResult.outcome != RevealOutcome::BOMB && winCheck())
        revealResult.outcome = RevealOutcome::WON;

    return revealResult;
}

void Game::revealRecursive(int idx, RevealResult& revealResult)
{
    if (idx < 0 || idx >= rows * cols)
        return;

    if (revealResult.outcome == RevealOutcome::BOMB)
        return;

    if(grid[idx].isFlagged())
        return;

    if(grid[idx].isRevealed())
        return;

    grid[idx].setRevealed(true);
    revealResult.changed.push_back(idx);

    if(grid[idx].isBomb())
    {
        revealResult.outcome = RevealOutcome::BOMB;
        return;
    }

    revealResult.outcome = RevealOutcome::REVEALED;
    revealedNumber++;

    if(grid[idx].getBombsAround() > 0)
        return;

    for(int n : neighborsIdx(idx))
        revealRecursive(n, revealResult);
}

std::vector<int> Game::neighborsIdx(int idx) const
{
    std::vector<int> neighbors;
    neighbors.reserve(8);

    int rowIdx = idx / cols;
    int columnIdx = idx % cols;

    for (int dirRow = -1; dirRow <= 1; ++dirRow)
    {
        for (int dirColumn = -1; dirColumn <= 1; ++dirColumn)
        {

            if (dirRow == 0 && dirColumn == 0)
                continue;

            int newRow = rowIdx + dirRow;
            int newColumn = columnIdx + dirColumn;

            if (newRow < 0 || newRow >= rows || newColumn < 0 || newColumn >= cols)
                continue;

            int neighborIdx = newRow * cols + newColumn;
            neighbors.push_back(neighborIdx);
        }
    }

    return neighbors;
}

bool Game::winCheck() const
{
    return revealedNumber == (rows*cols)-bombsNumber;
}
