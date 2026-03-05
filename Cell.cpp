#include "Cell.h"

Cell::Cell()
{
    x = 0; y = 0;
    bombsAround = 0;
    hasBomb = false;
    revealed = false;
    flagged = false;
}
Cell::Cell(int x, int y)
{
    this->x = x;
    this->y = y;
    bombsAround = 0;
    hasBomb = false;
    revealed = false;
    flagged = false;
}


int Cell::getX() const
{
    return x;
}
int Cell::getY() const
{
    return y;
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


void Cell::setX(int x)
{
    this->x = x;
}
void Cell::setY(int y)
{
    this->y = y;
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
