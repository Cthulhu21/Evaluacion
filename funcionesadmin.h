#ifndef FUNCIONESADMIN_H
#define FUNCIONESADMIN_H

#include <QDialog>
#include <agregarcombos.h>
#include <agregarinventario.h>
#include <verventas.h>
#include <map>

namespace Ui {
class FuncionesAdmin;
}

class FuncionesAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit FuncionesAdmin(QWidget *parent = nullptr);
    ~FuncionesAdmin();

private slots:
    void on_AgregarCombosCheck_stateChanged(int arg1);

    void on_AgregarInventarioCheck_stateChanged(int arg1);

    void on_Ok_FuncionesAdmin_clicked();

    void on_VerVentasCheck_stateChanged(int arg1);

private:
    Ui::FuncionesAdmin *ui;
    AgregarCombos *InterfazCombos;
    AgregarInventario *InterfazInventario;
    VerVentas *InterfazVentas;
};

#endif // FUNCIONESADMIN_H
