#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "gameform.h"
#include "playerconfigurationform.h"
#include "rankingform.h"

#include <QFont>
#include <QMenuBar>
#include <QMessageBox>
#include <QStackedWidget>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , stackedWidget(nullptr)
    , startPage(nullptr)
    , configurationPage(nullptr)
    , gamePage(nullptr)
    , rankingPage(nullptr)
{
    ui->setupUi(this);
    setFixedSize(1140, 745);
    setStyleSheet(
        "QMainWindow {"
        "    background-color: #08111f;"
        "}"
        "QStackedWidget {"
        "    background-color: #08111f;"
        "}"
        );

    menuBar()->hide();
    statusBar()->hide();

    ui->titleLabel->setText("BUSCAMINAS");
    ui->titleLabel->setAlignment(Qt::AlignCenter);
    ui->titleLabel->setGeometry(320, 45, 500, 70);

    ui->nameLabel->setAlignment(Qt::AlignCenter);
    ui->nameLabel->setGeometry(370, 170, 400, 45);

    ui->nameField->setGeometry(370, 225, 400, 55);
    ui->startBttn->setGeometry(420, 330, 300, 70);
    ui->exitButton->setGeometry(420, 430, 300, 70);

    ui->titleLabel->setStyleSheet("color: #d9e7ff;");
    QFont titleFont = ui->titleLabel->font();
    titleFont.setPointSize(28);
    titleFont.setBold(true);
    ui->titleLabel->setFont(titleFont);

    ui->nameLabel->setStyleSheet("color: #b8c7ff;");
    QFont labelFont = ui->nameLabel->font();
    labelFont.setPointSize(15);
    ui->nameLabel->setFont(labelFont);

    ui->nameField->setStyleSheet(
        "background-color: #111a2b;"
        "color: #f4f7ff;"
        "border: 2px solid #7c3aed;"
        "border-radius: 10px;"
        "padding: 8px;"
        );
    QFont fieldFont = ui->nameField->font();
    fieldFont.setPointSize(13);
    ui->nameField->setFont(fieldFont);

    const QString buttonStyle =
        "QPushButton {"
        "    background-color: #6d28d9;"
        "    color: white;"
        "    border: 2px solid #a855f7;"
        "    border-radius: 14px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #7c3aed;"
        "    border: 2px solid #c084fc;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #581c87;"
        "}";

    ui->startBttn->setStyleSheet(buttonStyle);
    ui->exitButton->setStyleSheet(buttonStyle);

    QFont buttonFont = ui->startBttn->font();
    buttonFont.setPointSize(16);
    buttonFont.setBold(true);
    ui->startBttn->setFont(buttonFont);
    ui->exitButton->setFont(buttonFont);

    startPage = new QWidget(this);
    startPage->setObjectName("startPage");
    startPage->setFixedSize(1140, 745);
    startPage->setStyleSheet("QWidget#startPage { background-color: #08111f; }");

    ui->titleLabel->setParent(startPage);
    ui->nameLabel->setParent(startPage);
    ui->nameField->setParent(startPage);
    ui->startBttn->setParent(startPage);
    ui->exitButton->setParent(startPage);

    stackedWidget = new QStackedWidget(this);
    stackedWidget->setContentsMargins(0, 0, 0, 0);
    stackedWidget->addWidget(startPage);

    configurationPage = new PlayerConfigurationForm(this);
    gamePage = new GameForm(this);
    rankingPage = new RankingForm(this);

    stackedWidget->addWidget(configurationPage);
    stackedWidget->addWidget(gamePage);
    stackedWidget->addWidget(rankingPage);
    setCentralWidget(stackedWidget);

    connect(configurationPage, &PlayerConfigurationForm::playRequested, this, &MainWindow::showGamePage);
    connect(configurationPage, &PlayerConfigurationForm::rankingRequested, this, &MainWindow::showRankingPage);
    connect(configurationPage, &PlayerConfigurationForm::backRequested, this, &MainWindow::showStartPage);
    connect(gamePage, &GameForm::backRequested, this, &MainWindow::showConfigurationPage);
    connect(rankingPage, &RankingForm::backRequested, this, &MainWindow::showConfigurationPage);

    stackedWidget->setCurrentWidget(startPage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startBttn_clicked()
{
    const QString name = ui->nameField->toPlainText().trimmed();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Validacion", "Debe ingresar su nombre");
        return;
    }

    playerName = name;
    configurationPage->setPlayerName(playerName);
    showConfigurationPage();
}

void MainWindow::on_exitButton_clicked()
{
    close();
}

void MainWindow::showStartPage()
{
    stackedWidget->setCurrentWidget(startPage);
}

void MainWindow::showConfigurationPage()
{
    configurationPage->setPlayerName(playerName);
    stackedWidget->setCurrentWidget(configurationPage);
}

void MainWindow::showGamePage(Difficulty difficulty, GameMode modo)
{
    gamePage->startGame(playerName, difficulty, modo);
    stackedWidget->setCurrentWidget(gamePage);
}

void MainWindow::showRankingPage()
{
    rankingPage->refreshScores();
    stackedWidget->setCurrentWidget(rankingPage);
}
