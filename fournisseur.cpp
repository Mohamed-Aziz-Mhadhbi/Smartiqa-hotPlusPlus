#include "fournisseur.h"
#include <QtDebug>
#include <QDateTime>
fournisseur::fournisseur()
{

}
fournisseur::fournisseur(QString id,QString nom,QString tel,QString ad,QString email,QString com)
{
    this->id_fourn=id;
    this->nom_fourn=nom;
    this->commentaire=com;
    this->adresse=ad;
    this->tel=tel;
    this->email=email;

}


QString fournisseur::get_id_fourn(){return  id_fourn;}
QString fournisseur::get_nom_fourn(){return  nom_fourn;}
QString fournisseur::get_tel(){return  tel;}
QString fournisseur::get_adresse(){return  adresse;}
QString fournisseur::get_email(){return email;}
QString fournisseur::get_commentaire(){return commentaire;}


void fournisseur::set_id_fourn(QString id_fourn){this->id_fourn=id_fourn;};
void fournisseur::set_nom_fourn(QString nom_fourn){this->nom_fourn=nom_fourn;};
void fournisseur::set_tel(QString tel){this->tel=tel;};
void fournisseur::set_adresse(QString adresse){this->adresse=adresse;};
void fournisseur::set_email(QString email){this->email=email;};
void fournisseur::set_commentaire(QString commentaire){this->commentaire=commentaire;};

bool fournisseur::ajouter_fournisseur()
{
    QSqlQuery query;

    query.prepare("INSERT INTO fournisseur ( ID_FOURN , NOM_FOURN , TEL , ADRESSE , EMAIL , COMMENTAIRE  ) "
                        "VALUES (:id_fourn, :nom_fourn, :tel, :adresse, :email , :commentaire)");

    query.bindValue(":id_fourn", id_fourn);
    query.bindValue(":nom_fourn", nom_fourn);
    query.bindValue(":tel", tel);
    query.bindValue(":adresse", adresse);
    query.bindValue(":email", email);
    query.bindValue(":commentaire", commentaire);


    return    query.exec();

}


QSqlQueryModel * fournisseur::afficher_fournisseur()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from fournisseur");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_fourn"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom Fourn"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Tel"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Commentaire"));
    return model;
}

bool fournisseur::supprimer_fournisseur(QString id_fourn )
{
QSqlQuery query;
QString res= QString(id_fourn);
query.prepare("Delete from fournisseur where ID_FOURN =:id_fourn ");
query.bindValue(":id_fourn", res);
return    query.exec();
}


bool fournisseur::modifier_fournisseur(fournisseur f)
{
    QSqlQuery query;
    query.prepare("UPDATE fournisseur set NOM_FOURN=:nom_fourn ,TEL=:tel ,ADRESSE=:adresse ,EMAIL=:email ,COMMENTAIRE=:commentaire  where ID_FOURN =:id_fourn ");
    query.bindValue(":id_fourn",f.get_id_fourn());
    query.bindValue(":nom_fourn",f.get_nom_fourn());
    query.bindValue(":tel",f.get_tel());
    query.bindValue(":adresse",f.get_adresse());
    query.bindValue(":email",f.get_email());
    query.bindValue(":commentaire",f.get_commentaire());
    return    query.exec();
}

QSqlQueryModel * fournisseur::afficher_fournisseurlist()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select ID_FOURN from fournisseur");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_FOURN"));
    return model;
}

QSqlQueryModel * fournisseur::rechercher(QSqlQuery q)
{
    QSqlQueryModel *model= new QSqlQueryModel();

    model->setQuery(q);
    return (model);
}


QSqlQueryModel * fournisseur::getMailModel()
{
    QSqlQuery *query = new QSqlQuery();
    QSqlQueryModel *model = new QSqlQueryModel();
    query->prepare("select ADRESSE_MAIL from fournisseur");
    query->exec();
    model->setQuery(*query);
    return model;
}


bool fournisseur::verif_email(QString ch){
   bool test=false;
   int i;
   for(i=0;i<ch.length();i++)
   {
       if(ch[i]=='@'){
           test=true;
       }
   }
   return  test;
}


bool fournisseur::verif_id(QString ch_id){
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
return test;
}
/*
bool fournisseur::verif_nom(QString nom){
    bool test=true;
    int i;
    if(nom.length()>20){
       test=false;
       return  test;
    }else{
        for(i=0;i<nom.length();i++){
            if(!(((nom[i]>='A')&&(nom[i]<='Z'))||((nom[i]>='a')&&(nom[i]<='z')&&(nom[i]<=' ')))){
                test=false;
                return  test;

        }
    }
  }
    return  test;
}
*/
