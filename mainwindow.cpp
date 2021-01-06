#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "film.h"
#include "clients.h"
#include <QMessageBox>
#include <QTableView>
#include <iostream>
#include <QDebug>
#include <QDateTime>
#include <QMultimedia>
#include <QMediaPlayer>
#include <QSound>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this ,SLOT(myfunction()));
    timer->start(1000);

    //client int
        ui->lineEdit_6->setValidator(new QIntValidator(100, 9999, this));  // des nombres entre 100 et 9999

        //client varchar
        ui->lineEdit_3->setMaxLength(20);
        ui->lineEdit_22->setMaxLength(3);//controle de saisie je ne peut pas depasser les 3 lettres
        ui->lineEdit_5->setMaxLength(20);

         //film varchar
          ui->lineEdit->setMaxLength(20);
          ui->lineEdit_8->setMaxLength(20);
          ui->lineEdit_7->setMaxLength(20);
          ui->lineEdit_2->setMaxLength(5);




    if (Film::afficher_ComboBox() != nullptr)
    {std:: cout<<"null";}
    ui->comboBox_2->setModel(Film::afficher_ComboBox());
    if (tabf.afficher() != nullptr)
    {std:: cout<<"null";}
    ui->tableView->setModel(tabf.afficher());
    ui->tableView_2->setModel(tabC.afficherC());
    ui->comboBox->setModel(Clients::afficher_ComboBox2());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{


           /*sound*/
                  QMediaPlayer *player = new QMediaPlayer;

                  player->setMedia(QUrl::fromLocalFile("C:\\Users\\LENEVO\\Desktop\\2A13\\Projet C++\\Interface_Clients_Films\\button-8.mp3"));
                  player->setVolume(100);
                  player->play();

    Film f(ui->lineEdit->text(),ui->dateEdit_2->text(),ui->lineEdit_8->text(),ui->lineEdit_7->text(),ui->lineEdit_2->text());
   bool test = f.ajouter();
    if (test)
    {
          ui->tableView->setModel(tabf.afficher());
        QMessageBox::information(nullptr,QObject::tr("Ajout !"),
                             QObject::tr("Le Film a bien été ajouté"),
                             QMessageBox::Ok);}
    else{

    QMessageBox::critical(nullptr,QObject::tr("Erreur d'ajout"),
                            QObject::tr("Le Film n'a pas pu etre ajouté"),
                            QMessageBox::Cancel);}

}

void MainWindow::on_pushButton_3_clicked() // controle de saisie lors de l'insertion
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\LENEVO\\Desktop\\2A13\\Projet C++\\Interface_Clients_Films\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    Clients C(ui->lineEdit_3->text(),ui->lineEdit_5->text(),ui->dateEdit->text(),ui->lineEdit_6->text().toInt(),ui->lineEdit_22->text());
   bool test1 = C.ajouterC();
    C.ajouterC();
    if (test1)
    {
          ui->tableView_2->setModel(tabC.afficherC());
        QMessageBox::information(nullptr,QObject::tr("Ajout !"),
                             QObject::tr("Le Client a bien été ajouté"),
                             QMessageBox::Ok);}
    else{

    QMessageBox::critical(nullptr,QObject::tr("Erreur d'ajout"),
                            QObject::tr("Le Client n'a pas pu etre ajouté"),
                            QMessageBox::Cancel);}
}

void MainWindow::on_pushButton_6_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\LENEVO\\Desktop\\2A13\\Projet C++\\Interface_Clients_Films\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    bool test=tabf.supprimer( ui->lineEdit_10->text());
        if (test)
        {
              ui->tableView->setModel(tabf.afficher());
            QMessageBox::information(nullptr,QObject::tr("Supression !"),
                                 QObject::tr("supression effectuée"),
                                 QMessageBox::Ok);}
        else{

        QMessageBox::critical(nullptr,QObject::tr("Erreur de supression"),
                                QObject::tr("supression non effectuée"),
                                QMessageBox::Cancel);}



}

void MainWindow::on_pushButton_9_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\LENEVO\\Desktop\\2A13\\Projet C++\\Interface_Clients_Films\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    bool test=tabf.recherche(ui->lineEdit_4->text());

     if( test == true)
     {
         QMessageBox::information(nullptr,QObject::tr("Recherche"),
                              QObject::tr("film trouvé"),
                              QMessageBox::Ok);
     }

     else
     {
         QMessageBox::information(nullptr,QObject::tr("Recherche"),
                              QObject::tr("Le film n'existe pas"),
                              QMessageBox::Ok);
     }
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    ui->comboBox_2->currentText();

}

void MainWindow::on_pushButton_5_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\LENEVO\\Desktop\\2A13\\Projet C++\\Interface_Clients_Films\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    bool  test = tabf.modifier(ui->comboBox_2->currentText(), ui->lineEdit_12->text(),ui->lineEdit_13->text(),ui->lineEdit_14->text(),ui->lineEdit_15->text()) ;
           if (test)
           {
                 ui->tableView->setModel(tabf.afficher());
               QMessageBox::information(nullptr,QObject::tr("OK"),
                                    QObject::tr("modification effectuée"),
                                    QMessageBox::Ok);}
           else{
           QMessageBox::critical(nullptr,QObject::tr("Erreur de modification"),
                                   QObject::tr("modification non effectuée"),
                                   QMessageBox::Cancel);}
}



void MainWindow::on_pushButton_10_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\LENEVO\\Desktop\\2A13\\Projet C++\\Interface_Clients_Films\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    ui->tableView->setModel(tabf.trier());
}

void MainWindow::on_pushButton_7_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\LENEVO\\Desktop\\2A13\\Projet C++\\Interface_Clients_Films\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    bool test=tabC.supprimerC( ui->lineEdit_16->text().toInt());
        if (test)
        {
              ui->tableView_2->setModel(tabC.afficherC());
            QMessageBox::information(nullptr,QObject::tr("Supression !"),
                                 QObject::tr("supression effectuée"),
                                 QMessageBox::Ok);}
        else{

        QMessageBox::critical(nullptr,QObject::tr("Erreur de supression"),
                                QObject::tr("supression non effectuée"),
                                QMessageBox::Cancel);}
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ui->comboBox->currentText();
}

void MainWindow::on_pushButton_8_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\LENEVO\\Desktop\\2A13\\Projet C++\\Interface_Clients_Films\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    bool  test = tabC.modifierC(ui->lineEdit_17->text()) ;
           if (test)
           {
                 ui->tableView_2->setModel(tabC.afficherC());
               QMessageBox::information(nullptr,QObject::tr("OK"),
                                    QObject::tr("modification effectuée"),
                                    QMessageBox::Ok);}
           else{
           QMessageBox::critical(nullptr,QObject::tr("Erreur de modification"),
                                   QObject::tr("modification non effectuée"),
                                   QMessageBox::Cancel);}
}

/*void MainWindow::on_pushButton_4_clicked()
{
    bool test=tabC.rechercheC(ui->lineEdit_21->text().toInt());

     if( test == true)
     {
         QMessageBox::information(nullptr,QObject::tr("Recherche"),
                              QObject::tr("Le client existe deja"),
                              QMessageBox::Ok);
     }

     else
     {
         QMessageBox::information(nullptr,QObject::tr("Recherche"),
                              QObject::tr("Le client n'existe pas"),
                              QMessageBox::Ok);
     }
}*/

void MainWindow::on_pushButton_2_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\LENEVO\\Desktop\\2A13\\Projet C++\\Interface_Clients_Films\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    ui->tableView_2->setModel(tabC.trierC());
}

void MainWindow::on_comboBox_3_currentIndexChanged(int index)
{
    ui->comboBox_3->currentText();
}


void MainWindow::on_lineEdit_21_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
               QSqlQuery   *query= new QSqlQuery();
       if(ui->comboBox_3->currentText()=="nom")
               {
           query->prepare("SELECT * FROM client WHERE nom LIKE'"+arg1+"%'");//+tri
   query->exec();
       model->setQuery(*query);
   ui->tableView_2->setModel(model);


       }
       else {
           if(ui->comboBox_3->currentText()=="prenom"){
               query->prepare("SELECT * FROM client WHERE prenom LIKE'"+arg1+"%'");//+tri
       query->exec();
           model->setQuery(*query);
       ui->tableView_2->setModel(model);
           }
           else {
               if(ui->comboBox_3->currentText()=="carte_fidelite"){
               query->prepare("SELECT * FROM client WHERE carte_fidelite LIKE'"+arg1+"%'");//+tri
       query->exec();
           model->setQuery(*query);
       ui->tableView_2->setModel(model);
               }

           }

       }}




void MainWindow::on_pushButton_11_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\LENEVO\\Desktop\\2A13\\Projet C++\\Interface_Clients_Films\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    stat_films=new statistique_film(this);
    stat_films->show();
}

void MainWindow::on_pushButton_12_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\LENEVO\\Desktop\\2A13\\Projet C++\\Interface_Clients_Films\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    stat_clients=new statistique_clients(this);
    stat_clients->show();
}

void MainWindow::on_pushButton_13_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\LENEVO\\Desktop\\2A13\\Projet C++\\Interface_Clients_Films\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    ui->tableView->setModel(tabf.trierdesc());
}

void MainWindow::on_pushButton_14_clicked()
{
    ui->tableView_2->setModel(tabC.trierCdesc());

    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\LENEVO\\Desktop\\2A13\\Projet C++\\Interface_Clients_Films\\button-8.mp3"));
           player->setVolume(100);
           player->play();


}

void MainWindow::myfunction()
{
   /* qDebug() << "update..";*/

    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm : ss");
    if ((time.second() % 2)==  0)
    {
        time_text[3] = ' ';
        time_text[8] = ' ' ;
    }
    ui->label_TimeFilm->setText(time_text);
    ui->label_TimeClient->setText(time_text);
}


void MainWindow::on_pushButton_15_clicked()
{
    camera= new Widget(this);
    camera->show();
}

void MainWindow::on_pushButton_16_clicked()
{
    camera= new Widget(this);
    camera->show();
}
