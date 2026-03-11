#include "Game.h"

#include <cstdlib>

Game::Game(Difficulty difficulty) : revealedNumber(0),flagsPlaced(0),
    firstClick(true), rndProvider(RandomProvider{}), board ({0,0})
{
    start(difficulty);
}

Game::Game(Difficulty difficulty, const RandomProvider& rndProvider) :
    revealedNumber(0), flagsPlaced(0), firstClick(true),
    rndProvider(rndProvider), board({0,0})
{
    start(difficulty);
}

void Game::start(Difficulty difficulty)
{
    board.reset(difficulty);

    this->difficulty = difficulty;
    revealedNumber = 0;
    flagsPlaced = 0;

    firstClick = true;

    switch(difficulty)
    {
    case Difficulty::BEGINNER: minesNumber = 10; break;
    case Difficulty::INTERMEDIATE: minesNumber = 40; break;
    case Difficulty::EXPERT: minesNumber = 99; break;
    }
}

void Game::placeMines(int idx){
    if(minesNumber <= 0){
        firstClick = false;
        return;
    }

    int minesPlaced = 0;
    int size = board.getRows() * board.getColumns();

    if(minesNumber > size - 1){
        minesNumber = size - 1;
    }

    while(minesPlaced < minesNumber){
        int mine = rndProvider.nextInt(0, size - 1);

        if(mine == idx){
            continue;
        }

        if(board.getCell(mine).isMine()){
            continue;
        }

        board.getCell(mine).setHasMine(true);
        minesPlaced++;
    }

    firstClick = false;
}

bool Game::toggleFlag(int idx){
    if(!board.isIdxValid(idx))
        return false;

    if(board.getCell(idx).isRevealed()){
        return false;
    }

    if(board.getCell(idx).isFlagged()){
        board.getCell(idx).setFlagged(false);
        flagsPlaced--;
    }else{
        if(flagsPlaced >= minesNumber)
            return false;

        board.getCell(idx).setFlagged(true);
        flagsPlaced++;
    }

    return true;
}

Game::RevealResult Game::reveal(int idx)
{
    RevealResult revealResult{RevealOutcome::NA, {}};

    if (!board.isIdxValid(idx))
        return revealResult;

    if(firstClick)
    {
        placeMines(idx);

        for(int i = 0; i < board.getRows() * board.getColumns(); i++)
        {
            int minesAround = board.minesAround(i);
            board.getCell(i).setMinesAround(minesAround);
        }
    }

    if(board.getCell(idx).isFlagged() || board.getCell(idx).isRevealed())
        return revealResult;

    revealRecursive(idx, revealResult);

    if(revealResult.outcome != RevealOutcome::BOMB && winCheck())
        revealResult.outcome = RevealOutcome::WON;

    return revealResult;
}

void Game::revealRecursive(int idx, RevealResult& revealResult)
{
    if (!board.isIdxValid(idx))
        return;

    if (revealResult.outcome == RevealOutcome::BOMB)
        return;

    if(board.getCell(idx).isFlagged())
        return;

    if(board.getCell(idx).isRevealed())
        return;

    board.getCell(idx).setRevealed(true);
    revealResult.changed.push_back(idx);

    if(board.getCell(idx).isMine())
    {
        revealResult.outcome = RevealOutcome::BOMB;
        return;
    }

    revealResult.outcome = RevealOutcome::REVEALED;
    revealedNumber++;

    if(board.getCell(idx).getMinesAround() > 0)
        return;

    for(int n : board.neighborsIdx(idx))
        revealRecursive(n, revealResult);
}

bool Game::winCheck() const
{
    return revealedNumber == (board.getRows()*board.getColumns())-minesNumber;
}

//GETTERS

Difficulty Game::getDifficulty() const
{
    return difficulty;
}

int Game::getMinesNumber() const{
    return minesNumber;
}

int Game::getFlagsPlaced() const{
    return flagsPlaced;
}
