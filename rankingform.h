#pragma once

#include <QDialog>
#include <QString>
#include <QWidget>
#include <QtTypes>
#include <vector>

#include "Enums.h"
#include "ScoreEntry.h"

class RankingForm : public QDialog
{
    Q_OBJECT

public:
    explicit RankingForm(QWidget *parent = nullptr);
    ~RankingForm() override;

private:
    QString difficultyToText(Difficulty difficulty) const;
    QString formatTime(qint64 timeMs) const;
    QWidget *buildRankingTable(const std::vector<ScoreEntry> &scores, QWidget *parent);
    void setupUi();
};
