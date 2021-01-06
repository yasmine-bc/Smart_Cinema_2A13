#ifndef FILM_H
#define FILM_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Film
{
    QString titre;
    QString date_de_sortie;
    QString categorie;
    QString nom_realisateur;
    QString duree;
public:
    Film();
    Film(QString,QString,QString,QString,QString);
    ~Film();

    QString getTitre(){return titre;}
    QString getdate_de_sortie() {return date_de_sortie;}
    QString getnom_realisateur() {return nom_realisateur;}
    QString getCategorie() {return categorie;}
    QString getDuree(){return duree;}

    void setTitre(QString t){titre=t;}
    void setdate_de_sortie(QString d){date_de_sortie=d;}
    void setcategorie(QString c){categorie=c;}
    void setnom_realisateur(QString nom){nom_realisateur=nom;}
    void setDuree(QString duree){this->duree=duree;}

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString titre) ;
    bool modifier(QString titre, QString date_de_sortie, QString categorie,QString nom_realisateur, QString duree);

    bool recherche(QString titre);
    static QSqlQueryModel * afficher_ComboBox();
    QSqlQueryModel *trier(); //ascendant
    QSqlQueryModel *trierdesc();

};

#endif // FILM_H
