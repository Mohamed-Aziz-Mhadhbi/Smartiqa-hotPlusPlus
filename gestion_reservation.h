#ifndef GESTION_RESERVATION_H
#define GESTION_RESERVATION_H

#include <QMainWindow>
#include "reservation.h"
#include"service.h"
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
#include <QRegExpValidator>
#include <QPropertyAnimation>

namespace Ui {
class gestion_reservation;
}

class gestion_reservation : public QMainWindow
{
    Q_OBJECT

public:
    explicit gestion_reservation(QWidget *parent = nullptr);
    ~gestion_reservation();

private slots:
    void on_on_pb_ajouter_clicked_clicked();
    void on_on_pb_supprimer_clicked();
    void on_on_pb_modifier_clicked();
    void on_on_pb_actualiser_clicked();
    void refrech();
    void on_refrech_mod_clicked();
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_lineEdit_rech_textEdited(const QString &arg1);

    void on_on_pb_actualiser_2_clicked();

    void on_on_pb_actualiser_m_p_clicked();

    //void on_radioButton_3_clicked();

    void on_lineEdit_rech_2_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_clicked();

    void on_on_pb_ajouter_service_clicked_clicked();

    void on_on_pb_supprimer_service_clicked();

    void on_on_pb_modifier_service_clicked();

    void on_on_pb_trier_service_croissante_clicked();

    void on_on_pb_trier_service_decroissante_clicked();

    void on_on_pb_choisir_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::gestion_reservation *ui;
    reservation tmpreservation;
    service tmpservice;
};

#endif // GESTION_RESERVATION_H
