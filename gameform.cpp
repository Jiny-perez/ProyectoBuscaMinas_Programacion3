#include "gameform.h"
#include "ui_gameform.h"

#include <QFont>
#include <QMessageBox>
#include <QVBoxLayout>

#include <iostream>

GameForm::GameForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameForm)
    , boardGui(nullptr)
    , timerStarted(false)
    , elapsedTimeMs(0)
{
    ui->setupUi(this);
    boardGui = new BoardGUI(ui->boardContainer);
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
    ui->flagsCounterLabel->setGeometry(600, 18, 150, 46);
    ui->boardContainer->setGeometry(90, 74, 900, 590);
    ui->playerNameLabel->setGeometry(90, 684, 245, 38);
    ui->difficultyLabel->setGeometry(355, 684, 205, 38);
    ui->backButton->setGeometry(780, 679, 210, 46);
    ui->restartButton->setGeometry(650, 679, 90, 46);

    ui->boardTitleLabel->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    ui->playerNameLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->difficultyLabel->setAlignment(Qt::AlignCenter);
    ui->timerLabel->setAlignment(Qt::AlignCenter);
    ui->flagsCounterLabel->setAlignment(Qt::AlignCenter);

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
    ui->flagsCounterLabel->setFont(timerFont);

    const QString labelsStyle =
        "QLabel {"
        "    color: #bfdbfe;"
        "    background-color: #122033;"
        "    border: 1px solid #1d3557;"
        "    border-radius: 10px;"
        "    padding: 0 10px;"
        "}";

    ui->boardTitleLabel->setStyleSheet(labelsStyle);
    ui->playerNameLabel->setStyleSheet(labelsStyle);
    ui->difficultyLabel->setStyleSheet(labelsStyle);

    const QString countersStyle =
        "QLabel {"
        "    color: #f8fafc;"
        "    background-color: #0f1c2e;"
        "    border: 2px solid #38bdf8;"
        "    border-radius: 16px;"
        "    padding: 0 14px;"
        "}";

    ui->timerLabel->setStyleSheet(countersStyle);
    ui->flagsCounterLabel->setStyleSheet(countersStyle);

    const QString buttonsStyle =
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
        "}";

    ui->backButton->setStyleSheet(buttonsStyle);
    ui->restartButton->setStyleSheet(buttonsStyle);
    ui->backButton->setFont(infoFont);

    auto *boardContainerLayout = new QVBoxLayout(ui->boardContainer);
    boardContainerLayout->setContentsMargins(0, 0, 0, 0);
    boardContainerLayout->addWidget(boardGui, 0, Qt::AlignCenter);

    connect(ui->backButton, &QPushButton::clicked, this, &GameForm::goBack);
    connect(ui->restartButton, &QPushButton::clicked, this, &GameForm::restart);
    connect(boardGui, &BoardGUI::leftCellClicked, this, &GameForm::alHacerClickIzquierdo);
    connect(boardGui, &BoardGUI::rightCellClicked, this, &GameForm::alHacerClickDerecho);

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
    ui->restartButton->setText("Restart");
}

GameForm::~GameForm()
{
    delete ui;
}

void GameForm::startGame(const QString &nombre, Difficulty difficulty)
{
    updateTimer.stop();
    timerStarted = false;
    elapsedTimeMs = 0;
    username = nombre;
    game = std::make_unique<Game>(difficulty);

    const int filas = game->getBoard().getRows();
    const int columnas = game->getBoard().getColumns();

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

    boardGui->setupBoard(filas, columnas);
    uptadeFlagsCounter();
}

void GameForm::goBack()
{
    updateTimer.stop();
    emit backRequested();
}

void GameForm::restart()
{
    if (!game) {
        return;
    }

    startGame(username, game->getDifficulty());
}

void GameForm::alHacerClickIzquierdo(int fila, int col)
{
    if (!game) {
        return;
    }

    const int totalColumnas = game->getBoard().getColumns();
    const int idx = fila * totalColumnas + col;

    if (!boardGui->isCellEnabled(fila, col) || game->isCellFlagged(idx)) {
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
        const auto &cell = game->getBoard().getCell(changedIdx);

        boardGui->showRevealedCell(f, c, cell.getMinesAround(), cell.isMine());
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
    if (!game || !boardGui->isCellEnabled(fila, col)) {
        return;
    }

    const int idx = fila * game->getBoard().getColumns() + col;
    const bool wasFlagged = game->getBoard().getCell(idx).isFlagged();

    if (!game->toggleFlag(idx)) {
        return;
    }

    boardGui->showFlaggedCell(fila, col, !wasFlagged);
    uptadeFlagsCounter();
}

void GameForm::uptadeFlagsCounter() const
{
    if (!game) {
        ui->flagsCounterLabel->clear();
        return;
    }

    ui->flagsCounterLabel->setText(QString::number(game->getMinesNumber() - game->getFlagsPlaced()));
}
