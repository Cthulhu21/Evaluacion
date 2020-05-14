#ifndef INTERFAZCLIENTES_H
#define INTERFAZCLIENTES_H

#include <QDialog>
#include <map>
#include <list>

using namespace std;

namespace Ui {
class InterfazClientes;
}

class InterfazClientes : public QDialog
{
    Q_OBJECT

public:
    explicit InterfazClientes(QWidget *parent = nullptr);
    ~InterfazClientes();

private slots:
    void on_BotonListo_clicked();

    void on_BotoAgregarCombo_clicked();

    void on_BotonReiniciarPedido_clicked();

    void GuardarVentas();

    void on_Salir_clicked();

private:
    Ui::InterfazClientes *ui;
    void CargarInventario();
    void CargarCombos();
    void MostrarTabla();
    list<string> Ventas;
    QList<QString> PaqueteActual, Clientes;
    map<string,list<string>> Inventario,Combos;
    int Filas=0, PrecioTotal=0;
};

#endif // INTERFAZCLIENTES_H
