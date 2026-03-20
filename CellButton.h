#ifndef CELLBUTTON_H
#define CELLBUTTON_H

#include <QMouseEvent>
#include <QPushButton>

class CellButton : public QPushButton
{
    Q_OBJECT

public:
    CellButton(int fila, int col, QWidget *parent = nullptr);
    ~CellButton() override;

signals:
    void clickIzquierdo(int fila, int col);
    void clickDerecho(int fila, int col);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    int fila;
    int col;
};

#endif // CELLBUTTON_H
