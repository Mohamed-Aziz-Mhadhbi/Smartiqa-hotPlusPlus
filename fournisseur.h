#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include "QString"
#include "QSqlQuery"
#include "QSqlQueryModel"


class fournisseur
{
public:
    fournisseur();
    fournisseur(QString,QString,QString,QString,QString,QString);
    QString get_id_fourn();
    QString get_nom_fourn();
    QString get_tel();
    QString get_email();
    QString get_commentaire();
    QString get_adresse();

    void set_id_fourn(QString);
    void set_nom_fourn(QString);
    void set_tel(QString);
    void set_email(QString);
    void set_commentaire(QString);
    void set_adresse(QString);


    bool ajouter_fournisseur();
    QSqlQueryModel * afficher_fournisseur();
    bool supprimer_fournisseur(QString);
    bool modifier_fournisseur(fournisseur);
     QSqlQueryModel *rechercher(QSqlQuery);
     bool verif_email(QString);
     bool verif_id(QString);
     QSqlQueryModel * getMailModel();
     QSqlQueryModel * afficher_fournisseurlist();

private:
    QString id_fourn,nom_fourn,tel,email,commentaire,adresse;
};

#endif // FOURNISSEUR_H
