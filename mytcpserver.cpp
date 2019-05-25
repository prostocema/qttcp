#include "mytcpserver.h"
#include <QtDebug>
#include <QCoreApplication>
#include "QString"
#include <string>
#include "function.h"

using namespace std;

#pragma warning(disable:4996)

MyTcpServer::~MyTcpServer()
{
    foreach(int id, sclients.keys()){
        QTextStream os(sclients[id]);
        sclients[id]->close();
        sclients.remove(id);
    }
    server_status = 0;
    mTcpServer->close();
}

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent) {

    mTcpServer = new QTcpServer(this);

    connect(mTcpServer, &QTcpServer::newConnection,this, &MyTcpServer::slotNewConnection);
    if(!mTcpServer->listen(QHostAddress::Any, 33333))

    {
        qDebug() << "server is not started" ;
    }
    else {
        qDebug() << "server Rabotaet" ;
        server_status=1;
    }


}

void MyTcpServer::slotNewConnection()
{
//    if(server_status==1)
//    {
//        mTcpSocket = mTcpServer->nextPendingConnection();
//        mTcpSocket->write("Hello, world! I am echo server!\r\n");
//        connect(mTcpSocket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
//        connect(mTcpSocket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);

//    }

    if(server_status==1){
            QTcpSocket* clientSocket=mTcpServer->nextPendingConnection();
            int id=(int)clientSocket->socketDescriptor();
            sclients[id]=clientSocket;
            connect(sclients[id], &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
            connect(sclients[id], &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);
            currentusers+=1;
            qDebug() << "User join" ;
            qDebug() << "Current Users :" << currentusers ;

        }
}

void MyTcpServer::slotServerRead()
{
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    int id=(int)clientSocket->socketDescriptor();
   // QByteArray array = clientSocket->readAll();
//    qDebug() << array;
    if(clientSocket->bytesAvailable()>0)
    {
        QByteArray array = clientSocket->readAll();
        //qDebug()<<array;
        string log = "admin";
        string pass = "123";
        string message;
        message = array.toStdString();
        qDebug() << QString::fromStdString(message);
        //<name_of_function>&<log>&<pass>
        int pos = message.find("&");
        message.erase(0,pos+1);

        //find
        pos = message.find("&");
        log = message.substr(0, pos);
        message.erase(0,pos+1);

        pos = message.find("&");
        pass = message.substr(0, pos);
        message.erase(0,pos+1);

        pass.pop_back();
        pass.pop_back();

        array.clear();
        array.append(authorize(log,pass));

       clientSocket->write(array);

    }
}

void MyTcpServer::slotClientDisconnected()
{
    if(server_status==1){
        QTcpSocket* clientSocket = (QTcpSocket*)sender();
        int id=(int)clientSocket->socketDescriptor();
        clientSocket->close();
        currentusers-=1;
        qDebug() << "User leave" ;
        qDebug() << "Current users:" << currentusers ;
    }
}

















//void MyTcpServer::slotServerRead()
//{
//    while(mTcpSocket->bytesAvailable()>0)
//    {
//        QByteArray array = mTcpSocket->readAll();

//        char s;
//        s=*array.data();
//        if (s=='z')
//            s='a';
//        else if (s=='Z')
//            s='A';
//        else
//            s+=1;
//        array[(array.size()-1)] =s;

//        mTcpSocket->write(array);
//    }
//}

//void MyTcpServer::slotServerRead()
//{
//    while(mTcpSocket->bytesAvailable() > 0 )
//    {

//    QByteArray array = mTcpSocket->readAll();

//    char *a = new char[255];
//    a = array.data();
//    char *ptr1 = nullptr;
//    char *ptr = strtok_s(
//                1," ",&ptr1);
////  char a;
////  a =*array.data();
////  a+=1;
////  array[(array.size()-1)] =*ptr;

//    mTcpSocket->write(ptr);

//    }
//}

//void MyTcpServer::slotClientDisconnected()
//{

//    if(server_status==1){
//        mTcpSocket->close();
//        mTcpServer->close();
//        qDebug() << QString::fromUtf8("Server is stopped!");
//        server_status = 0;
//    }
//}
