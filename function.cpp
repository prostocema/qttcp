#include "function.h"
#include "QDebug"
using namespace std;

QString authorize(string login, string password){

    QString result;
    if (login == "admin" && password == "123"){
        result = "admin\n";}
    else if (login == "manager" && password == "123")
        result = "manager\n";
    else if (login == "user" && password == "123")
        result = "user\n";
    else
        result = "aut error";
//qDebug() << "alooooo";
    return result;
}
