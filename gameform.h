#ifndef GAMEFORM_H
#define GAMEFORM_H

#include "Game.h"
#include "RankingManager.h"

#include <QDialog>
#include <QPushButton>
#include <QMouseEvent>
#include <QVector>
#include <QElapsedTimer>
#include <QCloseEvent>
#include <QTimer>


class CellButton : public QPushButton
{
    Q_OBJECT

public:
    CellButton(int fila, int col, QWidget *parent = nullptr);

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

class GameForm : public QDialog
{
    Q_OBJECT

public:
    explicit GameForm(QString nombre, Difficulty difficulty, QWidget *parent = nullptr);
    ~GameForm();

private slots:
    void alHacerClickIzquierdo(int fila, int col);
    void alHacerClickDerecho(int fila, int col);

private:
    Game game;
    Ui::GameForm *ui;
    QVector<QVector<CellButton*>> celdas;
    int filas;
    int columnas;

    bool modoTodos;

    int nivelActual;

    RankingManager rankingMng;
    QElapsedTimer timer;
    bool timerStarted;
    long long elapsedTimeMs;

    QTimer updateTimer;

    bool returningToWindow = false;

    QString username;

    void crearTablero(int filas, int columnas);

    void closeEvent(QCloseEvent *event) override;
};

#endif // GAMEFORM_H
