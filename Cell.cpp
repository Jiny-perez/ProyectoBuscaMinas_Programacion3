#include "Cell.h"

Cell::Cell(int x, int y)
{
    this->x = x;
    this->y = y;
    bombsAround = 0;
    hasBomb = false;
    revealed = false;
    flagged = false;
}
