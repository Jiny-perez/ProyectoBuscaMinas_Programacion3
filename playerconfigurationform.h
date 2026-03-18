#ifndef PLAYERCONFIGURATIONFORM_H
#define PLAYERCONFIGURATIONFORM_H

#include <QCloseEvent>
#include <QDialog>
#include <QString>

namespace Ui {
class PlayerConfigurationForm;
}

class PlayerConfigurationForm : public QDialog
{
    Q_OBJECT

public:
    explicit PlayerConfigurationForm(QString name, QWidget *parent = nullptr);
    ~PlayerConfigurationForm();

private slots:
    void jugar();
    void ranking();
    void regresarAMenu();
private:
    Ui::PlayerConfigurationForm *ui;
    QString playerName;
    bool returningToParent = false;

    void closeEvent(QCloseEvent *event) override;
};

#endif // PLAYERCONFIGURATIONFORM_H
