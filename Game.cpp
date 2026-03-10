#include "Game.h"

#include <cstdlib>

Game::Game() : rows(0), cols(0),
    minesNumber(0), revealedNumber(0),
    flagsPlaced(0), firstClick(true)
{
}

Game::Game(int rows, int cols, int minesNumber) :
    rows(rows), cols(cols), minesNumber(minesNumber), revealedNumber(0),
    flagsPlaced(0), firstClick(true), rndProvider(RandomProvider{})
{
    grid.assign(rows * cols, Cell{});
}

Game::Game(int rows, int cols, int minesNumber, const RandomProvider& rndProvider) :
    rows(rows), cols(cols), minesNumber(minesNumber),revealedNumber(0),
    flagsPlaced(0), firstClick(true), rndProvider(rndProvider)
{
    grid.assign(rows * cols, Cell{});
}

void Game::placeMines(int idx){

    if(minesNumber<=0){
        return;
    }

    int minesPlaced = 0;
    int size = rows * cols;

    while(minesPlaced < minesNumber){
        int mine = rndProvider.nextInt(0, size);

        if(mine == idx){
            continue;
        }

        if(grid[mine].isMine()){
            continue;
        }

        grid[mine].setHasMine(true);
        minesPlaced++;
    }

    firstClick = false;
}

int Game::minesAround(int idx) const {
    if(!isIdxValid(idx))
        return 0;

    if(grid[idx].isMine()){
        return 0;
    }

    int rowIdx = idx / cols;
    int columnIdx = idx % cols;

    int counterMinesAround=0;

    for(int dirRows = -1; dirRows <= 1; dirRows++){
        for(int dirCols = -1; dirCols <= 1; dirCols++){

            if(dirRows == 0 && dirCols == 0){
                continue;
            }

            int newRows = rowIdx + dirRows;
            int newCols = columnIdx + dirCols;

            if(newRows >= 0 && newRows < rows){
                if(newCols >= 0 && newCols < cols){

                    int mineIdx = newRows * cols + newCols;
                    if(grid[mineIdx].isMine()){
                        counterMinesAround++;
                    }

                }
            }
        }
    }
    return counterMinesAround;
}


int Game::index(int row, int column) const{
    return (row * cols) + column;
}

bool Game::toggleFlag(int idx){
    if(!isIdxValid(idx))
        return false;

    if(grid[idx].isRevealed()){
        return false;
    }

    if(grid[idx].isFlagged()){
        grid[idx].setFlagged(false);
        flagsPlaced--;
    }else{
        if(flagsPlaced >= minesNumber)
            return false;

        grid[idx].setFlagged(true);
        flagsPlaced++;
    }

    return true;
}

const Cell& Game::getCell(int idx) const
{
    return grid.at(idx);
}

Game::RevealResult Game::reveal(int idx)
{
    RevealResult revealResult{RevealOutcome::NA, {}};

    if (!isIdxValid(idx))
        return revealResult;

    if(firstClick)
    {
        placeMines(idx);

        for(int i = 0; i < rows * cols; i++)
        {
            int minesAround = minesAround(i);
            grid[i].setMinesAround(minesAround);
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
    if (!isIdxValid(idx))
        return;

    if (revealResult.outcome == RevealOutcome::BOMB)
        return;

    if(grid[idx].isFlagged())
        return;

    if(grid[idx].isRevealed())
        return;

    grid[idx].setRevealed(true);
    revealResult.changed.push_back(idx);

    if(grid[idx].isMine())
    {
        revealResult.outcome = RevealOutcome::BOMB;
        return;
    }

    revealResult.outcome = RevealOutcome::REVEALED;
    revealedNumber++;

    if(grid[idx].setMinesAround() > 0)
        return;

    for(int n : neighborsIdx(idx))
        revealRecursive(n, revealResult);
}

std::vector<int> Game::neighborsIdx(int idx) const
{
    if (!isIdxValid(idx))
        return {};

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
    return revealedNumber == (rows*cols)-minesNumber;
}

bool Game::isIdxValid(int idx) const
{
    return idx >= 0 && idx < rows * cols;
}
