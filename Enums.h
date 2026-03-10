#pragma once

//enum que guarda posibles resultados despues de presionar una casilla
enum class RevealOutcome {
    NA,       //Ya esta revelada o tiene bandera
    REVEALED, //No tiene minea
    BOMB,     //Tiene minea
    WON       //Gano
};

enum class Difficulty
{
    BEGINNER,
    INTERMEDIATE,
    EXPERT
};
