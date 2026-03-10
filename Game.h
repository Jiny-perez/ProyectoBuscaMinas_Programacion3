#pragma once

#include "Cell.h"
#include "RandomProvider.h"
#include "Enums.h"

#include <vector>

class Game
{

public:
    struct RevealResult {
        RevealOutcome outcome;
        //Vector que guarda indices revelados en un click
        //para que luego el GUI itere sobre el y repinte solo esos
        std::vector<int> changed;
    };

private:
    Difficulty difficulty;

    RandomProvider rndProvider;

    //Tamanio del tablero
    int rows, cols;

    //Cantidad de mineas inicialles (ej: grid 8x8 = 10)
    int minesNumber;
    //Numero de casillas reveladas (ya sea por click de usuario o por expansion)
    int revealedNumber;

    //Banderas puestas
    int flagsPlaced;

    /*
    ====================================================================================================
    IMPORTANTE: el tablero (matriz) se representara con un vector de tamanio rows*cols
    situandose en posiciones continuas de memoria.

    Se calculara el indice correcto utilizando las posiciones x,y desde la GUI con el siguiente proceso:
    idx = r * cols + c

    ej:
    r = 2 ; cols = 8 ; c = 3
    idx = 2*8+3 = [19]
    ====================================================================================================
    */
    std::vector<Cell> grid;

    //Para asegurarse que el primer click no sea sobre una minea
    bool firstClick;

public:
    Game(Difficulty difficulty);
    Game(Difficulty difficulty, const RandomProvider& rndProvider);

    void start(Difficulty difficulty);
    void placeMines(int idx);

    int minesAround(int idx) const;
    int index(int r, int c) const;

    bool toggleFlag(int idx);
    bool winCheck() const;
    bool isIdxValid(int idx) const;

    RevealResult reveal(int idx);
    void revealRecursive(int idx, RevealResult& revealResult);
    const Cell& getCell(int idx) const;

    std::vector<int> neighborsIdx(int idx) const;

    Difficulty getDifficulty() const;
    int getRows() const;
    int getCols() const;
    int getMinesNumber() const;
    int getFlagsPlaced() const;
    int getFlagsRemaining() const;
};
