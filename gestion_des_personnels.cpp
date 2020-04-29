#include "gestion_des_personnels.h"
#include "ui_gestion_des_personnels.h"
#include "statistiques.h"
#include "statestiquesperso.h"
#include "smtp.h"
#include "qcustomplot.h"
#include <QTextToSpeech>
#include <QMessageBox>
#include <QDate>
#include <QTime>
#include <QTimer>
#include <QProgressBar>
#include <QStatusBar>
#include <QWidget>
#include <QString>
#include <QDebug>
#include <windows.h>
#include <QFile>
#include <QPrinter>
#include <QPrintDialog>
#include <QPixmap>
#include "departement.h"
#include "personnel.h"
#include "widget.h"
#include <QLoggingCategory>
#include "mainwindow.h"

Gestion_des_personnels::Gestion_des_personnels(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gestion_des_personnels)
{
    ui->setupUi(this);
    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(UpadateTime()));
    timer->start(1000);
    ui->tableView_dep->setModel(tmpdep.afficher_departement());
    ui->comboBox_suppdep->setModel(tmpdep.afficher_departementlist());
    ui->tableView_per->setModel(tmpper.afficher_personnel());
    ui->comboBox->setModel(tmpper.afficher_personnellist());
    ui->comboBox_mail->setModel(tmpper.getMailModel());
    ui->comboBox_2->setModel(tmpdep.afficher_departementlist());

    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));
    UpadateTime();
    popUp = new PopUp();
    popUp->setPopupText("Welcome to Hot Plus Plus");
    popUp->show();
    //m_speech->say("heelllllllllll");
   // m_speech->say("HOT PLUS PLUS");
}

Gestion_des_personnels::~Gestion_des_personnels()
{
    delete ui;
}
void Gestion_des_personnels::UpadateTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm:ss");
    if ((time.second() % 2) == 0)
    {text[2] = ' ';}
        else{
    text[5] = ' ';}
    ui->time->setText(text);
    ui->time2->setText(text);
    ui->time3->setText(text);
}

void Gestion_des_personnels::initialiser()
{
     ui->cin->clear();
    ui->specialite->clear();
    ui->nom->clear();
    ui->prenom->clear();
   ui->date_naiss->clear();
    ui->age->clear();
    ui->sexe->clear();
    ui->tel->clear();
    ui->duree_travail->clear();
    ui->adresse_mail->clear();
    ui->id_dep->clear();
    ui->chemin->clear();
    ui->comboBox_mail->clear();
}

void Gestion_des_personnels::initialiser2()
{
    ui->ID_dep->clear();
    ui->Poste->clear();
    ui->Salaire->clear();

}

void Gestion_des_personnels::on_pushButton_clicked()
{
        QString ID_DEP,POSTE,SALAIRE;
            ID_DEP=ui->ID_dep->text();
            POSTE=ui->Poste->text();
            SALAIRE=ui->Salaire->text();
            ui->ID_dep->setEnabled(1);

            departement e(ID_DEP,POSTE,SALAIRE);

            if(e.verif_id(e.get_id())==false){                
                popUp = new PopUp();
                popUp->setPopupText("Id_dep doit contenir 8 chiffres !");
                popUp->show();
            }
            else{
          bool test=e.ajouter_departement();
          if(test)
        {
              QFile file("D:\\Personnel\\historiqueDepartement.txt");
                    if (!file.open(QIODevice::WriteOnly | QIODevice::Append |QIODevice::Text))
                        return;
                    QTextStream cout(&file);
                    QString message2="\n L'historique des departements à ajouter :"+ID_DEP+" "+POSTE+" "+SALAIRE+"";
                    cout << message2;

                //m_speech->say("Departement ajouter avec succee");
               ui->label_7->setText("DEPARTEMENT AJOUTE");
               ui->comboBox_suppdep->setModel(tmpdep.afficher_departementlist());
               ui->tableView_dep->setModel(tmpdep.afficher_departement());
               ui->comboBox_2->setModel(tmpdep.afficher_departementlist());
               initialiser2();


        }
          else
          {
              QMessageBox::critical(nullptr, QObject::tr("Ajouter un departement"),
                          QObject::tr("Departement existe deja  !.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    }
    }

}

void Gestion_des_personnels::on_pushButton_2_clicked()
{

    tmpdep.set_id(ui->comboBox_suppdep->currentText());
    tmpdep.set_poste(ui->Poste->text());
    tmpdep.set_salaire(ui->Salaire->text());
bool test=tmpdep.modifier_departement();
if(test)
{


    ui->label_7->setText("DEPARTEMENT MODIFIE");
    ui->comboBox_suppdep->setModel(tmpdep.afficher_departementlist());
    ui->tableView_dep->setModel(tmpdep.afficher_departement());
    initialiser2();
    ui->ID_dep->setEnabled(1);

}
else
    QMessageBox::critical(nullptr, QObject::tr("Modifier Un Departement"),
                QObject::tr("Departement non valide  !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}

void Gestion_des_personnels::on_pushButton_4_clicked()
{

    QString id = ui->comboBox_suppdep->currentText();
    bool test=tmpdep.supprimer_departement(id);
    if(test)
    {
        ui->tableView_dep->setModel(tmpdep.afficher_departement());
        ui->comboBox_suppdep->setModel(tmpdep.afficher_departementlist());
        ui->comboBox_2->setModel(tmpdep.afficher_departementlist());
        ui->comboBox_2->setModel(tmpdep.afficher_departementlist());
        ui->ID_dep->setEnabled(1);
        initialiser2();


        ui->label_7->setText("DEPARTEMENT SUPPRIME");
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer Departement"),
                    QObject::tr("verifier l'id  !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void Gestion_des_personnels::on_lineEdit_4_textChanged(const QString &arg1)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery q;
    q.prepare("select * from DEPARTEMENT WHERE ID_DEP like '"+ui->lineEdit_4->text()+"' OR POSTE like '"+ui->lineEdit_4->text()+"' OR SALAIRE like '"+ui->lineEdit_4->text()+"' ");
         tmpdep.rechercher(q) ;
           q.exec();
           model->setQuery(q);
           ui->tableView_dep->setModel(tmpdep.rechercher(q)) ;
           ui->label_7->setText("RECHERCHE");
}

void Gestion_des_personnels::on_radioButton_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from DEPARTEMENT ORDER BY ID_dep ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_Departement "));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Poste"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Salaire"));
ui->tableView_dep->setModel(model) ;
    ui->label_7->setText("TRI A-Z");
}

void Gestion_des_personnels::on_radioButton_2_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from DEPARTEMENT ORDER BY ID_dep desc");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_Departement "));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Poste"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Salaire"));
ui->tableView_dep->setModel(model) ;
    ui->label_7->setText("TRI Z-A");
}

void Gestion_des_personnels::on_radioButton_3_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from DEPARTEMENT ORDER BY SALAIRE ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_Departement "));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Poste"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Salaire"));
ui->tableView_dep->setModel(model) ;
    ui->label_7->setText("TRI CROISSANT DU CONTRAT");
}

void Gestion_des_personnels::on_radioButton_6_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from DEPARTEMENT ORDER BY SALAIRE desc");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_Departement "));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Poste"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Salaire"));
ui->tableView_dep->setModel(model) ;
    ui->label_7->setText("TRI DECROISSANT DU CONTRAT");
}

void Gestion_des_personnels::on_pushButton_3_clicked()
{
    QFile file ("D:\\Personnel\\historiqueDepartement.txt");
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(0,"info",file.errorString());
        }
        QTextStream in (&file);
        ui->textBrowser->setText(in.readAll());
}

void Gestion_des_personnels::on_pushButton_5_clicked()
{
    QPrinter printer;
        printer.setPrinterName("desierd printer name");
        QPrintDialog dialog(&printer,this);
        if(dialog.exec()== QDialog::Rejected) return;
        ui->textBrowser->print(&printer);
}

void Gestion_des_personnels::on_pushButton_6_clicked()
{
    QString val=ui->comboBox_suppdep->currentText()  ;
    QSqlQuery query ;
    query.prepare("select * from DEPARTEMENT where ID_DEP='"+val+"'") ;

  if (query.exec())
  {
      while (query.next()) {

        ui->ID_dep->setText(query.value(0).toString()) ;
        ui->Poste->setText(query.value(1).toString()) ;
        ui->Salaire->setText(query.value(2).toString()) ;
        ui->ID_dep->setDisabled(1);
  }
  }
}

void Gestion_des_personnels::on_pushButton_7_clicked()
{
popUp = new PopUp();
   ui->cin->setEnabled(1);
    QString CIN = ui->cin->text();
    QString specialite= ui->specialite->text();
    QString nom= ui->nom->text();
    QString prenom= ui->prenom->text();
    QDate date= ui->date_naiss->date();
    int Age = ui->age->text().toInt();
    QString sexe= ui->sexe->text();
    int Telephone = ui->tel->text().toInt();
    int Travail = ui->duree_travail->text().toInt();
    QString mail= ui->adresse_mail->text();
    QString id_dep= ui->id_dep->text();
    QString IMAGE= ui->chemin->text();//LABEL CHEMIN

 personnel p(CIN,specialite,nom,prenom,date,sexe,Telephone,Age,mail,Travail,id_dep,IMAGE);

 if(p.verif_email(p.get_adresse_mail())==false){ 
     popUp->setPopupText("verifier Mail !");
     popUp->show();
 }else if(p.verif_id(p.get_cin())==false){
        popUp->setPopupText("Id doit contenir 8 chiffres !");
        popUp->show();
 }else if(p.verif_nom(p.get_nom())==false){
     popUp->setPopupText("Nom doit contenir 20 caractéres !");
     popUp->show();
 }else if(p.verif_nom(p.get_prenom())==false){
     popUp->setPopupText("Prenom doit contenir 20 caractéres !");
     popUp->show();
 }
 else{

 bool test=p.ajouter_personnel();
  if(test)
  {   ui->label_21->setText("PERSONNEL AJOUTE");
      QFile file("D:\\Personnel\\historiquePersonnel.txt");
            if (!file.open(QIODevice::WriteOnly | QIODevice::Append |QIODevice::Text))
                return;
            QTextStream cout(&file);
            QString message2="\n L'historique des Personnels à ajouter :"+CIN+" "+specialite+" "+nom+" "+prenom+" "+sexe+" "+Telephone+" "+Age+" "+mail+" "+Travail+" "+id_dep;
            cout << message2;
      ui->tableView_per->setModel(tmpper.afficher_personnel());//refresh
       ui->comboBox->setModel(tmpper.afficher_personnellist());
       ui->comboBox_mail->setModel(tmpper.getMailModel());
       initialiser();

      //ui->comboBox_mail->setModel(tmppers.getMailModel());

  }
    else{
        QMessageBox::critical(nullptr, QObject::tr("Ajouter un Personnel"),
                    QObject::tr("Personnel existe deja  !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        initialiser();

}
}
}

void Gestion_des_personnels::on_pushButton_8_clicked()
{

    QString id = ui->comboBox->currentText();
    bool test=tmpper.supprimer_personnel(id);
    if(test)
    {    ui->tableView_per->setModel(tmpper.afficher_personnel());//refresh
         ui->comboBox->setModel(tmpper.afficher_personnellist());
         ui->comboBox_mail->setModel(tmpper.getMailModel());
         ui->cin->setEnabled(1);
         initialiser();
         ui->label_21->setText("PERSONNEL SUPPRIME");

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer Personnel"),
                    QObject::tr("verifier le cin  !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void Gestion_des_personnels::on_pushButton_9_clicked()
{

    QString CIN = ui->cin->text();
    QString specialite= ui->specialite->text();
    QString nom= ui->nom->text();
    QString prenom= ui->prenom->text();
    QDate date= ui->date_naiss->date();
    int Age = ui->age->text().toInt();
    QString sexe= ui->sexe->text();
    int Telephone = ui->tel->text().toInt();
    int Travail = ui->duree_travail->text().toInt();
    QString mail= ui->adresse_mail->text();
    QString id_dep= ui->id_dep->text();
    QString IMAGE= ui->chemin->text();//LABEL CHEMIN    


 personnel p(CIN,specialite,nom,prenom,date,sexe,Telephone,Age,mail,Travail,id_dep,IMAGE);


bool test=tmpper.modifier_personnel(p);
if(test)
{

    ui->tableView_per->setModel(tmpper.afficher_personnel());//refresh
    ui->comboBox->setModel(tmpper.afficher_personnellist());
    ui->comboBox_mail->setModel(tmpper.getMailModel());
    ui->cin->setEnabled(1);
    initialiser();
    ui->label_21->setText("PERSONNEL MODIFIE");

}
else
{
    QMessageBox::critical(nullptr, QObject::tr("modifier un Personnel"),
                QObject::tr("Perosnnel non valide  !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
}

void Gestion_des_personnels::on_pushButton_10_clicked()
{
    ui->label_21->setText("PERSONNEL CHOISI");
    QString val=ui->comboBox->currentText()  ;
    QSqlQuery query ;
    query.prepare("select * from PERSONNEL where CIN='"+val+"'") ;

  if (query.exec())
  {
      while (query.next()) {

        ui->cin->setText(query.value(0).toString()) ;
        ui->specialite->setText(query.value(1).toString()) ;
        ui->nom->setText(query.value(2).toString()) ;
        ui->prenom->setText(query.value(3).toString()) ;
        ui->date_naiss->setDate(query.value(4).toDate()) ;
        ui->sexe->setText(query.value(5).toString()) ;
        ui->tel->setText(query.value(6).toString()) ;
        ui->age->setText(query.value(7).toString()) ;
        ui->adresse_mail->setText(query.value(8).toString()) ;
        ui->duree_travail->setText(query.value(9).toString()) ;
        ui->id_dep->setText(query.value(10).toString()) ;
        ui->chemin->setText(query.value(11).toString()) ;
        //AFFICHER LABEL IMAGE
        QPixmap pix(ui->chemin->text());
        int w =ui->photo->width();
        int h =ui->photo->height();
        ui->photo->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        ui->comboBox_2->setCurrentText(query.value(10).toString());
         ui->cin->setDisabled(1);
  }
  }
}

void Gestion_des_personnels::on_pushButton_11_clicked()
{
    QFile file ("D:\\Personnel\\historiquePersonnel.txt");
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(0,"info",file.errorString());
        }
        QTextStream in (&file);
        ui->textBrowser_2->setText(in.readAll());
}

void Gestion_des_personnels::on_pushButton_12_clicked()
{
    QPrinter printer;
        printer.setPrinterName("desierd printer name");
        QPrintDialog dialog(&printer,this);
        if(dialog.exec()== QDialog::Rejected) return;
        ui->textBrowser_2->print(&printer);
}

void Gestion_des_personnels::on_pushButton_13_clicked()
{
    statistiques *s = new statistiques();
    setWindowModality(Qt::WindowModal);
    s->show();
}

void Gestion_des_personnels::on_pushButton_14_clicked()
{
    statestiquesperso *s = new statestiquesperso();
    setWindowModality(Qt::WindowModal);
    s->show();
}
void Gestion_des_personnels::sendMail()
{
    QString mail = ui->comboBox_mail->currentText();

    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toUShort());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    smtp->sendMail(ui->uname->text(), ui->comboBox_mail->currentText() , ui->subject->text(),ui->msg->toPlainText());
    //ui->comboBox_mail->setModel(tmpconstructeur.getMailModel());

}

void Gestion_des_personnels::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}

void Gestion_des_personnels::on_lineEdit_12_textChanged(const QString &arg1)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery q;
    q.prepare("select * from personnel WHERE CIN like '"+ui->lineEdit_12->text()+"' OR SPECIALITE like '"+ui->lineEdit_12->text()+"' OR NOM like '"+ui->lineEdit_12->text()+"' OR PRENOM like '"+ui->lineEdit_12->text()+"' OR DATEE like '"+ui->lineEdit_12->text()+"' OR SEXE like '"+ui->lineEdit_12->text()+"' OR TEL like '"+ui->lineEdit_12->text()+"' OR AGE like '"+ui->lineEdit_12->text()+"' OR MAIL like '"+ui->lineEdit_12->text()+"' OR HORAIRE like '"+ui->lineEdit_12->text()+"' OR ID_DEP like '"+ui->lineEdit_12->text()+"'");
         tmpdep.rechercher(q) ;
           q.exec();
           model->setQuery(q);
           ui->tableView_per->setModel(tmpper.rechercher(q)) ;
           ui->label_21->setText("RECHERCHE");
}

void Gestion_des_personnels::on_radioButton_5_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from personnel ORDER BY NOM");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin "));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Specialite"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prenom"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de naissance"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Sexe"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("Telephone"));
model->setHeaderData(7, Qt::Horizontal, QObject::tr("Age"));
model->setHeaderData(8, Qt::Horizontal, QObject::tr("Adresse E_mail"));
model->setHeaderData(9, Qt::Horizontal, QObject::tr("Duree de travail"));
model->setHeaderData(10, Qt::Horizontal, QObject::tr("ID_Département"));
model->setHeaderData(11, Qt::Horizontal, QObject::tr("Image"));
ui->tableView_per->setModel(model) ;
    ui->label_21->setText("TRI CROISSANT");
}

void Gestion_des_personnels::on_radioButton_8_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from personnel ORDER BY NOM desc");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin "));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Specialite"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prenom"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de naissance"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Sexe"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("Telephone"));
model->setHeaderData(7, Qt::Horizontal, QObject::tr("Age"));
model->setHeaderData(8, Qt::Horizontal, QObject::tr("Adresse E_mail"));
model->setHeaderData(9, Qt::Horizontal, QObject::tr("Duree de travail"));
model->setHeaderData(10, Qt::Horizontal, QObject::tr("ID_Département"));
model->setHeaderData(11, Qt::Horizontal, QObject::tr("Image"));
ui->tableView_per->setModel(model) ;
    ui->label_21->setText("TRI DECROISSANT");
}

void Gestion_des_personnels::on_radioButton_4_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from personnel ORDER BY HORAIRE");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin "));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Specialite"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prenom"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de naissance"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Sexe"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("Telephone"));
model->setHeaderData(7, Qt::Horizontal, QObject::tr("Age"));
model->setHeaderData(8, Qt::Horizontal, QObject::tr("Adresse E_mail"));
model->setHeaderData(9, Qt::Horizontal, QObject::tr("Duree de travail"));
model->setHeaderData(10, Qt::Horizontal, QObject::tr("ID_Département"));
model->setHeaderData(11, Qt::Horizontal, QObject::tr("Image"));
ui->tableView_per->setModel(model) ;
    ui->label_21->setText("TRI CROISSANT DU DUREE DE TRAVAIL");
}

void Gestion_des_personnels::on_radioButton_7_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from personnel ORDER BY HORAIRE desc");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin "));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Specialite"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prenom"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de naissance"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Sexe"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("Telephone"));
model->setHeaderData(7, Qt::Horizontal, QObject::tr("Age"));
model->setHeaderData(8, Qt::Horizontal, QObject::tr("Adresse E_mail"));
model->setHeaderData(9, Qt::Horizontal, QObject::tr("Duree de travail"));
model->setHeaderData(10, Qt::Horizontal, QObject::tr("ID_Département"));
model->setHeaderData(11, Qt::Horizontal, QObject::tr("Image"));
ui->tableView_per->setModel(model) ;
    ui->label_21->setText("TRI DECROISSANT DU DUREE DE TRAVAIL");
}

void Gestion_des_personnels::on_pushButton_15_clicked()
{

    QString filename = QFileDialog::getOpenFileName(this,tr("choose"), "" , tr("image (*.png *.jpg *.jpeg *.bmp *.gif)"));
    if ( QString::compare(filename, QString()) != 0 )
    {
        QImage image;
        bool valid =image.load(filename);
        if (valid)
        {
            ui->chemin->setText(filename);
            image =image.scaledToWidth(ui->photo->width(),Qt::SmoothTransformation);
            ui->photo->setPixmap(QPixmap::fromImage(image));
        }

    }
}

void Gestion_des_personnels::on_pushButton_16_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("choose"), "" , tr("image (*.png *.jpg *.jpeg *.bmp *.gif)"));
    if ( QString::compare(filename, QString()) != 0 )
    {
        QImage image;
        bool valid =image.load(filename);
        if (valid)
        {
            ui->chemin->setText(filename);
            image =image.scaledToWidth(ui->photo->width(),Qt::SmoothTransformation);
            ui->photo->setPixmap(QPixmap::fromImage(image));
        }
    }
}

void Gestion_des_personnels::on_comboBox_2_activated(const QString &arg1)
{
    ui->id_dep->setText(arg1);
}

void Gestion_des_personnels::on_Quitrrre_clicked()
{
    close();
}

void Gestion_des_personnels::on_Quiuiuiui_clicked()
{
    close();
}


void Gestion_des_personnels::on_tableView_per_activated(const QModelIndex &index)
{
    ui->label_21->setText("PERSONNEL CHOISI");
    QString val=ui->tableView_per->model()->data(index).toString();
    QSqlQuery query ;
    query.prepare("select * from PERSONNEL where CIN='"+val+"'") ;

  if (query.exec())
  {
      while (query.next()) {

        ui->cin->setText(query.value(0).toString()) ;
        ui->specialite->setText(query.value(1).toString()) ;
        ui->nom->setText(query.value(2).toString()) ;
        ui->prenom->setText(query.value(3).toString()) ;
        ui->date_naiss->setDate(query.value(4).toDate()) ;
        ui->sexe->setText(query.value(5).toString()) ;
        ui->tel->setText(query.value(6).toString()) ;
        ui->age->setText(query.value(7).toString()) ;
        ui->adresse_mail->setText(query.value(8).toString()) ;
        ui->duree_travail->setText(query.value(9).toString()) ;
        ui->id_dep->setText(query.value(10).toString()) ;
        ui->chemin->setText(query.value(11).toString()) ;
        //AFFICHER LABEL IMAGE
        QPixmap pix(ui->chemin->text());
        int w =ui->photo->width();
        int h =ui->photo->height();
        ui->photo->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        ui->comboBox_2->setCurrentText(query.value(10).toString());
         ui->cin->setDisabled(1);
  }
  }
}

void Gestion_des_personnels::on_tableView_dep_activated(const QModelIndex &index)
{
    QString val=ui->tableView_dep->model()->data(index).toString();
    QSqlQuery query ;
    query.prepare("select * from DEPARTEMENT where ID_DEP='"+val+"'") ;

  if (query.exec())
  {
      while (query.next()) {

        ui->ID_dep->setText(query.value(0).toString()) ;
        ui->Poste->setText(query.value(1).toString()) ;
        ui->Salaire->setText(query.value(2).toString()) ;
        ui->ID_dep->setDisabled(1);
  }
  }
}
