#pragma once

class Cell
{
private:
    int minesAround;

    bool hasMine;
    bool revealed;
    bool flagged;

public:
    Cell();

    //GETTERS
    int setMinesAround() const;

    bool isMine() const;
    bool isRevealed() const;
    bool isFlagged() const;

    //SETTERS
    void setMinesAround(int minesAround);

    void setHasMine(bool hasMine);
    void setRevealed(bool revealed);
    void setFlagged(bool flagged);
};
