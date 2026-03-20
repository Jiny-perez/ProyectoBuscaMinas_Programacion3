#include "playerconfigurationform.h"
#include "ui_playerconfigurationform.h"

#include <QComboBox>
#include <QFont>
#include <QLabel>
#include <QPushButton>

PlayerConfigurationForm::PlayerConfigurationForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlayerConfigurationForm)
    , difficultyLabel(nullptr)
    , difficultyCombo(nullptr)
{
    ui->setupUi(this);
    setFixedSize(1140, 745);
    setAttribute(Qt::WA_StyledBackground, true);

    setStyleSheet(
        "QWidget#PlayerConfigurationForm {"
        "    background-color: #08111f;"
        "}"
        "QLabel {"
        "    color: #d9e7ff;"
        "}"
        );

    ui->welcomeLabel->setText("Bienvenido.");
    ui->welcomeLabel->setAlignment(Qt::AlignCenter);
    ui->welcomeLabel->setGeometry(295, 80, 550, 70);
    ui->welcomeLabel->setStyleSheet("color: #d9e7ff;");

    QFont welcomeFont = ui->welcomeLabel->font();
    welcomeFont.setPointSize(26);
    welcomeFont.setBold(true);
    ui->welcomeLabel->setFont(welcomeFont);

    ui->playButton->setGeometry(420, 280, 300, 70);
    ui->rankingButton->setGeometry(420, 380, 300, 70);
    ui->backToMenuButton->setGeometry(420, 480, 300, 70);

    difficultyLabel = new QLabel("Dificultad", this);
    difficultyLabel->setAlignment(Qt::AlignCenter);
    difficultyLabel->setGeometry(420, 170, 300, 35);

    difficultyCombo = new QComboBox(this);
    difficultyCombo->setGeometry(420, 210, 300, 42);
    difficultyCombo->addItems({"Beginner", "Intermediate", "Expert"});

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

    difficultyCombo->setStyleSheet(
        "QComboBox {"
        "    background-color: #111a2b;"
        "    color: #f4f7ff;"
        "    border: 2px solid #a855f7;"
        "    border-radius: 10px;"
        "    padding: 6px 10px;"
        "}"
        "QComboBox QAbstractItemView {"
        "    background-color: #111a2b;"
        "    color: #f4f7ff;"
        "    selection-background-color: #5b21b6;"
        "}"
        );

    QFont buttonFont = ui->playButton->font();
    buttonFont.setPointSize(16);
    buttonFont.setBold(true);

    ui->playButton->setFont(buttonFont);
    ui->rankingButton->setFont(buttonFont);
    ui->backToMenuButton->setFont(buttonFont);
    difficultyLabel->setFont(buttonFont);
    difficultyCombo->setFont(buttonFont);

    connect(ui->playButton, &QPushButton::clicked, this, &PlayerConfigurationForm::jugar);
    connect(ui->rankingButton, &QPushButton::clicked, this, &PlayerConfigurationForm::abrirRanking);
    connect(ui->backToMenuButton, &QPushButton::clicked, this, &PlayerConfigurationForm::regresarAMenu);
}

PlayerConfigurationForm::~PlayerConfigurationForm()
{
    delete ui;
}

void PlayerConfigurationForm::setPlayerName(const QString &name)
{
    playerName = name;
    ui->welcomeLabel->setText("Bienvenido, " + playerName + ".");
}

void PlayerConfigurationForm::jugar()
{
    Difficulty difficulty = Difficulty::EXPERT;
    const QString selectedDifficulty = difficultyCombo->currentText();

    if (selectedDifficulty == "Beginner") {
        difficulty = Difficulty::BEGINNER;
    } else if (selectedDifficulty == "Intermediate") {
        difficulty = Difficulty::INTERMEDIATE;
    }

    emit playRequested(difficulty);
}

void PlayerConfigurationForm::abrirRanking()
{
    emit rankingRequested();
}

void PlayerConfigurationForm::regresarAMenu()
{
    emit backRequested();
}
