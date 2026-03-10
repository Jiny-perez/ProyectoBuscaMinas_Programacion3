#pragma once

#include "Cell.h"

#include <vector>

class Game
{

public:
    //enum que guarda posibles resultados despues de presionar una casilla
    enum class RevealOutcome {
        NA,       //Ya esta revelada o tiene bandera
        REVEALED, //No tiene minea
        BOMB,     //Tiene minea
        WON       //Gano
    };

    struct RevealResult {
        RevealOutcome outcome;
        //Vector que guarda indices revelados en un click
        //para que luego el GUI itere sobre el y repinte solo esos
        std::vector<int> changed;
    };

private:
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
    Game();
    Game(int rows, int cols, int minesNumber);

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

    int getRows() const;
    int getCols() const;
    int getMinesNumber() const;
    int getFlagsPlaced() const;
    int getFlagsRemaining() const;
};
