#include "interfazclientes.h"
#include "ui_interfazclientes.h"
#include <fstream>
#include <QMessageBox>

InterfazClientes::InterfazClientes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InterfazClientes)
{
    ui->setupUi(this);
    CargarInventario();
    CargarCombos();
    MostrarTabla();
}

InterfazClientes::~InterfazClientes()
{
    delete ui;
}

void InterfazClientes::CargarInventario()
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
            list<string> Informacion;
            Informacion.push_back({_Nombre});
            Informacion.push_back({_Cantidad});
            Informacion.push_back({_Precio});
            Inventario[_ID]={Informacion};
        }
        Archivo.close();
    }
}

void InterfazClientes::CargarCombos()
{
    ifstream Archivo;
    Archivo.open("Combos.txt",ios::in);
    if(Archivo.fail())
    {
        QMessageBox::critical(this, "Error", "No se pudo abrir el archivo");
    }
    else
    {
        while(!Archivo.eof())
        {
            string Linea, ID, IDs_Elementos, PrecioTotal;
            getline(Archivo,Linea);
            int Contador=0;
            for(auto Caracter : Linea)
            {
                switch (Contador)
                {
                case 0:
                    if(Caracter==';')
                    {
                        Contador++;
                    }
                    else
                    {
                        ID+=Caracter;
                    }
                    break;
                case 1:
                    if(Caracter==';')
                    {
                        Contador++;
                    }
                    else
                    {
                        IDs_Elementos+=Caracter;
                    }
                    break;
                case 2:
                    PrecioTotal+=Caracter;
                    break;
                }
            }
            if(ID!="")
            {
                Combos[ID]={IDs_Elementos,PrecioTotal};
            }
        }
    }
}

void InterfazClientes::MostrarTabla()
{
    ui->Tabla->show();
    ui->Tabla->setColumnCount(3);
    QStringList Cabecera, IDs, Contenido, Precios;
    Cabecera <<"ID"<<"Contenido"<<"Precio";
    for(auto Item: Combos)
    {
        QString _IDs,_Contenidos,_Precios;
        for(auto Caracter: Item.first)
        {
            _IDs+=Caracter;
        }
        int Contador=0;
        for(auto Lista: Item.second)
        {
            if(Contador==0)
            {
                for(auto Caracter: Lista)
                {
                    _Contenidos+=Caracter;
                }
            }
            else
            {
                for(auto Caracter: Lista)
                {
                    _Precios+=Caracter;
                }
            }
            Contador++;
        }
        IDs<<_IDs;
        Contenido<<_Contenidos;
        Precios<<_Precios;
    }
    ui->Tabla->setHorizontalHeaderLabels(Cabecera);
    int Fila=0;
    auto ComienzoContenido=Contenido.begin(), ComienzoPrecios=Precios.begin();
    for(auto Elemento: IDs)
    {
        ui->Tabla->insertRow(ui->Tabla->rowCount());
        ui->Tabla->setItem(Fila, 0, new QTableWidgetItem(Elemento));
        ui->Tabla->setItem(Fila, 1, new QTableWidgetItem(*ComienzoContenido));
        ui->Tabla->setItem(Fila++, 2, new QTableWidgetItem(*ComienzoPrecios));
        ComienzoPrecios++;
        ComienzoContenido++;
    }
}

