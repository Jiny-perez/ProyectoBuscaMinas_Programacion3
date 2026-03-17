#include "playerconfigurationform.h"
#include "ui_playerconfigurationform.h"

#include "gameform.h"
#include "mainwindow.h"

#include <QtWidgets>

PlayerConfigurationForm::PlayerConfigurationForm(QString name, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PlayerConfigurationForm)
    , playerName(name)
{
    ui->setupUi(this);
    ui->label->setText(playerName);

    connect(ui->btnJugar, &QPushButton::clicked, this, &PlayerConfigurationForm::jugar);
    connect(ui->btnRanking, &QPushButton::clicked, this, &PlayerConfigurationForm::ranking);
    connect(ui->btnRegresarMenu, &QPushButton::clicked, this, &PlayerConfigurationForm::regresarAMenu);
}

PlayerConfigurationForm::~PlayerConfigurationForm()
{
    delete ui;
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
    MainWindow *menuPrincipal = new MainWindow();
    menuPrincipal->show();
    this->close();
}


