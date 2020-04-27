QT       += core gui network sql printsupport serialport charts  \
            multimedia multimediawidgets
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    connexion.cpp \
    equipement.cpp \
    fournisseur.cpp \
    gestion_des_equipements.cpp \
    main.cpp \
    login.cpp \
    statistiques.cpp

HEADERS += \
    connexion.h \
    equipement.h \
    fournisseur.h \
    gestion_des_equipements.h \
    login.h \
    statistiques.h

FORMS += \
    gestion_des_equipements.ui \
    login.ui \
    statistiques.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
