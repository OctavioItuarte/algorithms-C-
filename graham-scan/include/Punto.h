#ifndef PUNTO_H
#define PUNTO_H
#include <math.h>
#include <stdio.h>

class Punto
{
    public:
        //constructora
        Punto(float z, float t);
        Punto();
        //observadoras
        float coordX() const;
        float coordY() const;
        float distanciaPunto(const Punto & otroPunto) const;
        bool operator==(const Punto & otroPunto) const;
    private:
        float z;
        float t;
};

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

#endif // PUNTO_H
