#ifndef PUNTO_H
#define PUNTO_H


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
        //modificadoras
        void moverPunto(float x, float y);
        void trasladarPunto(float x, float y);
    private:
        float z;
        float t;
};

#endif // PUNTO_H
