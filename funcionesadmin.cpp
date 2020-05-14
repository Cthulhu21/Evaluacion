#include "funcionesadmin.h"
#include "ui_funcionesadmin.h"

FuncionesAdmin::FuncionesAdmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FuncionesAdmin)
{
    ui->setupUi(this);
}

FuncionesAdmin::~FuncionesAdmin()
{
    delete ui;
}
/* Hasta el siguiente comentario; esta parte es para que sólo se pueda elegir una de las opciones mostradas
de manera que cuando se elija una de las opciones el resto se oculten*/
void FuncionesAdmin::on_AgregarCombosCheck_stateChanged(int arg1)
{
    if(arg1==2)
    {
        ui->AgregarInventarioCheck->hide();
        ui->VerVentasCheck->hide();
    }
    else
    {
        ui->AgregarInventarioCheck->show();
        ui->VerVentasCheck->show();
    }
}

void FuncionesAdmin::on_AgregarInventarioCheck_stateChanged(int arg1)
{
    if(arg1==2)
    {
        ui->AgregarCombosCheck->hide();
        ui->VerVentasCheck->hide();
    }
    else
    {
        ui->AgregarCombosCheck->show();
        ui->VerVentasCheck->show();
    }
}

void FuncionesAdmin::on_VerVentasCheck_stateChanged(int arg1)
{
    if(arg1==2)
    {
        ui->AgregarCombosCheck->hide();
        ui->AgregarInventarioCheck->hide();
    }
    else
    {
        ui->AgregarCombosCheck->show();
        ui->AgregarInventarioCheck->show();
    }
}
//hasta aquí

//Esta verifica cuál opción fue elegida e inicia su respectiva ui
void FuncionesAdmin::on_Ok_FuncionesAdmin_clicked()
{
    if(ui->AgregarCombosCheck->checkState()==2)
    {
        this->hide();
        InterfazCombos = new AgregarCombos;
        InterfazCombos->show();
    }
    else if(ui->AgregarInventarioCheck->checkState()==2)
    {
        this->hide();
        InterfazInventario = new AgregarInventario;
        InterfazInventario->show();
    }
    else if(ui->VerVentasCheck->checkState()==2)
    {
        this->hide();
        InterfazVentas=new VerVentas;
        InterfazVentas->show();
    }
}
