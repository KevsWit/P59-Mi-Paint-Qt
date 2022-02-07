#include "principal.h"

#include <QApplication>
#include <QTranslator>
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator traducion;
    QString idioma = QLocale::system().name();
    int pos = idioma.indexOf('_');
    idioma = idioma.mid(0, pos);
    if (idioma == "fr"){
        traducion.load(":/miPaint_fr.qm");
    }else if (idioma == "en"){
        traducion.load(":/miPaint_en.qm");
    }else if(idioma == "it"){
        traducion.load(":/miPaint_it.qm");
    }else if(idioma == "de"){
        traducion.load(":/miPaint_de.qm");
    }
    if (idioma != "es"){
        a.installTranslator(&traducion);
    }
    Principal w;
    w.show();
    return a.exec();
}
