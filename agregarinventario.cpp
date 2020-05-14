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
    //Apartado que esconde algunos widgets, Carga el inventario y muestra la tabla del inventario
    ui->setupUi(this);
    ui->MiniInterfazInventario->hide();
    CargarInventario();
    on_VerInventario_clicked();
}

AgregarInventario::~AgregarInventario()
{
    delete ui;
}

void AgregarInventario::CargarInventario()// Se carga el inventario desde un archivo .txt
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
                switch(Contador) // Se usa un conteo de ";" para guardar la información y que esta se anexe a un mapa
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
            if(_ID!="") // Este condicional para evitar vacios
            {
                Inventario[_ID]={Informacion};
            }
        }
        Archivo.close();
    }
}


void AgregarInventario::on_VerInventario_clicked() // Muestra y crea la tabla del inventario
{
    ui->MiniInterfazInventario->hide();
    ui->Tabla->show();
    if(!Primera) //Revisa que no se haya creado previamente
    {
        ui->Tabla->clearContents();
        ui->Tabla->setColumnCount(4);
        QStringList Cabecera, IDs, Nombres, Cantidades, Precios;
        Cabecera << "ID" << "Nombre" << "Cantidad" << "Precio";
        for(auto Item: Inventario) //Busca la información a mostrar en la información contenida en el mapa
        {
            QString _IDs,_Nombres,_Cantidades,_Precios;;
            for(auto Caracter: Item.first)
            {
                _IDs+=Caracter;
            }
            int Contador=0;
            for(auto Lista: Item.second)
            {
                if(Contador==0)
                {
                    for(auto Elemento: Lista)
                    {
                        for(auto Letra: Elemento)
                        {
                            _Nombres+=Letra;
                        }
                    }
                }
                else if(Contador==1)
                {
                    for(auto Elemento: Lista)
                    {
                        for(auto Letra: Elemento)
                        {
                            _Cantidades+=Letra;
                        }
                    }
                }
                else
                {
                    for(auto Elemento: Lista)
                    {
                        for(auto Letra: Elemento)
                        {
                            _Precios+=Letra;
                        }
                    }
                }
                Contador++;
            }
            IDs<<_IDs;
            Nombres<<_Nombres;
            Cantidades<<_Cantidades;
            Precios<<_Precios;
        }
        ui->Tabla->setHorizontalHeaderLabels(Cabecera);
        int Fila=0;
        auto ComienzoNombre=Nombres.begin(), ComienzoCantidades=Cantidades.begin(), ComienzoPrecios=Precios.begin();
        for(auto Elemento: IDs)
        {
            ui->Tabla->insertRow(ui->Tabla->rowCount());
            ui->Tabla->setItem(Fila, 0, new QTableWidgetItem(Elemento));
            ui->Tabla->setItem(Fila,1, new QTableWidgetItem(*ComienzoNombre));
            ui->Tabla->setItem(Fila,2, new QTableWidgetItem(*ComienzoCantidades));
            ui->Tabla->setItem(Fila++,3, new QTableWidgetItem(*ComienzoPrecios));
            ComienzoNombre++, ComienzoPrecios++, ComienzoCantidades++;
        }
        Primera=true; // Como se crea la tabla, se vuelve verdadero para no volver a ser creada
    }
}

void AgregarInventario::on_AgregarElementos_clicked() // Muestra la interfaz para agregar un nuevo elemento al inventario
{
    ui->MiniInterfazInventario->show();
    ui->Tabla->hide();
}

void AgregarInventario::on_BotonAgregar_clicked() // Se revisa que los parametros para ingresar un nuevo elemento al inventario sean validos
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
                auto Insertar=Inventario.insert({ID,{ListaNombre,ListaCantidad,ListaPrecio}}); // Se intenta ingresar el archivo
                if(Insertar.second==false) // de no poderse
                {
                    QMessageBox::information(this, "Error", "El elemento ya se encuentra registrado");
                }
                else // si se puede
                {
                    Primera=false;
                    QMessageBox::information(this, "Exito", "Se ha registrado de manera exitosa");
                }
            }
        }
    }
    if(Error) // Si se encuentra un error
    {
        QMessageBox::critical(this, "Error", "Introduzca valores correctos");
        ui->Nombre->clear();
        ui->Precio->clear();
        ui->Cantidad->clear();
        ui->ID->clear();
    }
}

void AgregarInventario::on_Salir_clicked() // cerrar el programa
{
    this->close();
}

void AgregarInventario::on_Guardar_clicked() // se guarda en un archivo .txt la información contenida en el mapa del inventario
{
    ofstream Archivo;
    Archivo.open("Inventario.txt",ios::out);
    if(Archivo.fail())
    {
        QMessageBox::critical(this, "Error", "Ha ocurrido un error al intentar abrir el archivo");
    }
    else
    {
        for(auto Elemento: Inventario)
        {
            string ID=Elemento.first, Nombre, Cantidad, Precio;
            int Contador=0;
            for(auto Lista: Elemento.second)
            {
                switch (Contador)
                {
                case 0:
                    for(auto Caracter : Lista)
                    {
                        Nombre+=Caracter;
                    }
                    break;
                case 1:
                    for(auto Caracter : Lista)
                    {
                        Cantidad+=Caracter;
                    }
                    break;
                case 2:
                    for(auto Caracter : Lista)
                    {
                        Precio+=Caracter;
                    }
                    break;
                }
                Contador++;
            }
            if(ID!="") // en esta parte se escoge ";" para dividir la informacion
            {
                Archivo <<ID<<";"<<Nombre<<";"<<Cantidad<<";"<<Precio<<endl;
            }
        }
        Archivo.close();
    }
}
