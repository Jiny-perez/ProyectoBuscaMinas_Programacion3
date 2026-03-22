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
class QRadioButton;

class PlayerConfigurationForm : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerConfigurationForm(QWidget *parent = nullptr);
    ~PlayerConfigurationForm();

    void setPlayerName(const QString &name);

signals:
    void playRequested(Difficulty difficulty, GameMode mode);
    void rankingRequested();
    void backRequested();

private slots:
    void jugar();
    void abrirRanking();
    void regresarAMenu();
    void actualizarModo();

private:
    Ui::PlayerConfigurationForm *ui;

    QString playerName;

    QLabel *difficultyLabel;
    QComboBox *difficultyCombo;

    QRadioButton *rbNormal;
    QRadioButton *rbStory;
};

#endif // PLAYERCONFIGURATIONFORM_H
