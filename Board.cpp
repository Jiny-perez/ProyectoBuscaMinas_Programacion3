#include "Board.h"

Board::Board(int rows, int columns) : rows(rows), columns(columns)
{
    grid.assign(rows*columns, Cell{});
}

Board::~Board()
{
}

void Board::reset(Difficulty difficulty)
{
    grid.clear();
    switch(difficulty)
    {
    case Difficulty::BEGINNER:
        setRows(8);
        setColumns(8);
        break;

    case Difficulty::INTERMEDIATE:
        setRows(16);
        setColumns(16);
        break;

    case Difficulty::EXPERT:
        setRows(16);
        setColumns(30);
        break;

    default:
        setRows(0);
        setColumns(0);
        break;
    }

    grid.assign(getRows()*getColumns(), Cell{});
}

std::vector<int> Board::neighborsIdx(int idx) const
{
    if (!isIdxValid(idx))
        return {};

    std::vector<int> neighbors;
    neighbors.reserve(8);

    int rowIdx = idx / columns;
    int columnIdx = idx % columns;

    for (int dirRow = -1; dirRow <= 1; ++dirRow)
    {
        for (int dirColumn = -1; dirColumn <= 1; ++dirColumn)
        {

            if (dirRow == 0 && dirColumn == 0)
                continue;

            int newRow = rowIdx + dirRow;
            int newColumn = columnIdx + dirColumn;

            if (newRow < 0 || newRow >= rows || newColumn < 0 || newColumn >= columns)
                continue;

            int neighborIdx = newRow * columns + newColumn;
            neighbors.push_back(neighborIdx);
        }
    }

    return neighbors;
}

int Board::index(int row, int column) const{
    return (row * columns) + column;
}

int Board::getRows() const
{
    return rows;
}

int Board::getColumns() const
{
    return columns;
}

std::vector<Cell>& Board::getGrid()
{
    return grid;
}

Cell& Board::getCell(int idx)
{
    return grid[idx];
}

const Cell& Board::getCell(int idx) const
{
    return grid[idx];
}

bool Board::isIdxValid(int idx) const
{
    return idx >= 0 && idx < rows * columns;
}

void Board::setRows(int rows)
{
    this->rows = rows;
}

void Board::setColumns(int columns)
{
    this->columns = columns;
}
