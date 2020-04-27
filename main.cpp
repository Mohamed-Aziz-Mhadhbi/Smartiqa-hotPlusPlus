#include "login.h"
#include "connexion.h"
#include <QApplication>


int main(int argc, char *argv[])
{  QApplication a(argc, argv);

    Connexion c;

  bool test=c.ouvrirConnexion();
  Login w;

  if(test)
  {
      w.resize(484, 234);
      w.show();}


    return a.exec();}
