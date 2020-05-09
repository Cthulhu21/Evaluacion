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
    void on_pushButton_clicked();

    void on_VerInventario_clicked();

    void on_Tabla_activated(const QModelIndex &index);

private:
    Ui::AgregarInventario *ui;
    string ID, Nombre, Cantidad, Precio;
    map<string,list<list<string>>> Inventario;
    void CargarInventario();
};

#endif // AGREGARINVENTARIO_H
