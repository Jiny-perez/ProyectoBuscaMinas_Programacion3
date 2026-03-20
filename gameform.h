#ifndef GAMEFORM_H
#define GAMEFORM_H

#include "BoardGUI.h"
#include "Game.h"
#include "RankingManager.h"

#include <QElapsedTimer>
#include <QString>
#include <QTimer>
#include <QWidget>
#include <memory>

namespace Ui {
class GameForm;
}

class GameForm : public QWidget
{
    Q_OBJECT

public:
    explicit GameForm(QWidget *parent = nullptr);
    ~GameForm();

    void startGame(const QString &nombre, Difficulty difficulty);

signals:
    void backRequested();

private slots:
    void alHacerClickIzquierdo(int fila, int col);
    void alHacerClickDerecho(int fila, int col);
    void goBack();
    void restart();

private:
    std::unique_ptr<Game> game;
    Ui::GameForm *ui;
    BoardGUI *boardGui;
    RankingManager rankingMng;
    QElapsedTimer timer;
    bool timerStarted;
    qint64 elapsedTimeMs;
    QTimer updateTimer;
    QString username;

    void uptadeFlagsCounter() const;
};

#endif // GAMEFORM_H
