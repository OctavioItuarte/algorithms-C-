#ifndef GRAFOD_H_
#define GRAFOD_H_

#include <list>
#include <map>
#include <cassert>
#include "AristaCompleta.h"

using namespace std;

template <typename C>
class GrafoD
{
public:
	class Arco
	{
	public:
		Arco();
		Arco(int adyacente, const C & costo);
		int devolverAdyacente() const;
		const C & devolverCosto() const;
	private:
		int vertice;
		C costo;
	}; // class Arco

public:
	// NOTA: Dependiendo de la implementación puede ser necesario incluir otras funciones constructuras
	GrafoD();
	GrafoD(const GrafoD & otroGrafo);

	~GrafoD();

	GrafoD & operator = (const GrafoD & otroGrafo);

	int nroArcos() const;

	// Devuelve true si la cantidad de vértices es cero
	bool estaVacio() const;

	// Devuelve la cantidad de vértices del grafo
	int cantidadVertices() const;

	bool existeVertice(int vertice) const;

	bool existeArco(int origen, int destino) const;

	// PRE CONDICION: existeArco(origen, destino)
	const C & costoArco(int origen, int destino) const;

	void devolverVertices(list<int> & vertices) const;

	void devolverAdyacentes(int origen, list<Arco> & adyacentes) const;

	void agregarVertice(int vertice);

	// POST CONDICION: Para todo vértice v != vertice: !existeArco(v, vertice) && !existeArco(vertice, v)
	void eliminarVertice(int vertice);

	// PRE CONDICION: existeVertice(origen) && existeVertice(destino)
	// POST CONDICION: existeArco(origen, destino)
	//return true si se pudo agregar el arco y falso en caso contrario
	bool agregarArco(int origen, int destino, const C & costo);

	// POST CONDICION: !existeArco(origen, destino)
	void eliminarArco(int origen, int destino);

	// PRE CONDICION: existeArco(origen, destino)
	void modificarCostoArco(int origen, int destino, const C & costo);

	void grafoReverso(GrafoD<C> & reverso) ;

	void vaciar();

	void devolverAristas(list<AristaCompleta<int> > & list_aristas);

private:
	/*
	 * Definir la estructura interna
	 */
    map<int, map<int, C> > grafo;

}; // class Grafo


/*
 * Arco
 */

template <typename C>
GrafoD<C>::Arco::Arco(){
}

template <typename C>
GrafoD<C>::Arco::Arco(int adyacente, const C & costo){
    this->vertice = adyacente;
    this->costo = costo;
}

template <typename C>
int GrafoD<C>::Arco::devolverAdyacente() const{
    return vertice;
}

template <typename C>
const C & GrafoD<C>::Arco::devolverCosto() const{
    return costo;
}


/*
 * Grafo
 */

template <typename C>
GrafoD<C>::GrafoD(){

}

template <typename C>
GrafoD<C>::GrafoD(const GrafoD & otroGrafo){
    this->operator=(otroGrafo);
}

template <typename C>
GrafoD<C>::~GrafoD(){

}

template <typename C>
GrafoD<C> & GrafoD<C>::operator = (const GrafoD & otroGrafo){
    grafo.clear();
    typename map<int, map<int, C> >::const_iterator itOtro = otroGrafo.grafo.begin();
    while (itOtro != otroGrafo.grafo.end()) {
        grafo[itOtro->first] = itOtro->second;
        itOtro++;
    }
    return *this;
}

template<typename C>
int GrafoD<C>::nroArcos() const{
    list<AristaCompleta<int> > list_aristas;
    devolverAristas(list_aristas);
    return (list_aristas.size());
}

template <typename C>
bool GrafoD<C>::estaVacio() const{
    return (grafo.empty());
}

template <typename C>
int GrafoD<C>::cantidadVertices() const{
    return (grafo.size());
}

template <typename C>
bool GrafoD<C>::existeVertice(int vertice) const{
    return (grafo.find(vertice) != grafo.end());
}

template <typename C>
bool GrafoD<C>::existeArco(int origen, int destino) const{
    bool result = false;
    typename map<int, map<int, C> >::const_iterator itV = grafo.find(origen);
    if (itV != grafo.end()) {
        typename map<int, C>::const_iterator itA = itV->second.find(destino);
        if (itA != itV->second.end())
            result = true;
    }
    return result;
}

template <typename C>
const C & GrafoD<C>::costoArco(int origen, int destino) const{
//    escriba aquí su código
//    assert(existeArco(origen, destino)); //si no existe el arco se aborta la funcion costoArco
    typename map<int, map<int, C> >::const_iterator itV = grafo.find(origen);
    typename map<int, C>::const_iterator itA = itV->second.find(destino);
    return itA->second;
}

template <typename C>
void GrafoD<C>::devolverVertices(list<int> & vertices) const{
    typename map<int, map<int, C> >::const_iterator itV = grafo.begin();
    while (itV != grafo.end()) {
        vertices.push_back(itV->first);
        itV++;
    }
}

template <typename C>
void GrafoD<C>::devolverAdyacentes(int origen, list<Arco> & adyacentes) const{
    typename map<int, map<int, C> >::const_iterator itV = grafo.find(origen);
    if (itV != grafo.end()) {
        typename map<int, C>::const_iterator itA = itV->second.begin();
        while (itA != itV->second.end()) {
            adyacentes.push_back(Arco(itA->first, itA->second));
            itA++;
        }
    }
}

template <typename C>
void GrafoD<C>::agregarVertice(int vertice){
    assert(existeVertice(vertice));
    if (grafo.find(vertice) == grafo.end()) {
        map<int, C> adyacentes;
        grafo[vertice] = adyacentes;
    }
}

template <typename C>
void GrafoD<C>::eliminarVertice(int vertice){
//    escriba aquí su código
    assert(existeVertice(vertice));
    typename map<int, map<int, C> > :: iterator it = grafo.begin();
    while(it!=grafo.end()){
        eliminarArco(it->first, vertice);
        it++;
    }
    it = grafo.find(vertice);
    grafo.erase(it);
}

template <typename C>
void GrafoD<C>::modificarCostoArco(int origen, int destino, const C & costo){
//    escriba aquí su código
    assert(!existeArco(origen, destino));
}

template <typename C>
bool GrafoD<C>::agregarArco(int origen, int destino, const C & costo){
    assert(!existeArco(origen, destino));
    typename map<int, map<int, C> >::iterator itV = grafo.find(origen);
    if ((itV != grafo.end()) and existeVertice(destino)){
        itV->second[destino] = costo;
        return true;
    }
    else return false;
}

template <typename C>
void GrafoD<C>::eliminarArco(int origen, int destino){
//    escriba aquí su código
    assert(!existeArco(origen, destino));
    typename map<int, map<int, C> >::iterator itV = grafo.find(origen);
    if ((itV != grafo.end()) and existeVertice(destino)){
        typename map<int, C>::iterator itA = itV->second.find(destino);
        if (itA!=itV->second.end())
            itV->second.erase(itA);
    }
}

template <typename C>
void GrafoD<C>::grafoReverso(GrafoD<C> & reverso){
    reverso.grafo.clear();
    typename map<int, map<int, C> >::iterator itV = grafo.begin();

    // agrego los vértices a reverso
    while (itV != grafo.end()){
        reverso.agregarVertice(itV->first);
//        cout << "vertice "  << itV->first;
        itV++;
    }
    itV = grafo.begin();
    while (itV!= grafo.end()){
        typename map<int,C>::iterator itA = itV->second.begin();
        while (itA!= itV->second.end()){
            reverso.agregarArco(itA->first, itV->first, itA->second);
            itA++;
        }
        itV++;
    }
}

template <typename C>
void GrafoD<C>::vaciar(){
    grafo.clear();
}

template <typename C>
void GrafoD<C>::devolverAristas(list<AristaCompleta<int> > & list_aristas){
    list<int> vertices;
    devolverVertices(vertices);
    list<int>::iterator it_vert=vertices.begin();
    list<Arco> list_ady;
    int u, v;
    while(it_vert!=vertices.end()){
        u=*it_vert;
        list_ady.clear();
        devolverAdyacentes(*it_vert, list_ady);
        typename list<GrafoD<C>::Arco>::iterator it_ady = list_ady.begin();
        list<AristaCompleta<int> >::iterator it_aristas = list_aristas.begin();
        while (it_ady!=list_ady.end()){
            v=it_ady->devolverAdyacente();
            if (!list_aristas.empty()){
                v=it_ady->devolverAdyacente();
                while(it_aristas!=list_aristas.end() && (it_aristas->devolverVertice1()!=u || it_aristas->devolverVertice2()!=v)){
                    it_aristas++;
                }
            }
            if(it_aristas==list_aristas.end()){
                AristaCompleta<int> nueva_arista(u, v, it_ady->devolverCosto());
                list_aristas.push_back(nueva_arista);
            }
            it_ady++;
        }
        it_vert++;
    }
}

#endif /* GRAFOD_H_ */
