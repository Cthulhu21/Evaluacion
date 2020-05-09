#include "verventas.h"
#include "ui_verventas.h"

VerVentas::VerVentas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VerVentas)
{
    ui->setupUi(this);
}

VerVentas::~VerVentas()
{
    delete ui;
}
