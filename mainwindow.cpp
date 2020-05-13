#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Ok_Acceder_clicked()
{
    QString Nombre=ui->TextUserName->text();
    QString CC=ui->TextCCUserName->text();
    if(Nombre=="A" and CC=="1")
    {
        InterfazAdmin = new FuncionesAdmin;
        this->hide();
        InterfazAdmin->show();
    }
    else
    {
        QMessageBox::information(this, "Error", "Ingreso Invalido");
    }
}

void MainWindow::on_pushButton_clicked()
{
    Interfaz = new InterfazClientes;
    this->hide();
    Interfaz->show();
}
