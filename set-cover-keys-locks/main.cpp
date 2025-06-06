#include <iostream>
#include <list>
#include <cstdlib>

using namespace std;

struct Key{
    int Cant_Locks;  //Cantidad de cerraduras sin cubrir que tiene una llave
    list<int> Locks;    //Cada llave tiene su lista de cerraduras

};

//---------------------IMPRIMIR MATRIZ---------------------------
void ImprimirMat (int ** Mat,unsigned int n, unsigned int m){
    cout<<"Esta es la matriz que usted construyo  de tamanio ( "<<m<<" x "<<n<<" )"<<" tal que,"<<endl;
    cout<<"las filas son las LLAVES y las columnas son las CERRADURAS"<<endl;

    for(unsigned int i=0; i < m ; i++){
        cout<<endl;
        for(unsigned int j=0; j < n ; j++){
            cout<<Mat[i][j]<<"   ";}
    }
    cout<<endl<<endl;
}
//----------------ALGORITMO DE APROXIMACION---------------------

void Inicializacion (int **Mat, Key Keys[], list<int> & Locks, unsigned int n, unsigned int m){    //Inicializacion del arreglo de listas(Keys) y de la lista (Locks)
    unsigned int Cant_L=0;
    for(unsigned int i=0; i<m; i++){
        for(unsigned int j=0; j<n; j++){
            if( Mat[i][j] == 1)
                Keys[i].Locks.push_back(j);
            if(Cant_L != n){
                Locks.push_back(j);
                Cant_L++;}
        }
    }
}


int ObtenerMayor(Key Keys[], unsigned int m){        //Obtiene el indice del arreglo donde hay mas llaves
    int j=0;
    for(unsigned int i=1; i<m; i++){
        if(Keys[i].Cant_Locks > Keys[j].Cant_Locks)
            j=i;
    }
    return j;
}

void Eliminar (int C, list<int> & Locks, Key Keys[], unsigned int m){       //Si la cerradura está en Locks, la elimino de Locks y de Keys
    bool esta;
    list<int> :: iterator it = Locks.begin();
    while(it != Locks.end() && (C != *it)){
        it++;
    }
    if (it!=Locks.end() && (C == *it)){
        Locks.erase(it);
    }
    for(unsigned int i=0; i<m; i++){
        esta=false;
        it = Keys[i].Locks.begin();
        while(it != Keys[i].Locks.end() && !esta){
            if(*it == C){
                Keys[i].Cant_Locks--;
                Keys[i].Locks.erase(it);
                esta=true;
            }
            it++;
        }
    }

}

void SetCover(int **Mat, list<int> & S,Key Keys[],unsigned int n, unsigned int m){
    list<int> Locks;
    Inicializacion(Mat, Keys, Locks, n, m);
    while(! Locks.empty()){
        int K = ObtenerMayor(Keys, m);                //Obtiene el indice del arreglo donde hay mas llaves
        list<int> :: iterator itK=Keys[K].Locks.begin();
        while ( itK != Keys[K].Locks.end()){
            Eliminar(*itK, Locks, Keys, m);
            itK++;
        }
        Keys[K].Cant_Locks=0;
        S.push_back(K);
        itK=S.begin();
    }

    cout<<endl<<endl;
    list<int>::const_iterator itS=S.begin();
    cout<<"La/s llave/s que abre/n la/s cerradura/s : ";
    while(itS != S.end()){
        cout<<*itS+1<< " ";
        itS++;}
    cout<<endl<<endl;
}

//---------------------BACKTRACKING---------------------------

//Los mayores valores que backtracking puede devolver una respuesta en tiempo razonable se encuentran aproximadamente
//para un tamaño 80x80 de una matriz

bool Poda(list<int> parcial, int llave, int nroParcial, int nroSol){

    if(nroParcial+1 == nroSol)  //si al agregar una llave mas a "parcial", el tamaño de esta se iguala al tamaño de "solucion"
        return true;            //entonces hace la poda con esa llave

    list<int> ::iterator it =parcial.begin();
    while(it!=parcial.end() && *it!=llave)
        it++;
    if (it!=parcial.end())
        return true;            // se fija si ya existe la llave dentro de "parcial"
    else
        return false;
}

void devolverCerraduras(int **A, list<int> cerraduras, list<int> & locks, unsigned int llave, unsigned int n){
    //devuelve las cerraduras sin cubrir de "llave", las mete dentro de una lista "locks"

    list<int>::iterator it=cerraduras.begin();
    for (unsigned int i=0; i<n; i++)
        if (A[llave][i]==1){
            it=cerraduras.begin();
            while(it!=cerraduras.end() && *it!=i)
                it++;
            if(it==cerraduras.end())
                locks.push_back(i);
        }
}

void AgregarCerraduras(list<int> & cerraduras, list<int> locks){
    list<int>::iterator it=locks.begin();
    while(it!=locks.end()){
        cerraduras.push_back(*it);
        it++;
    }
}

void SacarCerraduras(list<int> & cerraduras, list<int> locks){
    list<int>::iterator it=locks.begin();
    while(it!=locks.end()){
        cerraduras.pop_back();
        it++;
    }
}

void ActualizarSolucion(list<int> & solucion, list<int> parcial, int nroParcial, int & nroSol){
    solucion.clear();
    list<int>::iterator it=parcial.begin();
    while(it!=parcial.end()){
        solucion.push_back(*it);
        it++;
    }
    it=solucion.begin();
    nroSol=nroParcial;
}

void Cover_Backtracking(int **A, list<int> cerraduras, list<int> & solucion, list<int> parcial, int nroParcial, int & nroSol, unsigned int n, unsigned int m, unsigned int llave){
    if(cerraduras.size()==n){
        if(nroParcial<nroSol){        //HOJA: cuando la lista "cerraduras" contenga todas las cerraduras
            ActualizarSolucion(solucion, parcial, nroParcial, nroSol);
        }
    }
    else{
        for(unsigned int i=llave; i<m; i++){
            list<int> locks;
            if(!Poda(parcial, i, nroParcial, nroSol)){
                parcial.push_back(i);
                devolverCerraduras(A, cerraduras, locks, i, n);
                nroParcial++;
                AgregarCerraduras(cerraduras, locks);  //agrega a "cerraduras" las cerraduras que se encuentran en "locks"
                Cover_Backtracking(A, cerraduras, solucion, parcial, nroParcial, nroSol, n, m, i);
                parcial.pop_back();
                SacarCerraduras(cerraduras, locks);   //saca de "cerraduras" los valores que estan en "locks"
                nroParcial--;
            }
        }
    }
}


int main()
{
    unsigned int m,n,r,k;

    cout<<"Por favor ingrese la cantidad de llaves : ";
    cin>> m;
    cout<<"Por favor ingrese la cantidad de cerraduras : ";
    cin>> n;
    cout<<endl;

    list<int> solucion;
    list<int> parcial;
    list<int> cerraduras;
    Key Keys[m];             //Keys es un arreglo de listas (arreglo:almacena la cant de llaves y en list :almacena las cerraduras)
    int nroParcial=0;  //indica el tamaño de la lista parcial
    int nroSol=9999;   //indica el tamaño de la lista solucion


    int **Mat=new int*[m];                //definimos la matriz que contiene las relaciones de las llaves con las cerraduras
    for(unsigned int i=0; i<m; i++){   //consideramos a la cantidad de llaves como el numero de filas
        Mat[i]=new int[n];             //y a la cantidad de cerraduras como la cantidad de columnas
    }

    for (unsigned int i=0; i<m; i++)
        for (unsigned int j=0; j<n; j++)
            Mat[i][j]=0;
    cout<<endl;

    cout<<"Escriba la/s cerradura/s que abra cada llave: "<<endl<<endl;
    for (unsigned int i=0; i<m; i++){
        int a=0;
        int j;
        cout<<"Llave "<<i+1<<" -> ";
        cout<<"Ingrese la cantidad de cerraduras que abre : ";
        cin >> k;
        while(k < 0 || k > n){
            cout<<"Usted ingreso mal,por favor ingrese un numero entre 0 y "<<n<<endl;
            cin >> k;
        }
        Keys[i].Cant_Locks = k;
        if(k != 0){
            cout<<"Ingrese que cerraduras abre la llave "<<i+1<<endl;
            while(a<k){
                cin >> j;
                while( j < 1 || j > n){
                    cout<<"Usted ingreso mal,por favor ingrese un numero entre 1 y "<<n<<endl;
                    cin>>j;
                }
                Mat[i][j-1]=1;
                a++;
            }
        }
    }

    system("cls");

    cout<<"Eliga por cual algoritmo eencontrar el conjunto minimo de llaves :"<<endl;
    cout<<"         Presione 1 (UNO) si quiere por BACKTRACKING "<<endl;
    cout<<"         Presione 2 (DOS) si quiere por APROXIMACION "<<endl;
    cout<<"         Presione 3 (TRES) si quiere ambos algoritmos "<<endl;
    cout<<"Por favor ingrese su respuesta: ";
    cin>>r;
    while(r < 1 || r > 3) //r != 1 && r != 2 && r!=3
    {
        cout<<"Usted ingreso un numero incorrecto,por favor ingrese de nuevo :";
        cin>>r;
    }
    system("cls");

    if (r == 1){
        cout<<"Usted decidio resolver por BACKTRACKING"<<endl;
        //ALGORITMO BACKTRAKING
        ImprimirMat(Mat,n,m);
        Cover_Backtracking(Mat, cerraduras, solucion, parcial, nroParcial, nroSol, n, m, 0);

        cout<<endl<<endl;
        list<int>::const_iterator itS=solucion.begin();
        cout<<"La/s llave/s que abre/n la/s cerradura/s: ";
        while(itS != solucion.end()){
            cout<<*itS+1<< " ";
            itS++;
        }
        cout<<endl<<endl;
    }
    else{
        // Tenemos un error al ingresar la opcion "2". No nos ejecuta como corresponde el algoritmo aproximado.
        // Si elegimos la opcion "3" nos devuelve ejecuta bien.
        if(r == 2){
            cout<<"Usted decidio resolver por APROXIMACION"<<endl<<endl;
            ImprimirMat(Mat,n,m);
            SetCover(Mat,solucion,Keys, n, m);
        }
        else{
            cout<<"Usted decidio resolver por ambos algoritmos"<<endl;
            ImprimirMat(Mat,n,m);
            cout<<"1)BACKTRACKING :"<<endl<<endl;
            //Backtracking
            Cover_Backtracking(Mat, cerraduras, solucion, parcial, nroParcial, nroSol, n, m, 0);
            cout<<endl<<endl;
            list<int>::const_iterator itS=solucion.begin();
            cout<<"La/s llave/s que abre/n la/s cerradura/s: ";
            while(itS != solucion.end()){
                cout<<*itS+1<< " ";
                itS++;
            }
            cout<<endl<<endl;
            solucion.clear();       //limpiamos la lista solucion
            cout<<"-------------------------------------------------------"<<endl;
            cout<<"2)APROXIMACION :"<<endl<<endl;
            SetCover(Mat,solucion,Keys, n, m);
        }
    }
    for(unsigned int i=0; i<m; i++)
        delete[] Mat[i];
    delete[]Mat;

    return 0;
}
