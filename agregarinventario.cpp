#include "agregarinventario.h"
#include "ui_agregarinventario.h"
#include "fstream"
#include <QMessageBox>
#include <QStandardItemModel>
using namespace std;

AgregarInventario::AgregarInventario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AgregarInventario)
{
    ui->setupUi(this);
}

AgregarInventario::~AgregarInventario()
{
    delete ui;
}

void AgregarInventario::CargarInventario()
{
    ifstream Archivo;
    Archivo.open("Inventario.txt",ios::in);
    if(Archivo.fail())
    {
        QMessageBox::warning(this, "Revise la base datos", "No se pudo encontrar el archivo");
    }
    else
    {
        string Linea;
        while(!Archivo.eof())
        {
            string _ID,_Nombre,_Cantidad,_Precio;
            int Contador=0;
            getline(Archivo,Linea);
            for(auto Caracter: Linea)
            {
                switch(Contador)
                {
                case 0:
                    _ID+=Caracter;
                    break;
                case 1:
                    _Nombre+=Caracter;
                    break;
                case 2:
                    _Cantidad+=Caracter;
                    break;
                case 3:
                    _Precio+=Caracter;
                    break;
                }
                Contador++;
            }
            list<list<string>> Informacion;
            Informacion.push_back({_Nombre});
            Informacion.push_back({_Cantidad});
            Informacion.push_back({_Precio});
            Inventario[_ID]={Informacion};
        }
        Archivo.close();
    }
}


void AgregarInventario::on_VerInventario_clicked()
{
    CargarInventario();
}

void AgregarInventario::on_Tabla_activated(const QModelIndex &index)
{
}
