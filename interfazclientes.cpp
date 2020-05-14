#include "interfazclientes.h"
#include "ui_interfazclientes.h"
#include <fstream>
#include <QMessageBox>

InterfazClientes::InterfazClientes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InterfazClientes)
{
    //apartado que carga a un mapa el inventario, los combos; también oculta widgets y muestra la interfaz de los clientes
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

void InterfazClientes::CargarInventario() // Se carga desde un archivo .txt a un mapa información respecto al inventario
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
            for(auto Caracter: Linea) // Se coge como parametro ";" para que divida la informacion
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


//se carga desde un archivo .txt a un mapa la información perteneciente a los combos
// y se carga también a una copia
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
            for(auto Caracter : Linea) // se coge como parametro ";" para dividir la informacion
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
        _Combos=Combos;
    }
}

void InterfazClientes::MostrarTabla() // Crea la tabla de combos para los clientes
{
    ui->Tabla->clear();
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

// Esta funcion modifica la cantidad de elementos de los combos

void InterfazClientes::ModificarInventario()
{
    for(auto Elemento: PaqueteActual)
    {
        string ID, Cantidad, Nombre, Precio, Booleano;
        int Contador=0;
        for(auto Caracter : Elemento)
        {
            if(Caracter==";")
            {
                Contador++;
            }
            else if(Contador==0)
            {
                ID+=Caracter.toLatin1();
            }
            else if(Contador==3)
            {
                Booleano+=Caracter.toLatin1();
            }
        }
        if(Booleano=="0") // Esto evita que se elimine más de una vez los combos que se hayan escogido
        {
            list<string> Contenido=Combos[ID];
            Contador=0;
            for(auto Item: Contenido)
            {
                switch (Contador)
                {
                case 0:
                    Nombre=Item;
                    break;
                case 1:
                    Cantidad=Item;
                    break;
                case 2:
                    Precio=Item;
                    break;
                }
                Contador++;
            }
            int _Cantidad=(stoi(Cantidad,nullptr,10));
            _Cantidad--;
            Cantidad=to_string(_Cantidad);
            if(Cantidad!="0") // Se modifica la cantidad y el parametro para acceder a esta parte de la funcion se modifica
            {
                Combos[ID]={Nombre,Cantidad,Precio,"1"};
            }
            else // Si la cantidad se vuelve 0, entonces el combo se elimina
            {
                Combos.erase(ID);
            }
        }
    }
}

/*Se revisa que los parametros de combo y asiento si sean correctos
Después busca el precio total a pagar y lo agrega a un QString que se mostrará
agrega la informacion asociada (asiento y combos) a una lista con los clientes
agrega el ID, El contenido, y su precio a una lista de ventas
Llama a la funcion ModificarInventario() para que merme la cantidad disponible de combos y muestre los cambios
borra el paquete de combos actuales
limpia los textos modificables en la UI y esconde la tabla asociada a los combos que lleva el usuario
por último reinicia las filas y el precio total y redefine la copia de combos
*/


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
        QString Informacion=Asiento+';';
        for(auto Elemento: PaqueteActual) // cada elemento del paquete se agrega a las ventas
        {
            Informacion+=Elemento+';'; // cada elemento se agrega a la informacion del cliente
            string _Elemento;
            for(auto Caracter: Elemento)
            {
                _Elemento+=Caracter.toLatin1();
            }
            Ventas.push_back(_Elemento);
        }
        Clientes.push_back(Informacion);
        ModificarInventario();
        PaqueteActual.clear();
        ui->TextoAsiento->clear();
        ui->TablaPedido->clear();
        ui->TablaPedido->hide();
        _Combos=Combos;
        MostrarTabla();
        Filas=0;
        PrecioTotal=0;

    }
}

/* Se agrega el combo a la lista actual de combos.
Modificando el precio total a pagar
y mostrando una tabla con todo los elementos del combo
llama a la funcion modificarInventario() para que merme la cantidad de combos
*/

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
        PaqueteActual.push_back(_ID+";"+Nombre+";"+Precio+";"+"0");
        ModificarInventario();
        MostrarTabla();
        ui->TextoID->clear();
    }
    else
    {
        QMessageBox::critical(this, "Error", "Ingrese un ID válido");
    }
}


/*reinicia el combo actual, y usa la copia del mapa de combos para no perder la informacion*/
void InterfazClientes::on_BotonReiniciarPedido_clicked()
{
    Filas=0, PrecioTotal=0;;
    PaqueteActual.clear();
    Combos=_Combos;
    MostrarTabla();
    ui->TablaPedido->clear();
    ui->TablaPedido->hide();
    QMessageBox::information(this, "Reinicio", "Se ha reiniciado su pedido");
}


void InterfazClientes::on_Salir_clicked() //sale del programa
{
    GuardarVentas();
    this->close();
}

/*Guarda las ventas en un archivo .txt*/

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
            for(auto Caracter: Linea) // Se busca la información que ya contiene el archivo para volver a escribirla
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
                Ventas.push_back({ID+";"+Nombre+";"+Precio}); // se coge ";" como parametro para dividir la informacion
            }
        }
        Archivo.close();
        ofstream Archivo;
        Archivo.open("Ventas.txt",ios::out);
        for(auto Elemento: Ventas) // Cada elemento de ventas se guarda en el archivo
        {
            Archivo<<Elemento;
        }
        Archivo.close();
    }

}
