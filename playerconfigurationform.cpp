#include "playerconfigurationform.h"
#include "ui_playerconfigurationform.h"

#include "gameform.h"
#include "mainwindow.h"

#include <QApplication>
#include <QtWidgets>

PlayerConfigurationForm::PlayerConfigurationForm(QString name, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PlayerConfigurationForm)
    , playerName(name)
{
    ui->setupUi(this);
    ui->welcomeLabel->setText("Bienvenido, " + playerName + ".");

    setAttribute(Qt::WA_DeleteOnClose);

    setFixedSize(1100, 760);

    this->setStyleSheet(
        "QDialog {"
        "    background-color: #08111f;"
        "}"
        "QWidget#PlayerConfigurationForm {"
        "    background-color: #08111f;"
        "}"
        );

    ui->welcomeLabel->setText("Bienvenido, " + playerName + ".");
    ui->welcomeLabel->setAlignment(Qt::AlignCenter);
    ui->welcomeLabel->setGeometry(275, 90, 550, 70);
    ui->welcomeLabel->setStyleSheet(
        "color: #d9e7ff;"
        );

    QFont welcomeFont = ui->welcomeLabel->font();
    welcomeFont.setPointSize(26);
    welcomeFont.setBold(true);
    ui->welcomeLabel->setFont(welcomeFont);

    ui->playButton->setGeometry(400, 260, 300, 70);
    ui->rankingButton->setGeometry(400, 360, 300, 70);
    ui->backToMenuButton->setGeometry(400, 460, 300, 70);

    QString buttonStyle =
        "QPushButton {"
        "    background-color: #5b21b6;"
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

    ui->playButton->setStyleSheet(buttonStyle);
    ui->rankingButton->setStyleSheet(buttonStyle);
    ui->backToMenuButton->setStyleSheet(buttonStyle);

    QFont buttonFont = ui->playButton->font();
    buttonFont.setPointSize(16);
    buttonFont.setBold(true);

    ui->playButton->setFont(buttonFont);
    ui->rankingButton->setFont(buttonFont);
    ui->backToMenuButton->setFont(buttonFont);

    connect(ui->playButton, &QPushButton::clicked, this, &PlayerConfigurationForm::jugar);
    connect(ui->rankingButton, &QPushButton::clicked, this, &PlayerConfigurationForm::ranking);
    connect(ui->backToMenuButton, &QPushButton::clicked, this, &PlayerConfigurationForm::regresarAMenu);
}

PlayerConfigurationForm::~PlayerConfigurationForm()
{
    delete ui;
}

void PlayerConfigurationForm::closeEvent(QCloseEvent *event)
{
    if (!returningToParent) {
        QApplication::quit();
        return;
    }

    QDialog::closeEvent(event);
}

void PlayerConfigurationForm::jugar()
{
    Difficulty difficulty;
    QStringList difficultyList;
    difficultyList << "Beginner" << "Intermediate" << "Expert";

    bool selectDifficulty;

    QString difficulyDialog = QInputDialog::getItem(
        this,
        "Seleccionar dificultad",
        "Dificultad:",
        difficultyList,
        0,
        false,
        &selectDifficulty
        );

    if(!selectDifficulty){
        return;
    }

    if (difficulyDialog == "Beginner"){
        difficulty = Difficulty::BEGINNER;
    }else if (difficulyDialog == "Intermediate"){
        difficulty = Difficulty::INTERMEDIATE;
    }else{
        difficulty = Difficulty::EXPERT;
    }

    GameForm *form = new GameForm(playerName, difficulty, this);
    form->show();
    this->hide();
}

void PlayerConfigurationForm::ranking(){
    QMessageBox::information(this, "Ranking", "Todavia no esta disponible :c");
}

void PlayerConfigurationForm::regresarAMenu()
{
    if (parentWidget())
        parentWidget()->show();

    returningToParent = true;
    close();
}
