#include "equipement.h"
#include <QDebug>

equipement::equipement()
{

}

equipement::equipement(QString id_equi,QString nom,QString type,QString id_fourn)
{
  this->id_equi=id_equi;
  this->nom=nom;
  this->type=type;
  this->id_fourn=id_fourn;

}
QString equipement::get_id_equipement(){return  id_equi;}
QString equipement::get_nom(){return nom;}
QString equipement::get_type(){return  type;}
QString equipement::get_id_fourn(){return  id_fourn;}
void equipement::set_id(QString id){this->id_equi=id;};
void equipement::set_nom(QString nom ){this->nom=nom;};
void equipement::set_type(QString type ){this->type=type;};
void equipement::set_id_fourn(QString id_fourn){this->id_fourn=id_fourn;};

bool equipement:: ajouter_equipement()
{
QSqlQuery query;

query.prepare("INSERT INTO  equipement (ID_EQUI, NOM, TYPE, ID_FOURN) "
                    "VALUES (:id, :nom, :type, :id_fourn)");
query.bindValue(":id", id_equi);
query.bindValue(":nom", nom);
query.bindValue(":type", type);
query.bindValue(":id_fourn", id_fourn);

return    query.exec();
}

QSqlQueryModel * equipement::afficher_equipement()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from  equipement");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EQUI"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID_FOURN"));
    return model;
}





bool equipement::supprimer_equipement(QString idd)
{
QSqlQuery query;

query.prepare("Delete from equipement where ID_EQUI = :idd ");
query.bindValue(":idd", idd);
return    query.exec();
}

QSqlQueryModel * equipement::afficher_equipementlist()
{
    QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select ID_EQUI from equipement");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EQUI"));
    return model;
}

bool equipement::modifier_equipement()
{
    QSqlQuery query;
    query.prepare("UPDATE equipement set NOM=:nom, TYPE=:type, ID_FOURN=:id_fourn where ID_EQUI =:idd ");
    query.bindValue(":idd",id_equi);
    query.bindValue(":nom",nom);
    query.bindValue(":type",type);
    query.bindValue(":id_fourn",id_fourn);
    return    query.exec();

}



QSqlQueryModel * equipement::getIdModel()
{
    QSqlQuery *query = new QSqlQuery();
    QSqlQueryModel *model = new QSqlQueryModel();
    query->prepare("select ID_EQUI from equipement");
    query->exec();
    model->setQuery(*query);
    return model;
}
QSqlQueryModel * equipement::getid_fournModel()
{
    QSqlQuery *query = new QSqlQuery();
    QSqlQueryModel *model = new QSqlQueryModel();
    query->prepare("select ID_FOURN from equipement");
    query->exec();
    model->setQuery(*query);
    return model;
}


QSqlQueryModel *  equipement::rechercher(QSqlQuery q)
{
    QSqlQueryModel *model= new QSqlQueryModel();

    model->setQuery(q);
    return (model);
}

bool equipement::verif_id(QString ch_id)
{
   bool test=true;
   int i;
   if(ch_id.length()!=8){
      test=false;
      return  test;
   }else{
       for(i=0;i<ch_id.length();i++){
           if(!((ch_id[i]>='0')&&(ch_id[i]<='9'))){
               test=false;
               return  test;
       }
       }
   }
return test;}

