#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "funcionesadmin.h"
#include <QMainWindow>
#include "interfazclientes.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Ok_Acceder_clicked();

private:
    Ui::MainWindow *ui;
    FuncionesAdmin *InterfazAdmin;
    InterfazClientes *Interfaz;
};
#endif // MAINWINDOW_H
