#ifndef GRAFOND_H
#define GRAFOND_H

#include <list>
#include <map>
//#define NDEBUG
#include <assert.h>
#include "AristaCompleta.h"

using namespace std;

template <typename C>
class GrafoND
{
public:
	class Arista
	{
	public:
		Arista();
		Arista(int adyacente, const C & costo);
		int devolverAdyacente() const;
		const C & devolverCosto() const;
	private:
		int vertice;
		C costo;
	};

public:
    GrafoND();
	GrafoND(const GrafoND & otroGrafo);

	~GrafoND();

	GrafoND & operator = (const GrafoND & otroGrafo);

	int nroArcos() const;

	// Devuelve true si la cantidad de vértices es cero
	bool estaVacio() const;

	// Devuelve la cantidad de vértices del grafo
	int cantidadVertices() const;

	bool existeVertice(int vertice) const;

	bool existeArista(int origen, int destino) const;

	// PRE CONDICION: existeArista(origen, destino)
	const C & costoArista(int origen, int destino) const;

	void devolverVertices(list<int> & vertices) const;

	void devolverAdyacentes(int origen, list<Arista> & adyacentes) const;

	void agregarVertice(int vertice);

	// POST CONDICION: Para todo vértice v != vertice: !existeArista(v, vertice) && !existeArista(vertice, v)
	void eliminarVertice(int vertice);

	// PRE CONDICION: existeVertice(origen) && existeVertice(destino)
	// POST CONDICION: existeArista(origen, destino)
	//return true si se pudo agregar el Arista y falso en caso contrario
	bool agregarArista(int origen, int destino, const C & costo);

	// POST CONDICION: !existeArista(origen, destino)
	void eliminarArista(int origen, int destino);

	// PRE CONDICION: existeArista(origen, destino)
	void modificarCostoArista(int origen, int destino, const C & costo);

	void grafoReverso(GrafoND<C> & reverso) ;

	void vaciar();

	void devolverAristas(list<AristaCompleta<int> > & list_aristas);

	void devolverPuntosArticulacion(list<int> & points);

private:
	/*
	 * Definir la estructura interna
	 */
    map<int, map<int, C> > grafo;


};
template <typename C>
GrafoND<C>::Arista::Arista(){
}

template <typename C>
GrafoND<C>::Arista::Arista(int adyacente, const C & costo){
    this->vertice = adyacente;
    this->costo = costo;
}

template <typename C>
int GrafoND<C>::Arista::devolverAdyacente() const{
    return vertice;
}

template <typename C>
const C & GrafoND<C>::Arista::devolverCosto() const{
    return costo;
}


/*
 * Grafo
 */

template <typename C>
GrafoND<C>::GrafoND(){

}

template <typename C>
GrafoND<C>::GrafoND(const GrafoND & otroGrafo){
    this->operator=(otroGrafo);
}

template <typename C>
GrafoND<C>::~GrafoND(){

}

template <typename C>
GrafoND<C> & GrafoND<C>::operator = (const GrafoND & otroGrafo){
    grafo.clear();
    typename map<int, map<int, C> >::const_iterator itOtro = otroGrafo.grafo.begin();
    while (itOtro != otroGrafo.grafo.end()) {
        grafo[itOtro->first] = itOtro->second;
        itOtro++;
    }
    this->nroArcos = otroGrafo.nroArcos();
    return *this;
}

template<typename C>
int GrafoND<C>::nroArcos() const{
    list<AristaCompleta<int> > list_aristas;
    devolverAristas(list_aristas);
    return (list_aristas.size());
}

template <typename C>
bool GrafoND<C>::estaVacio() const{
    return (grafo.empty());
}

template <typename C>
int GrafoND<C>::cantidadVertices() const{
    return (grafo.size());
}

template <typename C>
bool GrafoND<C>::existeVertice(int vertice) const{
    return (grafo.find(vertice) != grafo.end());
}

template <typename C>
bool GrafoND<C>::existeArista(int origen, int destino) const{
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
const C & GrafoND<C>::costoArista(int origen, int destino) const{
//    escriba aquí su código
    typename map<int, map<int, C> >::const_iterator itV = grafo.find(origen);
    if (itV != grafo.end()) {
        typename map<int, C>::const_iterator itA = itV->second.find(destino);
        if (itA != itV->second.end())
            return itA->second;
    }
}

template <typename C>
void GrafoND<C>::devolverVertices(list<int> & vertices) const{
    typename map<int, map<int, C> >::const_iterator itV = grafo.begin();
    while (itV != grafo.end()) {
        vertices.push_back(itV->first);
        itV++;
    }
}

template <typename C>
void GrafoND<C>::devolverAdyacentes(int origen, list<Arista> & adyacentes) const{
    typename map<int, map<int, C> >::const_iterator itV = grafo.find(origen);
    if (itV != grafo.end()) {
        typename map<int, C>::const_iterator itA = itV->second.begin();
        while (itA != itV->second.end()) {
            adyacentes.push_back(Arista(itA->first, itA->second));
            itA++;
        }
    }
}

template <typename C>
void GrafoND<C>::agregarVertice(int vertice){
    if (grafo.find(vertice) == grafo.end()) {
        map<int, C> adyacentes;
        grafo[vertice] = adyacentes;
    }
}

template <typename C>
void GrafoND<C>::eliminarVertice(int vertice){
//  escriba aquí su código
    assert(existeVertice(vertice));
    typename map<int, map<int, C> > :: iterator it = grafo.begin();
    while(it!=grafo.end()){
        eliminarArista(it->first, vertice);
        it++;
    }
    it = grafo.find(vertice);
    grafo.erase(it);
}

template <typename C>
void GrafoND<C>::modificarCostoArista(int origen, int destino, const C & costo){
//    escriba aquí su código
    assert(existeArista(origen, destino));
    typename map<int, map<int, C> >::iterator itV = grafo.find(origen);
    typename map<int, map<int, C> >::iterator itV2 = grafo.find(destino);
    itV->second[destino] = costo;
    itV2->second[origen] = costo;
}

template <typename C>
bool GrafoND<C>::agregarArista(int origen, int destino, const C & costo){

    typename map<int, map<int, C> >::iterator itV = grafo.find(origen);
    typename map<int, map<int, C> >::iterator itV2 = grafo.find(destino);
    itV->second[destino] = costo;
    itV2->second[origen] = costo;
    return true;
}

template <typename C>
void GrafoND<C>::eliminarArista(int origen, int destino){
//    escriba aquí su código
    assert(existeArista(origen, destino));

    typename map<int, map<int, C> >::iterator itV = grafo.find(origen);
    typename map<int, map<int, C> >::iterator itV2 = grafo.find(destino);
    typename map<int, C>::iterator itA = itV->second.find(destino);
    typename map<int, C>::iterator itA2 = itV2->second.find(origen);
    itV->second.erase(itA);
    itV2->second.erase(itA2);
}

template <typename C>
void GrafoND<C>::grafoReverso(GrafoND<C> & reverso){
    reverso.grafo.clear();
    typename map<int, map<int, C> >::iterator itV = grafo.begin();

    // agrego los vértices a reverso
    while (itV != grafo.end()){
        reverso.agregarVertice(itV->first);
        cout << "vertice "  << itV->first;
        itV++;
    }
    itV = grafo.begin();
    while (itV!= grafo.end()){
        typename map<int,C>::iterator itA = itV->second.begin();
        while (itA!= itV->second.end()){
            reverso.agregarArista(itA->first, itV->first, itA->second);
            itA++;
        }
        itV++;
    }
}

template <typename C>
void GrafoND<C>::vaciar(){
    grafo.clear();
}

template <typename C>
void GrafoND<C>::devolverAristas(list<AristaCompleta<int> > & list_aristas){
    list<int> vertices;
    devolverVertices(vertices);
    list<int>::iterator it_vert=vertices.begin();
    list<Arista> list_ady;
    int u, v;
    while(it_vert!=vertices.end()){
        u=*it_vert;
        list_ady.clear();
        devolverAdyacentes(*it_vert, list_ady);
        typename list<GrafoND<C>::Arista>::iterator it_ady = list_ady.begin();
        list<AristaCompleta<int> >::iterator it_aristas = list_aristas.begin();
        while (it_ady!=list_ady.end()){
            v=it_ady->devolverAdyacente();
            if (!list_aristas.empty()){
                v=it_ady->devolverAdyacente();
                while(it_aristas!=list_aristas.end() && (it_aristas->devolverVertice1()!=u || it_aristas->devolverVertice2()!=v) && (it_aristas->devolverVertice1()!=v || it_aristas->devolverVertice2()!=u)){
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



#endif // GRAFOND_H
