#ifndef AGREGARCOMBOS_H
#define AGREGARCOMBOS_H

#include <QDialog>
#include <map>
#include <list>

using namespace std;

namespace Ui {
class AgregarCombos;
}

class AgregarCombos : public QDialog
{
    Q_OBJECT

public:
    explicit AgregarCombos(QWidget *parent = nullptr);
    ~AgregarCombos();

private slots:
    void on_Combos_clicked();
    void Cargar();
    void on_AgregarCombo_clicked();

    void on_BotonAgregar_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_Reiniciar_clicked();

    void on_AgregarID_clicked();

    void on_Listo_clicked();

private:
    Ui::AgregarCombos *ui;
    map<string, list<string>> Combos;
    QList<QString> NuevasIDs;
    bool Primera=false;
};

#endif // AGREGARCOMBOS_H
