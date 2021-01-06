#include "connexion.h"

connexion::connexion()
{

}
bool connexion::create_cnx(){

    bool test=false;
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("projet");
    db.setUserName("system");
    db.setPassword("system");
    if(db.open())
        test=true;
    return test;
}
