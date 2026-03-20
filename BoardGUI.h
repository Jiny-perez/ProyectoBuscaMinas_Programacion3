#pragma once

#include "CellButton.h"

#include <QGridLayout>
#include <QVector>
#include <QWidget>

class BoardGUI : public QWidget
{
    Q_OBJECT

public:
    explicit BoardGUI(QWidget *parent = nullptr);
    ~BoardGUI() override;

    void setupBoard(int filas, int columnas);
    void resetBoard();
    bool isCellEnabled(int fila, int col) const;
    void showRevealedCell(int fila, int col, int minasAlrededor, bool isMine);
    void showFlaggedCell(int fila, int col, bool flagged);

signals:
    void leftCellClicked(int fila, int col);
    void rightCellClicked(int fila, int col);

private:
    QVector<QVector<CellButton*>> celdas;
    QGridLayout *boardLayout;

    void clearBoard();
    void resetCell(CellButton *celda);
    void applyCellState(CellButton *celda, const char *state);
    int cellSizeForColumns(int columnas) const;
};
