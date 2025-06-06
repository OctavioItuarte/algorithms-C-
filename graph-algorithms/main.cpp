#include <iostream>
#include "GrafoD.h"
#include "GrafoND.h"
#include <queue>
#include "sets.h"
#include "AristaCompleta.h"
#include "heapDijkstra.h"

using namespace std;

struct nodo{
    char estado;
    int padre;
    int tiempoi;
    int tiempof;
    int bajo;
};

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

template<typename C>
ostream & operator << (ostream & salida, const GrafoD<C> & Grafo){
	// Recorremos todos los vertices
	list<int> vertices;
	Grafo.devolverVertices(vertices);
	list<int>::iterator v = vertices.begin();

	while (v != vertices.end()) {
		salida << "    " << *v << "\n";
		// Recorremos todos los adyacentes de cada vertice
		list< typename GrafoD<C>::Arco> adyacentes;
		Grafo.devolverAdyacentes(*v, adyacentes);
		typename list< typename GrafoD<C>::Arco>::iterator ady = adyacentes.begin();
		while (ady != adyacentes.end()) {
			salida << "   " <<  *v << "->"  << ady->devolverAdyacente() << " (" << ady->devolverCosto() << ")\n";
			ady++;
		}
		v++;
	}
	return salida;
}

//-----------   R E C O R R I D O S ----------------

template<typename C>
void componentes_conexas(GrafoND<C> & g, int n){
    Sets componentes(n);
    list<AristaCompleta<int> > list_aristas;
    g.devolverAristas(list_aristas);
    list<AristaCompleta<int> >::iterator it=list_aristas.begin();
    int u, v;
    int comp_u, comp_v;
    while(it!=list_aristas.end()){
        cout << "(" << it->devolverVertice1() << ", " << it->devolverVertice2() << ") " << it->devolverCosto() << endl;
        it++;
    }
    it=list_aristas.begin();
    while(it!=list_aristas.end()){
        u=it->devolverVertice1();
        v=it->devolverVertice2();
        comp_u=componentes.Find(u);
        comp_v=componentes.Find(v);
        if (comp_u!=comp_v){
            componentes.Union(comp_u, comp_v);
        }
        it++;
    }
    cout << "cantidad: " << endl;
    componentes.Imprimir(n);
    cout << endl;
    cout << componentes.Count()<< endl;
}

template<typename C>
void DFS_PO(GrafoD<C> & g, int i, nodo marcas[], int time, int n, list<int> & list_postorden){
    time++;
    marcas[i].tiempoi = time;
    marcas[i].estado = 'V';
    list<GrafoD<int>::Arco > list_ady;
    g.devolverAdyacentes(i+1, list_ady);
    list<GrafoD<int>::Arco > :: iterator it_ady = list_ady.begin();
    while (it_ady != list_ady.end()){
        int n=it_ady->devolverAdyacente();
        if (marcas[n-1].estado == 'N'){
            marcas[n-1].padre= i;
            DFS_PO(g, n-1, marcas, time, n, list_postorden);
        }
        it_ady++;
    }
    marcas[i].estado = 'M';
    time++;
    marcas[i].tiempof = time;
    cout<< i+1 << " ";
    list_postorden.push_front(i+1);
}

template<typename C>
void DFS_Forest_PO(GrafoD<C> g, nodo marcas[], int n, list<int> & list_postorden){
    int time=0;
    for(int i=0; i<n; i++){
        marcas[i].estado = 'N';
        marcas[i].padre = -1;
        marcas[i].tiempoi = 0;
        marcas[i].tiempof = 0;
    }
    for(int i=0; i<n; i++){
        if (marcas[i].estado == 'N')
            DFS_PO(g, i, marcas, time, n, list_postorden);
    }
}

template<typename C>
void DFS_Forest_PO_Reverso(GrafoD<C> & reverso, list<int> & list_postorden, nodo marcas[], int n){
    int time=0;
    for(int i=0; i<n; i++){
        marcas[i].estado = 'N';
        marcas[i].padre = -1;
        marcas[i].tiempoi = 0;
        marcas[i].tiempof = 0;
    }
    list<int>::iterator it=list_postorden.begin();
    while(it!=list_postorden.end()){
        if (marcas[*it-1].estado == 'N'){
            cout << "\n";
            DFS(reverso, *it-1, marcas, time);
        }
        it++;
    }
}

template<typename C>
void DFS_ND (GrafoND<C> & g, int i, nodo marcas[], int & time, int tamano){
// escriba aquí su código
    time++;
    marcas[i].tiempoi = time;
    marcas[i].estado = 'V';
    list<GrafoND<int>::Arista > list_ady;
    g.devolverAdyacentes(i+1, list_ady);
    list<GrafoND<int>::Arista > :: iterator it_ady = list_ady.begin();
    while (it_ady != list_ady.end()){
        int n=it_ady->devolverAdyacente();
        if (marcas[n].estado == 'N'){
            marcas[n-1].padre = marcas[i];
            DFS_ND(g, n-1, marcas, time, tamano);
        }
        it_ady++;
    }
    marcas[i].estado = 'M';
    time++;
    marcas[i].tiempof = time;
}

template<typename C>
void DFS_Forest_ND (GrafoND<C> & g, nodo marcas[], int n){
// escriba aquí su código
    int time=0;
    for(int i=0; i<n; i++){
        marcas[i].estado = 'N';
        marcas[i].padre = -1;
        marcas[i].tiempoi = 0;
        marcas[i].tiempof = 0;
    }
    for(int i=0; i<n; i++){
        if (marcas[i].estado == 'N')
            DFS_ND(g, i, marcas, time, n);
    }
}

template<typename C>
void DFS (GrafoD<C> & g, int i, nodo marcas[], int & time){
//  escriba aquí su código
    cout<< i+1;
    time++;
    marcas[i].tiempoi = time;
    marcas[i].estado = 'V';
    list<GrafoD<int>::Arco > list_ady;
    g.devolverAdyacentes(i+1, list_ady);
    list<GrafoD<int>::Arco > :: iterator it_ady = list_ady.begin();
    while (it_ady != list_ady.end()){
        int n=it_ady->devolverAdyacente();
        if (marcas[n-1].estado == 'N'){
            cout << "->";
            marcas[n-1].padre= i+1;
            DFS(g, n-1, marcas, time);
        }
        it_ady++;
    }
    marcas[i].estado = 'M';
    time++;
    marcas[i].tiempof = time;
}

template<typename C>
void DFS_Forest (GrafoD<C> & g, nodo marcas[], int n){
//  escriba aquí su código
    int time=0;
    for(int i=0; i<n; i++){
        marcas[i].estado = 'N';
        marcas[i].padre = -1;
        marcas[i].tiempoi = 0;
        marcas[i].tiempof = 0;
    }
    for(int i=0; i<n; i++){
        if (marcas[i].estado == 'N')
            DFS(g, i, marcas, time, n);
    }
}

template<typename C>
void Bosque_BFS(GrafoD<C> & g, nodo marca[], int n){
    for (int i=0;i<n; i++){
        marca[i].estado='N';
        marca[i].padre=-1;
        marca[i].tiempof=0;
        marca[i].tiempoi=0;
    }
    for (int j=0; j<n; j++){
        if (marca[j].estado=='N')
            BFS(g, j, marca, n);
    }
}

template<typename C>
void BFS(GrafoD<C> & g, int i, nodo marcas[], int tamano){
    queue<int> F;
    F.push(i);
    marcas[i].estado='V';
    while (!F.empty()){
        list<GrafoD<int> ::Arco> list_ady;
        g.devolverAdyacentes(F.front()+1, list_ady);
        list<GrafoD<int>::Arco>::iterator it_ady = list_ady.begin();
        while(it_ady!=list_ady.end()){
            int n=it_ady->devolverAdyacente();
            if (marcas[n-1].estado=='N'){
                marcas[n-1].estado='V';
                marcas[n-1].padre=marcas[i];
                marcas[n-1].tiempoi=marcas[i].tiempoi + 1;
                F.push(it_ady->devolverAdyacente()-1);
            }
            it_ady++;
        }
        F.pop();
    }
}

template<typename C>
void Comp_Strongly_C(GrafoD<C> & g, nodo marcas[], int n){

//1. DFS_FOREST (G) rotulando a los vértices en postorden
    list<int> list_postorden;
    DFS_Forest_PO(g, marcas, n, list_postorden);

//2. Calcular GT , grafo transpuesto de G (se obtiene invirtiendo sus arcos)
    GrafoD<int> reverso;
    g.grafoReverso(reverso);

//3. DFS_FOREST ( GT ) a partir del vértice con mayor número de postorden.
    DFS_Forest_PO_Reverso(reverso, list_postorden, marcas, n);
    cout<<"\n";
    cout << "------------------------" << endl;

    cout<<reverso;

/*4. A partir del DFS_FOREST ( GT ) armar las componentes conectados.
Cada una de ellas incluye:
• los vértices de cada árbol del DFS_FOREST (GT) y
• los arcos con inicio y fin en esos vértices*/

}

template<typename C>
void DFS_Articulacion (GrafoND<C> & g, int i, nodo marcas[], int & time, list<int> & points){
    time++;
    list<int> backs;
    list<int> hijos;
    marcas[i].tiempoi = time;
    marcas[i].estado = 'V';
    list<GrafoND<int>::Arista > list_ady;
    g.devolverAdyacentes(i+1, list_ady);
    list<GrafoND<int>::Arista > :: iterator it_ady = list_ady.begin();
    while (it_ady != list_ady.end()){
        int n=it_ady->devolverAdyacente();
        if (marcas[n-1].estado == 'N'){
            marcas[n-1].padre = i+1;
            hijos.push_back(n);
            DFS_Articulacion(g, n-1, marcas, time, points);
        }
        if (marcas[n-1].estado=='V' and marcas[i].padre!=n){
            backs.push_back(n);
        }
        it_ady++;
    }
    marcas[i].estado = 'M';
    bool esPunto=false;
    int menor=marcas[i].tiempoi;
    if(!backs.empty()){
        list<int>::iterator it=backs.begin();
        while(it!=backs.end()){
            if (menor > marcas[*it-1].tiempoi)
                menor=marcas[*it-1].tiempoi;
            it++;
        }
    }
    if(!hijos.empty()){
        list<int>::iterator it=hijos.begin();
        while(it!=hijos.end()){
            if (menor > marcas[*it-1].bajo)
                menor=marcas[*it-1].bajo;
            if (marcas[*it-1].bajo >= marcas[i].tiempoi)
                esPunto=true;
            it++;
        }
    }
    if(marcas[i].padre==-1 and hijos.size()>=2){
        esPunto=true;
    }
    if (esPunto){
        points.push_back(i+1);
    }
    marcas[i].bajo=menor;
    cout <<"vertice: "<< i+1 << ", preorden: " << marcas[i].tiempoi << ", bajo: " << marcas[i].bajo << endl;
}

template<typename C>
void devolverPuntosArticulacion(GrafoND<C> & g, list<int> & points){
    int time=0;
    int n=g.cantidadVertices();
    nodo marcas[n];
    for(int i=0; i<n; i++){
        marcas[i].estado = 'N';
        marcas[i].padre = -1;
        marcas[i].tiempoi = 0;
        marcas[i].tiempof = 0;
    }
    for(int i=0; i<n; i++){
        if (marcas[i].estado == 'N')
            DFS_Articulacion(g, i, marcas, time, points);
    }
}

int ExtraerMin(list<int> vertices, int D[]){
    list<int>::iterator it_vert=vertices.begin();
    int menor=D[*it_vert-1];
    int j = *it_vert-1;
    while(it_vert!=vertices.end()){
        if(menor > D[*it_vert-1]){
            menor = D[*it_vert-1];
            j = *it_vert-1;
        }
        it_vert++;
    }
    return j;
}

template<typename C>
void Dijkstra(GrafoD<C> & g, int origen){
    int n=g.cantidadVertices();
    list<int> vertices;
    g.devolverVertices(vertices);
    int P[n];
    int D[n];
    list<int> solucion;
    solucion.push_back(origen);
    vertices.remove(origen);
    D[origen-1]=0;
    P[origen-1]=-1;
    for(int i=1; i<n; i++){
        if (g.existeArco(origen, i+1))
            D[i]=g.costoArco(origen, i+1);
        else
            D[i]=99999;
        P[i]=origen;
    }
    while(!vertices.empty()){
        int w=ExtraerMin(vertices, D);
        solucion.push_back(w+1);
        list<GrafoD<int>::Arco> list_ady;
        g.devolverAdyacentes(w+1, list_ady);
        list<GrafoD<int>::Arco>::iterator it_ady=list_ady.begin();
        while(it_ady!=list_ady.end()){
            int ady = it_ady->devolverAdyacente();
            int cost = it_ady->devolverCosto();
            if(D[ady-1] > D[w] + cost){
                D[ady-1] = D[w] + cost;
                P[ady-1] = w+1;
            }
            it_ady++;
        }
        vertices.remove(w+1);
    }
    for(int i=0;i<n;i++){
        cout << D[i] << " | " << P[i] <<endl;
    }
}

void Floyd(float A[][n], int P[][n], int C[][n], int E[][n], int T[]){
    int i, j, k;

//inicializo la matriz A de minimos costoscon los valores que estan en la matriz C
    for(i=0; i<n; i++)
        for(j=0; j<n; j++){
            A[i][j] = C[i][j];
            P[i][j]=0;
            if (C[i][j] != 9999){
                E[i][j] = C[i][j];
                if (T[j] < E[i][j])
                    T[j] = C[i][j];
            }
            else
                E[i][j]=-1;
        }

// inicializo la matriz E, donde guardo los caminos maximos

//actualizo la matriz A de minimos costos, con valores que voy encontrando
    for(k=0; k<n; k++)
        for(i=0; i<n; i++)
            for(j=0; j<n; j++){
                if (A[i][k]+A[k][j] < A[i][j]){
                    A[i][j]=A[i][k]+A[k][j];
                    P[i][j]=k+1;
                }
                if (E[i][j] < E[i][k]+E[k][j]){
                    E[i][j] = E[i][k]+E[k][j];
                    if (E[i][j] > T[j])
                        T[j] = E[i][j];
                }
            }

//actualizo la matriz E de caminos maximos
}
//-----------------   M A I N  ------------------

int main(int argc, char **argv){

    GrafoND<int> g;


	// Cargamos un GrafoDirigido dirigido
	// Primero los vértices

	g.agregarVertice(1);
	g.agregarVertice(2);
	g.agregarVertice(3);
	g.agregarVertice(4);
	g.agregarVertice(5);

    // Luego los arcos
	g.agregarArista(1, 2, 10);
	g.agregarArista(1, 4, 30);
	g.agregarArista(1, 5, 100);
	g.agregarArista(2, 3, 50);
	g.agregarArista(3, 5, 10);
	g.agregarArista(4, 3, 60);
	g.agregarArista(4, 5, 20);


    //g.eliminarArco(3, 5);
/*
    g.agregarVertice(1);
    g.agregarVertice(2);
    g.agregarVertice(3);
    g.agregarVertice(4);
    g.agregarVertice(5);
    g.agregarVertice(6);
    g.agregarVertice(7);

    g.agregarArista(1,2,0);
    g.agregarArista(1,3,0);
    g.agregarArista(1,4,0);
    g.agregarArista(2,3,0);
    g.agregarArista(2,4,0);
    g.agregarArista(1,5,0);
    g.agregarArista(5,6,0);
    g.agregarArista(6,7,0);
    g.agregarArista(5,7,0);
    g.agregarArista(3,4,0);
*/
    cout << "Estructura del GrafoDirigido: " << endl;
    cout << g;

    //g.modificarCostoArista(2, 4, 100);
//    g.eliminarVertice(7);
//    g.eliminarArista(3, 4);

    //int n = g.cantidadVertices();
    //nodo marcas[n];

    //GrafoD<int> g_reverso;
    //g.grafoReverso(g_reverso);
    //cout << "Estructura del Grafo Dirigido Reverso: " << endl;
    //cout << g_reverso;

    cout << "------------------------" << endl;
    cout << g;

    float A[n][n];
    int P[n][n], C[n][n];
    int E[n][n];
    int T[n];

    for (int i=0; i<n; i++)
        T[i]=-1;

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            C[i][j] = 0;

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(i!=j){
                if(g.existeArista(i+1,j+1)){
                    int c = g.costoArista(i+1, j+1);
                    C[i][j] = c;
                }
                else{
                    C[i][j] = 9999;
                }

            }

    Floyd(A, P, C, E, T);
    cout<<"matriz A"<<endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            cout << A[i][j] << " ";
        cout<<"\n";
    }

    cout<<"matriz P"<<endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            cout << P[i][j] << " ";
        cout<<"\n";
    }

    cout<<"matriz C"<<endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            cout << C[i][j] << " ";
        cout<<"\n";
    }

    cout<<"matriz E"<<endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            cout << E[i][j] << " ";
        cout<<"\n";
    }

    for(int i=0; i<n; i++)
            cout << T[i] << " ";


    return 0;
}
