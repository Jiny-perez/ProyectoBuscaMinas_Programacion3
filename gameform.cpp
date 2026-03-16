#include "gameform.h"
#include "ui_gameform.h"

#include <QGridLayout>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QFont>

// ── Botón de cada celda ──────────────────────
CellButton::CellButton(int fila, int col, QWidget *parent)
    : QPushButton(parent), fila(fila), col(col)
{
}

void CellButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        emit clickIzquierdo(fila, col);
    else if (event->button() == Qt::RightButton)
        emit clickDerecho(fila, col);
}

// ── GameForm ─────────────────────────────────
GameForm::GameForm(QString nombre, Difficulty difficulty, QWidget *parent)
    : QDialog(parent), ui(new Ui::GameForm),
    game(difficulty)
{
    ui->setupUi(this);

    game.start(difficulty);

    filas = game.getBoard().getRows();
    columnas = game.getBoard().getColumns();

    ui->label->setText("Buscaminas " + QString::number(filas) + "x" + QString::number(columnas));
    ui->label_2->setText("Jugador: " + nombre);

    QString difficultyText;

    switch(difficulty){
    case Difficulty::BEGINNER:
        difficultyText = "Beginner";
        break;

    case Difficulty::INTERMEDIATE:
        difficultyText = "Intermediate";
        break;

    case Difficulty::EXPERT:
        difficultyText = "Expert";
        break;
    }

    ui->label_3->setText("Nivel: " + difficultyText );

    crearTablero(filas, columnas);
}

GameForm::~GameForm()
{
    delete ui;
}

// ── Crear tablero ────────────────────────────
void GameForm::crearTablero(int filas, int columnas)
{
    if (ui->widget->layout() != nullptr)
        delete ui->widget->layout();

    QGridLayout *grid = new QGridLayout();
    grid->setSpacing(2);
    grid->setAlignment(Qt::AlignCenter);
    ui->widget->setLayout(grid);

    celdas.clear();
    celdas.resize(filas);

    int tamCelda;

    if (columnas == 32)
        tamCelda = 22;
    else if (columnas == 16)
        tamCelda = 30;
    else
        tamCelda = 40;

    for (int i = 0; i < filas; i++) {
        celdas[i].resize(columnas);

        for (int j = 0; j < columnas; j++) {
            CellButton *celda = new CellButton(i, j, ui->widget);

            celda->setFixedSize(tamCelda, tamCelda);
            celda->setFont(QFont("Segoe UI Emoji", tamCelda / 2));

            celda->setStyleSheet(
                "QPushButton {"
                " background: #2e3250;"
                " border: 1px solid #4a5080;"
                " border-radius: 4px;"
                "}"
                "QPushButton:hover {"
                " background: #3d4470;"
                " border: 1px solid #7ec8e3;"
                "}"
                );

            connect(celda, &CellButton::clickIzquierdo,
                    this, &GameForm::alHacerClickIzquierdo);

            connect(celda, &CellButton::clickDerecho,
                    this, &GameForm::alHacerClickDerecho);

            grid->addWidget(celda, i, j);
            celdas[i][j] = celda;
        }
    }

    adjustSize();
}

// ── Click izquierdo ──────────────────────────
void GameForm::alHacerClickIzquierdo(int fila, int col)
{
    int columnas = game.getBoard().getColumns();
    int idx = fila * columnas + col;
    CellButton* celda = celdas[fila][col];

    if (!celda->isEnabled())
        return;

    //Colocar minas despues del primer click
    if (game.isfirstClick()) {
        game.placeMines(idx);
    }

    // Revelar la celda
    Game::RevealResult result = game.reveal(idx);

    // Actualizar todas las celdas reveladas
    for (int changedIdx : result.changed) {
        int f = changedIdx / columnas;
        int c = changedIdx % columnas;
        CellButton* btn = celdas[f][c];
        const auto& cell = game.getBoard().getCell(changedIdx);

        if (cell.isMine()) {
            btn->setText("💣");
            btn->setStyleSheet(
                "QPushButton { background: #5c0a0a; border: 1px solid #ff4444; border-radius: 4px; }"
                );
        } else {
            int minasAlrededor = cell.getMinesAround();
            btn->setText(minasAlrededor > 0 ? QString::number(minasAlrededor) : "");
            btn->setStyleSheet(
                "QPushButton { background: #0a3a1a; border: 1px solid #44cc77; border-radius: 4px; }"
                );
        }
        btn->setEnabled(false);
    }

    // Fin del juego
    if (result.outcome == RevealOutcome::BOMB) {
        QMessageBox::information(this, "Fin del juego", "Perdiste");
        if (parentWidget()) parentWidget()->show();
        this->close();
    } else if (result.outcome == RevealOutcome::WON) {
        QMessageBox::information(this, "Victoria", "Ganaste");
        if (parentWidget()) parentWidget()->show();
        this->close();
    }
}

// ── Click derecho ────────────────────────────
void GameForm::alHacerClickDerecho(int fila, int col)
{
    CellButton *celda = celdas[fila][col];

    if (!celda->isEnabled())
        return;

    if (celda->text().isEmpty())
        celda->setText("🚩");
    else
        celda->setText("");
}
