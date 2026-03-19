#pragma once

#include "Cell.h"
#include "RandomProvider.h"
#include "Enums.h"
#include "Board.h"

#include <vector>

class Game
{

public:
    struct RevealResult {
        RevealOutcome outcome;
        //Vector que guarda indices revelados en un click
        //para que luego el GUI itere sobre el y repinte solo esos
        std::vector<int> changed;

        ~RevealResult();
    };

private:
    Board board;

    Difficulty difficulty;

    RandomProvider rndProvider;

    //Cantidad de mineas inicialles (ej: grid 8x8 = 10)
    int minesNumber;
    //Numero de casillas reveladas (ya sea por click de usuario o por expansion)
    int revealedNumber;

    //Banderas puestas
    int flagsPlaced;

    //Para asegurarse que el primer click no sea sobre una minea
    bool firstClick;

    std::vector<int> minesPositions;

public:
    Game(Difficulty difficulty);
    Game(Difficulty difficulty, const RandomProvider& rndProvider);
    ~Game();

    void start(Difficulty difficulty);   
    void placeMines(int idx);

    bool toggleFlag(int idx);
    bool winCheck() const;

    RevealResult reveal(int idx);
    void revealRecursive(int idx, RevealResult& revealResult);

    Difficulty getDifficulty() const;
    int getMinesNumber() const;
    int getFlagsPlaced() const;

    bool isfirstClick() const;
    bool isCellFlagged(int idx) const;

    Board &getBoard();
    const Board& getBoard() const;

};
