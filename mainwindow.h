#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "film.h"
#include "clients.h"
#include "statistique_film.h"
#include <QWidget>
#include "statistique_clients.h"
#include <QTimer>
#include "arduino.h"
#include "widget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButtonValidFilm_clicked();

    void on_pushButtonValidC_clicked();

    void on_pushButtonSuppFilm_clicked();

    void on_pushButtonRechFilm_clicked();

    void on_comboBox_ModifFilm_currentIndexChanged(int index);

    void on_pushButtonModifFilm_clicked();

    void on_pushButtonTriAscFilm_clicked();

    void on_pushButtonSuppC_clicked();

    void on_comboBoxModifC_currentIndexChanged(int index);

    void on_pushButtonModifC_clicked();

    /*void on_pushButtonRechC_clicked();*/

    void on_pushButtonAscC_clicked();

    void on_comboBoxRechC_currentIndexChanged(int index);

    void on_lineEditRechC_textChanged(const QString &arg1);

    void on_pushButtonStatFilm_clicked();

    void on_pushButtonStatC_clicked();

    void on_pushButtonTriDescFilm_clicked();

    void on_pushButtonTriDescC_clicked();

    void myfunction();

    void on_pushButtonCamC_clicked();

    void on_pushButtonCamFilm_clicked();



private:
    Ui::MainWindow *ui;
    Film tabf;
    Clients tabC;
    statistique_film *stat_films;
    statistique_clients *stat_clients;
    QTimer *timer;
    Widget *camera;
    Arduino  ard;

};
#endif // MAINWINDOW_H
