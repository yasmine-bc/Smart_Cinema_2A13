#ifndef STATISTIQUE_FILM_H
#define STATISTIQUE_FILM_H

#include <QWidget>
#include <QDialog>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QWidget>
#include <QList>


namespace Ui {
class statistique_film;
}

class statistique_film : public QWidget
{
    Q_OBJECT

public:
    explicit statistique_film(QWidget *parent = nullptr);
    ~statistique_film();

private:
    Ui::statistique_film *ui;
    // QList<qreal> stat_films();
     QList<qreal> stat_films();
    QList<QString> stat_films_nom();
};

#endif // STATISTIQUE_FILM_H
