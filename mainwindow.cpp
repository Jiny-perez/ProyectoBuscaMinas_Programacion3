#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "playerconfigurationform.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(1100, 760);

    ui->titleLabel->setText("BUSCAMINAS");
    ui->titleLabel->setAlignment(Qt::AlignCenter);
    ui->titleLabel->setGeometry(300, 50, 500, 70);

    ui->nameLabel->setAlignment(Qt::AlignCenter);
    ui->nameLabel->setGeometry(350, 180, 400, 45);

    ui->nameField->setGeometry(350, 235, 400, 55);
    ui->startBttn->setGeometry(400, 345, 300, 70);
    ui->exitButton->setGeometry(400, 445, 300, 70);

    this->setStyleSheet(
        "QMainWindow {"
        "    background-color: #08111f;"
        "}"
        "QWidget#centralwidget {"
        "    background-color: #08111f;"
        "}"
        );

    ui->titleLabel->setStyleSheet(
        "color: #d9e7ff;"
        );
    QFont titleFont = ui->titleLabel->font();
    titleFont.setPointSize(28);
    titleFont.setBold(true);
    ui->titleLabel->setFont(titleFont);

    ui->nameLabel->setStyleSheet(
        "color: #b8c7ff;"
        );
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

    QString buttonStyle =
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startBttn_clicked()
{

    QString name = ui->nameField->toPlainText().trimmed();

    if(name.isEmpty())
    {
        QMessageBox::warning(this, "Validación", "Debe ingresar su nombre");
        return;
    }

    PlayerConfigurationForm *form = new PlayerConfigurationForm(name, this);
    form->show();
    this->hide();
}


void MainWindow::on_exitButton_clicked()
{
    this->close();
}

