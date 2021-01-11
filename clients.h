#ifndef CLIENTS_H
#define CLIENTS_H

#include <QString>
#include <QTime>
#include <QSqlQuery>
#include <QSqlQueryModel>

class clients
{
    QString nom;
    QString prenom;
    QString date_naissance;
    int carte_fidelite;
    QString reduction;

public:
    clients();
    clients(QString,QString,QString,int,QString);
    ~clients();

    QString getNom(){return nom;}
    QString getPrenom() {return prenom;}
    QString getdate_naissance() {return date_naissance;}
    int getCarte() {return carte_fidelite;}
    QString getReduction(){return reduction;}

    void setNom(QString n){nom=n;}
    void setdate_naissance(QString d){date_naissance=d;}
    void setprenom(QString p){prenom=p;}
    void setcarte(int c){carte_fidelite=c;}
    void setReduction(QString r){reduction=r;}

    bool ajouterC();
    QSqlQueryModel * afficherC();
    bool supprimerC(int carte) ;
    bool modifierC(QString redu);

    static QSqlQueryModel * afficher_ComboBox2();
    bool rechercheC(int carte);
    QSqlQueryModel *trierC();
    QSqlQueryModel *trierCdesc();
};

#endif // CLIENTS_H
