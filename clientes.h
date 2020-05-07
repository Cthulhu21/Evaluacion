#ifndef CLIENTES_H
#define CLIENTES_H
#include <map>
#include <list>

using namespace std;

class Clientes
{
public:
    Clientes(string _Asiento, list<string> _Pedido, list<string> _Nombre);
    map<string, list<list<string>>> InformacionCliente;
private:
    string Asiento;
    list<string> Pedido;
    list<string> _Nombre;
};

#endif // CLIENTES_H
