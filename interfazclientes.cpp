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
    ui->TablaPedido->hide();
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
            string Linea, ID, IDs_Elementos, PrecioTotal, Cantidad;
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
                    if(Caracter==';')
                    {
                        Contador++;
                    }
                    else
                    {
                        Cantidad+=Caracter;
                    }
                    break;
                case 3:
                    PrecioTotal+=Caracter;
                    break;
                }
            }
            if(ID!="")
            {
                Combos[ID]={IDs_Elementos,Cantidad,PrecioTotal};
            }
        }
    }
}

void InterfazClientes::MostrarTabla()
{
    ui->Tabla->show();
    ui->Tabla->setColumnCount(4);
    QStringList Cabecera, IDs, Contenido, Precios, Cantidad;
    Cabecera <<"ID"<<"Contenido"<<"Cantidad"<<"Precio";
    for(auto Item: Combos)
    {
        QString _IDs,_Contenidos,_Precios,_Cantidad;
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
            else if(Contador==1)
            {
                for(auto Caracter : Lista)
                {
                    _Cantidad+=Caracter;
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
        Cantidad<<_Cantidad;
    }
    ui->Tabla->setHorizontalHeaderLabels(Cabecera);
    int Fila=0;
    auto ComienzoContenido=Contenido.begin(), ComienzoPrecios=Precios.begin(), ComienzoCantidad=Cantidad.begin();
    for(auto Elemento: IDs)
    {
        ui->Tabla->insertRow(ui->Tabla->rowCount());
        ui->Tabla->setItem(Fila, 0, new QTableWidgetItem(Elemento));
        ui->Tabla->setItem(Fila, 1, new QTableWidgetItem(*ComienzoContenido));
        ui->Tabla->setItem(Fila, 2, new QTableWidgetItem(*ComienzoCantidad));
        ui->Tabla->setItem(Fila++, 3, new QTableWidgetItem(*ComienzoPrecios));
        ComienzoPrecios++, ComienzoContenido++, ComienzoCantidad++;
    }
}


void InterfazClientes::on_BotonListo_clicked()
{
    QString Asiento=ui->TextoAsiento->text();
    if(PaqueteActual.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Ingrese su pedido");
    }
    else if(Asiento=="")
    {
        QMessageBox::critical(this, "Error", "Ingrese su asiento");
    }
    else
    {
        QString Mensaje;
        string Contenido="Debe pagar: "+to_string(PrecioTotal)+" pesos";
        for(auto Caracter: Contenido)
        {
            Mensaje+=Caracter;
        }
        QMessageBox::information(this, "Exito", Mensaje);
        for(auto Elemento: PaqueteActual)
        {
            string _Elemento;
            for(auto Caracter: Elemento)
            {
                _Elemento+=Caracter.toLatin1();
            }
            Ventas.push_back(_Elemento);
        }
        QString Informacion=Asiento+';';
        for(auto Elemento:PaqueteActual)
        {
            Informacion+=Elemento+';';
        }
        Clientes.push_back(Informacion);
        PaqueteActual.clear();
        ui->TextoAsiento->clear();
        ui->TablaPedido->clear();
        ui->TablaPedido->hide();
        Filas=0;
        PrecioTotal=0;

    }
}

void InterfazClientes::on_BotoAgregarCombo_clicked()
{
    QString _ID=ui->TextoID->text();
    string ID;
    bool Error=false;
    for(auto Caracter: _ID)
    {
        ID+=Caracter.toLatin1();
    }
    if(ID=="" or Combos.find(ID)==Combos.end())
    {
        Error=true;
    }
    if(!Error)
    {
        QStringList Cabecera;
        ui->TablaPedido->setColumnCount(2);
        Cabecera<<"Pedido"<<"Coste";
        ui->TablaPedido->setHorizontalHeaderLabels(Cabecera);

        QString Nombre, Precio;
        list<string> Contenido=Combos[ID];
        int Contador=0;
        for(auto Elemento: Contenido)
        {
            switch (Contador)
            {
            case 0:
                for(auto Caracter: Elemento)
                {
                    Nombre+=Caracter;
                }
                break;
            case 2:
                PrecioTotal+=stoi(Elemento,nullptr,10);
                for(auto Caracter:Elemento)
                {
                    Precio+=Caracter;
                }
            }
            Contador++;
        }
        ui->TablaPedido->insertRow(ui->TablaPedido->rowCount());
        ui->TablaPedido->setItem(Filas,0,new QTableWidgetItem(Nombre));
        ui->TablaPedido->setItem(Filas++,1, new QTableWidgetItem(Precio));
        ui->TablaPedido->show();
        PaqueteActual.push_back(_ID+";"+Nombre+";"+Precio);
        ui->TextoID->clear();
    }
    else
    {
        QMessageBox::critical(this, "Error", "Ingrese un ID válido");
    }
}

void InterfazClientes::on_BotonReiniciarPedido_clicked()
{
    Filas=0, PrecioTotal=0;;
    PaqueteActual.clear();
    ui->TablaPedido->clear();
    ui->TablaPedido->hide();
    QMessageBox::information(this, "Reinicio", "Se ha reiniciado su pedido");
}


void InterfazClientes::on_Salir_clicked()
{
    GuardarVentas();
    this->close();
}

void InterfazClientes::GuardarVentas()
{
    fstream Archivo;
    Archivo.open("Ventas.txt",ios::in);
    if(Archivo.fail())
    {
        QMessageBox::information(this,"Error", "No se pudieron guardar las ventas");
    }
    else
    {
        string Linea;
        while(!Archivo.eof())
        {
            string ID, Nombre, Precio;
            getline(Archivo,Linea);
            int Contador=0;
            for(auto Caracter: Linea)
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
                        Nombre+=Caracter;
                    }
                case 2:
                    if(Caracter==';')
                    {
                        Contador++;
                    }
                    else
                    {
                        Precio+=Caracter;
                    }
                    break;
                }
            }
            if(ID!="")
            {
                Ventas.push_back({ID+";"+Nombre+";"+Precio});
            }
        }
        Archivo.close();
        ofstream Archivo;
        Archivo.open("Ventas.txt",ios::out);
        for(auto Elemento: Ventas)
        {
            Archivo<<Elemento;
        }
        Archivo.close();
    }

}
