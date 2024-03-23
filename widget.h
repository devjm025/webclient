#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QSslSocket>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QTcpSocket tcp_socket_; // behind member variable, put _
    QSslSocket ssl_socket_; // SSL communication
    //QUdpSocket socket_;
    void checkState();

public slots:
    void doConnected(); // we have to make doConnected func's body in widget.cpp
    void doDisconnected(); // it's slot func
    void doreadyRead();

private slots:
    void on_pbConnect_clicked();

    void on_pbDisconnect_clicked();

    void on_pbSend_clicked();

    void on_cbSSL_clicked(bool checked);

    void on_cbTCP_clicked(bool checked);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
