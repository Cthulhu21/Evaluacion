#include "clientes.h"


Clientes::Clientes(string _Asiento, list<string> _Pedido, list<string> _Nombre)
{
    Nombre=_Nombre;
    Pedido=_Pedido;
    Asiento=_Asiento;
    InformacionCliente.insert({Asiento,{Pedido,Nombre}});
}
