#include <stdio.h>
#include "Punto.h"
#include "Lista.h"


Lista::Lista(){
    primero=NULL;
}

Lista::~Lista(){
    nodo*cursor=primero;
    nodo*aux;
    while (cursor!=NULL){
        aux=cursor->siguiente;
        delete(cursor);
        cursor=NULL;
        if (aux!=NULL){
            cursor=aux;
        }
    }
}

void Lista::agregarListaFinal(const Punto & elemento){
     if (primero){
        nodo *aux=primero;
        while (aux->siguiente!=NULL)
            aux=aux->siguiente;
        aux->siguiente=new nodo;
        aux->siguiente->elemento=elemento;
        aux->siguiente->siguiente=NULL;
    }
    else{
        primero=new nodo;
        primero->elemento=elemento;
        primero->siguiente=NULL;
    }
}

int Lista::longlista() const{
    int i=0;
    nodo*cursor=primero;
    while (cursor!=NULL){
        cursor=cursor->siguiente;
        i++;
    }
    return i;
}

void Lista::eliminarNodoPrimero(){
    nodo*cursor=primero;
    if (cursor!=NULL){
        cursor=cursor->siguiente;
        delete(primero);
        primero=cursor;
    }
}

void Lista::eliminarNodoFinal(){
    nodo*cursor=primero;
    while(cursor->siguiente!=NULL)
        cursor=cursor->siguiente;
    if (cursor->siguiente==NULL){
        delete(cursor);
        cursor=NULL;
    }
}

const Punto & Lista::recuperarPrimero() const{
    if (primero!=NULL){
        return primero->elemento;
    }
}

bool Lista::existeElemento(Punto elemento) const{
    nodo*cursor=primero;
    while ((cursor!=NULL) && ((cursor->elemento.coordX()!=elemento.coordX()) || (cursor->elemento.coordY()!=elemento.coordY()))){
        cursor=cursor->siguiente;
    }
    return (cursor!=NULL);
}

bool Lista::esVacia() const{
    if (primero!=NULL)
        return false;
    else
        return true;
}
