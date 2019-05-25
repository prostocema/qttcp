#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <string>

using namespace std;

class MyTcpServer: public QObject
{
    Q_OBJECT
public:

    explicit MyTcpServer(QObject *parent =nullptr);

   ~MyTcpServer();

public slots:
    void slotNewConnection();
    void slotClientDisconnected();
    void slotServerRead();
private:
    QTcpServer * mTcpServer;
    //QTcpSocket * mTcpSocket;
    QMap <int, QTcpSocket*> sclients;
    int server_status;
    int currentusers =0;
};

#endif // MYTCPSERVER_H
