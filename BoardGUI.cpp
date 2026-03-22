#include "BoardGUI.h"

#include <QFont>
#include <QStyle>

namespace {
const char *hiddenCellState = "hidden";
const char *revealedCellState = "revealed";
const char *mineCellState = "mine";

const char *cellStyles =
    "QPushButton[cellState=\"hidden\"] {"
    " background: #2e3250;"
    " border: 1px solid #4a5080;"
    " border-radius: 4px;"
    "}"
    "QPushButton[cellState=\"hidden\"]:hover {"
    " background: #3d4470;"
    " border: 1px solid #7ec8e3;"
    "}"
    "QPushButton[cellState=\"revealed\"] {"
    " background: #182033;"
    " border: 1px solid #7b8db8;"
    " border-radius: 4px;"
    " color: #dbeafe;"
    " font-weight: 700;"
    "}"
    "QPushButton[cellState=\"revealed\"][dangerLevel=\"1\"] {"
    " border-radius: 4px;"
    " color: #60A5FA;"
    "}"
    "QPushButton[cellState=\"revealed\"][dangerLevel=\"2\"] {"
    " border-radius: 4px;"
    " color: #3B82F6;"
    "}"
    "QPushButton[cellState=\"revealed\"][dangerLevel=\"3\"] {"
    " border-radius: 4px;"
    " color: #6366F1;"
    "}"
    "QPushButton[cellState=\"revealed\"][dangerLevel=\"4\"] {"
    " border-radius: 4px;"
    " color: #8B5CF6;"
    "}"
    "QPushButton[cellState=\"revealed\"][dangerLevel=\"5\"] {"
    " border-radius: 4px;"
    " color: #A855F7;"
    "}"
    "QPushButton[cellState=\"revealed\"][dangerLevel=\"6\"] {"
    " border-radius: 4px;"
    " color: #A855F7;"
    "}"
    "QPushButton[cellState=\"revealed\"][dangerLevel=\"7\"] {"
    " border-radius: 4px;"
    " color: #A855F7;"
    "}"
    "QPushButton[cellState=\"revealed\"][dangerLevel=\"8\"] {"
    " border-radius: 4px;"
    " color: #A855F7;"
    "}"
    "QPushButton[cellState=\"mine\"] {"
    " background: #5c0a0a;"
    " border: 1px solid #ff4444;"
    " border-radius: 4px;"
    "}";
}

BoardGUI::BoardGUI(QWidget *parent)
    : QWidget(parent)
    , boardLayout(new QGridLayout(this))
{
    setStyleSheet(cellStyles);
    boardLayout->setSpacing(2);
    boardLayout->setAlignment(Qt::AlignCenter);
    boardLayout->setContentsMargins(0, 0, 0, 0);
}

BoardGUI::~BoardGUI()
{
    clearBoard();
}

void BoardGUI::setupBoard(int filas, int columnas)
{
    const int tamCelda = cellSizeForColumns(columnas);
    const bool sameBoardSize = !celdas.isEmpty()
        && celdas.size() == filas
        && celdas[0].size() == columnas;

    if (!sameBoardSize) {
        clearBoard();
        celdas.resize(filas);

        for (int i = 0; i < filas; ++i) {
            celdas[i].resize(columnas);

            for (int j = 0; j < columnas; ++j) {
                CellButton *celda = new CellButton(i, j, this);
                connect(celda, &CellButton::clickIzquierdo, this, &BoardGUI::leftCellClicked);
                connect(celda, &CellButton::clickDerecho, this, &BoardGUI::rightCellClicked);
                boardLayout->addWidget(celda, i, j);
                celdas[i][j] = celda;
            }
        }
    }

    for (int i = 0; i < celdas.size(); ++i) {
        for (int j = 0; j < celdas[i].size(); ++j) {
            CellButton *celda = celdas[i][j];
            celda->setFixedSize(tamCelda, tamCelda);
            celda->setFont(QFont("Segoe UI Emoji", tamCelda / 2));
            resetCell(celda);
        }
    }
}

void BoardGUI::resetBoard()
{
    for (int i = 0; i < celdas.size(); ++i) {
        for (int j = 0; j < celdas[i].size(); ++j) {
            resetCell(celdas[i][j]);
        }
    }
}

bool BoardGUI::isCellEnabled(int fila, int col) const
{
    return celdas[fila][col]->isEnabled();
}

void BoardGUI::showRevealedCell(int fila, int col, int minasAlrededor, bool isMine)
{
    CellButton *btn = celdas[fila][col];

    if (isMine) {
        btn->setText("💣");
        applyCellState(btn, mineCellState);
    } else {
        btn->setText(minasAlrededor > 0 ? QString::number(minasAlrededor) : "");
        btn->setProperty("dangerLevel", minasAlrededor);
        applyCellState(btn, revealedCellState);
    }

    btn->setEnabled(false);
}

void BoardGUI::showFlaggedCell(int fila, int col, bool flagged)
{
    CellButton *celda = celdas[fila][col];
    celda->setText(flagged ? "🚩" : "");
}

void BoardGUI::clearBoard()
{
    while (QLayoutItem *item = boardLayout->takeAt(0)) {
        if (QWidget *widget = item->widget()) {
            delete widget;
        }
        delete item;
    }

    celdas.clear();
}

void BoardGUI::resetCell(CellButton *celda)
{
    celda->setEnabled(true);
    celda->setText("");
    celda->setProperty("dangerLevel", 0);
    applyCellState(celda, hiddenCellState);
}

void BoardGUI::applyCellState(CellButton *celda, const char *state)
{
    if (celda->property("cellState").toString() == state) {
        return;
    }

    celda->setProperty("cellState", state);
    celda->style()->unpolish(celda);
    celda->style()->polish(celda);
    celda->update();
}

int BoardGUI::cellSizeForColumns(int columnas) const
{
    if (columnas == 30) {
        return 28;
    }

    if (columnas == 16) {
        return 30;
    }

    return 50;
}
