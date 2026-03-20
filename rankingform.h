#pragma once

#include <QString>
#include <QWidget>
#include <QtTypes>
#include <vector>

#include "Enums.h"
#include "ScoreEntry.h"

class QLabel;
class QPushButton;
class QTabWidget;

class RankingForm : public QWidget
{
    Q_OBJECT

public:
    explicit RankingForm(QWidget *parent = nullptr);
    ~RankingForm() override;

    void refreshScores();

signals:
    void backRequested();

private:
    QString difficultyToText(Difficulty difficulty) const;
    QString formatTime(qint64 timeMs) const;
    QWidget *buildRankingTable(const std::vector<ScoreEntry> &scores, QWidget *parent);
    void setupUi();

    QLabel *totalScoresLabel;
    QTabWidget *tabs;
    QPushButton *closeButton;
};
