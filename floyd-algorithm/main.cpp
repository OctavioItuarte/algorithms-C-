#include <iostream>

#include "GrafoND.h"


using namespace std;

const int n= 5;

template<typename C>
ostream & operator << (ostream & salida, const GrafoND<C> & Grafo){
	// Recorremos todos los vertices
	list<int> vertices;
	Grafo.devolverVertices(vertices);
	list<int>::iterator v = vertices.begin();

	while (v != vertices.end()) {
		salida << "    " << *v << "\n";
		// Recorremos todos los adyacentes de cada vertice
		list< typename GrafoND<C>::Arista> adyacentes;
		Grafo.devolverAdyacentes(*v, adyacentes);
		typename list< typename GrafoND<C>::Arista>::iterator ady = adyacentes.begin();
		while (ady != adyacentes.end()) {
			salida << "   " <<  *v << "->"  << ady->devolverAdyacente() << " (" << ady->devolverCosto() << ")\n";
			ady++;
		}
		v++;
	}
	return salida;
}

void Floyd(float A[][n], int P[][n], int C[][n], int T[]){
    int i, j, k;

//inicializo la matriz A de minimos costos con los valores que estan en la matriz C
    for(i=0; i<n; i++)
        for(j=0; j<n; j++){
            A[i][j] = C[i][j];
            P[i][j]=0;
        }

//actualizo la matriz A de minimos costos, con valores que voy encontrando
    for(k=0; k<n; k++)
        for(i=0; i<n; i++)
            for(j=0; j<n; j++)
                if (A[i][k]+A[k][j] < A[i][j]){
                    A[i][j]=A[i][k]+A[k][j];
                    P[i][j]=k+1;
                }

// busco las excentricidades de cada vertice y las guardo en el arreglo
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
            if (T[j] < A[i][j])
                T[j]=A[i][j];

    int menor=9999;
    i=0;
    for (j=0; j<n; j++)
        if(T[j]<menor){
            menor=T[j];
            i=j;
        }
    cout <<"\n";
    cout<< "El centro del grafo es el vertice: " << i+1 <<endl;
    cout <<"\n";
}

void camino (int P[][n], int i, int j) {
    int k= P[i][j];
    if (k>0){
        camino (P,i,k-1);
        cout << k << " ";
        camino (P, k-1, j);
    }
}

void MostrarEstructuras(float A[][n], int P[][n], int C[][n], int T[]){
    cout<<"matriz A"<<endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            cout << A[i][j] << " ";
        cout<<"\n";
    }
    cout <<"\n";

    cout<<"matriz P"<<endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            cout << P[i][j] << " ";
        cout<<"\n";
    }
    cout <<"\n";

    cout<<"matriz C"<<endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            cout << C[i][j] << " ";
        cout<<"\n";
    }
    cout<<"\n";

    cout << "Arreglo de excentricidades"<<endl;
    for(int i=0; i<n; i++)
        cout << T[i] << " ";
    cout<<"\n";
}

//-----------------   M A I N  ------------------

int main(int argc, char **argv){

    GrafoND<int> g;

	g.agregarVertice(1);
	g.agregarVertice(2);
	g.agregarVertice(3);
	g.agregarVertice(4);
	g.agregarVertice(5);

	g.agregarArista(1, 2, 10);
	g.agregarArista(1, 4, 30);
	g.agregarArista(1, 5, 100);
	g.agregarArista(2, 3, 50);
	g.agregarArista(3, 5, 10);
	g.agregarArista(4, 3, 60);
	g.agregarArista(4, 5, 20);

    cout << "Estructura del GrafoNoDirigido: " << endl;
    cout << g;

    cout << "------------------------" << endl;

    float A[n][n];
    int P[n][n], C[n][n];
    int T[n];
    // arreglo donde van a estar las excentricidades de cada vertice
    for (int i=0; i<n; i++)
        T[i]=-1;

    //inicializo las estructuras
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            if(i!=j){
                if(g.existeArista(i+1,j+1)){
                    C[i][j] = g.costoArista(i+1, j+1);
                }
                else
                    C[i][j] = 9999; //asumimos que es el infinito
            }
            else
                C[i][j] = 0;
        }

    Floyd(A, P, C, T);

    // mostramos los caminos de costos minimos entre cada par de vertices
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            if (i<j){ // acotamos el recorrido de la matriz, ya que es un grafo no dirigido, solo mira de la diagonal para arriba
                cout << "camino de " << i+1 <<" hasta "<< j+1<<endl;
                cout << i+1 <<" ";
                camino(P, i, j);
                cout << j+1 <<" "<<endl;
                cout << "costo del camino: " << A[i][j]<<endl;
                cout <<"\n";
            }

//    MostrarEstructuras(A, P, C, T);

    return 0;
}
