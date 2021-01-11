#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class employe
{
    QString nom;
    QString prenom;
    QString ID;
    QString fonction;

    int age;
    int CIN;
public:
    employe();
    employe(QString, QString , int ,  QString,int ,QString);

    int get_age(){return age;}
    int get_CIN() {return CIN;}
        QString get_nom(){return nom;}
        QString get_prenom(){return prenom;}
        QString get_fonction (){return fonction;}
        QString get_ID(){return ID;}


            QSqlQueryModel * afficher();
            bool ajouter();
            bool supprimer(QString ID);
            bool modifier();
            void chercher();
            QSqlQueryModel * rechercher (const QString &aux);
            QSqlQueryModel *  trie(const QString &critere, const QString &mode );


};

#endif // EMPLOYE_H
