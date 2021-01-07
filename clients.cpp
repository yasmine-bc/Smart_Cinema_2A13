#include "clients.h"
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
Clients::Clients()
{

}

Clients::~Clients()
{

}

Clients::Clients(QString n,QString p,QString d,int pts,QString reduc)
{
  nom=n;
  prenom=p;
  date_naissance=d;
  carte_fidelite=pts;
  reduction=reduc;

}

bool Clients::ajouterC()
{
    QSqlQuery q;


    q.prepare("INSERT INTO CLIENT (nom,prenom,date_naissance,carte_fidelite,reduction) "
                  "VALUES (:nom,:prenom,:date_naissance,:carte_fidelite,:reduction)");
    q.bindValue(":nom",nom);
    q.bindValue(":prenom",prenom);
    q.bindValue(":date_naissance",date_naissance);
    q.bindValue(":carte_fidelite",carte_fidelite);
    q.bindValue(":reduction",reduction);

    return q.exec();
}

QSqlQueryModel * Clients::afficherC()
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("select *from client");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_naissance"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("carte_fidelite"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("reduction"));

    return model;
}

bool Clients::supprimerC(int carte)
{
    QSqlQuery q;
    q.prepare("Delete from client where carte_fidelite = :carte_fidelite");
    q.bindValue(":carte_fidelite",carte);
    return    q.exec();
}

QSqlQueryModel * Clients::afficher_ComboBox2()
{
    QSqlQueryModel * m= new QSqlQueryModel();

    m->setQuery("select * from CLIENT");
    m->setHeaderData(0, Qt::Horizontal, QObject::tr("carte_fidelite"));

    return m;
}

bool Clients::modifierC(QString redu)
{
    QSqlQuery q;
    //QString idc=QString::number(carte);
    q.prepare("UPDATE Client SET reduction= :reduction where nom= :nom ");

    q.bindValue(":reduction", redu);

       return    q.exec();
}

bool Clients::rechercheC(int carte)
{
    QSqlQuery q;
             QString idc=QString::number(carte);
             q.prepare("Select * from client where carte_fidelite= :carte_fidelite");//verifier avec la base
             q.bindValue(":carte_fidelite", idc);
             q.exec();
              QSqlQueryModel * model = new QSqlQueryModel();
            model->setQuery(q);
            if(model->rowCount() == 0){ return false;}//comparer avc les colonnes
         return  true;
}

QSqlQueryModel * Clients::trierC()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from client order by carte_fidelite  ASC");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("prenom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_de_naisssance"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("carte_fidelite"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("reduction"));

        return model;
}

QSqlQueryModel * Clients::trierCdesc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from client order by carte_fidelite  DESC");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("prenom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_de_naisssance"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("carte_fidelite"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("reduction"));

        return model;
}
