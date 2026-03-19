#include "RankingManager.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

RankingManager::RankingManager(): filePath("ranking.json")
{

}

RankingManager::~RankingManager()
{
}

void RankingManager::saveScore(const ScoreEntry &score)
{
    std::vector<ScoreEntry> scores = loadScores();

    scores.push_back(score);

    QJsonArray jsonArray;

    for(const ScoreEntry& thisScore : scores)
    {
        QJsonObject jsonObject;

        jsonObject["username"] = thisScore.username;
        jsonObject["difficulty"] = static_cast<int>(thisScore.difficulty);
        jsonObject["timeMs"] = thisScore.timeMs;

        jsonArray.append(jsonObject);
    }

    QJsonDocument document(jsonArray);

    QFile file(getPath());

    if(!file.open(QIODevice::WriteOnly))
        return;

    file.write(document.toJson());
    file.close();
}

std::vector<ScoreEntry> RankingManager::loadScores() const
{
    std::vector<ScoreEntry> scores;

    QFile file(getPath());

    if(!file.open(QIODevice::ReadOnly))
        return scores;

    QByteArray allScores = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(allScores);

    if(!document.isArray())
        return scores;

    QJsonArray jsonArray = document.array();

    for(int i = 0; i < jsonArray.size(); i++)
    {
        QJsonObject jsonObject = jsonArray[i].toObject();

        ScoreEntry score;

        score.username = jsonObject["username"].toString();
        score.difficulty = static_cast<Difficulty>(jsonObject["difficulty"].toInt());
        score.timeMs = jsonObject["timeMs"].toInt();

        scores.push_back(score);
    }

    return scores;
}

std::vector<ScoreEntry> RankingManager::loadScoresDifficulty(Difficulty difficulty) const
{
    std::vector<ScoreEntry> scores;

    QFile file(getPath());

    if(!file.open(QIODevice::ReadOnly))
        return scores;

    QByteArray allScores = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(allScores);

    if(!document.isArray())
        return scores;

    QJsonArray jsonArray = document.array();

    for(int i = 0; i < jsonArray.size(); i++)
    {
        QJsonObject jsonObject = jsonArray[i].toObject();

        ScoreEntry score;

        score.username = jsonObject["username"].toString();
        score.difficulty = static_cast<Difficulty>(jsonObject["difficulty"].toInt());
        score.timeMs = jsonObject["timeMs"].toInt();

        if(score.difficulty != difficulty)
            continue;

        scores.push_back(score);
    }

    return scores;
}

QString RankingManager::getPath() const
{
    return filePath;
}
