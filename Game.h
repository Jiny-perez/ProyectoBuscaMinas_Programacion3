#pragma once

#include "Cell.h"

#include <vector>

class Game
{

public:
    //enum que guarda posibles resultados despues de presionar una casilla
    enum class RevealOutcome {
        NA,       //Ya esta revelada o tiene bandera
        REVEALED, //No tiene bomba
        MINE,     //Tiene bomba
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

    //Cantidad de bombas inicialles (ej: para 8x8 = 10)
    int bombsNumber;
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

    //Para asegurarse que el primer click no sea sobre una bomba
    bool bombsPlaced;

public:
    Game();
    Game(int rows, int cols, int bombsNumber);

    void init();
    void placeBombs(int idx);

    int bombsAround(int idx)const;
    int index(int r, int c) const;

    bool toggleFlag(int idx);
    bool hasBomb(int idx)const;

    RevealResult reveal(int idx);
    const Cell& getCell(int idx);

    int getRows() const;
    int getCols() const;
    int getBombsNumber() const;
    int getFlagsPlaced() const;
    int getFlagsRemaining() const;
};
