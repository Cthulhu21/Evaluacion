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

private:
    Ui::VerVentas *ui;
    map<string, int> CantidadCombosOriginal, CantidadInventarioOriginal;
    void CargarCombosO();
    void CargarInventario();
    void CargarCombosA();
    void CargarInventarioA();
};

#endif // VERVENTAS_H
