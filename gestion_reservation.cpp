#include "gestion_reservation.h"
#include "ui_gestion_reservation.h"

gestion_reservation::gestion_reservation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gestion_reservation)
{
    ui->setupUi(this);
    ui->tablreservation_2->setModel(tmpreservation.afficher());
    ui->tableView_service->setModel(tmpservice.afficher_service());
    ui->comboBox_reser->setModel(tmpreservation.afficher());
    ui->comboBox_service->setModel(tmpservice.afficher_service());
}

gestion_reservation::~gestion_reservation()
{
    delete ui;
}

void gestion_reservation::refrech()
{
    QSqlQueryModel * model2= new QSqlQueryModel();
        model2->setQuery("select id  from reservation")  ;

}

void gestion_reservation::on_on_pb_ajouter_clicked_clicked()
{
    int id =ui->lineEdit_id_2->text().toInt();
QString nom=ui->lineEdit_nom_2->text();
QString prenom= ui->lineEdit_prenom_2->text();
QDate date_d=ui->dateEdit_date_d->date();
QDate date_f=ui->dateEdit_date_f->date();
int nombre=ui->lineEdit_nombre->text().toInt();
    int id_service=ui->lineEdit_idservice->text().toInt();

reservation r( id , nom , prenom, date_d, date_f, nombre , id_service);


bool test=r.ajouter();
if(test)
{
ui->tablreservation_2->setModel(tmpreservation.afficher());

refrech();
QMessageBox::information(nullptr, windowTitle(),QObject::tr("Reservastion ajoutée"));

}
}


void gestion_reservation::on_on_pb_supprimer_clicked()
{
    int id = ui->comboBox_reser->currentText().toInt();
    bool test=tmpreservation.supprimer(id);
    if(test)
  {
  ui->tablreservation_2->setModel(tmpreservation.afficher());
  ui->comboBox_reser->setModel(tmpreservation.afficher());

  refrech();
  QMessageBox::information(nullptr, windowTitle(),QObject::tr("Supprimé avec succés"));
  }
    else
    {
        QMessageBox::information(nullptr, windowTitle(),QObject::tr("Id n'existe pas"));
}
}
void gestion_reservation::on_on_pb_modifier_clicked()
{


        int id =ui->comboBox_reser->currentText().toInt();
        QString prenom =ui->lineEdit_nom_2->text();
        QString nom =ui->lineEdit_prenom_2->text();
        QDate date_d=ui->dateEdit_date_d->date();
        QDate date_f=ui->dateEdit_date_f->date();
        int nombre=ui->lineEdit_nombre->text().toInt();
            int id_service=ui->lineEdit_idservice->text().toInt();

reservation r(id,prenom,nom,date_d,date_f,nombre,id_service);

bool test=false;
         if (id>0)test=tmpreservation.modifier(r);
        {

             ui->tablreservation_2->setModel(tmpreservation.afficher());
refrech();
            QMessageBox::information(this,"Reservation supprimée","cette Reservation a eté modifiée");
        }

}




void gestion_reservation::on_on_pb_actualiser_clicked()
{
    ui->tablreservation_2->setModel(tmpreservation.afficher());
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select code from reservation");
    ui->comboBox_reser->setModel(model);


}

void gestion_reservation::on_refrech_mod_clicked()
{
    QSqlQueryModel * model2= new QSqlQueryModel();
        model2->setQuery("select id  from reservation")  ;
        ui->comboBox_reser->setModel(model2) ;
}

void gestion_reservation::on_radioButton_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from reservation ORDER BY ID ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID "));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_d "));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_f"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("nombre"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("id_service"));
ui->tablreservation_2->setModel(model) ;

}


void gestion_reservation::on_radioButton_2_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from reservation ORDER BY ID desc");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID "));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_d "));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_f"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("nombre"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("id_service"));
ui->tablreservation_2->setModel(model) ;
}

void gestion_reservation::on_lineEdit_rech_textEdited(const QString &arg1)
{
    QSqlQueryModel * model= new QSqlQueryModel();
        QSqlQuery q;
        q.prepare("select * from reservation WHERE ID like '"+ui->lineEdit_rech->text()+"' OR  NOM like '"+ui->lineEdit_rech->text()+"' OR PRENOM like '"+ui->lineEdit_rech->text()+"' ");
             tmpreservation.rechercher(q) ;
               q.exec();
               model->setQuery(q);
               ui->tablreservation_2->setModel(tmpreservation.rechercher(q));
}
void gestion_reservation::on_on_pb_ajouter_service_clicked_clicked()
{
    int id_ser =ui->lineEdit_ID_service->text().toInt();
QString type=ui->lineEdit_type->text();
QString disponibilte= ui->lineEdit_disponibilite->text();

service s(id_ser,type,disponibilte);

bool test=s.ajouter_service();
if(test)
{
ui->tableView_service->setModel(tmpservice.afficher_service());

refrech();
QMessageBox::information(nullptr, windowTitle(),QObject::tr("service ajouté"));

}
}


void gestion_reservation::on_on_pb_actualiser_2_clicked()
{

        ui->tableView_service->setModel(tmpservice.afficher_service());
        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery("select id_ser from service");
        ui->comboBox_service->setModel(model);

}

void gestion_reservation::on_on_pb_supprimer_service_clicked()
{
    int id_ser = ui->comboBox_service->currentText().toInt();
    bool test=tmpservice.supprimer_service(id_ser);
    if(test)
  {
  ui->tableView_service->setModel(tmpservice.afficher_service());

  refrech();
  QMessageBox::information(nullptr, windowTitle(),QObject::tr("Supprimé avec succés"));
  }
    else
    {
        QMessageBox::information(nullptr, windowTitle(),QObject::tr("Id n'existe pas"));
}


}

void gestion_reservation::on_on_pb_modifier_service_clicked()
{
    int id_ser =ui->comboBox_service->currentText().toInt();
    QString type =ui->lineEdit_type->text();
    QString disponibilte= ui->lineEdit_disponibilite->text();

service s(id_ser,type,disponibilte);

bool test=false;
     if (id_ser>0)test=tmpservice.modifier_service(s);
    {
         ui->tableView_service->setModel(tmpservice.afficher_service());

        QMessageBox::information(this,"service supprimé","ce service a eté modifié");
    }
}

void gestion_reservation::on_on_pb_actualiser_m_p_clicked()
{
    QSqlQueryModel * model2= new QSqlQueryModel();
        model2->setQuery("select id_ser  from service")  ;
        ui->comboBox_service->setModel(model2) ;
}

void gestion_reservation::on_lineEdit_rech_2_cursorPositionChanged(int arg1, int arg2)
{
    QSqlQueryModel * model= new QSqlQueryModel();
        QSqlQuery q;
        q.prepare("select * from service WHERE id_ser like '"+ui->lineEdit_rech_2->text()+"' OR  type like '"+ui->lineEdit_rech_2->text()+"' OR disponibilte like '"+ui->lineEdit_rech_2->text()+"' ");
             tmpservice.rechercher_m(q) ;
               q.exec();
               model->setQuery(q);
               ui->tableView_service->setModel(tmpservice.rechercher_m(q));
}

void gestion_reservation::on_pushButton_clicked()
{

}

void gestion_reservation::on_on_pb_trier_service_croissante_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from service ORDER BY id_ser ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_ser "));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("disponibilte"));
ui->tableView_service->setModel(model) ;
}

void gestion_reservation::on_on_pb_trier_service_decroissante_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from service ORDER BY id_ser desc");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_ser "));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("disponibilte"));
ui->tableView_service->setModel(model) ;
}

void gestion_reservation::on_on_pb_choisir_clicked()
{

    int id =ui->comboBox_reser->currentText().toInt();
    QSqlQuery query;
    query.prepare("select * from reservation where id=id");

      while (query.next()) {

          ui->lineEdit_nom_2->setText(query.value(1).toString());
          ui->lineEdit_prenom_2->setText(query.value(2).toString());
          ui->dateEdit_date_d->setDate(query.value(3).toDate());
          ui->dateEdit_date_f->setDate(query.value(4).toDate());
          ui->lineEdit_nombre->setText(query.value(5).toString());
          ui->lineEdit_idservice->setText(query.value(6).toString());
      }

}

void gestion_reservation::on_pushButton_3_clicked()
{
    int id_ser =ui->comboBox_service->currentText().toInt();
    QSqlQuery query;
    query.prepare("select * from service where id_ser=id_ser");

      while (query.next()) {

          ui->lineEdit_type->setText(query.value(1).toString());
          ui->lineEdit_disponibilite->setText(query.value(2).toString());
      }
}


void gestion_reservation::on_pushButton_2_clicked()
{

    QPrinter printer;

                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setOutputFileName("C:/Users/asus/Desktop/CRUUUUD/CRUUUUD/Crud_Amine/amine.pdf");

               QPainter painter;
               painter.begin(&printer);
               QFont font;

               int id =ui->comboBox_reser->currentText().toInt();
               QString prenom =ui->lineEdit_nom_2->text();
               QString nom =ui->lineEdit_prenom_2->text();
               QDate date_d=ui->dateEdit_date_d->date();
               QDate date_f=ui->dateEdit_date_f->date();
               int nombre=ui->lineEdit_nombre->text().toInt();
               int id_service=ui->lineEdit_idservice->text().toInt();

               font.setPixelSize(35);
               painter.setFont(font);
               painter.setPen(Qt::blue);

               painter.drawText(100,500,"id:");
               painter.drawText(100,300,"nom :");
               painter.drawText(100,500,"prenom:");
               painter.drawText(100,400,"date_e :");
               painter.drawText(100,500,"date_d:");
               painter.drawText(100,500,"date_e:");
               painter.drawText(100,500,"nombre:");
               painter.drawText(100,500,"id_service:");





               font.setPixelSize(22);
               painter.setFont(font);
               painter.setPen(Qt::green);
               QString iid= QString::number(id);
               QString number= QString::number(nombre);
               QString id_s= QString::number(id_service);
               QDate date_dd=ui->dateEdit_date_d->date();
               QDate date_ff=ui->dateEdit_date_f->date();



               painter.drawText(500,500,iid);
               painter.drawText(500,300,nom);
               painter.drawText(500,500,prenom);
               painter.drawText(500,400,"date_e ");
               painter.drawText(500,200,"date_d:");

               painter.drawText(500,300,number);
               painter.drawText(500,300,id_s);


               painter.end();
}


