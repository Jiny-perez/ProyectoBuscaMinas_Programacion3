#pragma once

#include <vector>
#include "Cell.h"
#include "Enums.h"

class Board
{
private:

    int columns;
    int rows;

    std::vector<Cell> grid;

public:

    Board(int rows, int columns);
    ~Board();

    void reset(Difficulty difficulty);

    int index(int row, int col) const;
    int getColumns() const;
    int getRows() const;

    std::vector<int> neighborsIdx(int idx) const;
    std::vector<Cell>& getGrid();

    Cell& getCell(int idx);
    const Cell& getCell(int idx) const;

    bool isIdxValid(int idx) const;

    void setRows(int rows);
    void setColumns(int columns);
};
