#ifndef VERVENTAS_H
#define VERVENTAS_H
#include <QDialog>
#include <map>

using namespace std;

namespace Ui {
class VerVentas;
}

class VerVentas : public QDialog
{
    Q_OBJECT

public:
    explicit VerVentas(QWidget *parent = nullptr);
    ~VerVentas();

private slots:
    void on_Venta_clicked();

    void on_Salir_clicked();

private:
    Ui::VerVentas *ui;
    void CargarVentas();
    list<string> IDs, Nombres, Precios;
    int PrecioTotal=0;
    void MostrarVentas();
    void LimpiarVentas();
};

#endif // VERVENTAS_H
