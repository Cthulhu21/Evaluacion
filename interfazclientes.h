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

private:
    Ui::InterfazClientes *ui;
    void CargarInventario();
    void CargarCombos();
    void MostrarTabla();
    list<string> Ventas;
    QList<QString> PaqueteActual;
    map<string,list<string>> Inventario,Combos;
};

#endif // INTERFAZCLIENTES_H
