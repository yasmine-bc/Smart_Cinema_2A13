#ifndef PROFIL_H
#define PROFIL_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QPainter>
#include<QPdfWriter>
#include<QSystemTrayIcon>

class profil
{
    QString NOM_UTILI;
    QString MOT_DE_PASSE;
public:
    profil();
    profil(QString,QString);
           //QString get_NOM_UTILI(){return NOM_UTILI;}
          // QString get_MOT_DE_PASSE(){return MOT_DE_PASSE;}


         QSqlQueryModel * afficher();
           bool ajouter();
           bool supprimer(QString NOM_UTILI);
           bool modifier(QString, QString);
           void HISTORIQUE_PDF();
          QSqlQueryModel *mot_de_passe(const QString &aux1);

};

#endif // PROFIL_H
