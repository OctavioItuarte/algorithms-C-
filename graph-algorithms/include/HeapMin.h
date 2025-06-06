/* heap mínimo: árbol binario con la propiedad de que
el valor de cada nodo es menor o a lo sumo igual que el valor
de sus hijos(si estos existen)
Para cada nodo i, 1<= i <= n
	padre(i) está en i/2(parte entera inferior)  si i!= n,
	hijoizq(i) está en 2i si 2i<=n,
	hijoder(i) está en 2i+1  si 2i+1<=n
*/

/* heapDijkstra es un heap modificado para mejorar la complejidad temporal
    del algoritmo de Dijkstra.
    Permite modificar las claves según las cuales el heap está organizado.
    Para que esto se haga de forma eficiente requiere un arreglo adicional
    que almacena para cada vértice su ubicación en el heap.
*/

#ifndef heapDijkstra_H_
#define heapDijkstra_H_

#include <cassert>
#include <iostream>


using namespace std;

template <typename T>
class heapDijkstra
{
	pair<T,int> *arreglo;   // almacena distancias desde el origen y el vértice asociado
	int *pHeap;             // almacena para cada vértice , su ubicación en el arreglo
	int capacidad;
	int cantidad_elementos;
	void organizar(int i, int n);	// O(log n)

public:
    //constructores

	heapDijkstra(int capacidad);

    heapDijkstra( const pair<T,int>* elementos, int n);
        /*  Si conocemos los elementos del heapD con anterioridad,
            podemos construilo de la siguiente manera:
                -se almacenan todos los elementos en el arreglo
                -y luego aplica organizar sobre la mitad del arreglo
                (sobre cada nodo intermedio, ya que cada hoja es un heapD).
            Complejidad temporal:  O(n).
        */

	//destructor

	~heapDijkstra();

	//observadoras

	pair<T,int>& raiz() const;
        // precondición: el heapD no es vacío
        // devuelve el elemeto mínimo

	bool vacioHeapD() const;
        // devuelve true si el heapD está vacío, false en otro caso

    int get_cantidad_elementos() {return cantidad_elementos;} // para debuggear

	//modificacoras

	void insertar(const pair<T,int>& elem);		// O(log n)
        //precondición: el heapD no está lleno

	void eliminar();		// O(log n)
        //precondición: el heapD no es vacío
        //elimina la raiz del heapD

    void imprimir();	// este método no un método propio de un heap,
                        // fue implementado con el fin de comprobar que
						// el heap construido cumple la propiedad del heap
						// util para debuggear

    void modificar(T& elem, int v);  // esta función no es propia del heap
                        // es especial para el heap usado por Dijkstra
                        // ya que las distancias del origen a los vértices en V-S
                        // pueden ser modificadas en cada paso.
                        // Nota: Las distancias, si se modifican,lo hacen por valores menores
};

// ---------------- heapDijkstra.cpp ----------------

template <typename T>
heapDijkstra<T>::heapDijkstra(int capacidad)
{
    arreglo= new pair<T,int>[capacidad];
    pHeap= new int[capacidad];
    this->capacidad= capacidad;
	cantidad_elementos= 0;
}

template <typename T>
heapDijkstra<T>::heapDijkstra( const pair<T,int>* elementos, const int n)
{
    arreglo= new T[n];
    pHeap= new T[n];
	capacidad = cantidad_elementos = n;
	for ( int i = 0; i < n; i++)
		{
        arreglo[i]= elementos[i];
		pHeap[elementos[i].second]= i;
		}
	for ( int i = (cantidad_elementos/2)-1; i >= 0; i--)
		organizar(i, cantidad_elementos-1);
}

template <typename T>
heapDijkstra<T>::~heapDijkstra()
{
    delete[] arreglo;
    delete[] pHeap;
}

template <typename T>
pair<T,int> & heapDijkstra<T>::raiz()const
{
    return arreglo[0];
}

template <typename T>
bool heapDijkstra<T>::vacioHeapD()const
{
    return cantidad_elementos == 0;
}

template <typename T>
void heapDijkstra<T>::insertar(const pair<T,int>& item)
{
    assert (cantidad_elementos < capacidad);
	int i= cantidad_elementos;
	while ((i>0) && (arreglo[(i-1)/2] > item))
		{
		    arreglo[i]= arreglo[(i-1)/2];
		    pHeap[arreglo[(i-1)/2].second]=i;
			i=(i-1)/2;
        }
    arreglo[i]= item;
    cantidad_elementos++;
}

template <typename T>
void heapDijkstra<T>::organizar(int i, int n)
{
    int hijo = 2*i+1;
    pair<T,int> item = arreglo[i]
        ;
    bool ubicado= false;
	while (hijo <= n && ubicado == false)
		{
		if ((hijo < n) && (arreglo[hijo] > arreglo[hijo+1]))  //compara hijo izq. y der.
            hijo++;								       // deja hijo apuntando al menor
        if (item <= arreglo[hijo])
            ubicado= true;            //se encontró posición para item
        else
            {
            arreglo[i]= arreglo[hijo];
            pHeap[arreglo[hijo].second]=i;
            i= hijo;
            hijo= hijo*2+1;
            }
		}
	arreglo[i]= item;
	pHeap[item.second]= i;
}

template <typename T>
void heapDijkstra<T>::eliminar()
{
    assert( ! vacioHeapD() );
    arreglo[0]= arreglo[--cantidad_elementos];
    if (cantidad_elementos > 0)
        organizar(0, cantidad_elementos-1);
}

template <typename T>
void heapDijkstra<T>::imprimir()
{
    int n=1;  // cantidad de nodos a imprimir por nivel
    for (int i=0; i<cantidad_elementos; )
    {
        for (int j= 1; j<= n && i < cantidad_elementos;  j++)   // 2^i
            cout << arreglo[i++] << '\t';
        cout<< endl;
        n= 2*n;
    }
	cout<<"\n";
}

template <typename T>
void heapDijkstra<T>::modificar(T& elem, int v)
{
    arreglo[pHeap[v]].first= elem;
    int i= pHeap[v];
	while ((i>0) && (arreglo[(i-1)/2].first > elem))
		{
		    arreglo[i]= arreglo[(i-1)/2];
		    pHeap[arreglo[(i-1)/2].second]=i;
			i=(i-1)/2;
        }
    arreglo[i]= pair<int,int> (elem,v);
}

#endif /* heapDijkstra_H_ */
