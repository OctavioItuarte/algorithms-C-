#include <stdio.h>
#include "Punto.h"
#include <math.h>

Punto::Punto(float x, float y){
    //ctor
    this -> z = x; //x ES LA VARIABLE DEFINIDA EN ESTE CONSTRUCTOR. z ES LA VARIABLE DEFINIDA EN LA CLASE.
    this -> t = y;
}

Punto::Punto(){
}

float Punto::coordX() const{
    return z;
}

float Punto::coordY() const{
    return t;
}

float Punto::distanciaPunto(const Punto & otroPunto) const{
    return sqrt(pow(z - otroPunto.coordX(),2)+pow(t - otroPunto.coordY(),2));
}

bool Punto::operator==(const Punto & otroPunto) const{
    return (z == otroPunto.coordX() and t == otroPunto.coordY());
}

void Punto::moverPunto(float x, float y){
    this -> z += x;
    this -> t += y;
}

void Punto::trasladarPunto(float x, float y){
    this -> z = x;
    this -> t = y;
}
