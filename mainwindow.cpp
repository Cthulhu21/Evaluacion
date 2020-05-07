#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clientes.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Clientes Informacion("",{},{});
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Ok_Acceder_clicked()
{
    QString Nombre=ui->TextUserName->text();
    QString CC=ui->TextCCUserName->text();
    if(Nombre=="Admin" and CC=="123456789")
    {
    }
}
