#include "Cell.h"

Cell::Cell()
{
    bombsAround = 0;
    hasBomb = false;
    revealed = false;
    flagged = false;
}


int Cell::getBombsAround() const
{
    return bombsAround;
}
bool Cell::isBomb() const
{
    return hasBomb;
}
bool Cell::isRevealed() const
{
    return revealed;
}
bool Cell::isFlagged() const
{
    return flagged;
}


void Cell::setBombsAround(int bombsAround)
{
    this->bombsAround = bombsAround;
}
void Cell::setHasBomb(bool hasBomb)
{
    this->hasBomb = hasBomb;
}
void Cell::setRevealed(bool revealed)
{
    this->revealed = revealed;
}
void Cell::setFlagged(bool flagged)
{
    this->flagged = flagged;
}
