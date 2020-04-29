#ifndef MainWindow_H
#define MainWindow_H
#include "evenements.h"
#include <QMainWindow>
#include"promotions.h"
#include "smtp.h"
#include "qcustomplot.h"
#include<QtSql>
#include<QtCore>
#include<QtGui>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void initialiser();
    void on_on_pb_ajouter_clicked_clicked();
    void on_on_pb_supprimer_clicked();
    void on_on_pb_modifier_clicked();

    void on_on_pb_actualiser_clicked();
    void refrech();
    void on_refrech_mod_clicked();
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_lineEdit_rech_textEdited(const QString &arg1);

    void on_on_pb_ajouter_p_clicked();

    void on_on_pb_actualiser_2_clicked();

    void on_on_pb_supprimer_promo_clicked();

    void on_on_pb_modifier_promo_clicked();

    void on_on_pb_actualiser_m_p_clicked();

    //void on_radioButton_3_clicked();

    void on_on_pb_trier_p_croissante_clicked();

    void on_on_pb_trier_promo_decroissante_clicked();



    void on_lineEdit_rech_2_cursorPositionChanged(int arg1, int arg2);


    void sendMail();
    void mailSent(QString);


    void on_on_pb_statistique_clicked();

    void on_pushButton_3_clicked();

    void on_on_pb_imprimer_clicked();


    void on_pushButton_4_clicked();

    void on_tablevenement_2_activated(const QModelIndex &index);

    void on_sendBtn_clicked();

    void on_tableView_promo_activated(const QModelIndex &index);



private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
    evenement tmpevenement;
    promotions tmppromotions;
};

#endif // MainWindow_H
