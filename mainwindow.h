#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Enums.h"

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class GameForm;
class PlayerConfigurationForm;
class QStackedWidget;
class RankingForm;
class QWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startBttn_clicked();
    void on_exitButton_clicked();
    void showStartPage();
    void showConfigurationPage();
    void showGamePage(Difficulty difficulty);
    void showRankingPage();

private:
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget;
    QWidget *startPage;
    PlayerConfigurationForm *configurationPage;
    GameForm *gamePage;
    RankingForm *rankingPage;
    QString playerName;
};

#endif // MAINWINDOW_H
