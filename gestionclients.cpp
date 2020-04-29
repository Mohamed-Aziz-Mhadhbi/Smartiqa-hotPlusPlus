#include "gestionclients.h"
#include "ui_gestionclients.h"
#include "client.h"
#include "avis.h"
#include "smtp.h"
#include <QMessageBox>
#include <QComboBox>
#include <QTextStream>
#include <QPixmap>
#include <QDebug>
#include"QMessageBox"
#include<QPropertyAnimation>
#include<random>
#include"QPainter"
#include"QFont"
#include"QPen"
#include"QPdfWriter"
#include"QTextDocumentWriter"
#include"QDesktopServices"
#include"QtPrintSupport/QPrinter"
#include <QPropertyAnimation>
#include <QTableWidget>
#include <QFile>
#include <popup.h>

Gestionclients::Gestionclients(QWidget *parent):

    QMainWindow(parent),
       ui(new Ui::Gestionclients)
   {
    ui->setupUi(this);
   ui->tabclient->setModel(tmpclient.afficher());
   ui->tableavis->setModel(tmpavis.afficher());
   ui->idclient->setModel(a.shownumavis());
   QPixmap pic("C:/Users/infoMix/Desktop/imen/b.jpeg");
              ui->label_13->setPixmap(pic);
              ui->label_14->setPixmap(pic);
              popUp = new PopUp();
              popUp->setPopupText("Welcome to Hot Plus Plus");
              popUp->show();

}
Gestionclients::~Gestionclients()
{
    delete ui;
}


void Gestionclients::initialiser()
{
                ui->lineEdit_idClient->clear();
             ui->lineEdit_nom->clear();
             ui->lineEdit_prenom->clear();
             ui->lineEdit_email->clear();
            ui->lineEdit_num->clear();
}
void Gestionclients::init()
{
              ui->num->clear();
             ui->idclient->clear();
             ui->dateavis->clear();
             ui->etat_2->clear();

}

// ajouter client

void Gestionclients::on_pushButton_12_clicked()
{
  // Client p;
       QTableWidgetItem *idClient =new QTableWidgetItem();
        QTableWidgetItem *nom =new QTableWidgetItem();
        QTableWidgetItem *prenom =new QTableWidgetItem();
        QTableWidgetItem *email =new QTableWidgetItem();
        QTableWidgetItem *numero =new QTableWidgetItem();


        idClient->setText(ui->lineEdit_idClient->text());
        nom->setText(ui->lineEdit_nom->text());
        prenom->setText(ui->lineEdit_prenom->text());
        email->setText(ui->lineEdit_email->text());
        numero->setText(ui->lineEdit_num->text());

        QString ic=ui->lineEdit_idClient->text();
        QString nomm= ui->lineEdit_nom->text();
        QString prenomm= ui->lineEdit_prenom->text();
        QString em= ui->lineEdit_email->text();
        QString nu =ui->lineEdit_num->text();
        Client c (ic,nomm,prenomm,em,nu);


         bool test=c.ajouter(c);
        ui->tabclient->sortByColumn(0,Qt::AscendingOrder);
         if (test)
         { ui->tabclient->setModel(tmpclient.afficher());//refresh

        }

        if(c.verif_email(em)==false){
            popUp = new PopUp();
            popUp->setPopupText("verifiez le champ email ");
            popUp->show();

         }else if(c.verif_id(ic)==false){
            popUp = new PopUp();
            popUp->setPopupText("ID doit contenir 8 chiffres ! ");
            popUp->show();

         }else if(nomm==""){
            popUp = new PopUp();
            popUp->setPopupText(" veuillez remplir le champ nom ! ");
            popUp->show();

         }else if(prenomm==""){
            popUp = new PopUp();
            popUp->setPopupText("veuillez remplir le champ prenom ! ");
            popUp->show();

        }else if(nu==""){
           popUp = new PopUp();
           popUp->setPopupText("veuillez remplir le champ num! ");
           popUp->show();
         }
         else{
            QMessageBox::information(nullptr, QObject::tr("ajouter un client"),
                              QObject::tr(" client ajoute .\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
       initialiser();
        int inserROW = ui->tabclient->rowCount();
        ui->tabclient->insertRow(inserROW);
        ui->tabclient->setItem(inserROW,0,idClient);
        ui->tabclient->setItem(inserROW,1,nom);
        ui->tabclient->setItem(inserROW,2,prenom);
        ui->tabclient->setItem(inserROW,3,email);
        ui->tabclient->setItem(inserROW,4,numero);
        QFile file("C:\\Users\\infoMix\\Desktop\\imen\\Historique1.txt");
                    if (!file.open(QIODevice::WriteOnly | QIODevice::Append |QIODevice::Text))
                        return;
                    QTextStream cout(&file);
                    QString message2="\n L'historique des clients à ajouter :"+ic+" "+nomm+" "+prenomm+" "+em+" "+nu;
                    cout << message2;
        }
}

//supprimer client

void Gestionclients::on_pb_supprimer_clicked()
{
    ui->tabclient->removeRow(ui->tabclient->currentRow());
}
//modifier client

void Gestionclients::on_pushButton_6_clicked()
{
    QString idClient = ui->lineEdit_idClient->text();
        QString nom = ui->lineEdit_nom->text();
        QString prenom =ui->lineEdit_prenom->text();
        QString  email = ui->lineEdit_email->text();
         QString  num = ui->lineEdit_num->text();

         Client c (idClient,nom,prenom,email,num);


          bool test=c.modifier(c);

          if (test)
          { ui->tabclient->setModel(tmpclient.afficher());//refresh
          QMessageBox::information(nullptr, QObject::tr("modifier un client"),
                            QObject::tr(" client modifie .\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
         }
        int currentRow = ui->tabclient->currentRow();
        ui->tabclient->item(currentRow,0)->setText(idClient);
        ui->tabclient->item(currentRow,1)->setText(nom);
        ui->tabclient->item(currentRow,2)->setText(prenom);
        ui->tabclient->item(currentRow,3)->setText(email);
        ui->tabclient->item(currentRow,4)->setText(num);
        initialiser();
}



//trier client

void Gestionclients::on_pushButton_3_clicked()
{   Client cc;
    QSqlQueryModel * p=cc.tri();
   // ui->tabclient->setModel(tmpclient.tri());
    ui->tabclient->setModel(p);
     ui->tabclient->sortByColumn(0,Qt::AscendingOrder);

}

//rechercher client

void Gestionclients::on_pushButton_2_clicked()
{
    QString nom =ui->idClient2_2->text();

    Client cc;



   /*  if (test)

     {  ui->tabclient->findItems(nom,Qt::MatchContains);
         QMessageBox::information(nullptr, QObject::tr("Rechercher un client"),
                           QObject::tr(" client existe  .\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
     else

     QMessageBox::critical(nullptr, QObject::tr("Rechercher un client"),
                 QObject::tr("Erreur !.\n"
                             "essayez une autre fois !"), QMessageBox::Retry);*/
}


//actualiser

void Gestionclients::on_pushButton_13_clicked()
{
    int i;
      ui->tabclient->setModel(c.afficher());
      qDebug()<<ui->tabclient->model()->rowCount();
      for (i=0;i<ui->tabclient->model()->rowCount();i++)
      {
      ui->tabclient->model()->index(i,0).data().toString();


      }
}


//Avis


 //ajouter avis

void Gestionclients::on_pushButton_4_clicked()
{

   //Avis n;
    QTableWidgetItem *num =new QTableWidgetItem();
    QTableWidgetItem *idClient =new QTableWidgetItem();
    QTableWidgetItem *dateavis =new QTableWidgetItem();
    QTableWidgetItem *etat =new QTableWidgetItem();

    num->setText(ui->num->text());
    idClient->setText(ui->idclient->currentText());
    dateavis->setText(ui->dateavis->text());
    etat->setText(ui->etat_2->text());


           QString numm= ui->num->text();
           QString id=ui->idclient->currentText();
           QString da= ui->dateavis->text();
           QString et =ui->etat_2->text();
           Avis a (numm,id,da,et);


           bool test=a.ajouter(a);
          ui->tableavis->sortByColumn(0,Qt::AscendingOrder);
           if (test)
           { ui->tableavis->setModel(tmpavis.afficher());//refresh

            }
             if(a.verif_id(id)==false){
               popUp = new PopUp();
               popUp->setPopupText("ID doit contenir 8 chiffres ! ");
               popUp->show();


           }else if(a.verif_num(numm)==false){
              popUp = new PopUp();
              popUp->setPopupText("num  doit contenir 8 chiffres ! ");
              popUp->show();


            }else if(da==""){
               popUp = new PopUp();
               popUp->setPopupText(" veuillez remplir le champ date ! ");
               popUp->show();


           }else if(et==""){
              popUp = new PopUp();
              popUp->setPopupText("veuillez remplir le champ etat! ");
              popUp->show();
            }
            else {
               QMessageBox::information(nullptr, QObject::tr("ajouter un avis"),
                                 QObject::tr(" avis ajoute .\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

     init();
    int inserROW = ui->tableavis->rowCount();
    ui->tableavis->insertRow(inserROW);
    ui->tableavis->setItem(inserROW,0,num);
    ui->tableavis->setItem(inserROW,1,idClient);
    ui->tableavis->setItem(inserROW,2,dateavis);
    ui->tableavis->setItem(inserROW,3,etat);
    QFile file("C:\\Users\\infoMix\\Desktop\\imen\\Historique2.txt");
                        if (!file.open(QIODevice::WriteOnly | QIODevice::Append |QIODevice::Text))
                            return;
                        QTextStream cout(&file);
                        QString message2="\n L'historique des avis"
                                         " à ajouter :"+numm+" "+id+" "+da+" "+et+" ";
                        cout << message2;
            }

}

 //tri avis

void Gestionclients::on_pushButton_16_clicked()
{
    Avis aa;
       QSqlQueryModel * a=aa.tri();
       ui->tableavis->setModel(tmpavis.tri());
      ui->tableavis->sortByColumn(0,Qt::AscendingOrder);


}

//modifier avis

void Gestionclients::on_pushButton_8_clicked()
{


        QString num = ui->num->text();
        QString idClient = ui->idclient->currentText();
        QString dateavis =ui->dateavis->text();
        QString  etat = ui->etat_2->text();

        int currentRow = ui->tableavis->currentRow();
        ui->tableavis->item(currentRow,0)->setText(num);
        ui->tableavis->item(currentRow,1)->setText(idClient);
        ui->tableavis->item(currentRow,2)->setText(dateavis);
        ui->tableavis->item(currentRow,3)->setText(etat);
        init();

}
//supprimer avis

void Gestionclients::on_pushButton_10_clicked()
{
  ui->tableavis->removeRow(ui->tableavis->currentRow());
}

//actualiser
void Gestionclients::on_pushButton_15_clicked()
{
    int i;
      ui->tableavis->setModel(a.afficher());
      qDebug()<<ui->tableavis->model()->rowCount();
      for (i=0;i<ui->tableavis->model()->rowCount();i++)
      {
    //  ui->tableavis->model()->index(i,0).data().toString();

      ui->idclient->addItem(ui->tableavis->model()->index(i,0).data().toString());
      }
}

//recherer  avis
void Gestionclients::on_pushButton_11_clicked()
{
    QString numAviss=ui->lineEdit_4->text();  /*->currentText();*/



        bool test=tmpavis.rechercher(numAviss);
        if (test)
        { ui->tableavis->setModel(tmpavis.rechercher(numAviss));
        QMessageBox::information(nullptr, QObject::tr("Rechercher un avis "),
                          QObject::tr("Avis trouvé "), QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Recherche un avis"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}

//pdf

void Gestionclients::on_pushButton_5_clicked()
{
    QPrinter printer;

        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName("C:/Users/infoMix/Desktop/imen/hot++.pdf");

       QPainter painter;
       painter.begin(&printer);
       QFont font;
        QString idClient = ui->lineEdit_idClient->text();
        QString nom = ui->lineEdit_nom->text();
        QString prenom = ui->lineEdit_prenom->text();
         QString email = ui->lineEdit_email->text();
         int numero = ui->lineEdit_num->text().toInt();

       font.setPixelSize(35);
       painter.setFont(font);
       painter.setPen(Qt::blue);

       painter.drawText(100,300,"idClient :");

       painter.drawText(100,400,"nom :");

       painter.drawText(100,500,"prenom :");

       painter.drawText(100,600,"email:");

       painter.drawText(100,700,"numero :");

       font.setPixelSize(22);
       painter.setFont(font);
       painter.setPen(Qt::green);
        QString numm= QString::number(numero);
       painter.drawText(500,300,idClient);
       painter.drawText(500,400,nom);
       painter.drawText(500,500,prenom);
       painter.drawText(500,600,email);
       painter.drawText(500,700,numm);
       painter.end();

}

void Gestionclients::on_pushButton_7_clicked()
{
    QPrinter printer;

        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName("C:/Users/infoMix/Desktop/imen/hot++.pdf");

       QPainter painter;
       painter.begin(&printer);
       QFont font;
       QString num = ui->num->text();
        QString idClient = ui->lineEdit_idClient->text();

        QString dateavis= ui->dateavis->text();
         QString etat = ui->etat_2->text();

       font.setPixelSize(35);
       painter.setFont(font);
       painter.setPen(Qt::blue);

       painter.drawText(100,300,"num :");

       painter.drawText(100,400,"idClient :");

       painter.drawText(100,500,"dateavis:");

       painter.drawText(100,600,"etat:");



       font.setPixelSize(22);
       painter.setFont(font);
       painter.setPen(Qt::green);
      //  QString numm= QString::number(numero);
       painter.drawText(500,300,num);
       painter.drawText(500,400,idClient);
       painter.drawText(500,500,dateavis);
       painter.drawText(500,600,etat);

       painter.end();

}



void Gestionclients::on_pushButton_clicked()
{
    QFile file ("C:\\Users\\infoMix\\Desktop\\imen\\Historique1.txt");
            if (!file.open(QIODevice::ReadOnly))
            {
                QMessageBox::information(0,"info",file.errorString());
            }
            QTextStream in (&file);
            ui->textBrowser->setText(in.readAll());
}

void Gestionclients::on_pushButton_9_clicked()
{
    QFile file ("C:\\Users\\infoMix\\Desktop\\imen\\Historique2.txt");
            if (!file.open(QIODevice::ReadOnly))
            {
                QMessageBox::information(0,"info",file.errorString());
            }
            QTextStream in (&file);
            ui->textBrowser_2->setText(in.readAll());
}


void Gestionclients::on_pushButton_14_clicked()
{
    Smtp* smtp = new Smtp("hotsmartiqua@gmail.com", "smartiquahot++", "smtp.gmail.com", 465);
                           connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
                               smtp->sendMail("hotsmartiqua@gmail.com", "imen.chakroun@esprit.tn" , "Smart Rapid Hotel, Nouveau Evenement!","Congrats!");
}
