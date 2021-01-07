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
    int ret= ard.connect_arduino();
    switch(ret)
    {case(0):
        qDebug() << "arduino is available and cooneted to  : "<<ard.getarduino_port_name();
        break;
     case(1):
        qDebug()<< "arduino is available but not conected to : "<< ard.getarduino_port_name();
        break;
     case(-1):
        qDebug()<<"arduino is no available ";
        break;
    }
    QObject::connect(ard.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()) );
    /* updtae_label thoteha bech tamel mise a jour lel label eli feha heya bech trajja el valeur taa el arduino
      yani el retour taa el arduino */

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this ,SLOT(myfunction()));
    timer->start(1000);

    //client int
        ui->lineEditPrenomC->setValidator(new QIntValidator(100, 9999, this));  // des nombres entre 100 et 9999

        //client varchar
        ui->lineEditNomC->setMaxLength(20);
        ui->lineEditRedu->setMaxLength(3);//controle de saisie je ne peut pas depasser les 3 lettres
        ui->lineEditPrenomC->setMaxLength(20);

         //film varchar
          ui->lineEditTitre->setMaxLength(20);
          ui->lineEditCatAjout->setMaxLength(20);
          ui->lineEditNomRea->setMaxLength(20);
          ui->lineEditDuree->setMaxLength(5);




    if (Film::afficher_ComboBox() != nullptr)
    {std:: cout<<"null";}
    ui->comboBox_ModifFilm->setModel(Film::afficher_ComboBox());
    if (tabf.afficher() != nullptr)
    {std:: cout<<"null";}
    ui->tableView->setModel(tabf.afficher());
    ui->tableView_2->setModel(tabC.afficherC());
    ui->comboBoxModifC->setModel(Clients::afficher_ComboBox2());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonValidFilm_clicked()
{


           /*sound*/
                  QMediaPlayer *player = new QMediaPlayer;

                  player->setMedia(QUrl::fromLocalFile("C:\\Users\\LENEVO\\Desktop\\2A13\\Projet C++\\Interface_Clients_Films\\button-8.mp3"));
                  player->setVolume(100);
                  player->play();

    Film f(ui->lineEditTitre->text(),ui->dateEdit_2->text(),ui->lineEditCatAjout->text(),ui->lineEditNomRea->text(),ui->lineEditDuree->text());
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

void MainWindow::on_pushButtonValidC_clicked() // controle de saisie lors de l'insertion
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\LENEVO\\Desktop\\2A13\\Projet C++\\Interface_Clients_Films\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    Clients C(ui->lineEditNomC->text(),ui->lineEditPrenomC->text(),ui->dateEdit->text(),ui->lineEditPrenomC->text().toInt(),ui->lineEditRedu->text());
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

void MainWindow::on_pushButtonSuppFilm_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\LENEVO\\Desktop\\2A13\\Projet C++\\Interface_Clients_Films\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    bool test=tabf.supprimer( ui->lineEditSuppFilm->text());
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

void MainWindow::on_pushButtonRechFilm_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\LENEVO\\Desktop\\2A13\\Projet C++\\Interface_Clients_Films\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    bool test=tabf.recherche(ui->lineEditRechFilm->text());

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

void MainWindow::on_comboBox_ModifFilm_currentIndexChanged(int index)
{
    ui->comboBox_ModifFilm->currentText();

}

void MainWindow::on_pushButtonModifFilm_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\LENEVO\\Desktop\\2A13\\Projet C++\\Interface_Clients_Films\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    bool  test = tabf.modifier(ui->comboBox_ModifFilm->currentText(), ui->lineEditNvDateF->text(),ui->lineEditNvCat->text(),ui->lineEditNvNomRea->text(),ui->lineEditNvDuree->text()) ;
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



void MainWindow::on_pushButtonTriAscFilm_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\LENEVO\\Desktop\\2A13\\Projet C++\\Interface_Clients_Films\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    ui->tableView->setModel(tabf.trier());
}

void MainWindow::on_pushButtonSuppC_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\LENEVO\\Desktop\\2A13\\Projet C++\\Interface_Clients_Films\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    bool test=tabC.supprimerC( ui->lineEditSuppC->text().toInt());
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

void MainWindow::on_comboBoxModifC_currentIndexChanged(int index)
{
    ui->comboBoxModifC->currentText();
}

void MainWindow::on_pushButtonModifC_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\LENEVO\\Desktop\\2A13\\Projet C++\\Interface_Clients_Films\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    bool  test = tabC.modifierC(ui->pushButtonModifC->text()) ;
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

/*void MainWindow::on_pushButtonRechC_clicked()
{
    bool test=tabC.rechercheC(ui->lineEditRechC->text().toInt());

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

void MainWindow::on_pushButtonAscC_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\LENEVO\\Desktop\\2A13\\Projet C++\\Interface_Clients_Films\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    ui->tableView_2->setModel(tabC.trierC());
}

void MainWindow::on_comboBoxRechC_currentIndexChanged(int index)
{
    ui->comboBoxRechC->currentText();
}


void MainWindow::on_lineEditRechC_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
               QSqlQuery   *query= new QSqlQuery();
       if(ui->comboBoxRechC->currentText()=="nom")
               {
           query->prepare("SELECT * FROM client WHERE nom LIKE'"+arg1+"%'");//+tri
   query->exec();
       model->setQuery(*query);
   ui->tableView_2->setModel(model);


       }
       else {
           if(ui->comboBoxRechC->currentText()=="prenom"){
               query->prepare("SELECT * FROM client WHERE prenom LIKE'"+arg1+"%'");//+tri
       query->exec();
           model->setQuery(*query);
       ui->tableView_2->setModel(model);
           }
           else {
               if(ui->comboBoxRechC->currentText()=="carte_fidelite"){
               query->prepare("SELECT * FROM client WHERE carte_fidelite LIKE'"+arg1+"%'");//+tri
       query->exec();
           model->setQuery(*query);
       ui->tableView_2->setModel(model);
               }

           }

       }}




void MainWindow::on_pushButtonStatFilm_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\LENEVO\\Desktop\\2A13\\Projet C++\\Interface_Clients_Films\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    stat_films=new statistique_film(this);
    stat_films->show();
}

void MainWindow::on_pushButtonStatC_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\LENEVO\\Desktop\\2A13\\Projet C++\\Interface_Clients_Films\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    stat_clients=new statistique_clients(this);
    stat_clients->show();
}

void MainWindow::on_pushButtonTriDescFilm_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\LENEVO\\Desktop\\2A13\\Projet C++\\Interface_Clients_Films\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    ui->tableView->setModel(tabf.trierdesc());
}

void MainWindow::on_pushButtonTriDescC_clicked()
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


void MainWindow::on_pushButtonCamC_clicked()
{
    camera= new Widget(this);
    camera->show();
}

void MainWindow::on_pushButtonCamFilm_clicked()
{
    camera= new Widget(this);
    camera->show();
}


