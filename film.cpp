#include "film.h"
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>

Film::Film()
{

}

Film::Film(QString t,QString d,QString c,QString n, QString du)
{
   titre= t;
   date_de_sortie=d;
   categorie=c;
   nom_realisateur= n;
   duree=du;
}

Film::~Film()
{

}

bool Film::ajouter() // conrole de saisie sur l'ajout et sur le type(date etc)
{
    QSqlQuery q;


    q.prepare("INSERT INTO FILM(titre,date_de_sortie,categorie,nom_realisateur,duree) "
                  "VALUES (:titre,:date_de_sortie,:categorie,:nom_realisateur,:duree)");
    q.bindValue(":titre",titre);
    q.bindValue(":date_de_sortie",date_de_sortie);
    q.bindValue(":categorie",categorie);
    q.bindValue(":nom_realisateur",nom_realisateur);
    q.bindValue(":duree",duree);

    return q.exec();
}

QSqlQueryModel * Film:: afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("select * from film");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("titre"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date_de_sortie"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("categorie"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("nom_realisateur"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("duree"));

    return model;

}

QSqlQueryModel * Film::afficher_ComboBox()
{
    QSqlQueryModel * m= new QSqlQueryModel();

    m->setQuery("select * from FILM");
    m->setHeaderData(0, Qt::Horizontal, QObject::tr("TITRE"));

    return m;
}

bool Film::supprimer(QString titre)
{

    QSqlQuery q;
    q.prepare("Delete from film where titre = :titre ");
    q.bindValue(":titre",titre);
    return    q.exec();
}

bool Film::modifier(QString titre, QString date_de_sortie, QString categorie,QString nom_realisateur, QString duree)
{

    QSqlQuery q;

    q.prepare("UPDATE Film SET date_de_sortie= :date_de_sortie, categorie= :categorie, nom_realisateur= :nom_realisateur, duree= :duree where titre= :titre ");
    q.bindValue(":titre", titre);
    q.bindValue(":date_de_sortie", date_de_sortie);
    q.bindValue(":categorie",categorie);
    q.bindValue(":nom_realisateur",nom_realisateur);
    q.bindValue(":duree",duree);
       return    q.exec();

}

bool Film::recherche(QString titre)
{
    QSqlQuery q;
             q.prepare("Select * from Film where titre= :titre");//verifier avec la base
             q.bindValue(":titre", titre);
             q.exec();
              QSqlQueryModel * model = new QSqlQueryModel();
            model->setQuery(q);
            if(model->rowCount() == 0){ return false;}//comparer avc les colonnes
         return  true;
}

QSqlQueryModel * Film::trier()
{

   QSqlQueryModel * model= new QSqlQueryModel();
       model->setQuery("select * from film order by titre  ASC");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("titre"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("date_de_sortie"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("categorie"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("nom_realisateur"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("duree"));

       return model;
}


QSqlQueryModel * Film::trierdesc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from film order by titre  DESC");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("titre"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("date_de_sortie"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("categorie"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("nom_realisateur"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("duree"));

        return model;
}

