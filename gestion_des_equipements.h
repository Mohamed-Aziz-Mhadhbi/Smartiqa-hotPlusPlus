#ifndef GESTION_DES_EQUIPEMENTS_H
#define GESTION_DES_EQUIPEMENTS_H

#include <QDialog>
#include "equipement.h"
#include "fournisseur.h"
namespace Ui {
class gestion_des_equipements;
}

class gestion_des_equipements : public QDialog
{
    Q_OBJECT

public:
    explicit gestion_des_equipements(QWidget *parent = nullptr);
    ~gestion_des_equipements();

private slots:
    void initialiser();

    void on_pushButton_4_clicked();   

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_radioButton_2_clicked();

    void on_radioButton_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_clicked();

    void on_ajouter_four_clicked();

    void on_modifier_four_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_supprimer_four_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_8_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_3_clicked();

    void on_comboBox_3_activated(const QString &arg1);

    void on_pushButton_6_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::gestion_des_equipements *ui;
    equipement tmpequi;
    fournisseur tmpfour;
};

#endif // GESTION_DES_EQUIPEMENTS_H
