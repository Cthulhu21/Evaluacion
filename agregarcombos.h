#ifndef AGREGARCOMBOS_H
#define AGREGARCOMBOS_H

#include <QDialog>

namespace Ui {
class AgregarCombos;
}

class AgregarCombos : public QDialog
{
    Q_OBJECT

public:
    explicit AgregarCombos(QWidget *parent = nullptr);
    ~AgregarCombos();

private:
    Ui::AgregarCombos *ui;
};

#endif // AGREGARCOMBOS_H
