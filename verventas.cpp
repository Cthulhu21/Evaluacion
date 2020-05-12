#include "verventas.h"
#include "ui_verventas.h"
#include <fstream>
#include <QMessageBox>


VerVentas::VerVentas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VerVentas)
{
    ui->setupUi(this);
}

VerVentas::~VerVentas()
{
    delete ui;
}

void VerVentas::CargarCombosO()
{
    fstream Archivo;
    Archivo.open("Ventas.txt", ios::in);
    if(Archivo.fail())
    {
        QMessageBox::critical(this, "Error", "No se pudo abrir el archivo");
    }
    else
    {
        string Linea;
        while(!Archivo.eof())
        {
            string ID;
            int Cantidad;
            getline(Archivo,Linea);
        }
    }
}

