#include "gestion_des_equipements.h"
#include "ui_gestion_des_equipements.h"
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
#include "equipement.h"
#include <QSqlQuery>
#include <QDesktopServices>
#include <QDialog>
//#include "smtp.h"
//#include "qcustomplot.h"
#include "equipement.h"
#include "fournisseur.h"
#include "statistiques.h"
#include "connexion.h"
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

gestion_des_equipements::gestion_des_equipements(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestion_des_equipements)
{
    ui->setupUi(this);
    ui->tableView->setModel(tmpequi.afficher_equipement());
    ui->tableView_2->setModel(tmpfour.afficher_fournisseur());
    ui->comboBox_2->setModel(tmpfour.afficher_fournisseurlist());
    ui->comboBox_3->setModel(tmpfour.afficher_fournisseurlist());
    ui->comboBox->setModel(tmpequi.afficher_equipementlist());


}

gestion_des_equipements::~gestion_des_equipements()
{
    delete ui;

}

void gestion_des_equipements::initialiser()
{
    ui->id_four->clear();
    ui->nomfour->clear();
    ui->tel->clear();
    ui->adres->clear();
   ui->emioak->clear();
   ui->dddd->clear();
   ui->id_eq->clear();
   ui->nomeq->clear();
   ui->typeequi->clear();
   ui->idfourr->clear();
}

//hedi li fournisseur imprimer commente
/*void gestion_des_personnels::on_pushButton_2_clicked()
{
    QPrinter printer ;
    printer.setPrinterName("blablabla") ;
    QPrintDialog dialog (&printer,this) ;
    if ( dialog.exec()== QDialog::Rejected) return ;
    ui->textEdit->print(&printer) ;
}*/
//toufa lena


/*

void gestion_des_personnels::on_stat_clicked()
{
    statistiques *s = new statistiques();
    setWindowModality(Qt::WindowModal);
    s->show();
}


void gestion_des_personnels::sendMail()
{
    QString mail = ui->comboBox_mail->currentText();

    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toUShort());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    smtp->sendMail(ui->uname->text(), ui->comboBox_mail->currentText() , ui->subject->text(),ui->msg->toPlainText());
    //ui->comboBox_mail->setModel(tmpconstructeur.getMailModel());

}

void gestion_des_personnels::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}
*/

//ghjklfffffffffff


void gestion_des_equipements::on_radioButton_2_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from fournisseur ORDER BY NOM_FOURN desc ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_fourn"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom Fourn"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Tel"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Commentaire"));
ui->tableView_2->setModel(model) ;
}

void gestion_des_equipements::on_radioButton_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from fournisseur ORDER BY NOM_FOURN ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_fourn"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom Fourn"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Tel"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Commentaire"));
ui->tableView_2->setModel(model) ;
}


void gestion_des_equipements::on_pushButton_clicked()
{
    QString val=ui->comboBox_2->currentText()  ;
    QSqlQuery query ;
    query.prepare("select * from fournisseur where ID_FOURN='"+val+"'") ;
    //query.bindValue(":id",val) ;
  if (query.exec())
  {
      while (query.next()) {


        ui->id_four->setText(query.value(0).toString()) ;
        ui->nomfour->setText(query.value(1).toString()) ;
        ui->tel->setText(query.value(2).toString()) ;
        ui->adres->setText(query.value(3).toString()) ;
        ui->emioak->setText(query.value(4).toString()) ;
        ui->dddd->setText(query.value(5).toString()) ;

  }
  }
}

void gestion_des_equipements::on_ajouter_four_clicked()
{
    QString ID_FOUR,NOM,TEL,ADRESSE,EMAIL,COMM;
        ID_FOUR=ui->id_four->text();
        NOM=ui->nomfour->text();
        TEL=ui->tel->text();
        ADRESSE=ui->adres->text();
       EMAIL=ui->emioak->text();
       COMM=ui->dddd->toPlainText();

        fournisseur f(ID_FOUR,NOM,TEL,ADRESSE,EMAIL,COMM);

        if(f.verif_id(f.get_id_fourn())==false){
            QMessageBox::critical(nullptr, QObject::tr("Ajouter Fournisseur"),
                        QObject::tr(" Id_dep doit contenir 8 chiffres !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else{
      bool test=f.ajouter_fournisseur();
      if(test)
    {
          ui->tableView_2->setModel(tmpfour.afficher_fournisseur());
          QFile file("D:\\historiqueFournisseur.txt");
                if (!file.open(QIODevice::WriteOnly | QIODevice::Append |QIODevice::Text))
                    return;
                QTextStream cout(&file);
                QString message2="\n L'historique des Fournisseurs à ajouter :"+ID_FOUR+" "+NOM+" "+TEL+" "+ADRESSE+" "+EMAIL+" "+COMM;
                cout << message2;
          initialiser();

          //refresh

          ui->comboBox_2->setModel(tmpfour.afficher_fournisseurlist());
          ui->comboBox_3->setModel(tmpfour.afficher_fournisseurlist());


          QMessageBox::information(nullptr, QObject::tr("Ajouter un Fournissur"),
                      QObject::tr("FOURNISSEUR ajouté.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
    }
      else
      {
          QMessageBox::critical(nullptr, QObject::tr("Ajouter un Fournisseur"),
                      QObject::tr("FOURNISSUR existe deja  !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
}
}
}

void gestion_des_equipements::on_modifier_four_clicked()
{
    QString ID_FOUR,NOM,TEL,ADRESSE,EMAIL,COMM;
    ID_FOUR=ui->id_four->text();
    NOM=ui->nomfour->text();
    TEL=ui->tel->text();
    ADRESSE=ui->adres->text();
   EMAIL=ui->emioak->text();
   COMM=ui->dddd->toPlainText();

        fournisseur f(ID_FOUR,NOM,TEL,ADRESSE,EMAIL,COMM);

bool test=tmpfour.modifier_fournisseur(f);
if(test)
{
    ui->tableView_2->setModel(tmpfour.afficher_fournisseur());

    initialiser();

    //refresh

    ui->comboBox_2->setModel(tmpfour.afficher_fournisseurlist());
    ui->comboBox_3->setModel(tmpfour.afficher_fournisseurlist());

    QMessageBox::information(nullptr, QObject::tr("modifer un Fournisseur"),
                QObject::tr("FOURNISSEUR modifié.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else
    QMessageBox::critical(nullptr, QObject::tr("modifier un Fournisseur"),
                QObject::tr("FOURNISSEUR non valide  !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}

void gestion_des_equipements::on_lineEdit_textChanged(const QString &arg1)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery q;

    q.prepare("select * from fournisseur WHERE ADRESSE like '"+ui->lineEdit->text()+"' OR ID_FOURN like '"+ui->lineEdit->text()+"' OR NOM_FOURN like '"+ui->lineEdit->text()+"' OR TEL like '"+ui->lineEdit->text()+"' OR EMAIL like '"+ui->lineEdit->text()+"' ");
         tmpequi.rechercher(q) ;
           q.exec();
           model->setQuery(q);
           ui->tableView_2->setModel(tmpfour.rechercher(q));
}

void gestion_des_equipements::on_supprimer_four_clicked()
{
    QString id = ui->comboBox_2->currentText();
    bool test=tmpfour.supprimer_fournisseur(id);;
    if(test)
    {
        ui->tableView_2->setModel(tmpfour.afficher_fournisseur());

        initialiser();

        //refresh

        ui->comboBox_2->setModel(tmpfour.afficher_fournisseurlist());
        ui->comboBox_3->setModel(tmpfour.afficher_fournisseurlist());

        QMessageBox::information(nullptr, QObject::tr("Supprimer Fournisseur"),
                    QObject::tr("FOURNISSEUR supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer Fournisseur"),
                    QObject::tr("verifier l'id  !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void gestion_des_equipements::on_pushButton_2_clicked()
{
    QString ID_EQUI,NOM,TYPE,ID_FOUR;
        ID_EQUI=ui->id_eq->text();
        NOM=ui->nomeq->text();
        TYPE=ui->typeequi->text();
        ID_FOUR=ui->idfourr->text();


        equipement e(ID_EQUI,NOM,TYPE,ID_FOUR);

        if(e.verif_id(e. get_id_equipement())==false){
            QMessageBox::critical(nullptr, QObject::tr("Ajouter constructeur"),
                        QObject::tr(" Id_dep doit contenir 8 chiffres !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else{
      bool test=e.ajouter_equipement();
      if(test)
    {
          ui->tableView->setModel(tmpequi.afficher_equipement());
          QFile file("D:\\historiqueEquipement.txt");
                if (!file.open(QIODevice::WriteOnly | QIODevice::Append |QIODevice::Text))
                    return;
                QTextStream cout(&file);
                QString message2="\n L'historique des Equipements à ajouter :"+ID_EQUI+" "+NOM+" "+TYPE+" "+ID_FOUR;
                cout << message2;

          initialiser();

          //refresh


          ui->comboBox->setModel(tmpequi.afficher_equipementlist());

          QMessageBox::information(nullptr, QObject::tr("Ajouter un departement"),
                      QObject::tr("departement ajouté.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
    }
      else
      {
          QMessageBox::critical(nullptr, QObject::tr("Ajouter un departement"),
                      QObject::tr("departement existe deja  !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
}
}
}


void gestion_des_equipements::on_pushButton_7_clicked()
{
    QString id = ui->comboBox->currentText();
    bool test=tmpequi.supprimer_equipement(id);
    if(test)
    {
        ui->tableView->setModel(tmpequi.afficher_equipement());

        initialiser();

        //refresh


        ui->comboBox->setModel(tmpequi.afficher_equipementlist());
        ui->comboBox->setModel(tmpequi.afficher_equipementlist());


        QMessageBox::information(nullptr, QObject::tr("Supprimer Departement"),
                    QObject::tr("Departement supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer Departement"),
                    QObject::tr("verifier l'id  !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void gestion_des_equipements::on_pushButton_4_clicked()
{
    tmpequi.set_id(ui->id_eq->text());
    tmpequi.set_nom(ui->nomeq->text());
    tmpequi.set_type(ui->typeequi->text());
    tmpequi.set_id_fourn(ui->idfourr->text());
    bool test=tmpequi.modifier_equipement();
    if(test)
    {
        ui->tableView->setModel(tmpequi.afficher_equipement());

        initialiser();

        //refresh


        ui->comboBox->setModel(tmpequi.afficher_equipementlist());
    QMessageBox::information(nullptr, QObject::tr("modifer un departement"),
                QObject::tr("departement modifié.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
    QMessageBox::critical(nullptr, QObject::tr("modifier un departement"),
                QObject::tr("departement non valide  !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}

void gestion_des_equipements::on_pushButton_8_clicked()
{
    QString val=ui->comboBox->currentText();
    QSqlQuery query ;
    query.prepare("select * from equipement WHERE ID_EQUI='"+val+"'") ;
    //query.bindValue(":id",val) ;
  if (query.exec())
  {
      while (query.next()) {

        ui->id_eq->setText(query.value(0).toString()) ;
        ui->nomeq->setText(query.value(1).toString()) ;
        ui->typeequi->setText(query.value(2).toString()) ;
        ui->idfourr->setText(query.value(3).toString()) ;
  }
  }
}

void gestion_des_equipements::on_radioButton_4_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from EQUIPEMENT ORDER BY NOM desc ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_Equipement "));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID_Fournisseur"));
ui->tableView->setModel(model) ;
}

void gestion_des_equipements::on_radioButton_3_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from EQUIPEMENT ORDER BY NOM ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_Equipement "));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID_Fournisseur"));
ui->tableView->setModel(model) ;
}


void gestion_des_equipements::on_lineEdit_2_textChanged(const QString &arg1)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery q;
    q.prepare("select * from equipement WHERE ID_EQUIP like '"+ui->lineEdit_2->text()+"' OR NOM like '"+ui->lineEdit_2->text()+"' OR TYPE like '"+ui->lineEdit_2->text()+"' OR ID_FOURN like '"+ui->lineEdit_2->text()+"' ");
         tmpequi.rechercher(q) ;
           q.exec();
           model->setQuery(q);
           ui->tableView->setModel(tmpequi.rechercher(q)) ;
}

void gestion_des_equipements::on_comboBox_3_activated(const QString &arg1)
{
    ui->idfourr->setText(arg1);
}

void gestion_des_equipements::on_pushButton_6_clicked()
{
    statistiques *s = new statistiques();
    setWindowModality(Qt::WindowModal);
    s->show();
}



void gestion_des_equipements::on_pushButton_9_clicked()
{
    QFile file ("D:\\historiqueEquipement.txt");
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(0,"info",file.errorString());
        }
        QTextStream in (&file);
        ui->textBrowser_2->setText(in.readAll());
}

void gestion_des_equipements::on_pushButton_3_clicked()
{
    QFile file ("D:\\historiqueFournisseur.txt");
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(0,"info",file.errorString());
        }
        QTextStream in (&file);
        ui->textBrowser->setText(in.readAll());
}
