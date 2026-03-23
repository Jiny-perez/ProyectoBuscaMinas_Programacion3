#include "creditsform.h"

#include <QFont>
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>
#include <QResizeEvent>
#include <QShowEvent>
#include <QHideEvent>
#include <QTimer>

CreditsForm::CreditsForm(QWidget *parent)
    : QWidget(parent)
    , timer(new QTimer(this))
    , labelCreditos(new QLabel(this))
    , btnCerrar(new QPushButton("Cerrar", this))
    , posY(0)
{
    configurarVentana();
    configurarCreditos();

    connect(timer, &QTimer::timeout, this, &CreditsForm::moverCreditos);
    connect(btnCerrar, &QPushButton::clicked, this, &CreditsForm::backRequested);
}

void CreditsForm::configurarVentana()
{
    setObjectName("CreditsForm");
    setFixedSize(1140, 745);
    setStyleSheet(
        "QWidget#CreditsForm {"
        "    background-color: #000000;"
        "}"
        "QPushButton {"
        "    background-color: #1a1026;"
        "    color: #f5e9ff;"
        "    border: 2px solid #c084fc;"
        "    border-radius: 12px;"
        "    padding: 8px 18px;"
        "    font-weight: 700;"
        "}"
        "QPushButton:hover {"
        "    background-color: #241336;"
        "    border: 2px solid #e9d5ff;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #140b1d;"
        "}"
    );

    btnCerrar->setGeometry(505, 675, 130, 42);
}

void CreditsForm::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QRect outerRect = rect().adjusted(10, 10, -10, -10);
    QRect innerRect = rect().adjusted(16, 16, -16, -16);

    painter.setPen(QPen(QColor("#6b21a8"), 3));
    painter.drawRoundedRect(outerRect, 18, 18);

    painter.setPen(QPen(QColor("#c084fc"), 2));
    painter.drawRoundedRect(innerRect, 14, 14);
}

void CreditsForm::configurarCreditos()
{
    const QString texto =
        "BUSCAMINAS\n\n\n"
        "PROYECTO DESARROLLADO POR:\n\n"
        "JOSE OMAR GARCÍA PINEDA\n\n"
        "LUIS FERNANDO NORIEGA MEJÍA\n\n"
        "JINY MARYEIRI PÉREZ REYES\n\n\n"
        "ASIGNATURA:\n\n"
        "PROGRAMACIÓN III\n\n"
        "SECCIÓN 467 - 2026Q1\n\n\n"
        "DOCENTE:\n\n"
        "PAUL ENRIQUE IDIAQUEZ GONZÁLEZ\n\n\n"
        "AGRADECIMIENTOS:\n\n"
        "PAUL ENRIQUE IDIAQUEZ GONZÁLEZ\n\n"
        "JAFETH RAUL HERNÁNDEZ CANIZALES\n\n"
        "DAVID JOSEPH CÁRCAMO CEDILLO\n\n"
        "ALEX FERNANDO SANTOS CERRATO\n\n"
        "EDWIN GABRIEL PORTILLO GARCÍA\n\n"
        "NADIESDA YAILIN FUENTES HERNÁNDEZ\n\n"
        "MERARI MARCELA DUBÓN LOPEZ\n\n"
        "WERNER JOHANNES BODE MALONE\n\n"
        "SALVADOR ENMANUEL CANTARERO MEZA\n\n"
        "NELSON ADALBERTO AGUILAR PINEDA\n\n"
        "ESTEBAN FABRICIO FERNÁNDEZ SÁNCHEZ\n\n"
        "NAJMAH KARYME ZABLAH\n\n\n"
        "UNITEC\n\n"
        "23 DE MARZO DE 2026";


    labelCreditos->setText(texto);
    labelCreditos->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    labelCreditos->setWordWrap(true);
    labelCreditos->setStyleSheet(
        "QLabel {"
        "    color: #c084fc;"
        "    background: transparent;"
        "}"
    );

    QFont fuente("Arial", 18, QFont::Bold);
    fuente.setLetterSpacing(QFont::AbsoluteSpacing, 1.5);
    labelCreditos->setFont(fuente);

    labelCreditos->setFixedWidth(width() - 120);
    labelCreditos->adjustSize();
    reiniciarAnimacion();
    labelCreditos->show();
}

void CreditsForm::actualizarPosicionHorizontal()
{
    const int x = (width() - labelCreditos->width()) / 2;
    labelCreditos->move(x, posY);
}

void CreditsForm::moverCreditos()
{
    posY -= 2;
    actualizarPosicionHorizontal();

    if (posY + labelCreditos->height() < 0) {
        posY = height();
        actualizarPosicionHorizontal();
    }
}

void CreditsForm::reiniciarAnimacion()
{
    posY = height();
    actualizarPosicionHorizontal();
}

void CreditsForm::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    reiniciarAnimacion();
    timer->start(30);
}

void CreditsForm::hideEvent(QHideEvent *event)
{
    timer->stop();
    QWidget::hideEvent(event);
}

void CreditsForm::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    labelCreditos->setFixedWidth(width() - 120);
    labelCreditos->adjustSize();
    if (!isVisible()) {
        reiniciarAnimacion();
    } else {
        actualizarPosicionHorizontal();
    }

    btnCerrar->setGeometry((width() - 130) / 2, height() - 70, 130, 42);
}
