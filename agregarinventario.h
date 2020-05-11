#ifndef AGREGARINVENTARIO_H
#define AGREGARINVENTARIO_H

#include <QDialog>
#include <map>
#include <list>

using namespace std;

namespace Ui {
class AgregarInventario;
}

class AgregarInventario : public QDialog
{
    Q_OBJECT
public:
    explicit AgregarInventario(QWidget *parent = nullptr);
    ~AgregarInventario();

private slots:
    void on_VerInventario_clicked();

    void on_AgregarElementos_clicked();

    void on_BotonAgregar_clicked();

    void on_Salir_clicked();

    void on_Guardar_clicked();

private:
    Ui::AgregarInventario *ui;
    //string ID, Nombre, Cantidad, Precio;
    map<string,list<list<string>>> Inventario;
    bool Primera=false;
    void CargarInventario();
};

#endif // AGREGARINVENTARIO_H
