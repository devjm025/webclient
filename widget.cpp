#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //signals
    //socket_.disconnected();// it is signal function, we have to make
    QObject::connect(&socket_,&QAbstractSocket::connected, this, &Widget::doConnected);// fuction pointer
    // if signal occurs, print Message (connect slot func and signal)
    QObject::connect(&socket_,&QAbstractSocket::disconnected, this, &Widget::doDisconnected); // slot func
    QObject::connect(&socket_,&QAbstractSocket::readyRead, this, &Widget::doreadyRead); // slot func


}

Widget::~Widget()
{
    delete ui;
}

void Widget::doConnected(){
    ui->pteMessage->insertPlainText("Connected");// It call when we connected
}

void Widget::doDisconnected(){
    ui->pteMessage->insertPlainText("Disconnected");
}

void Widget::doreadyRead(){
    ui->pteMessage->insertPlainText(socket_.readAll());
}

void Widget::on_pbConnect_clicked()
{
    // to use components in ui, we have approach it as ui ->
    // toUShort : unsigned 2byte : port
    //socket_.connectToHost(ui->leHost->text(),ui->lePort->text().toUShort()); // udp, Qsocket
    socket_.connectToHostEncrypted(ui->leHost->text(),ui->lePort->text().toUShort()); // QsslSocket using
}


void Widget::on_pbDisconnect_clicked()
{
    socket_.close();
}


void Widget::on_pbSend_clicked()
{
    socket_.write(ui->pteSend->toPlainText().toUtf8());//Qbyte array send(qstring -> qbyte : toUtf8)
}

