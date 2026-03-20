#include "CellButton.h"

CellButton::CellButton(int fila, int col, QWidget *parent)
    : QPushButton(parent)
    , fila(fila)
    , col(col)
{
}

CellButton::~CellButton()
{
}

void CellButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clickIzquierdo(fila, col);
        event->accept();
        return;
    }

    if (event->button() == Qt::RightButton) {
        emit clickDerecho(fila, col);
        event->accept();
        return;
    }

    QPushButton::mousePressEvent(event);
}
