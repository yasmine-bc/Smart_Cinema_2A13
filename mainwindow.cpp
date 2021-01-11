#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"employe.h"
#include"profil.h"
#include"smtp.h"
#include"clients.h"
#include"statistique_clients.h"
#include"statistique_film.h"
#include"arduino.h"
#include"widget.h"


#include<iostream>
#include<QMessageBox>
#include <QPixmap>
#include <QMovie>
#include <QMediaPlayer>
#include<QtMultimedia>
#include<QSound>
#include<QDialog>
#include<QPrintDialog>
#include<QPrinter>
#include<QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QDateTime>
#include <QSqlDatabase>
#include <QSqlError>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    //arduino

        int ret= ard.connect_arduino();
                switch(ret)
                {case(0):
                    qDebug() << "arduino is available and cooneted to  : "<<ard.getarduino_port_name();
                    break;
                 case(1):
                    qDebug()<< "arduino is available but not conected to : "<< ard.getarduino_port_name();
                    break;
                 case(-1):
                    qDebug()<<"arduino is not available ";
                    break;
                }
      QObject::connect(ard.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()) );



    /*controle de saisie*/
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this ,SLOT(myfunction()));
    timer->start(1000); //l'heure en miliseconde
    //employee int    age cin
ui->lineEdit_age->setValidator(new QIntValidator(100, 999, this));  // des nombres entre100 et 999
ui->lineEdit_CIN->setValidator(new QIntValidator(100, 999, this));


//employe varchar
ui->lineEdit_nom->setMaxLength(100);
ui->lineEdit_prenom->setMaxLength(50);//controle de saisie je ne peut pas depasser les 50 lettres
ui->lineEdit_ID->setMaxLength(50);
ui->lineEdit_fonction->setMaxLength(50);

 //profile varchar
  ui->lineEdit_nomUtili->setMaxLength(50);
  ui->lineEdit_mot->setMaxLength(50);

  if (film::afficher_ComboBox_modif_client() != nullptr)
  {std:: cout<<"null";}
  ui->comboBox_2_modif_film->setModel(film::afficher_ComboBox_modif_client());
  if (tabf.afficher() != nullptr)
  {std:: cout<<"null";}
  ui->tableView->setModel(tabf.afficher());
  ui->tableView_2->setModel(tabC.afficherC());
  ui->comboBox_modif_client->setModel(clients::afficher_ComboBox2_modif_film());
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::mail(QString email, QString sub, QString obj)
{

    smtp *smtp = new smtp("rentcar.projet@gmail.com", "azer123@", "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    smtp->sendMail(email, sub, obj);
}

void MainWindow::mailSent(QString status)
{
    if (status == "Message sent")
        QMessageBox::information(nullptr, QObject::tr("RentCar mailing !"), QObject::tr("Un email est envoye a votre client pour l informer de\nsa nouvelle carte de fidelite!\n"));
}


void MainWindow::on_pushButton_clicked()
{
    /*sound*/
       QMediaPlayer *player = new QMediaPlayer;

       player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
       player->setVolume(100);
       player->play();

       QString nom =ui->lineEdit_nom->text();
       QString prenom =ui->lineEdit_prenom->text();
       int age =ui->lineEdit_age->text().toInt();
       QString ID =ui->lineEdit_ID->text();
       int CIN =ui->lineEdit_CIN->text().toInt();
       QString fonction=ui->lineEdit_fonction->text();



       employe e( nom,prenom, age,ID,CIN,fonction);
       bool test=e.ajouter();
               if (test)
                {
                   ui->tableView_3->setModel(e.afficher());

                    QMessageBox::information(nullptr,QObject::tr("ok"),
                            QObject::tr("ajout effectue\n"
                                        "Clich cancel to exit ."),QMessageBox::Cancel );
                }
                else
                    QMessageBox::critical(nullptr, QObject::tr("Not ok "),
                                QObject::tr("connexion failed.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pushButton_3_clicked()
{
    /*sound*/
       QMediaPlayer *player = new QMediaPlayer;

       player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
       player->setVolume(100);
       player->play();

    QString ID=ui->lineEdit_ID->text();
        bool test= e.supprimer(ID);
        if (test)
        {
            ui->tableView_3->setModel(e.afficher());

            QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("supression établie"),
                                 QMessageBox::Ok);}
        else{
        //qDebug()<<"connexion echouer";
        QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                                QObject::tr("supression non établie"),
                                QMessageBox::Cancel);}

}


void MainWindow::on_pushButton_MODIFIER_clicked()
{
    /*sound*/
   QMediaPlayer *player = new QMediaPlayer;

   player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
   player->setVolume(100);
   player->play();

   QString nom =ui->lineEdit_nom->text();
   QString prenom =ui->lineEdit_prenom->text();
   int age =ui->lineEdit_age->text().toInt();
   QString ID =ui->lineEdit_ID->text();
   int CIN =ui->lineEdit_CIN->text().toInt();
   QString fonction=ui->lineEdit_fonction->text();


    employe e(nom,prenom, age, ID, CIN,fonction);

    bool test=e.modifier();
    if (test)
    {
        ui->tableView_3->setModel(e.afficher());

        QMessageBox::information(nullptr,QObject::tr("OK"),
                             QObject::tr("ajout effectue\n"
                                         "Clich cancel to exit ."),  QMessageBox::Cancel);}
    else{
    //qDebug()<<"connexion echouer";
    QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                            QObject::tr("modification non établie"),
                            QMessageBox::Cancel);}
         ui->lineEdit_nom->setText("");
         ui->lineEdit_prenom->setText("");
         ui->lineEdit_age->setText("");
         ui->lineEdit_ID->setText("");
         ui->lineEdit_CIN->setText("");
         ui->lineEdit_fonction->setText("");

}

//molka

void MainWindow::on_pushButton_refresh_clicked()
{
    /*sound*/
       QMediaPlayer *player = new QMediaPlayer;

       player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
       player->setVolume(100);
       player->play();

    ui->tableView_3->setModel(e.afficher());
}

void MainWindow::on_pushButton_7_clicked()
{
    /*sound*/
       QMediaPlayer *player = new QMediaPlayer;

       player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
       player->setVolume(100);
       player->play();


    QString critere=ui->comboBox->currentText();
        QString mode;
        if (ui->checkBox_5->checkState()==false)
    {
             mode="DESC";
    }
         else if(ui->checkBox_4->checkState()==false)
         {
             mode="ASC";
         }
    ui->tableView->setModel(e.trie(critere,mode));

}


void MainWindow::on_pushButton_Impression_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
           player->setVolume(100);
           player->play();
           QString strStream;
                       QTextStream out(&strStream);
                       const int rowCount = ui->tableView_3->model()->rowCount();
                       const int columnCount =ui->tableView_3->model()->columnCount();

                       out <<  "<html>\n"
                               "<head>\n"
                               "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                               <<  QString("<title>%1</title>\n").arg("facture")
                               <<  "</head>\n"
                               "<body bgcolor=#CFC4E1 link=#5000A0>\n"

                                   "<h1>Liste des employes</h1>"



                                   "<table border=1 cellspacing=0 cellpadding=2>\n";


                       // headers
                           out << "<thead><tr bgcolor=#f0f0f0>";
                           for (int column = 0; column < columnCount; column++)
                               if (!ui->tableView_3->isColumnHidden(column))
                                   out << QString("<th>%1</th>").arg(ui->tableView_3->model()->headerData(column, Qt::Horizontal).toString());
                           out << "</tr></thead>\n";
                           // data table
                              for (int row = 0; row < rowCount; row++) {
                                  out << "<tr>";
                                  for (int column = 0; column < columnCount; column++) {
                                      if (!ui->tableView_3->isColumnHidden(column)) {
                                          QString data = ui->tableView_3->model()->data(ui->tableView_3->model()->index(row, column)).toString().simplified();
                                          out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                      }
                                  }
                                  out << "</tr>\n";
                              }
                              out <<  "</table>\n"
                                  "</body>\n"
                                  "</html>\n";

                              QTextDocument *document = new QTextDocument();
                              document->setHtml(strStream);

                              QPrinter printer;

                              QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                              if (dialog->exec() == QDialog::Accepted) {
                                  document->print(&printer);
                           }

}


void MainWindow::on_pushButton_camEmploye_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    Camera = new Widget(this);
    Camera ->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    ui->stackedWidget->setCurrentIndex(4);
      ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_tableView_3_activated(const QModelIndex &index)
{
    QString val1 =ui->tableView_3->model()->data(index).toString();
       QSqlQuery query;
       query.prepare("select *from EMPLOYE where nom='"+val1+"' or prenom='"+val1+"' or age='"+val1+"' or ID='"+val1+"' or fonction='"+val1+"' or CIN='"+val1+"'");

       if(query.exec())
       { while(query.next())
           {     ui->lineEdit_nom->setText(query.value(0).toString());
               ui->lineEdit_prenom->setText(query.value(1).toString());
               ui->lineEdit_age->setText(query.value(2).toString());
               ui->lineEdit_ID->setText(query.value(3).toString());
               ui->lineEdit_fonction->setText(query.value(5).toString());
               ui->lineEdit_CIN->setText(query.value(6).toString());


             }
       }
}
void MainWindow::myfunction()
{
   // qDebug() <<"update..";
    QTime time =QTime::currentTime();
    QString time_text= time.toString("hh : mm : ss");
    if ((time.second() % 2 )== 0)
    {
        time_text[3] = ' ';
        time_text[8] = ' ';


    }
    ui->label_timePROFIL ->setText(time_text);
    ui->label_timeEmploye->setText(time_text);
    ui->label_timeCLIENT ->setText(time_text);
    ui->label_timeFILM->setText(time_text);
}

void MainWindow::on_pushButton_modifier_2_clicked()
{
    /*sound*/
    QMediaPlayer *player = new QMediaPlayer;

    player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
    player->setVolume(100);
    player->play();

 QString NOM_UTILI =ui->lineEdit_nomUtili->text();
 QString MOT_DE_PASSE =ui->lineEdit_mot->text();



    profil p(NOM_UTILI,MOT_DE_PASSE);
    bool test=p.ajouter();
            if (test)
             {   ui->tableView_4->setModel(p.afficher()) ;
                 QMessageBox::information(nullptr,QObject::tr("ok"),
                         QObject::tr("ajout effectue\n"
                                     "Clich cancel to exit ."),QMessageBox::Cancel );
             }
             else
                 QMessageBox::critical(nullptr, QObject::tr("Not ok "),
                             QObject::tr("connexion failed.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);

            ui->stackedWidget->setCurrentIndex(2);

            ui->stackedWidget->setCurrentIndex(3);


}

void MainWindow::on_pushButton_mdp_clicked()
{
    /*sound*/
    QMediaPlayer *player = new QMediaPlayer;

    player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
    player->setVolume(100);
    player->play();

    smtp* smtp = new smtp("rentcar.projet@gmail.com", "azer123@", "smtp.gmail.com", 465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    //QModelIndexList selection = ui->tableView->selectionModel()->selectedRows(0);
    QSqlQuery query;
    QString NOM_UTILI= ui->lineEdit_nomUtili->text();
    QString MOT_DE_PASSE;
    QString msg ="non";

    //if (!selection.empty()) {
       // QModelIndex idIndex = selection.at(0);
     //   int id = idIndex.sibling(idIndex.row(),0).data().toInt();
        //int etat = idIndex.sibling(idIndex.row(),5).data().toInt();
       // QString idS= QString::number(id);

            query.prepare("select NOM_UTILI,MOT_DE_PASSE from PROFIL WHERE NOM_UTILI= 'molka.azaouzi@esprit.tn' ");

            //if (query.exec())
            {
                while (query.next()) {
                     NOM_UTILI =query.value(0).toString();
                    MOT_DE_PASSE =query.value(1).toString();

                }

            qDebug()<<"nom , mdp "<< NOM_UTILI + MOT_DE_PASSE;
            msg="Cher employé "+NOM_UTILI+" Votre mot de passe est " + MOT_DE_PASSE;
            smtp->sendMail(NOM_UTILI, "Mot de passe!",msg);
            QMessageBox::information(this, tr("Mail"),
                                     tr("Mail Envoyé!"));



}}

void MainWindow::on_pushButton_modifier_clicked()
{
    /*sound*/
   QMediaPlayer *player = new QMediaPlayer;

   player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
   player->setVolume(100);
   player->play();

   QString nom =ui->lineEdit_nom->text();
   QString prenom =ui->lineEdit_prenom->text();
   int age =ui->lineEdit_age->text().toInt();
   QString ID =ui->lineEdit_ID->text();
   int CIN =ui->lineEdit_CIN->text().toInt();
   QString fonction=ui->lineEdit_fonction->text();


    employe e(nom,prenom, age, ID, CIN,fonction);

    bool test=e.modifier();
    if (test)
    {
        ui->tableView_4->setModel(e.afficher());

        QMessageBox::information(nullptr,QObject::tr("OK"),
                             QObject::tr("ajout effectue\n"
                                         "Clich cancel to exit ."),  QMessageBox::Cancel);}
    else{
    //qDebug()<<"connexion echouer";
    QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                            QObject::tr("modification non établie"),
                            QMessageBox::Cancel);}
         ui->lineEdit_nom->setText("");
         ui->lineEdit_prenom->setText("");
         ui->lineEdit_age->setText("");
         ui->lineEdit_ID->setText("");
         ui->lineEdit_CIN->setText("");
         ui->lineEdit_fonction->setText("");


}

void MainWindow::on_pushButton_supp_clicked()
{
    /*sound*/
       QMediaPlayer *player = new QMediaPlayer;

       player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
       player->setVolume(100);
       player->play();

    QString NOM_UTILI=ui->lineEdit_nomUtili->text();
        bool test= p.supprimer(NOM_UTILI);
        if (test)
        {
            ui->tableView_4->setModel(p.afficher());

            QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("supression établie"),
                                 QMessageBox::Ok);}
        else{
        //qDebug()<<"connexion echouer";
        QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                                QObject::tr("supression non établie"),
                                QMessageBox::Cancel);}



}

void MainWindow::on_pushButton_HISTORIQUE_clicked()
{
    /*sound*/
       QMediaPlayer *player = new QMediaPlayer;

       player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
       player->setVolume(100);
       player->play();

     ui->tableView_4->setModel(p.afficher());
     p.HISTORIQUE_PDF();
}

void MainWindow::on_pushButton_connecter_clicked()
{
    /*sound*/
       QMediaPlayer *player = new QMediaPlayer;

       player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
       player->setVolume(100);
       player->play();


           QString email = ui->lineEdit_nomUtili->text(), pass = ui->lineEdit_nomUtili->text();
           if(email != "")
           {
               if(pass == "")
               {
                   QMessageBox::critical(nullptr,QObject::tr("Login."),QObject::tr("Le champs du mot de passe est vide !\n"));
                   ui->lineEdit_nomUtili->setText("");
               }
               else
               {
                   QString ID;
                   QSqlQuery query;
                   query.prepare("SELECT NOM from EMPOLYE where Nom d utilisateur = '"+email+"' or email = '"+email+"'");
                   query.exec();
                   while (query.next()) {
                       ID = query.value(0).toString();
                   }
                   if(	ID != "")
                   {
                       QString ID1;
                       QSqlQuery query1;
                       query1.prepare("SELECT NOM2 from EMPOLYE where Nom d utilisateur = '"+email+"' or email = '"+email+"' AND mdp = '"+pass+"'");
                       query1.exec();
                       while (query1.next()) {
                           ID1 = query1.value(0).toString();
                       }
                       if(ID1 != "")
                       {
                           QString role;
                           QSqlQuery query11;
                           query11.prepare("SELECT role from EMPLOYE where Nom d utilisateur = '"+email+"' AND mdp = '"+pass+"'");
                           query11.exec();
                           while (query11.next()) {
                               role = query11.value(0).toString();
                           }
                           close();
                       }
                       else
                       {
                           QMessageBox::critical(nullptr,QObject::tr("Nom d utilisateur."),QObject::tr("Le mot de passe est incorrecte, \nEssayez une autre fois !\n"));
                           ui->lineEdit_mot->setText("");
                       }
                   }
                   else
                   {
                       QMessageBox::critical(nullptr,QObject::tr("Login."),QObject::tr("Cet E mail n'existe pas !\n"));
                       ui->lineEdit_mot->setText("");
                       ui->lineEdit_mot->setText("");
                   }
               }
           }
           else
           {
               if(pass == "")
                   QMessageBox::critical(nullptr,QObject::tr("Nom d utilisateur."),QObject::tr("Les champs du mot de passe et du E mail \nsont vides !\n"));
               else
                   QMessageBox::critical(nullptr,QObject::tr("Nom d utilisateur."),QObject::tr("Le champs de l E mail est vide !\n"));
               ui->lineEdit_nomUtili->setText("");
               ui->lineEdit_mot->setText("");
           }
}

void MainWindow::on_pushButton_camPROFIL_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    Camera = new Widget(this);
    Camera ->show();
}

void MainWindow::on_pushButton_impression_clicked()
{
    /*sound*/
               QMediaPlayer *player = new QMediaPlayer;

               player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
               player->setVolume(100);
               player->play();
               QString strStream;
                           QTextStream out(&strStream);
                           const int rowCount = ui->tableView_4->model()->rowCount();
                           const int columnCount =ui->tableView_4->model()->columnCount();

                           out <<  "<html>\n"
                                   "<head>\n"
                                   "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                   <<  QString("<title>%1</title>\n").arg("facture")
                                   <<  "</head>\n"
                                   "<body bgcolor=#CFC4E1 link=#5000A0>\n"

                                       "<h1>Liste des employes</h1>"



                                       "<table border=1 cellspacing=0 cellpadding=2>\n";


                           // headers
                               out << "<thead><tr bgcolor=#f0f0f0>";
                               for (int column = 0; column < columnCount; column++)
                                   if (!ui->tableView_4->isColumnHidden(column))
                                       out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                               out << "</tr></thead>\n";
                               // data table
                                  for (int row = 0; row < rowCount; row++) {
                                      out << "<tr>";
                                      for (int column = 0; column < columnCount; column++) {
                                          if (!ui->tableView_4->isColumnHidden(column)) {
                                              QString data = ui->tableView_4->model()->data(ui->tableView_4->model()->index(row, column)).toString().simplified();
                                              out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                          }
                                      }
                                      out << "</tr>\n";
                                  }
                                  out <<  "</table>\n"
                                      "</body>\n"
                                      "</html>\n";

                                  QTextDocument *document = new QTextDocument();
                                  document->setHtml(strStream);

                                  QPrinter printer;

                                  QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                                  if (dialog->exec() == QDialog::Accepted) {
                                      document->print(&printer);
                               }

}

void MainWindow::on_pushButton_23_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    ui->stackedWidget->setCurrentIndex(5);
    ui->stackedWidget->setCurrentIndex(3);

}

void MainWindow::on_pushButton_22_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    ui->stackedWidget->setCurrentIndex(6);
    ui->stackedWidget->setCurrentIndex(3);

}

void MainWindow::on_pushButton_authentification_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->setCurrentIndex(2);

}

void MainWindow::on_pushButton_3_valider_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    clients C(ui->lineEdit_3->text(),ui->lineEdit_5->text(),ui->dateEdit->text(),ui->lineEdit_6->text().toInt(),ui->lineEdit_22->text());
   bool test1 = C.ajouterC();
    C.ajouterC();
    if (test1)
    {
          ui->tableView->setModel(tabC.afficherC());
        QMessageBox::information(nullptr,QObject::tr("Ajout !"),
                             QObject::tr("Le Client a bien été ajouté"),
                             QMessageBox::Ok);}
    else{

    QMessageBox::critical(nullptr,QObject::tr("Erreur d'ajout"),
                            QObject::tr("Le Client n'a pas pu etre ajouté"),
                            QMessageBox::Cancel);}
}

void MainWindow::on_pushButton_8_modifier_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    bool  test = tabC.modifierC(ui->lineEdit_19->text()) ;
           if (test)
           {
                 ui->tableView->setModel(tabC.afficherC());
               QMessageBox::information(nullptr,QObject::tr("OK"),
                                    QObject::tr("modification effectuée"),
                                    QMessageBox::Ok);}
           else{
           QMessageBox::critical(nullptr,QObject::tr("Erreur de modification"),
                                   QObject::tr("modification non effectuée"),
                                   QMessageBox::Cancel);}
}

void MainWindow::on_pushButton_4_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
           player->setVolume(100);
           player->play();

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
}

void MainWindow::on_pushButton_7_supprimer_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    bool test=tabC.supprimerC( ui->lineEdit_16->text().toInt());
        if (test)
        {
              ui->tableView->setModel(tabC.afficherC());
            QMessageBox::information(nullptr,QObject::tr("Supression !"),
                                 QObject::tr("supression effectuée"),
                                 QMessageBox::Ok);}
        else{

        QMessageBox::critical(nullptr,QObject::tr("Erreur de supression"),
                                QObject::tr("supression non effectuée"),
                                QMessageBox::Cancel);}
}

void MainWindow::on_comboBox_modif_client_currentIndexChanged(int index)
{
     ui->comboBox_modif_client->currentText();
}

void MainWindow::on_comboBox_3_recherche_client_currentIndexChanged(int index)
{

    ui->comboBox_3_recherche_client->currentText();
}

void MainWindow::on_pushButton_triDESC_clicked()
{
    ui->tableView->setModel(tabC.trierCdesc());

    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
           player->setVolume(100);
           player->play();

}

void MainWindow::on_pushButton_trieASC_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    ui->tableView->setModel(tabC.trierC());
}

void MainWindow::on_pushButton_camClients_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
           player->setVolume(100);
           player->play();


    Camera= new Widget(this);
    Camera->show();
}

void MainWindow::on_pushButton_12_clicked()
{

    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    stat_clients=new statistique_clients(this);
    stat_clients->show();
}

void MainWindow::on_pushButton_val_film_clicked()
{

    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
           player->setVolume(100);
           player->play();

film f(ui->lineEdit->text(),
       ui->dateEdit_2->text(),
       ui->lineEdit_8->text(),
       ui->lineEdit_nomrea->text(),
       ui->lineEdit_2->text());
bool test = f.ajouter();
if (test)
{
   ui->tableView_2->setModel(tabf.afficher());
 QMessageBox::information(nullptr,QObject::tr("Ajout !"),
                      QObject::tr("Le Film a bien été ajouté"),
                      QMessageBox::Ok);}
else{

QMessageBox::critical(nullptr,QObject::tr("Erreur d'ajout"),
                     QObject::tr("Le Film n'a pas pu etre ajouté"),
                     QMessageBox::Cancel);}

}

void MainWindow::on_pushButton_6_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    bool test=tabf.supprimer( ui->lineEdit_10->text());
        if (test)
        {
              ui->tableView_2->setModel(tabf.afficher());
            QMessageBox::information(nullptr,QObject::tr("Supression !"),
                                 QObject::tr("supression effectuée"),
                                 QMessageBox::Ok);}
        else{

        QMessageBox::critical(nullptr,QObject::tr("Erreur de supression"),
                                QObject::tr("supression non effectuée"),
                                QMessageBox::Cancel);}


}

void MainWindow::on_pushButton_5_clicked()
{
    /*sound*/
           QMediaPlayer *player = new QMediaPlayer;

           player->setMedia(QUrl::fromLocalFile("C:\\Users\\user1\\Documents\\integration_final\\button-8.mp3"));
           player->setVolume(100);
           player->play();

    bool  test = tabf.modifier(ui->comboBox_2_modif_film->currentText(),
                               ui->lineEdit_12->text(),
                               ui->lineEdit_13->text(),
                               ui->lineEdit_14->text(),
                               ui->lineEdit_15->text()) ;
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
