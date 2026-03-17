#pragma once

#include "Enums.h"

#include <QString>

struct ScoreEntry
{
    QString username;

    Difficulty difficulty;

    long long timeMs;
};
