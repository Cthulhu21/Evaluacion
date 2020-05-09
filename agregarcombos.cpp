#include "agregarcombos.h"
#include "ui_agregarcombos.h"

AgregarCombos::AgregarCombos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AgregarCombos)
{
    ui->setupUi(this);
}

AgregarCombos::~AgregarCombos()
{
    delete ui;
}
