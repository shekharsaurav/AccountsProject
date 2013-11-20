#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>

namespace Ui {
class HomeScreen;
}

class HomeScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit HomeScreen(QWidget *parent = 0);
    ~HomeScreen();

private slots:


    void on_leUsername_editingFinished();

    void on_pbCancel_clicked();

    void on_pbLogin_clicked();

    void on_leUsername_textEdited(const QString &arg1);

    bool createConnection();

private:
    Ui::HomeScreen *ui;
};

#endif // HOMESCREEN_H
