#ifndef GRAFOND_H
#define GRAFOND_H

#include <list>
#include <map>
#define NDEBUG
#include <assert.h>

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

	// Devuelve true si la cantidad de v�rtices es cero
	bool estaVacio() const;

	// Devuelve la cantidad de v�rtices del grafo
	int cantidadVertices() const;

	bool existeVertice(int vertice) const;

	bool existeArista(int origen, int destino) const;

	// PRE CONDICION: existeArista(origen, destino)
	const C & costoArista(int origen, int destino) const;

	void devolverVertices(list<int> & vertices) const;

	void devolverAdyacentes(int origen, list<Arista> & adyacentes) const;

	void agregarVertice(int vertice);

	// POST CONDICION: Para todo v�rtice v != vertice: !existeArista(v, vertice) && !existeArista(vertice, v)
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
    return *this;
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
//    escriba aqu� su c�digo
    assert(existeArista(origen, destino));
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
//  escriba aqu� su c�digo
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
//    escriba aqu� su c�digo
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
//    escriba aqu� su c�digo
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

    // agrego los v�rtices a reverso
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



#endif // GRAFOND_H
