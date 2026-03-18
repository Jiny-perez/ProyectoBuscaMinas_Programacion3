#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "playerconfigurationform.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    QString name = ui->textEdit->toPlainText().trimmed();

    if(name.isEmpty())
    {
        QMessageBox::warning(this, "Validación", "Debe ingresar su nombre");
        return;
    }

    PlayerConfigurationForm *form = new PlayerConfigurationForm(name, this);
    form->show();
    this->hide();
}


void MainWindow::on_pushButton_2_clicked()
{
    this->close();
}

