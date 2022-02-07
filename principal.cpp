#include "principal.h"
#include "ui_principal.h"

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    // Instanciando la imagen (creando)
    mImagen = new QImage(this->size(),QImage::Format_ARGB32_Premultiplied);
    // Rellenar la imagen de color blanco
    mImagen->fill(Qt::white);
    // Instanciar el Painter a partir de la imagen
    mPainter = new QPainter(mImagen);
    mPainter->setRenderHint(QPainter::Antialiasing);
    // Inicializar otras variables
    mPuedeDibujar = false;
    mColor = Qt::black;
    mAncho = DEFAULT_ANCHO;
    mNumLineas = 0;
    this->mPuedeDibujar = false;
}

Principal::~Principal()
{
    delete ui;
    delete mPainter;
    delete mImagen;
}

void Principal::paintEvent(QPaintEvent *event)
{
    // Crear el painter de la ventana principal
    QPainter painter(this);
    // Dibujar la imagen
    painter.drawImage(0, 0, *mImagen);
    // Acepatr el evento
    event->accept();
}

void Principal::mousePressEvent(QMouseEvent *event)
{
    mPuedeDibujar = true;
    mInicial = event->pos();
    event->accept();
}

void Principal::mouseMoveEvent(QMouseEvent *event)
{
    // Validar si se puede dibujar
    if ( !mPuedeDibujar ) {
        event->accept();
        return;
    }
    if (ui->actionLibre->isChecked()){
        // Capturar el punto donde se mueve el mouse
        mFinal = event->pos();
        // Crear un pincel y establecer atributos
        QPen pincel;
        pincel.setColor(mColor);
        pincel.setWidth(mAncho);
        // Dibujar una linea
        mPainter->setPen(pincel);
        mPainter->drawLine(mInicial, mFinal);
        // Mostrar el número de líneas en la barra de estado
        ui->statusbar->showMessage("Número de líneas: " + QString::number(++mNumLineas));
        // Actualizar la interfaz
        update();
        // actualizar el punto inicial
        mInicial = mFinal;
    }
}

void Principal::mouseReleaseEvent(QMouseEvent *event)
{
    mPuedeDibujar = false;
    // Aceptar el vento
    event->accept();
    if (ui->actionLineas->isChecked()){
        if (ui->actionLibre->isChecked()){
            ui->actionLibre->setChecked(false);
        }
        if (ui->actionRectangles->isChecked()){
            ui->actionRectangles->setChecked(false);
        }
        if (ui->actionCircunferencias->isChecked()){
            ui->actionCircunferencias->setChecked(false);
        }
        // Capturar el punto donde se mueve el mouse
        mFinal = event->pos();

        // Crear un pincel y establecer atributos
        QPen pincel;
        pincel.setColor(mColor);
        pincel.setWidth(mAncho);
        // Dibujar una linea
        mPainter->setPen(pincel);
        mPainter->drawLine(mInicial, mFinal);
        // Mostrar el número de líneas en la barra de estado
        ui->statusbar->showMessage("Número de líneas: " + QString::number(++mNumLineas));
        // Actualizar la interfaz
        update();
    }
    if (ui->actionRectangles->isChecked()){
        if (ui->actionLibre->isChecked()){
            ui->actionLibre->setChecked(false);
        }
        if (ui->actionLineas->isChecked()){
            ui->actionLineas->setChecked(false);
        }
        if (ui->actionCircunferencias->isChecked()){
            ui->actionCircunferencias->setChecked(false);
        }
        // Capturar el punto donde se mueve el mouse
        mFinal = event->pos();

        // Crear un pincel y establecer atributos
        QPen pincel;
        pincel.setColor(mColor);
        pincel.setWidth(mAncho);
        // Dibujar una linea
        mPainter->setPen(pincel);
        int x2 = mInicial.x() - mFinal.x();
        int y2 = mInicial.y() - mFinal.y();

        mPainter->drawRect(mInicial.x(), mInicial.y(), -x2, -y2);
        // Mostrar el número de líneas en la barra de estado
        ui->statusbar->showMessage("Número de líneas: " + QString::number(mNumLineas += 4));
        // Actualizar la interfaz
        update();
    }
    if (ui->actionCircunferencias->isChecked()){
        if (ui->actionLibre->isChecked()){
            ui->actionLibre->setChecked(false);
        }
        if (ui->actionLineas->isChecked()){
            ui->actionLineas->setChecked(false);
        }
        if (ui->actionRectangles->isChecked()){
            ui->actionRectangles->setChecked(false);
        }
        // Capturar el punto donde se mueve el mouse
        mFinal = event->pos();

        // Crear un pincel y establecer atributos
        QPen pincel;
        pincel.setColor(mColor);
        pincel.setWidth(mAncho);
        // Dibujar una linea
        mPainter->setPen(pincel);
        float r = sqrt(pow((mFinal.x()-mInicial.x()),2)+pow((mFinal.y()-mInicial.y()),2));
        mPainter->drawEllipse(mInicial.x()-r, mInicial.y()-r, r*2, r*2);
        // Mostrar el número de líneas en la barra de estado
        ui->statusbar->showMessage("Número de líneas: " + QString::number(++mNumLineas));
        // Actualizar la interfaz
        update();
    }
}


void Principal::on_actionAncho_triggered()
{
    mAncho = QInputDialog::getInt(this,
                                  "Ancho del pincel",
                                  "Ingrese el ancho del pincel de dibujo",
                                  mAncho,
                                  1, 100);
}

void Principal::on_actionSalir_triggered()
{
    this->close();
}

void Principal::on_actionColor_triggered()
{
    mColor = QColorDialog::getColor(mColor,
                                    this,
                                    "Color del pincel");
}

void Principal::on_actionNuevo_triggered()
{
    mImagen->fill(Qt::white);
    mNumLineas = 0;
    update();
}

void Principal::on_actionGuardar_triggered()
{
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         "Guardar imagen",
                                                         QString(),
                                                         "Imágenes (*.png)");
    if ( !nombreArchivo.isEmpty() ){
        if (mImagen->save(nombreArchivo))
            QMessageBox::information(this,
                                     "Guardar imagen",
                                     "Archivo almacenado en: " + nombreArchivo);
        else
            QMessageBox::warning(this,
                                 "Guardar imagen",
                                 "No se pudo almacenar la imagen.");
    }
}

