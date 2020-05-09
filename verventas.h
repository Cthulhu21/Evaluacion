#ifndef VERVENTAS_H
#define VERVENTAS_H

#include <QDialog>

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
};

#endif // VERVENTAS_H
