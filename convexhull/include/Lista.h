#ifndef LISTA_H
#define LISTA_H
#include "Punto.h"

class Lista:
    public Punto
{
    public:
        Lista(); //constructor
        ~Lista(); //destructor
        void agregarListaFinal (const Punto & elemento);
        int longlista() const;
        void eliminarNodoPrimero();
        void eliminarNodoFinal();
        const Punto & recuperarPrimero() const;
        bool existeElemento(Punto elemento) const;
        bool esVacia() const;
    private:
        struct nodo{
            Punto elemento;
            nodo*siguiente;
        };
        nodo*primero;
};

#endif // LISTA_H
