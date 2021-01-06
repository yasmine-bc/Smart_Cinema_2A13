#include "statistique_film.h"
#include "ui_statistique_film.h"
#include "connexion.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

statistique_film::statistique_film(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistique_film)
{
    ui->setupUi(this);
    QPieSeries *series =new QPieSeries ;

        QList<qreal> list= stat_films();
        QList<QString> list2= stat_films_nom();

        for(int i=0 ;i<list.size();i++)
                    {
                         series->append(list2[i],list[i]);

                    }

         //   series->append("Action",list[0]);
           // series->append("Comedie",list[1]);
           // series->append("Romance",list[2]);




            QChart *chart =new QChart;
            chart->addSeries(series);
            chart->setTitle("STATS des Films");
             QChartView *chartview= new QChartView(chart);
             chartview->setParent(ui->horizontalFrame);

}

statistique_film::~statistique_film()
{
    delete ui;
}

QList<qreal> statistique_film::stat_films()
{
    QList<qreal> list ;
        QSqlQuery query;
        query.prepare("SELECT categorie, count(*) AS counter FROM film GROUP BY categorie ORDER BY categorie");
        query.exec();
        while(query.next())
        {list.append(query.value(1).toInt());}
        return list ;
}
QList<QString> statistique_film::stat_films_nom()
{
    QList<QString>  list ;
        QSqlQuery query;
        query.prepare("SELECT categorie, count(*) AS counter FROM film GROUP BY categorie ORDER BY categorie");
        query.exec();
        while(query.next())
        {list.append(query.value(0).toString());}
        return list ;

}
