#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    checkState();

    //signals
    QObject::connect(&tcp_socket_,&QAbstractSocket::connected, this, &Widget::doConnected);// fuction pointer
    // if signal occurs, print Message (connect slot func and signal)
    QObject::connect(&tcp_socket_,&QAbstractSocket::disconnected, this, &Widget::doDisconnected); // slot func
    QObject::connect(&tcp_socket_,&QAbstractSocket::readyRead, this, &Widget::doreadyRead); // slot func

    QObject::connect(&ssl_socket_,&QAbstractSocket::connected, this, &Widget::doConnected);// fuction pointer
    // if signal occurs, print Message (connect slot func and signal)
    QObject::connect(&ssl_socket_,&QAbstractSocket::disconnected, this, &Widget::doDisconnected); // slot func
    QObject::connect(&ssl_socket_,&QAbstractSocket::readyRead, this, &Widget::doreadyRead); // slot func


}

Widget::~Widget()
{
    delete ui;
}

void Widget::doConnected(){
    ui->pteMessage->insertPlainText("Connected");// It call when we connected
    checkState();
}

void Widget::doDisconnected(){
    ui->pteMessage->insertPlainText("Disconnected");
    checkState();
}

void Widget::doreadyRead(){
    if(ui->cbTCP->isChecked())
        ui->pteMessage->insertPlainText(tcp_socket_.readAll());
    else
        ui->pteMessage->insertPlainText(ssl_socket_.readAll());
}

void Widget::checkState(){
    if(ui->cbTCP->isChecked())
    {
        ui->pbDisconnect->setEnabled(tcp_socket_.state() == QAbstractSocket::ConnectedState);
        ui->pbConnect->setEnabled(tcp_socket_.state() != QAbstractSocket::ConnectedState);
        ui->cbTCP->setEnabled(tcp_socket_.state() != QAbstractSocket::ConnectedState);
        ui->cbSSL->setEnabled(tcp_socket_.state() != QAbstractSocket::ConnectedState);
    }
    else
    {
        ui->pbDisconnect->setEnabled(ssl_socket_.state() == QAbstractSocket::ConnectedState);
        ui->pbConnect->setEnabled(ssl_socket_.state() != QAbstractSocket::ConnectedState);
        ui->cbTCP->setEnabled(ssl_socket_.state() != QAbstractSocket::ConnectedState);
        ui->cbSSL->setEnabled(ssl_socket_.state() != QAbstractSocket::ConnectedState);
    }


}

void Widget::on_pbConnect_clicked()
{
    // to use components in ui, we have approach it as ui ->
    // toUShort : unsigned 2byte : port
    if(ui->cbTCP->isChecked())
        tcp_socket_.connectToHost(ui->leHost->text(),ui->lePort->text().toUShort()); // udp, Qsocket
    else
        ssl_socket_.connectToHostEncrypted(ui->leHost->text(),ui->lePort->text().toUShort()); // QsslSocket using
}


void Widget::on_pbDisconnect_clicked()
{
    if(ui->cbTCP->isChecked())
        tcp_socket_.close();
    else
        ssl_socket_.close();
}


void Widget::on_pbSend_clicked()
{
    if(ui->cbTCP->isChecked())
        tcp_socket_.write(ui->pteSend->toPlainText().toUtf8());//Qbyte array send(qstring -> qbyte : toUtf8)
    else
        ssl_socket_.write(ui->pteSend->toPlainText().toUtf8());
}

void Widget::on_cbSSL_clicked(bool checked)
{
    if(checked)
        ui->lePort->setText("443");
    else
        ui->lePort->setText("0");
}


void Widget::on_cbTCP_clicked(bool checked)
{
    if(checked)
        ui->lePort->setText("80");
    else
        ui->lePort->setText("0");
}

