#include "Cell.h"

Cell::Cell() :
    minesAround(0), hasMine(false),
    revealed(false), flagged(false)
{
}


int Cell::getMinesAround() const
{
    return minesAround;
}
bool Cell::isMine() const
{
    return hasMine;
}
bool Cell::isRevealed() const
{
    return revealed;
}
bool Cell::isFlagged() const
{
    return flagged;
}


void Cell::setMinesAround(int minesAround)
{
    this->minesAround = minesAround;
}
void Cell::setHasMine(bool hasMine)
{
    this->hasMine = hasMine;
}
void Cell::setRevealed(bool revealed)
{
    this->revealed = revealed;
}
void Cell::setFlagged(bool flagged)
{
    this->flagged = flagged;
}
