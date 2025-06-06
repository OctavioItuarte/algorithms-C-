#include <iostream>
#include <cmath>
#include "Punto.h"
#include "Lista.h"

using namespace std;

void Imprimir(Lista Solucion){
    cout << "Los puntos que forman la envoltura convexa son:\n";
    Punto T;
    while (!Solucion.esVacia()){
        T=Solucion.recuperarPrimero();
        cout << "(" << T.coordX() << "," << T.coordY() << ")"<< endl;
        Solucion.eliminarNodoPrimero();
    }
}

int Orientacion(Punto P1, Punto P2, Punto P){
    int val=(P.coordY() - P1.coordY()) * (P2.coordX() - P1.coordX()) -
               (P2.coordY() - P1.coordY()) * (P.coordX() - P1.coordX());
    if (val==0)
        return 0;
    else {
        if (val>0)
            return 1;
        else
            return -1;
    }
}

int lineDist(Punto P1, Punto P2, Punto P){
//  Abs es una funcion que devuelve el valor absoluto del numero pasado como parametro.
    return abs((P.coordY() - P1.coordY()) * (P2.coordX() - P1.coordX()) -
               (P2.coordY() - P1.coordY()) * (P.coordX() - P1.coordX()));
}

void QuickHull(Punto Puntos[], Lista & Solucion, int n, Punto P1, Punto P2, int Lado){
    int ind = -1;
    int max_dist = 0;
    for (int i=0; i<n; i++){
        int temp=lineDist(P1, P2, Puntos[i]);
        if ((Orientacion(P1, P2, Puntos[i]) == Lado) && (temp > max_dist)){
            ind=i;
            max_dist=temp;
        }
    }
    if (ind == -1){
        if (!Solucion.existeElemento(P1))
            Solucion.agregarListaFinal(P1);
        if (!Solucion.existeElemento(P2))
            Solucion.agregarListaFinal(P2);
        return;
    }
    QuickHull(Puntos, Solucion, n, Puntos[ind], P1, -Orientacion(Puntos[ind], P1, P2));
    QuickHull(Puntos, Solucion, n, Puntos[ind], P2, -Orientacion(Puntos[ind], P2, P1));
}

void PrintHull(Punto Puntos[], int n, Lista & Solucion){
    //Encuentra el punto mas chico y el mas grande en X y
    //luego llama a la funcion "QuickHull" que retorna los puntos solucion encontrados.
    if (n<3){
        cout << "El convex hull no es posible";
        return;
    }
    int min_x= 0, max_x=0;
    for (int i=1; i<n; i++){
        if (Puntos[i].coordX() < Puntos[min_x].coordX())
            min_x=i;
        if (Puntos[i].coordX() > Puntos[max_x].coordX())
            max_x=i;
    }
    QuickHull(Puntos, Solucion, n, Puntos[min_x], Puntos[max_x], 1);
    QuickHull(Puntos, Solucion, n, Puntos[min_x], Puntos[max_x], -1);
    Imprimir(Solucion);
}


void JarvisMarch(Punto Puntos[], int n, Lista Solucion){
    //Resuelve el convex hull de manera antihoraria.
    if (n<3)
        return;
    int l=0;
    for (int i=1; i<n; i++)     //Busca el punto mas a la izquierda.
        if (Puntos[i].coordX() < Puntos[l].coordX())
            l = i;
    int p=l, q;
    int a=0;
    do{
        Punto P=Puntos[p];
        Solucion.agregarListaFinal(P);   //Guarda las soluciones encontradas.
        q=(p+1)%n;
        for (int i=0; i<n; i++)    //Busca la curva mas antihorario con los tres puntos.
            if (Orientacion(Puntos[p], Puntos[i], Puntos[q]) == 1)
               q=i;
        p=q;
        a++;
    } while (p!=l);
    Imprimir(Solucion);
}

// Programa Principal
int main(){
    int n, X, Y;
    Lista Solucion;
    cout << "Ingrese cantidad de puntos" << endl;
    cin >> n;
    Punto Puntos[n];
    for (int i=0; i<n; i++){     // Le pide al usuario que cargue los puntos por teclado.
        cout <<"Ingrese primero la coordenada X y luego la coordenada en Y" << endl;
        cin >> X;
        cin >> Y;
        Punto P(X,Y);
        Puntos[i]=P;
    }
    char L;
    cout <<"Para obtener la solucion en convex hull por Jarvis March ingrese 'J', "<< endl;
    cout <<"si la quiere resolver por Divide y Conquista ingrese 'Q'"<< endl;
    cin >> L;
    if (L=='J'){
        JarvisMarch(Puntos,n, Solucion);
    }
    else{
        if (L=='Q'){
            PrintHull(Puntos, n, Solucion);
        }
        else
            cout << "El caracter ingresado no corresponde a una accion" << endl;
    }
}
