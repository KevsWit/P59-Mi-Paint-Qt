#include "principal.h"

#include <QApplication>
#include <QTranslator>
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Objeto para manejar las traducciones
    QTranslator traducion;
    // Obtención del idioma y la región del sistema
    QString idioma = QLocale::system().name();
    // Obtención del código del idioma en formato ISO 639-1
    int pos = idioma.indexOf('_');
    idioma = idioma.mid(0, pos);
    // Carga del archivo de traducción según el idioma
    if (idioma == "fr"){
        traducion.load(":/miPaint_fr.qm");
    }else if (idioma == "en"){
        traducion.load(":/miPaint_en.qm");
    }else if(idioma == "it"){
        traducion.load(":/miPaint_it.qm");
    }else if(idioma == "de"){
        traducion.load(":/miPaint_de.qm");
    }
    // Si es diferente de español, se instala la traducción en TODA la aplicación
    if (idioma != "es"){
        a.installTranslator(&traducion);
    }
    Principal w;
    w.show();
    return a.exec();
}
