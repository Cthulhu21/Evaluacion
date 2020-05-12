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
    on_Combos_clicked();
    ui->CajaAgregarCombos->hide();
    CargarInventario();
    ui->CajaEliminarCombo->hide();
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
            list<list<string>> Informacion;
            Informacion.push_back({_Nombre});
            Informacion.push_back({_Cantidad});
            Informacion.push_back({_Precio});
            Inventario[_ID]={Informacion};
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
        string Linea, ID, IDs_Elementos, PrecioTotal;
        while(!Archivo.eof())
        {
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
            Combos[ID]={IDs_Elementos,PrecioTotal};
        }
    }
}

void AgregarCombos::on_Combos_clicked()
{
    ui->CajaAgregarCombos->hide();
    ui->Tabla->show();
    ui->CajaEliminarCombo->hide();
    if(!Primera)
    {
        ui->Tabla->clearContents();
        ui->Tabla->setColumnCount(3);
        QStringList Cabecera, IDs, IDs_Elementos, PreciosTotales;
        Cabecera << "ID" << "IDs Contenido" << "Precio Total";
        for(auto Item: Combos)
        {
            QString _IDs, _IDs_Elementos,_PreciosTotales;
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
                        _IDs_Elementos+=Caracter;
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
            IDs_Elementos<<_IDs_Elementos;
            PreciosTotales<<_PreciosTotales;
        }
        ui->Tabla->setHorizontalHeaderLabels(Cabecera);
        int Fila=0;
        auto ComienzoIDsContenido=IDs_Elementos.begin(), ComienzoPreciosTotales=PreciosTotales.begin();
        for(auto Elemento: IDs)
        {
            ui->Tabla->insertRow(ui->Tabla->rowCount());
            ui->Tabla->setItem(Fila,0, new QTableWidgetItem(Elemento));
            ui->Tabla->setItem(Fila,1, new QTableWidgetItem(*ComienzoIDsContenido));
            ui->Tabla->setItem(Fila++,2, new QTableWidgetItem(*ComienzoPreciosTotales));
            ComienzoIDsContenido++, ComienzoPreciosTotales++;
        }
        Primera=true;
    }
}

void AgregarCombos::on_AgregarCombo_clicked()
{
    ui->Tabla->hide();
    ui->CajaAgregarCombos->show();
    ui->CajaEliminarCombo->hide();
}

void AgregarCombos::on_Reiniciar_clicked()
{
    NuevasIDs.clear();
}

void AgregarCombos::on_AgregarID_clicked()
{
    QString ID=ui->TextoIDAgregar->text();
    bool Error=false;
    string _ID;
    for(auto Caracter: ID)
    {
        if(!Caracter.isDigit())
        {
            Error=true;
            break;
        }
        else
        {
            _ID+=Caracter.toLatin1();
        }
    }
    if(!Error)
    {
        Error=(Inventario.find(_ID)==Inventario.end())? true :false;
        if(!Error)
        {
            NuevasIDs.push_back(ID);
            ui->TextoIDAgregar->clear();
        }
        else
        {
            QMessageBox::critical(this, "Error", "Introduzca un valor válido");
            ui->TextoIDAgregar->clear();
        }
    }
    else
    {
        QMessageBox::critical(this, "Error", "Introduzca un valor válido");
        ui->TextoIDAgregar->clear();
    }
}


void AgregarCombos::on_Listo_clicked()
{
    QString ID=ui->TextoIDNueva->text(), Precio=ui->TextoPrecio->text();
    string _ID, _Precio;
    bool Error=false;
    for(auto Caracter: ID)
    {
        if(!Caracter.isDigit())
        {
            Error=true;
            break;
        }
        else
        {
            _ID+=Caracter.toLatin1();
        }
    }
    if(!Error)
    {
        for(auto Caracter: Precio)
        {
            if(!Caracter.isDigit())
            {
                Error=true;
                break;
            }
            else
            {
                _Precio+=Caracter.toLatin1();
            }
        }
        if(!Error)
        {
            string StringNuevasIDs;
            int Contador=0;
            for(auto Elemento: NuevasIDs)
            {
                for(auto Caracter: Elemento)
                {
                    StringNuevasIDs+=Caracter.toLatin1();
                }
                if(Contador<NuevasIDs.size()-1)
                {
                    StringNuevasIDs+="-";
                }
                Contador++;
            }
            auto Insertar=Combos.insert({_ID,{StringNuevasIDs,_Precio}});
            if(!Insertar.second)
            {
                QMessageBox::information(this, "Error", "El elemento ya se encuentra registrado");
            }
            else
            {
                QMessageBox::information(this, "Exito", "El combo se ha registrado de manera exitosa");
                Primera=false;
                NuevasIDs.clear();
                ui->TextoPrecio->clear();
                ui->TextoIDNueva->clear();
                ui->TextoIDAgregar->clear();
            }
        }
        else
        {
            QMessageBox::critical(this, "Error", "Escriba un valor válido");
        }
    }
    else
    {
        QMessageBox::critical(this, "Error", "Escriba un valor válido");
    }
}

void AgregarCombos::on_EliminarCombo_clicked()
{
    ui->CajaEliminarCombo->show();
    ui->Tabla->hide();
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
            string ID=Elemento.first, ID_Elementos, Precio;
            int Contador=0;
            for(auto Lista: Elemento.second)
            {
                int i=0;
                switch (Contador)
                {
                case 0:
                    for(auto Caracter : Lista)
                    {
                        if(i<int(Lista.size()))
                        {
                            ID_Elementos+=string(1,Caracter);
                        }
                        else
                        {
                            ID_Elementos+=string(1,Caracter);
                        }
                        i++;
                    }
                    break;
                case 1:
                    for(auto Caracter : Lista)
                    {
                        Precio+=string(1,Caracter);
                    }
                }
                Contador++;
            }
            Archivo<<ID<<";"<<ID_Elementos<<";"<<Precio<<endl;
        }
        Archivo.close();
    }
}
