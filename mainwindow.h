#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"employe.h"
#include"profil.h"
#include"connexion.h"
#include"smtp.h"
#include"widget.h"
#include"clients.h"
#include"film.h"
#include"statistique_clients.h"
#include"statistique_film.h"

#include <QMainWindow>
#include <QTimer>
#include <QWidget>
#include<QMessageBox>
#include<QTableView>


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

    void mail(QString email, QString sub, QString obj);

    void mailSent(QString);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_MODIFIER_clicked();

    void on_pushButton_refresh_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_Impression_clicked();


    void on_pushButton_camEmploye_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_3_activated(const QModelIndex &index);
    void myfunction();//pour l'heure

    void on_pushButton_modifier_2_clicked();

    void on_pushButton_mdp_clicked();

    void on_pushButton_modifier_clicked();

    void on_pushButton_supp_clicked();

    void on_pushButton_HISTORIQUE_clicked();

    void on_pushButton_connecter_clicked();

    void on_pushButton_camPROFIL_clicked();

    void on_pushButton_impression_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_authentification_clicked();

    void on_pushButton_3_valider_clicked();

    void on_pushButton_8_modifier_clicked();

    void on_lineEdit_Recherche_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_4_clicked();

    void on_pushButton_7_supprimer_clicked();

    void on_comboBox_modif_client_currentIndexChanged(int index);

    void on_comboBox_3_recherche_client_currentIndexChanged(int index);

    void on_pushButton_triDESC_clicked();

    void on_pushButton_trieASC_clicked();

    void on_pushButton_camClients_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_val_film_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    Widget *Camera;
    employe e;
    profil p;
    film tabf;
    clients tabC;

    statistique_film *stat_films;
    statistique_clients *stat_clients;
};
#endif // MAINWINDOW_H
