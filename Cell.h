#pragma once

class Cell
{
private:
    int x, y;
    int bombsAround;

    bool hasBomb;
    bool revealed;
    bool flagged;

public:
    Cell();
    Cell(int x, int y);

    //GETTERS
    int getX() const;
    int getY() const;
    int getBombsAround() const;

    bool isBomb() const;
    bool isRevealed() const;
    bool isFlagged() const;

    //SETTERS
    void setX(int x);
    void setY(int y);
    void setBombsAround(int bombsAround);

    void setHasBomb(bool hasBomb);
    void setRevealed(bool revealed);
    void setFlagged(bool flagged);
};
