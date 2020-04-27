#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H
#include "QString"
#include "QSqlQuery"
#include "QSqlQueryModel"

class equipement
{
public:
    equipement();
    equipement(QString,QString,QString,QString);
    void initialiser();
    QString get_id_equipement();
    QString get_nom();
    QString get_type();
    QString get_id_fourn();
    void set_id(QString);
    void set_nom(QString);
    void set_type(QString);
    void set_id_fourn(QString);

    bool ajouter_equipement();
    QSqlQueryModel * afficher_equipement();
    bool supprimer_equipement(QString);
    QSqlQueryModel * afficher_equipementlist();
    bool modifier_equipement();

    QSqlQueryModel * getIdModel();
     QSqlQueryModel * getid_fournModel();
    bool verif_id(QString);
    QSqlQueryModel *rechercher(QSqlQuery);

private:
    QString id_equi,id_fourn,nom,type;
};

#endif // EQUIPEMENT_H
