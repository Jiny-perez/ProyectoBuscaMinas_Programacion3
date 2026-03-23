#pragma once

#include <QWidget>

class QLabel;
class QPushButton;
class QTimer;
class QResizeEvent;

class CreditsForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreditsForm(QWidget *parent = nullptr);
    ~CreditsForm() override = default;

protected:
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

signals:
    void backRequested();

private:
    void configurarVentana();
    void configurarCreditos();
    void actualizarPosicionHorizontal();
    void reiniciarAnimacion();
    void moverCreditos();

    QTimer *timer;
    QLabel *labelCreditos;
    QPushButton *btnCerrar;
    int posY;
};
