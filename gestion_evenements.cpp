#include "gestion_evenements.h"
#include "ui_gestion_evenements.h"
#include "evenements.h"

#include "statistiques.h"
#include <QMessageBox>
#include "login.h"
#include "ui_login.h"
#include "smtp.h"
#include "qcustomplot.h"

//#include"statistiques.h"
#include <QRegExpValidator>
#include <QPrinter>
#include <QPrintDialog>
#include <QIntValidator>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QSystemTrayIcon>
#include <QStyledItemDelegate>

#include <QSqlQuery>
#include <QDesktopServices>
#include <QDialog>
//#include "smtp.h"
//#include "qcustomplot.h"

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
#include <QMap>
#include <QVector>
#include <QString>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtWidgets/QGridLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->tablevenement_2->setModel(tmpevenement.afficher());
    ui->tableView_promo->setModel(tmppromotions.afficher_p());



    QSqlQueryModel * model2= new QSqlQueryModel();
        model2->setQuery("select ID from evenement")  ;

        QSqlQuery* qry = new QSqlQuery();
                qry->prepare("Select * from evenement");
                qry->exec();
                connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialiser()
{
    ui->lineEdit_id_2->clear();
        ui->lineEdit_nom_2->clear();
        ui->dateEdit_evenements->clear();
        ui->lineEdit_pourcentage->clear();
       ui->lineEdit_Nom_p->clear();
       ui->lineEdit_ID_promo->clear();
       ui->dateEdit_date_d->clear();
       ui->dateEdit_date_f->clear();

}
void MainWindow::refrech()
{
    QSqlQueryModel * model2= new QSqlQueryModel();
        model2->setQuery("select id  from evenement")  ;

}



void MainWindow::on_on_pb_ajouter_clicked_clicked()
{
    QString id =ui->lineEdit_id_2->text();
QString nom=ui->lineEdit_nom_2->text();
QString date_e= ui->dateEdit_evenements->text();
QString prix=ui->lineEdit_prix->text();
QString duree=ui->timeEdit_time->text();


evenement e(id,nom,date_e,prix,duree);

bool test=e.ajouter();
if(test)
{
ui->tablevenement_2->setModel(tmpevenement.afficher());

}


       if(e.verif_id(id)==false){
            QMessageBox::critical(nullptr, QObject::tr("Ajouter Client"),
                        QObject::tr("Id doit contenir 8 chiffres!\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);




        }else if(nom==""){
            QMessageBox::critical(nullptr, QObject::tr("Ajouter Client"),
                        QObject::tr(" Nom doit contenir 20 caractéres au maximum!\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }




  }
void MainWindow::on_pushButton_3_clicked()
{
    QFile file ("C:/hhhh/llll/historiqueEquipement.txt");
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(0,"info",file.errorString());
        }
        QTextStream in (&file);
        ui->textBrowser->setText(in.readAll());
}


void MainWindow::on_on_pb_supprimer_clicked()
{

    int id =ui->lineEdit_id_2->text().toInt();
    bool test=tmpevenement.supprimer(id);
    initialiser();
    if(test)
  {
  ui->tablevenement_2->setModel(tmpevenement.afficher());


  refrech();
  QMessageBox::information(nullptr, windowTitle(),QObject::tr("Supprimer succés"));
  }
    else
    {
        QMessageBox::information(nullptr, windowTitle(),QObject::tr("Id n'existe pas"));
}
}
void MainWindow::on_on_pb_modifier_clicked()
{


        QString id =ui->lineEdit_id_2->text();
        QString date_e =ui->dateEdit_evenements->text();
        QString nom =ui->lineEdit_nom_2->text();
        QString prix=ui->lineEdit_prix->text();
        QString duree=ui->timeEdit_time->text();


evenement e(id,nom,date_e,prix,duree);

bool test=false;
         if (id>0)test=tmpevenement.modifier(e);
        {
             ui->tablevenement_2->setModel(tmpevenement.afficher());

            QMessageBox::information(this,"evenement supprime","ce evenement a ete modifie");
        }

}




void MainWindow::on_on_pb_actualiser_clicked()
{
    ui->tablevenement_2->setModel(tmpevenement.afficher());
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select code from evenement");



}
void MainWindow::on_on_pb_actualiser_2_clicked()
{
    ui->tableView_promo->setModel(tmppromotions.afficher_p());
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select id from promo");
}


void MainWindow::on_refrech_mod_clicked()
{
    QSqlQueryModel * model2= new QSqlQueryModel();
        model2->setQuery("select id  from evenement")  ;

}

void MainWindow::on_radioButton_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from evenement ORDER BY ID ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID "));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("date"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("duree"));
ui->tablevenement_2->setModel(model) ;

}


void MainWindow::on_radioButton_2_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from evenement ORDER BY ID desc");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID "));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("date"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("duree"));
ui->tablevenement_2->setModel(model) ;
}

void MainWindow::on_lineEdit_rech_textEdited(const QString &arg1)
{
    QSqlQueryModel * model= new QSqlQueryModel();
        QSqlQuery q;
        q.prepare("select * from evenement WHERE ID like '"+ui->lineEdit_rech->text()+"' OR  NOM like '"+ui->lineEdit_rech->text()+"' OR date_e like '"+ui->lineEdit_rech->text()+"' ");
             tmpevenement.rechercher(q) ;
               q.exec();
               model->setQuery(q);
               ui->tablevenement_2->setModel(tmpevenement.rechercher(q));
}
void MainWindow::on_on_pb_ajouter_p_clicked()
{

    QString idpromo =ui->lineEdit_ID_promo->text();
QString nomp=ui->lineEdit_Nom_p->text();
int pourcentage= ui->lineEdit_pourcentage->text().toFloat();
QString date_f= ui->dateEdit_date_f->text();
QString date_d= ui->dateEdit_date_d->text();

promotions p(idpromo,nomp,pourcentage,date_d,date_f);

bool test=p.ajouter_p();
if (test)
         { ui->tableView_promo->setModel(tmppromotions.afficher_p());//refresh

        }

        if(p.verif_nomp(nomp)==false){
             QMessageBox::critical(nullptr, QObject::tr("Ajouter Client"),
                         QObject::tr("Nom doit contenir 20 caractéres au maximum !\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);

         }else if (p.verif_idp(idpromo)==false){
             QMessageBox::critical(nullptr, QObject::tr("Ajouter Client"),
                         QObject::tr(" Id doit contenir 8 chiffres !\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
        }
         else{
            QMessageBox::information(nullptr, QObject::tr("ajouter un client"),
                              QObject::tr(" client ajoute .\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

        }
        }
void MainWindow::on_on_pb_supprimer_promo_clicked()
{

    int idpromo =ui->lineEdit_ID_promo->text().toInt();
    bool test=tmppromotions.supprimer_p(idpromo);
      initialiser();
    if(test)
  {
  ui->tableView_promo->setModel(tmppromotions.afficher_p());

  refrech();
  QMessageBox::information(nullptr, windowTitle(),QObject::tr("Supprimer succés"));
  }
    else
    {
        QMessageBox::information(nullptr, windowTitle(),QObject::tr("Id n'existe pas"));
}


}

void MainWindow::on_on_pb_modifier_promo_clicked()
{

    QString idpromo =ui->lineEdit_ID_promo->text();
QString nomp=ui->lineEdit_Nom_p->text();
int pourcentage= ui->lineEdit_pourcentage->text().toFloat();
QString date_f= ui->dateEdit_date_f->text();
QString date_d= ui->dateEdit_date_f->text();


promotions p(idpromo,nomp,pourcentage,date_f,date_d);
initialiser();
bool test=false;
     if (idpromo>0)test=tmppromotions.modifier_p(p);
    {
         ui->tableView_promo->setModel(tmppromotions.afficher_p());

        QMessageBox::information(this,"promo supprime","ce promo a ete modifie");
    }
}

void MainWindow::on_on_pb_actualiser_m_p_clicked()
{
    QSqlQueryModel * model2= new QSqlQueryModel();
        model2->setQuery("select idpromo  from promo") ;

}



void MainWindow::on_on_pb_trier_p_croissante_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from promo ORDER BY IDPROMO ");

model->setHeaderData(0, Qt::Horizontal, QObject::tr("ide "));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("idpromo "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("nomp"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("pourcentage"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_d"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_f"));
ui->tableView_promo->setModel(model) ;
}

void MainWindow::on_on_pb_trier_promo_decroissante_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from promo ORDER BY IDpromo desc");

model->setHeaderData(0, Qt::Horizontal, QObject::tr("ide "));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("idpromo "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("nomp"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("pourcentage"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_d"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_f"));
ui->tableView_promo->setModel(model) ;
}



void MainWindow::on_lineEdit_rech_2_cursorPositionChanged(int arg1, int arg2)
{
    QSqlQueryModel * model= new QSqlQueryModel();
        QSqlQuery q;
        q.prepare("select * from promo WHERE IDPROMO like '"+ui->lineEdit_rech_2->text()+"' OR  NOMP like '"+ui->lineEdit_rech_2->text()+"' OR pourcentage like '"+ui->lineEdit_rech_2->text()+"' ");
             tmppromotions.rechercher_m(q) ;
               q.exec();
               model->setQuery(q);
               ui->tableView_promo->setModel(tmppromotions.rechercher_m(q));
}



void MainWindow::sendMail()
{
    QString mail = ui->comboBox_mail->currentText();

    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toUShort());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    smtp->sendMail(ui->uname->text(), ui->comboBox_mail->currentText() , ui->subject->text(),ui->msg->toPlainText());
    //ui->comboBox_mail->setModel(tmpconstructeur.getMailModel());

}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}


void MainWindow::on_on_pb_statistique_clicked()
{
    statistiques *s = new statistiques();
       setWindowModality(Qt::WindowModal);
       s->show();
}





void MainWindow::on_on_pb_imprimer_clicked()
{
    QPrinter printer;

            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName("C:/hhhh/llll/evenements.pdf");

           QPainter painter;
           painter.begin(&printer);
           QFont font;
           QString nom = ui->lineEdit_nom_2->text();
            QString date_e = ui->dateEdit_evenements->text();

            QString id= ui->lineEdit_id_2->text();


           font.setPixelSize(35);
           painter.setFont(font);
           painter.setPen(Qt::blue);

           painter.drawText(100,300,"nom :");

           painter.drawText(100,400,"date_e :");

           painter.drawText(100,500,"id:");





           font.setPixelSize(22);
           painter.setFont(font);
           painter.setPen(Qt::red);
          //  QString numm= QString::number(numero);
           painter.drawText(500,300,nom);
           painter.drawText(500,400,id);
           painter.drawText(500,500,date_e);


           painter.end();
}



void MainWindow::on_pushButton_4_clicked()
{
    QPrinter printer;

            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName("C:/hhhh/llll/promo.pdf");

           QPainter painter;
           painter.begin(&printer);
           QFont font;
           QString nomp = ui->lineEdit_Nom_p->text();
            QString pourcentage = ui->lineEdit_pourcentage->text();

            QString idpromo= ui->lineEdit_ID_promo->text();


           font.setPixelSize(35);
           painter.setFont(font);
           painter.setPen(Qt::blue);

           painter.drawText(100,300,"nomp :");

           painter.drawText(100,400,"pourcentage :");

           painter.drawText(100,500,"idpromo:");

           font.setPixelSize(22);
           painter.setFont(font);
           painter.setPen(Qt::red);
          //  QString numm= QString::number(numero);
           painter.drawText(500,300,nomp);
           painter.drawText(500,400,pourcentage);
           painter.drawText(500,500,idpromo);


           painter.end();

}

void MainWindow::on_tablevenement_2_activated(const QModelIndex &index)
{


    QString val=ui->tablevenement_2->model()->data(index).toString();


    QSqlQuery qry;
    qry.prepare("select * from evenement where id='"+val+"' or nom='"+val+"' or date_e='"+val+"'");

if(qry.exec())
{

while(qry.next())
{

    ui->lineEdit_id_2->setText(qry.value(0).toString());
    ui->lineEdit_nom_2->setText(qry.value(1).toString());
    ui->dateEdit_evenements->setDate(qry.value(2).toDate());

}

}
else
{
    QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}
}






void MainWindow::on_sendBtn_clicked()
{
    Smtp* smtp = new Smtp("hotsmartiqua@gmail.com", "smartiquahot++", "smtp.gmail.com", 465);
                              connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
                                  smtp->sendMail("hotsmartiqua@gmail.com", "dhiya.baccari@esprit.tn" , "Smart Rapid Hotel, Nouveau Evenement!","Congrats!");
}


void MainWindow::on_tableView_promo_activated(const QModelIndex &index)
{

    QString val=ui->tableView_promo->model()->data(index).toString();


    QSqlQuery qry;
    qry.prepare("select * from promo where  idpromo='"+val+"' or nomp='"+val+"' or pourcentage='"+val+"' or date_d='"+val+"' or date_f='"+val+"'");

if(qry.exec())
{

while(qry.next())
{

    ui->lineEdit_ID_promo->setText(qry.value(0).toString());
    ui->lineEdit_Nom_p->setText(qry.value(1).toString());
    ui->lineEdit_pourcentage->setText(qry.value(2).toString());
    ui->dateEdit_date_d->setDate(qry.value(3).toDate());
    ui->dateEdit_date_f->setDate(qry.value(4).toDate());

}

}
else
{
    QMessageBox::critical(this,tr("error::"),qry.lastError().text());
}
}

