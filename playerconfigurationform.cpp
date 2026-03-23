#include "playerconfigurationform.h"
#include "ui_playerconfigurationform.h"

#include <QCoreApplication>
#include <QComboBox>
#include <QDesktopServices>
#include <QFileInfo>
#include <QFont>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QRadioButton>
#include <QStringList>
#include <QButtonGroup>
#include <QUrl>


PlayerConfigurationForm::PlayerConfigurationForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlayerConfigurationForm)
    , difficultyLabel(nullptr)
    , difficultyCombo(nullptr)
    , helpButton(nullptr)
    , creditsButton(nullptr)
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
    ui->welcomeLabel->setGeometry(295, 50, 550, 70);
    ui->welcomeLabel->setStyleSheet("color: #d9e7ff;");

    QFont welcomeFont = ui->welcomeLabel->font();
    welcomeFont.setPointSize(26);
    welcomeFont.setBold(true);
    ui->welcomeLabel->setFont(welcomeFont);

    ui->playButton->setGeometry(420, 320, 300, 70);
    ui->rankingButton->setGeometry(420, 420, 300, 70);
    ui->backToMenuButton->setGeometry(420, 620, 300, 70);

    difficultyLabel = new QLabel("Dificultad", this);
    difficultyLabel->setAlignment(Qt::AlignCenter);
    difficultyLabel->setGeometry(420, 200, 300, 35);

    difficultyCombo = new QComboBox(this);
    difficultyCombo->setGeometry(420, 250, 300, 42);
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

    helpButton = new QPushButton("Ayuda", this);
    helpButton->setGeometry(840, 640, 210, 55);
    helpButton->setStyleSheet(buttonStyle);

    creditsButton = new QPushButton("Creditos", this);
    creditsButton->setGeometry(420, 520, 300, 70);
    creditsButton->setStyleSheet(buttonStyle);

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
    helpButton->setFont(buttonFont);
    creditsButton->setFont(buttonFont);
    difficultyLabel->setFont(buttonFont);
    difficultyCombo->setFont(buttonFont);

    rbNormal = new QRadioButton("Modo Libre", this);
    rbNormal->setGeometry(350, 150, 150, 40);
    rbNormal->setFont(buttonFont);
    rbNormal->setChecked(true);

    rbStory= new QRadioButton("Modo Campaña", this);
    rbStory->setGeometry(600, 150, 200, 40);
    rbStory->setFont(buttonFont);

    QButtonGroup *modeGroup = new QButtonGroup(this);
    modeGroup->addButton(rbNormal, 0);
    modeGroup->addButton(rbStory, 1);

    connect(ui->playButton, &QPushButton::clicked, this, &PlayerConfigurationForm::jugar);
    connect(ui->rankingButton, &QPushButton::clicked, this, &PlayerConfigurationForm::abrirRanking);
    connect(helpButton, &QPushButton::clicked, this, &PlayerConfigurationForm::abrirAyuda);
    connect(creditsButton, &QPushButton::clicked, this, &PlayerConfigurationForm::solicitarCreditos);
    connect(ui->backToMenuButton, &QPushButton::clicked, this, &PlayerConfigurationForm::regresarAMenu);

    connect(rbNormal, &QRadioButton::toggled, this, &PlayerConfigurationForm::actualizarModo);
    connect(rbStory, &QRadioButton::toggled, this, &PlayerConfigurationForm::actualizarModo);

    actualizarModo();
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

void PlayerConfigurationForm::actualizarModo()
{
    if (rbNormal->isChecked()) {
        difficultyLabel->setEnabled(true);
        difficultyCombo->setEnabled(true);
    } else {
        difficultyLabel->setEnabled(false);
        difficultyCombo->setEnabled(false);
    }
}

void PlayerConfigurationForm::jugar()
{
    Difficulty difficulty = Difficulty::BEGINNER;

    if (rbNormal->isChecked()) {
        const QString selectedDifficulty = difficultyCombo->currentText();

        if (selectedDifficulty == "Beginner") {
            difficulty = Difficulty::BEGINNER;
        } else if (selectedDifficulty == "Intermediate") {
            difficulty = Difficulty::INTERMEDIATE;
        } else if (selectedDifficulty == "Expert") {
            difficulty = Difficulty::EXPERT;
        }
    }

    GameMode modo = rbStory->isChecked() ? GameMode::STORY : GameMode::NORMAL;

    emit playRequested(difficulty, modo);
}

void PlayerConfigurationForm::abrirRanking()
{
    emit rankingRequested();
}

void PlayerConfigurationForm::abrirAyuda()
{
    const QString appDir = QCoreApplication::applicationDirPath();
    const QStringList candidatePaths = {
        appDir + "/Ayuda.pdf",
        appDir + "/docs/Ayuda.pdf",
        appDir + "/../Ayuda.pdf",
        appDir + "/../../Ayuda.pdf"
    };

    for (const QString &candidatePath : candidatePaths) {
        const QFileInfo pdfFile(candidatePath);
        if (!pdfFile.exists() || !pdfFile.isFile()) {
            continue;
        }

        if (QDesktopServices::openUrl(QUrl::fromLocalFile(pdfFile.absoluteFilePath()))) {
            return;
        }

        QMessageBox::warning(
            this,
            "Ayuda",
            "Se encontro el archivo de ayuda, pero no se pudo abrir el visor de PDF.");
        return;
    }

    QMessageBox::information(
        this,
        "Ayuda",
        "No se encontro el archivo de ayuda.\n\n"
        "Coloca el PDF como 'Ayuda.pdf' junto al ejecutable o dentro de la carpeta 'docs'.");
}

void PlayerConfigurationForm::solicitarCreditos()
{
    emit creditsRequested();
}

void PlayerConfigurationForm::regresarAMenu()
{
    emit backRequested();
}
