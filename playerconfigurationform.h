#ifndef PLAYERCONFIGURATIONFORM_H
#define PLAYERCONFIGURATIONFORM_H

#include "Enums.h"

#include <QString>
#include <QWidget>

namespace Ui {
class PlayerConfigurationForm;
}

class QComboBox;
class QLabel;

class PlayerConfigurationForm : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerConfigurationForm(QWidget *parent = nullptr);
    ~PlayerConfigurationForm();

    void setPlayerName(const QString &name);

signals:
    void playRequested(Difficulty difficulty);
    void rankingRequested();
    void backRequested();

private slots:
    void jugar();
    void abrirRanking();
    void regresarAMenu();

private:
    Ui::PlayerConfigurationForm *ui;
    QString playerName;
    QLabel *difficultyLabel;
    QComboBox *difficultyCombo;
};

#endif // PLAYERCONFIGURATIONFORM_H
