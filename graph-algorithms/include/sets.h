#ifndef SETS_H
#define SETS_H


class Sets {
private:
    int *p;
    int count; // almacena la cantidad de conjuntos
public:
    Sets (int n);
    ~ Sets ();
    int Count();
    bool Connected (int i, int j);
    void Union (int i, int j);
    int Find (int j);
    void Imprimir(int n);
};

Sets::Sets (int n) {
    p= new int[n+1];
    for (int i=0; i<=n; i++)
        p[i]= -1;
    count = n;
}

Sets::~Sets () {
    delete []p;
}

int Sets::Count(){
    return count; //devuelve la cantidad de conjuntos
}

void Sets::Union (int i, int j) {

    int temp = p[i] + p[j];
    if ( p[i] > p[j]){ // i tiene menos nodos
        p[i] = j;
        p [j] = temp;
    }
    else{ // j tiene menos nodos
        p[j] = i ;
        p [i] = temp;
    }
    count--;
}
int Sets::Find(int i){
    int r = i, temp;
    while (p[r] >= 0)
        r = p[r]; // encuentra la raíz
    while ( i != r) { // cuelga cada nodo en el camino de i a la raíz de la raíz
        temp = p[i];
        p[i] = r;
        i= temp;
    }
    return r;
}


bool Sets::Connected (int i, int j){
    return (Find(i) == Find(j)); // true si i y j están en la misma componente
} // false en otro caso

void Sets::Imprimir(int n){
    for(int i=1;i<=n;i++){
        cout<< "vertice: " << i << " predecesor " << p[i] << endl;
    }
}

#endif // SETS_H
