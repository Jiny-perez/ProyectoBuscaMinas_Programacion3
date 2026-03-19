#pragma once

#include "Enums.h"

#include <QString>

struct ScoreEntry
{
    QString username;

    Difficulty difficulty;

    qint64 timeMs;

    ~ScoreEntry();
};
