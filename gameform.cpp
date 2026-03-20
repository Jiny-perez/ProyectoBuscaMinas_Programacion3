#include "gameform.h"
#include "ui_gameform.h"

#include <QFont>
#include <QGridLayout>
#include <QLayoutItem>
#include <QMessageBox>

#include <iostream>

CellButton::CellButton(int fila, int col, QWidget *parent)
    : QPushButton(parent), fila(fila), col(col)
{
}

CellButton::~CellButton()
{
}

void CellButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clickIzquierdo(fila, col);
    } else if (event->button() == Qt::RightButton) {
        emit clickDerecho(fila, col);
    }

    QPushButton::mousePressEvent(event);
}

GameForm::GameForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameForm)
    , filas(0)
    , columnas(0)
    , timerStarted(false)
    , elapsedTimeMs(0)
{
    ui->setupUi(this);
    setFixedSize(1140, 745);
    setAttribute(Qt::WA_StyledBackground, true);

    setStyleSheet(
        "QWidget#GameForm {"
        "    background-color: #08111f;"
        "}"
        "QWidget#boardContainer {"
        "    background-color: transparent;"
        "}"
        );

    ui->boardTitleLabel->setGeometry(90, 18, 450, 46);
    ui->timerLabel->setGeometry(800, 18, 170, 46);

    ui->boardContainer->setGeometry(90, 74, 900, 590);

    ui->playerNameLabel->setGeometry(90, 684, 245, 38);
    ui->difficultyLabel->setGeometry(355, 684, 205, 38);
    ui->backButton->setGeometry(780, 679, 210, 46);

    ui->boardTitleLabel->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    ui->playerNameLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->difficultyLabel->setAlignment(Qt::AlignCenter);
    ui->timerLabel->setAlignment(Qt::AlignCenter);

    QFont titleFont = ui->boardTitleLabel->font();
    titleFont.setPointSize(23);
    titleFont.setBold(true);
    ui->boardTitleLabel->setFont(titleFont);

    QFont infoFont = ui->playerNameLabel->font();
    infoFont.setPointSize(13);
    infoFont.setBold(true);
    ui->playerNameLabel->setFont(infoFont);
    ui->difficultyLabel->setFont(infoFont);

    QFont timerFont("Courier New");
    timerFont.setPointSize(16);
    timerFont.setBold(true);
    timerFont.setLetterSpacing(QFont::AbsoluteSpacing, 2.0);
    ui->timerLabel->setFont(timerFont);

    ui->boardTitleLabel->setStyleSheet(
        "QLabel {"
        "    color: #bfdbfe;"
        "    background-color: #122033;"
        "    border: 1px solid #1d3557;"
        "    border-radius: 10px;"
        "    padding: 0 10px;"
        "}"
        );

    ui->playerNameLabel->setStyleSheet(
        "QLabel {"
        "    color: #dbeafe;"
        "    background-color: #122033;"
        "    border: 1px solid #1d3557;"
        "    border-radius: 10px;"
        "    padding: 0 10px;"
        "}"
        );

    ui->difficultyLabel->setStyleSheet(
        "QLabel {"
        "    color: #bfdbfe;"
        "    background-color: #122033;"
        "    border: 1px solid #1d3557;"
        "    border-radius: 10px;"
        "    padding: 0 10px;"
        "}"
        );

    ui->timerLabel->setStyleSheet(
        "QLabel {"
        "    color: #f8fafc;"
        "    background-color: #0f1c2e;"
        "    border: 2px solid #38bdf8;"
        "    border-radius: 16px;"
        "    padding: 0 14px;"
        "}"
        );

    ui->backButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #1d4ed8;"
        "    color: white;"
        "    border: 2px solid #60a5fa;"
        "    border-radius: 12px;"
        "    padding: 0 14px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #2563eb;"
        "    border: 2px solid #93c5fd;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #1e40af;"
        "}"
        );

    ui->backButton->setFont(infoFont);

    connect(ui->backButton, &QPushButton::clicked, this, &GameForm::goBack);
    connect(&updateTimer, &QTimer::timeout, this, [this]() {
        const qint64 elapsedMs = timer.elapsed();
        const int totalSeconds = elapsedMs / 1000;
        const int minutes = totalSeconds / 60;
        const int seconds = totalSeconds % 60;

        ui->timerLabel->setText(
            QString("%1:%2")
                .arg(minutes, 2, 10, QChar('0'))
                .arg(seconds, 2, 10, QChar('0'))
            );
    });

    ui->boardTitleLabel->setText("Buscaminas");
    ui->playerNameLabel->setText("Jugador:");
    ui->difficultyLabel->setText("Nivel:");
    ui->timerLabel->setText("00:00");
}

GameForm::~GameForm()
{
    limpiarTablero();
    delete ui;
}

void GameForm::startGame(const QString &nombre, Difficulty difficulty)
{
    updateTimer.stop();
    timerStarted = false;
    elapsedTimeMs = 0;
    username = nombre;
    game = std::make_unique<Game>(difficulty);

    filas = game->getBoard().getRows();
    columnas = game->getBoard().getColumns();

    QString difficultyText;
    switch (difficulty) {
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

    ui->boardTitleLabel->setText("Buscaminas " + QString::number(filas) + "x" + QString::number(columnas));
    ui->playerNameLabel->setText("Jugador: " + nombre);
    ui->difficultyLabel->setText("Nivel: " + difficultyText);
    ui->timerLabel->setText("00:00");

    limpiarTablero();
    crearTablero(filas, columnas);
}

void GameForm::goBack()
{
    updateTimer.stop();
    emit backRequested();
}

void GameForm::crearTablero(int filas, int columnas)
{
    QGridLayout *grid = new QGridLayout();
    grid->setSpacing(2);
    grid->setAlignment(Qt::AlignCenter);
    ui->boardContainer->setLayout(grid);

    celdas.resize(filas);

    int tamCelda = 50;
    if (columnas == 30) {
        tamCelda = 28;
    } else if (columnas == 16) {
        tamCelda = 34;
    }

    for (int i = 0; i < filas; i++) {
        celdas[i].resize(columnas);

        for (int j = 0; j < columnas; j++) {
            CellButton *celda = new CellButton(i, j, ui->boardContainer);
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

            connect(celda, &CellButton::clickIzquierdo, this, &GameForm::alHacerClickIzquierdo);
            connect(celda, &CellButton::clickDerecho, this, &GameForm::alHacerClickDerecho);

            grid->addWidget(celda, i, j);
            celdas[i][j] = celda;
        }
    }
}

void GameForm::limpiarTablero()
{
    if (QLayout *layout = ui->boardContainer->layout()) {
        while (QLayoutItem *item = layout->takeAt(0)) {
            if (QWidget *widget = item->widget()) {
                delete widget;
            }
            delete item;
        }

        delete layout;
    }

    celdas.clear();
}

void GameForm::alHacerClickIzquierdo(int fila, int col)
{
    if (!game) {
        return;
    }

    const int totalColumnas = game->getBoard().getColumns();
    const int idx = fila * totalColumnas + col;
    CellButton *celda = celdas[fila][col];

    if (!celda->isEnabled() || game->isCellFlagged(idx)) {
        return;
    }

    if (game->isfirstClick()) {
        game->placeMines(idx);

        if (!timerStarted) {
            timer.start();
            timerStarted = true;
            updateTimer.start(250);
        }

        std::cout << "\nMINAS: " << game->getMinesNumber() << "\n";
    }

    Game::RevealResult result = game->reveal(idx);

    for (int changedIdx : result.changed) {
        const int f = changedIdx / totalColumnas;
        const int c = changedIdx % totalColumnas;
        CellButton *btn = celdas[f][c];
        const auto &cell = game->getBoard().getCell(changedIdx);

        if (cell.isMine()) {
            btn->setText("💣");
            btn->setStyleSheet(
                "QPushButton { background: #5c0a0a; border: 1px solid #ff4444; border-radius: 4px; }"
                );
        } else {
            const int minasAlrededor = cell.getMinesAround();
            btn->setText(minasAlrededor > 0 ? QString::number(minasAlrededor) : "");
            btn->setStyleSheet(
                "QPushButton { background: #0a3a1a; border: 1px solid #44cc77; border-radius: 4px; }"
                );
        }

        btn->setEnabled(false);
    }

    if (result.outcome == RevealOutcome::BOMB) {
        updateTimer.stop();
        QMessageBox::information(this, "Fin del juego", "Perdiste");
        emit backRequested();
    } else if (result.outcome == RevealOutcome::WON) {
        updateTimer.stop();
        elapsedTimeMs = timer.elapsed();

        ScoreEntry score;
        score.username = username;
        score.difficulty = game->getDifficulty();
        score.timeMs = elapsedTimeMs;
        rankingMng.saveScore(score);

        std::cout << "\n" << elapsedTimeMs << "\n";

        QMessageBox::information(this, "Victoria", "Ganaste");
        emit backRequested();
    }
}

void GameForm::alHacerClickDerecho(int fila, int col)
{
    if (!game) {
        return;
    }

    CellButton *celda = celdas[fila][col];
    if (!celda->isEnabled()) {
        return;
    }

    const int idx = fila * game->getBoard().getColumns() + col;
    const bool isFlagged = game->getBoard().getCell(idx).isFlagged();

    if (!game->toggleFlag(idx)) {
        return;
    }

    celda->setText(isFlagged ? "" : "🚩");
}
