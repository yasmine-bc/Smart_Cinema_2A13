#include "statistique_clients.h"
#include "ui_statistique_clients.h"
#include "connexion.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

statistique_clients::statistique_clients(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::statistique_clients)
{
    ui->setupUi(this);
    QPieSeries *series =new QPieSeries ;

        QList<qreal> list= stat_clients();
      //  QList<QString> list2= stat_clients_nom();

            series->append("oui",list[0]);
            series->append("non",list[1]);
        /*for(int i=0 ;i<list.size();i++)
            {
                 series->append(list2[i],list[i]);

            }

*/



            QChart *chart =new QChart;
            chart->addSeries(series);
            chart->setTitle("STATS des clients");
             QChartView *chartview= new QChartView(chart);
             chartview->setParent(ui->horizontalFrame);
}

statistique_clients::~statistique_clients()
{
    delete ui;
}

QList<qreal> statistique_clients::stat_clients()
{
    QList<qreal> list ;
        QSqlQuery query;
        query.prepare("SELECT reduction, count(*) AS counter FROM client GROUP BY reduction ORDER BY reduction");
        query.exec();
        while(query.next())
        {list.append(query.value(1).toInt());}
        return list ;
}
/*
QList<QString> statistique_clients::stat_clients_nom()
{
    QList<QString>  list ;
        QSqlQuery query;
        query.prepare("select promotion,count(promotion) from promotion group by promotion");
        query.exec();
        while(query.next())
        {list.append(query.value(0).toString());}
        return list ;

}*/
