#include "agregarcombos.h"
#include "ui_agregarcombos.h"
#include <fstream>
#include <QMessageBox>

AgregarCombos::AgregarCombos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AgregarCombos)
{
    ui->setupUi(this);
    Cargar();
    CargarInventario();
    TablaInventario();
    on_Combos_clicked();
    ui->CajaAgregarCombos->hide();
    ui->CajaEliminarCombo->hide();
    ui->TablaInventario->hide();
}

AgregarCombos::~AgregarCombos()
{
    delete ui;
}

void AgregarCombos::CargarInventario()
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
            if(_ID!="")
            {
                Inventario[_ID]={Informacion};
            }
        }
        Archivo.close();
    }
}


void AgregarCombos::Cargar()
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
            string Linea, ID, Contenido, PrecioTotal, Cantidad;
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
                        Contenido+=Caracter;
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
                Combos[ID]={Contenido,Cantidad,PrecioTotal};
            }
        }
    }
}

void AgregarCombos::on_Combos_clicked()
{
    ui->CajaAgregarCombos->hide();
    ui->Tabla->show();
    ui->CajaEliminarCombo->hide();
    ui->TablaInventario->hide();
    if(!Primera)
    {
        ui->Tabla->clearContents();
        ui->Tabla->setColumnCount(4);
        QStringList Cabecera, IDs, Contenido, PreciosTotales, Cantidad;
        Cabecera << "ID" << "Contenido"<<"Cantidad"<< "Precio Total";
        for(auto Item: Combos)
        {
            QString _IDs, _Contenido,_PreciosTotales, _Cantidad;
            for(auto Caracter: Item.first)
            {
                _IDs+=Caracter;
            }
            int Contador=0;
            for(auto Elementos: Item.second)
            {
                if(Contador==0)
                {
                    for(auto Caracter: Elementos)
                    {
                        _Contenido+=Caracter;
                    }
                }
                else if(Contador==1)
                {
                    for(auto Caracter: Elementos)
                    {
                        _Cantidad+=Caracter;
                    }
                }
                else
                {
                    for(auto Caracter: Elementos)
                    {
                        _PreciosTotales+=Caracter;
                    }
                }
                Contador++;
            }
            IDs<<_IDs;
            Contenido<<_Contenido;
            PreciosTotales<<_PreciosTotales;
            Cantidad<<_Cantidad;
        }
        ui->Tabla->setHorizontalHeaderLabels(Cabecera);
        int Fila=0;
        auto ComienzoContenido=Contenido.begin(), ComienzoPreciosTotales=PreciosTotales.begin();
        auto ComienzoCantidad=Cantidad.begin();
        for(auto Elemento: IDs)
        {
            ui->Tabla->insertRow(ui->Tabla->rowCount());
            ui->Tabla->setItem(Fila,0, new QTableWidgetItem(Elemento));
            ui->Tabla->setItem(Fila,1, new QTableWidgetItem(*ComienzoContenido));
            ui->Tabla->setItem(Fila,2, new QTableWidgetItem(*ComienzoCantidad));
            ui->Tabla->setItem(Fila++,3, new QTableWidgetItem(*ComienzoPreciosTotales));
            ComienzoContenido++, ComienzoPreciosTotales++, ComienzoCantidad++;
        }
        Primera=true;
    }
}

void AgregarCombos::on_AgregarCombo_clicked()
{
    ui->Tabla->hide();
    ui->TablaInventario->hide();
    ui->CajaAgregarCombos->show();
    ui->CajaEliminarCombo->hide();
}

void AgregarCombos::on_Reiniciar_clicked()
{
    NuevasIDs.clear();
}

void AgregarCombos::on_Listo_clicked()
{
    QString _ID=ui->TextoID->text(), _Precio=ui->TextoPrecio->text();
    QString _Contenido=ui->TextoNombre->text(), _Cantidad=ui->TextoCantidad->text();
    bool Error=false;
    string ID, Precio, Contenido, Cantidad;
    for(auto Caracter: _ID)
    {
        if(!Caracter.isDigit())
        {
            Error=true;
            break;
        }
        else
        {
            ID+=Caracter.toLatin1();
        }
    }
    if(!Error)
    {
        for(auto Caracter: _Precio)
        {
            if(!Caracter.isDigit())
            {
                Error=true;
                break;
            }
            else
            {
                Precio+=Caracter.toLatin1();
            }
        }
        if(!Error)
        {
            int a=0;
            for(auto Caracter: _Contenido)
            {
                Contenido+=Caracter.toLatin1();
                a++;
            }
            Error=(a==0)?true: false;
            if(!Error)
            {
                for(auto Caracter: _Cantidad)
                {
                    if(!Caracter.isDigit())
                    {
                        Error=true;
                        break;
                    }
                    else
                    {
                        Cantidad+=Caracter.toLatin1();
                    }
                }
                if(!Error)
                {
                    auto Insertar=Combos.insert({ID,{Contenido,Cantidad,Precio}});
                    if(Insertar.second)
                    {
                        QMessageBox::information(this,"Exito","Combo agregado con exito");
                        ui->TextoID->clear();
                        ui->TextoNombre->clear();
                        ui->TextoPrecio->clear();
                        ui->TextoCantidad->clear();
                        Primera=false;
                    }
                    else
                    {
                        QMessageBox::information(this, "Error", "La ID ingresada ya está registrada");
                    }
                }
                else
                {
                    QMessageBox::critical(this, "Error", "Ingrese datos válidos");
                }
            }
            else
            {
                QMessageBox::critical(this, "Error", "Ingrese datos válidos");
            }
        }
        else
        {
            QMessageBox::critical(this, "Error", "Ingrese datos válidos");
        }
    }
    else
    {
        QMessageBox::critical(this, "Error", "Ingrese datos válidos");
    }
}

void AgregarCombos::on_EliminarCombo_clicked()
{
    ui->CajaEliminarCombo->show();
    ui->Tabla->hide();
    ui->TablaInventario->hide();
    ui->CajaAgregarCombos->hide();
}

void AgregarCombos::on_BotonEliminarCombo_clicked()
{
    QString _ID=ui->TextoEliminarCombo->text();
    string ID;
    bool Error=false;
    for(auto Caracter: _ID)
    {
        if(!Caracter.isDigit())
        {
            Error=true;
            break;
        }
        else
        {
            ID+=Caracter.toLatin1();
        }
    }
    if(!Error)
    {
        Error=(Combos.find(ID)==Combos.end())? true: false;
        if(!Error)
        {
            Combos.erase(ID);
            QMessageBox::information(this, "Exito", "Se ha borrado el combo");
            ui->TextoEliminarCombo->clear();
            Primera=false;
        }
        else
        {
            QMessageBox::critical(this, "Error", "Ingrese un valor válido");
        }
    }
    else
    {
        QMessageBox::critical(this, "Error", "Ingrese un valor válido");
    }
}

void AgregarCombos::on_Salir_clicked()
{
    this->close();
}

void AgregarCombos::on_Guardar_clicked()
{
    ofstream Archivo;
    Archivo.open("Combos.txt",ios::out);
    if(Archivo.fail())
    {
        QMessageBox::critical(this, "Error", "Ha ocurrido un error al intentar abrir el archivo");
    }
    else
    {
        for(auto Elemento : Combos)
        {
            string ID=Elemento.first, ID_Elementos, Precio, Cantidad;
            int Contador=0;
            for(auto Lista: Elemento.second)
            {
                switch (Contador)
                {
                case 0:
                    for(auto Caracter : Lista)
                    {
                        ID_Elementos+=string(1,Caracter);
                    }
                    break;
                case 1:
                    for(auto Caracter :Lista)
                    {
                        Cantidad+=string(1,Caracter);
                    }
                    break;
                case 2:
                    for(auto Caracter : Lista)
                    {
                        Precio+=string(1,Caracter);
                    }
                    break;
                }
                Contador++;
            }
            Archivo<<ID<<";"<<ID_Elementos<<";"<<Cantidad<<";"<<Precio<<endl;
        }
        Archivo.close();
    }
}

void AgregarCombos::on_BotonInventario_clicked()
{
    TablaInventario();
    ui->TablaInventario->show();
    ui->Tabla->hide();
    ui->CajaAgregarCombos->hide();
    ui->CajaEliminarCombo->hide();
}

void AgregarCombos::TablaInventario()
{
    if(!PrimeraInventario)
    {
        ui->TablaInventario->clearContents();
        ui->TablaInventario->setColumnCount(4);
        QStringList Cabecera, IDs, Nombres, Cantidades, Precios;
        Cabecera << "ID" << "Nombre" << "Cantidad" << "Precio";
        for(auto Item: Inventario)
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
                    for(auto Caracter: Lista)
                    {
                        _Nombres+=Caracter;
                    }
                }
                else if(Contador==1)
                {
                    for(auto Caracter: Lista)
                    {
                            _Cantidades+=Caracter;
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
            Nombres<<_Nombres;
            Cantidades<<_Cantidades;
            Precios<<_Precios;
        }
        ui->TablaInventario->setHorizontalHeaderLabels(Cabecera);
        int Fila=0;
        auto ComienzoNombre=Nombres.begin(), ComienzoCantidades=Cantidades.begin(), ComienzoPrecios=Precios.begin();
        for(auto Elemento: IDs)
        {
            ui->TablaInventario->insertRow(ui->TablaInventario->rowCount());
            ui->TablaInventario->setItem(Fila, 0, new QTableWidgetItem(Elemento));
            ui->TablaInventario->setItem(Fila,1, new QTableWidgetItem(*ComienzoNombre));
            ui->TablaInventario->setItem(Fila,2, new QTableWidgetItem(*ComienzoCantidades));
            ui->TablaInventario->setItem(Fila++,3, new QTableWidgetItem(*ComienzoPrecios));
            ComienzoNombre++, ComienzoPrecios++, ComienzoCantidades++;
        }
        PrimeraInventario=true;
    }
}

