#ifndef GAMEFORM_H
#define GAMEFORM_H

#include "Game.h"
#include "RankingManager.h"

#include <QElapsedTimer>
#include <QMouseEvent>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <QTimer>
#include <QVector>
#include <QWidget>
#include <QtTypes>
#include <memory>

class CellButton : public QPushButton
{
    Q_OBJECT

public:
    CellButton(int fila, int col, QWidget *parent = nullptr);
    ~CellButton() override;

    int fila;
    int col;

signals:
    void clickIzquierdo(int fila, int col);
    void clickDerecho(int fila, int col);

protected:
    void mousePressEvent(QMouseEvent *event) override;
};

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
    QVector<QVector<CellButton*>> celdas;
    int filas;
    int columnas;
    RankingManager rankingMng;
    QElapsedTimer timer;
    bool timerStarted;
    qint64 elapsedTimeMs;
    QTimer updateTimer;
    QString username;
    QGridLayout *boardLayout;

    void crearTablero(int filas, int columnas);
    void limpiarTablero();
    void resetVisualGrid();
    void resetCell(CellButton *celda);
    void applyCellState(CellButton *celda, const char *state);
};

#endif // GAMEFORM_H
