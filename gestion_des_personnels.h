#ifndef GESTION_DES_PERSONNELS_H
#define GESTION_DES_PERSONNELS_H

#include <QDialog>
#include "departement.h"
#include "personnel.h"
#include "smtp.h"
#include "qcustomplot.h"
#include <QTextToSpeech>
#include "popup.h"


namespace Ui {
class Gestion_des_personnels;
}

class Gestion_des_personnels : public QDialog
{
    Q_OBJECT

public:
    explicit Gestion_des_personnels(QWidget *parent = nullptr);
    ~Gestion_des_personnels();

private slots:
    void UpadateTime();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_lineEdit_4_textChanged(const QString &arg1);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_6_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();
    void sendMail();
    void mailSent(QString);

    void on_lineEdit_12_textChanged(const QString &arg1);

    void on_radioButton_5_clicked();

    void on_radioButton_8_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_7_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_comboBox_2_activated(const QString &arg1);
    void initialiser();
    void initialiser2();

    void on_Quitrrre_clicked();

    void on_Quiuiuiui_clicked();


    void on_tableView_per_activated(const QModelIndex &index);

    void on_tableView_dep_activated(const QModelIndex &index);

private:
    Ui::Gestion_des_personnels *ui;
    departement tmpdep;
    personnel tmpper;
    QTextToSpeech *m_speech;
    QVector<QVoice> m_voices;
    PopUp *popUp;   
};

#endif // GESTION_DES_PERSONNELS_H
