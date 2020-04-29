#ifndef GESTIONCLIENTS_H
#define GESTIONCLIENTS_H
#include "client.h"
#include "smtp.h"
#include"avis.h"
#include "popup.h"
#include <QMainWindow>
#include <QComboBox>
#include <QPixmap>
#include<QPainter>
#include"QFont"
#include"QPen"
#include<QPrintDialog>
#include"QPdfWriter"
#include"QDesktopServices"
#include"QtPrintSupport/QPrinter"
#include <QPropertyAnimation>


namespace Ui {
class Gestionclients;
}

class Gestionclients: public QMainWindow
{
    Q_OBJECT

public:
    explicit Gestionclients(QWidget *parent = nullptr);
    ~Gestionclients();
private slots:
    void on_pushButton_12_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

   void on_pb_supprimer_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_clicked();
    void initialiser();
   void init();
    void on_pushButton_9_clicked();

    void on_pushButton_14_clicked();

private:
    Ui::Gestionclients *ui;
  Client tmpclient;
  Client c ;
    Avis a ;
    Avis tmpavis;
    PopUp *popUp;
};

#endif // GESTIONCLIENTS_H
