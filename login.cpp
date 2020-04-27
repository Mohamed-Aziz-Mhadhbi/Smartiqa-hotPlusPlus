#include "login.h"
#include "ui_login.h"
#include <QTime>
#include <QTimer>
#include <QProgressBar>
#include <QStatusBar>
#include <QWidget>
#include <QString>
#include <QDebug>
#include <windows.h>
#include "gestion_des_equipements.h"


Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(UpadateTime()));
    timer->start();
}

Login::~Login()
{
    delete ui;
}

void Login::UpadateTime()
{
    ui->time->setText(QTime::currentTime().toString("hh:mm:ss"));
}

void Login::on_checkBox_clicked(bool checked)
{
    if(checked)
    {

        ui->lineEdit_2->setEchoMode(QLineEdit::EchoMode(0));
    }
    else
    {
        ui->lineEdit_2->setEchoMode(QLineEdit::EchoMode(2));
    }
}

void Login::on_pushButton_clicked()
{
    QString identifiant;
    QString mot_de_passe;
    identifiant = ui->lineEdit->text();
    mot_de_passe = ui->lineEdit_2->text();

    if(identifiant=="nour" && mot_de_passe == "1234")
    {
        QProgressBar * _progressBar = new QProgressBar();
        //  QMainWindow * mw = new QMainWindow;
        //  mw->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        //  mw->resize(100, 100);
        //  mw->pos();
        //  mw->show();
        _progressBar->setRange(0, 100);
        _progressBar->setValue(0);
        _progressBar->setTextVisible(true);
        _progressBar->setFormat("Connecting");
        ui->statusbar->addPermanentWidget( _progressBar, 2 );
        for( int i = 0; i<=100; i+=10 ) {
            _progressBar->setValue(i);
            Sleep(50);
        }
        _progressBar->setVisible(false);
        ui->statusbar->showMessage(" Connected.....",1000);
        //here you can change to an other window
        gestion_des_equipements e;
        e.exec();
    }
    else
    {
        ui->statusbar->showMessage(" Login failed . Invalid username or password !!",2000);
    }
}


