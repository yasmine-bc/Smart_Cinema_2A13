#include "employe.h"

employe::employe()
{

}

employe::employe(QString nom, QString prenom, int age,  QString ID,int CIN,QString fonction)
{
    this->nom=nom;
    this->prenom=prenom;
     this->age=age ;
     this->ID=ID;
    this->CIN=CIN;
    this->fonction=fonction;


}


bool employe ::ajouter()
{
    QSqlQuery query;
    QString res1 = QString::number(CIN);
    QString res2 = QString::number(age);
    query.prepare("INSERT INTO EMPLOYE (nom ,prenom,age,ID, CIN,fonction) " "values(:nom, :prenom,:age,:ID,:CIN, :fonction)");

    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":age",res2);
    query.bindValue(":ID",ID);
    query.bindValue(":CIN",res1);
    query.bindValue(":fonction",fonction);


 return query.exec();


}
bool employe::supprimer(QString ID)
{
QSqlQuery query;

query.prepare("Delete from EMPLOYE where ID=:ID ");
query.bindValue(":ID", ID);
return    query.exec();
}
bool employe::modifier()
{

    QSqlQuery query;
        QString res2 = QString::number(age);
        QString res1 = QString::number(CIN);

        query.prepare("Update EMPLOYE set NOM=:nom,PRENOM=:prenom,AGE=:res1, FONCTION=:fonction, CIN =:res2 where ID=:ID");

        query.bindValue(":NOM",nom);
        query.bindValue(":PRENOM",prenom);
        query.bindValue(":AGE",res2);
         query.bindValue(":ID",ID);
         query.bindValue(":CIN",res1);
        query.bindValue(":FONCTION",fonction);

        return       query.exec()  ;
    }
    QSqlQueryModel *employe ::afficher()
    {

       QSqlQueryModel * model1= new QSqlQueryModel();

       model1->setQuery("select NOM,PRENOM,AGE,ID,CIN,FONCTION from EMPLOYE");

       model1->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
       model1->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
       model1->setHeaderData(2, Qt::Horizontal, QObject::tr("AGE"));
       model1->setHeaderData(3, Qt::Horizontal, QObject::tr("ID"));
       model1->setHeaderData(4, Qt::Horizontal, QObject::tr("CIN"));
       model1->setHeaderData(5, Qt::Horizontal, QObject::tr("FONCTION"));



       return  model1;
}
QSqlQueryModel * employe::rechercher (const QString &aux)

{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from EMPLOYE where ((NOM||PRENOM||AGE||ID||CIN||FONCTION) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("AGE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("FONCTION"));

    return model;
}
QSqlQueryModel *  employe::trie(const QString &critere, const QString &mode )
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from EMPLOYE order by "+critere+" "+mode+"");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("AGE"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("CIN"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("FONCTION"));

    return model;
}
