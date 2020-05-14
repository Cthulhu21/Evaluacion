#include "verventas.h"
#include "ui_verventas.h"
#include <fstream>
#include <QMessageBox>


VerVentas::VerVentas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VerVentas)
{
    // Se cargan las ventas en una lista y se muestra una tabla con dicha informacion
    ui->setupUi(this);
    CargarVentas();
    MostrarVentas();
}

VerVentas::~VerVentas()
{
    delete ui;
}

/*Se busca en un archivo .txt la información de las ventas*/

void VerVentas::CargarVentas()
{
    fstream Archivo;
    Archivo.open("Ventas.txt",ios::in);
    if(Archivo.fail())
    {
        QMessageBox::critical(this, "Error", "No se pudo abrir el archivo");
    }
    else
    {
        while(!Archivo.eof())
        {
            string Linea, ID, Nombre, Precio;
            getline(Archivo,Linea);
            int Contador=0;
            for( auto Caracter : Linea) // Se escoge ";" como parametro para dividir la informacion
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
                    break;
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
                IDs.push_back(ID);
                Nombres.push_back(Nombre);
                Precios.push_back(Precio);
                PrecioTotal+=stoi(Precio,nullptr,10); // Se guarda la información del total vendido
            }
        }
        Archivo.close();
    }
}

/* se muestra una tabla con todos los elementos vendidos
 ID, Nombre, Precio*/

void VerVentas::MostrarVentas()
{
    ui->Tabla->setColumnCount(3);
    QStringList Cabecera, _IDs, _Nombres, _Precios;
    Cabecera<<"ID"<<"Nombre"<<"Precio";
    for(auto Item: IDs)
    {
        QString Tempo;
        for(auto Caracter : Item)
        {
            Tempo+=Caracter;
        }
        _IDs<<Tempo;
    }
    for(auto Item: Nombres)
    {
        QString Tempo;
        for(auto Caracter : Item)
        {
            Tempo+=Caracter;
        }
        _Nombres<<Tempo;
    }
    for(auto Item: Precios)
    {
        QString Tempo;
        for(auto Caracter : Item)
        {
            Tempo+=Caracter;
        }
        _Precios<<Tempo;
    }
    ui->Tabla->setHorizontalHeaderLabels(Cabecera);
    auto ComienzoNombres=_Nombres.begin(), ComienzoPrecios=_Precios.begin();
    int Fila=0;
    for(auto ID: _IDs)
    {
        ui->Tabla->insertRow(ui->Tabla->rowCount());
        ui->Tabla->setItem(Fila, 0, new QTableWidgetItem(ID));
        ui->Tabla->setItem(Fila,1, new QTableWidgetItem(*ComienzoNombres));
        ui->Tabla->setItem(Fila++,2, new QTableWidgetItem(*ComienzoPrecios));
        ComienzoNombres++, ComienzoPrecios++;
    }
}

/*El archivo .txt se reabre, pero en modo de escritura, haciendo que su contenido se borre
y se cierra el programa
*/

void VerVentas::LimpiarVentas()
{
    fstream Archivo;
    Archivo.open("Ventas.txt",ios::out);
    if(Archivo.fail())
    {
        QMessageBox::critical(this, "Error", "No se pudo abrir el archivo");
    }
    else
    {
        QMessageBox::information(this, "Salida","Se ha limpiado las ventas");
        this->close();
    }

}


// se muestra en un mensaje cuánto fue el total vendido
void VerVentas::on_Venta_clicked()
{
    QString Texto="Las ventas hasta el momento fueron de: ";
    string Venta=to_string(PrecioTotal);
    for(auto Caracter : Venta)
    {
        Texto+=Caracter;
    }
    QMessageBox::information(this, "Venta", Texto);
}

// se llama a la funcion LimpiarVentas()
void VerVentas::on_Salir_clicked()
{
    LimpiarVentas();
}
