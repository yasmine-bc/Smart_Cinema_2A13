#ifndef STATISTIQUE_CLIENTS_H
#define STATISTIQUE_CLIENTS_H


#include <QDialog>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QWidget>
#include <QList>

namespace Ui {
class statistique_clients;
}

class statistique_clients : public QDialog
{
    Q_OBJECT

public:
    explicit statistique_clients(QWidget *parent = nullptr);
    ~statistique_clients();
    QList<qreal> stat_clients();
   // QList<QString> stat_clients_nom();

private:
    Ui::statistique_clients *ui;
  //  QList<qreal> stat_clients();
};

#endif // STATISTIQUE_CLIENTS_H
