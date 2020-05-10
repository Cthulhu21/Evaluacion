#include "agregarinventario.h"
#include "ui_agregarinventario.h"
#include "fstream"
#include <QMessageBox>
#include <QStandardItemModel>
#include "funcionesadmin.h"
#include "mainwindow.h"

using namespace std;

AgregarInventario::AgregarInventario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AgregarInventario)
{
    ui->setupUi(this);
    ui->MiniInterfazInventario->hide();
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
                    if(Caracter==';')
                    {
                        Contador++;
                    }
                    else
                    {
                        _ID+=Caracter;
                    }
                    break;
                case 1:
                    if(Caracter==';')
                    {
                        Contador++;
                    }
                    else
                    {
                        _Nombre+=Caracter;
                    }
                    break;
                case 2:
                    if(Caracter==';')
                    {
                        Contador++;
                    }
                    else
                    {
                        _Cantidad+=Caracter;
                    }
                    break;
                case 3:
                    if(Caracter==';')
                    {
                        Contador++;
                    }
                    else
                    {
                        _Precio+=Caracter;
                    }
                    break;
                }
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
    ui->Tabla->hide();
}

void AgregarInventario::on_BotonAgregar_clicked()
{
    string  ID, Nombre, Cantidad, Precio;
    QString _ID =ui->ID->text();
    QString _Nombre=ui->Nombre->text();
    QString _Cantidad=ui->Cantidad->text();
    QString _Precio=ui->Precio->text();
    bool Error=false;
    for(auto Caracter: _ID)
    {
        if(Caracter.isDigit())
        {
            ID+=Caracter.toLatin1();
        }
        else
        {
            Error=true;
            break;
        }
    }
    if(!Error)
    {
        for(auto Caracter: _Nombre)
        {
            Nombre+=Caracter.toLatin1();
        }
        for(auto Caracter: _Cantidad)
        {
            if(Caracter.isDigit())
            {
                Cantidad+=Caracter.toLatin1();
            }
            else
            {
                Error=true;
                break;
            }
        }
        if(!Error)
        {
            for(auto Caracter: _Precio)
            {
                if(Caracter.isDigit())
                {
                    Precio+=Caracter.toLatin1();
                }
                else
                {
                    Error=true;
                    break;
                }
            }
            if(Nombre=="" or Cantidad=="" or Precio=="" or ID=="")
            {
                Error=true;
            }
            if(!Error)
            {
                list<string> ListaNombre={Nombre}, ListaCantidad={Cantidad}, ListaPrecio={Precio};
                auto Insertar=Inventario.insert({ID,{ListaNombre,ListaCantidad,ListaPrecio}});
                if(Insertar.second==false)
                {
                    QMessageBox::information(this, "Error", "El elemento ya se encuentra registrado");
                }
                else
                {
                    Primera=false;
                    QMessageBox::information(this, "Exito", "Se ha registrado de manera exitosa");
                }
            }
        }
    }
    if(Error)
    {
        QMessageBox::critical(this, "Error", "Introduzca valores correctos");
        ui->Nombre->clear();
        ui->Precio->clear();
        ui->Cantidad->clear();
        ui->ID->clear();
    }
}

void AgregarInventario::on_Salir_clicked()
{

}
