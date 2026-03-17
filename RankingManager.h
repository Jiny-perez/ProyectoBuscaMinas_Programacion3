#pragma once

#include "Enums.h"
#include "ScoreEntry.h"

#include <QString>
#include <vector>

class RankingManager
{

private:
    QString filePath;

public:
    RankingManager();

    void saveScore(const ScoreEntry& score);

    std::vector<ScoreEntry> loadScores() const;
    std::vector<ScoreEntry> loadScoresDifficulty(Difficulty difficulty) const;

    QString getPath() const;
};
