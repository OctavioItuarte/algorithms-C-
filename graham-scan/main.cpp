#include <iostream>
#include "Punto.h"
#include <list>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <cassert>

using namespace std;

ostream & operator << (ostream & stream, const Punto & punto) {
    return stream << "(" << punto.coordX() << "," << punto.coordY() << ")";
}

int Producto_Cruzado(Punto origen, Punto top, Punto Pi){
    float C1= Pi.coordX()-origen.coordX();
    float C2= Pi.coordY()-origen.coordY();
    float C3= top.coordX()-origen.coordX();
    float C4= top.coordY()-origen.coordY();
    return ((C1*C4)-(C2*C3));
}

void Merge(Punto Arp[], int inic, int med, int fin)
{
    int i=inic;
    int k =inic;
    int j = med+1;
    Punto c[50];
    while (i <= med && j <= fin) {
        if (Producto_Cruzado(Arp[0],Arp[i],Arp[j]) < 0) {
            c[k] = Arp[i];
            i++;
        }
        else
            if(Producto_Cruzado(Arp[0],Arp[i],Arp[j]) > 0){
                c[k] = Arp[j];
                j++;}
            else{
                if(Arp[i].coordY() < Arp[j].coordY()){
                    c[k]=Arp[i];
                    i++;}
                else{
                    c[k]=Arp[j];
                    j++;}
            }
        k++;
    }
    while (i <= med) {
        c[k] = Arp[i];
        k++;
        i++;
    }
    while (j <= fin) {
        c[k] = Arp[j];
        k++;
        j++;
    }
    for (i = inic; i < k; i++)  {
        Arp[i] = c[i];
    }
}
void merge_sort(Punto Arp[], int inic, int fin)
{
    int med;
    if (inic < fin){
        med=(inic+fin)/2;
        merge_sort(Arp,inic,med);
        merge_sort(Arp,med+1,fin);
        Merge(Arp,inic,med,fin);
    }
}

int BuscarAncla(Punto *Arp, int N){
    int ancla=0;
    for(int i=1; i < N; i++){
        if(Arp[i].coordY() < Arp[ancla].coordY())
            ancla = i;
        else
            if (Arp[i].coordY() == Arp[ancla].coordY())
                if (Arp[i].coordX() < Arp[ancla].coordX())
                    ancla = i;
    }
    return ancla;
}

void Graham_Scan(list<Punto> & solucion, Punto Arp[], int N){
    int pd;
    pd = BuscarAncla(Arp, N);
    Punto Ancla;
    Ancla=Arp[pd];
    for(int i=pd; i>0; i--)
        Arp[i]=Arp[i-1];
    Arp[0]=Ancla;

    //ordenar arreglo
    merge_sort(Arp, 1, N-1);

    //eliminar angulos repetidos
    int i=1;
    int fin=N;
    while (i<fin-1){
        while (i<fin-1 and Producto_Cruzado(Arp[0], Arp[i], Arp[i+1])==0){
            for(int k=i; k<fin-1; k++)
                Arp[k]=Arp[k+1];
            fin--;
        }
        i++;
    }

    solucion.push_back(Arp[0]);
    solucion.push_back(Arp[1]);
    solucion.push_back(Arp[2]);
    list<Punto>::iterator it=solucion.begin();
    it++;
    for(int i=3; i<fin; i++){
        while(!(Producto_Cruzado(*it, solucion.back(), Arp[i]) < 0)){
            solucion.pop_back();
            it--;
        }
        solucion.push_back(Arp[i]);
        it++;
    }
}

void Agregar (Punto Arp[],Punto Nube[], int& N, int M, Punto PSMin,Punto PSMax,Punto PRMin,Punto PRMax){
    for (int i=0;i < N;i++){
        if (Producto_Cruzado(PSMin,PRMax,Arp[i]) > 0){
            Nube[M]=Arp[i];
            M++;}
        else
            if(Producto_Cruzado(PRMax,PSMax,Arp[i]) > 0){
                Nube[M]=Arp[i];
                M++;}
            else
                if(Producto_Cruzado(PSMax,PRMin,Arp[i]) > 0){
                    Nube[M]=Arp[i];
                    M++;}
                else
                    if(Producto_Cruzado(PRMin,PSMin,Arp[i]) > 0){
                        Nube[M]=Arp[i];
                        M++;}
    }
    N=M;
}

void Elim_P_interiores(Punto Arp[],Punto Nube[],int& N){
    int SMax,SMin,RMax,RMin,SumaP,RestaP;
    int M=4;
    Punto PSMax,PSMin,PRMax,PRMin;

    SMax=Arp[0].coordX()+Arp[0].coordY();
    SMin=RMax=RMin=SMax;

    for(int i=0;i < N;i++){
        SumaP = Arp[i].coordX() + Arp[i].coordY();
        RestaP = Arp[i].coordX() - Arp[i].coordY();
        if (SumaP > SMax){
            SMax = SumaP;
            PSMax= Arp[i];}
        else
            if (SumaP < SMin){
                SMin = SumaP;
                PSMin = Arp[i];}
            else
                if(RestaP > RMax){
                    RMax= RestaP;
                    PRMax= Arp[i];}
                else
                    if (RestaP < RMin){
                        RMin=RestaP;
                        PRMin=Arp[i];}
    }
    cout<<endl<<"SUMA MAXIMA: "<<SMax<<" -> "<<PSMax<<endl;
    cout<<"SUMA MINIMA: "<<SMin<<" -> "<<PSMin<<endl;
    cout<<"RESTA MAXIMA: "<<RMax<<" -> "<<PRMax<<endl;
    cout<<"RESTA MINIMA: "<<RMin<<" -> "<<PRMin<<endl;

    Nube[0]= PSMax;
    Nube[1]= PSMin;
    Nube[2]= PRMax;
    Nube[3]= PRMin;

    Agregar(Arp,Nube,N,M,PSMin,PSMax,PRMin,PRMax);
}

int main()
{
    string line;
    ifstream arch("Puntos.txt");
    getline(arch, line, '\n');
    int N=atoi(line.c_str());
    Punto Arp[N];
    int i=0;
    assert(!arch.fail());
    while(!arch.eof()){
        getline(arch, line, '\t');
        int x = atoi(line.c_str());
        getline(arch, line, '\n');
        int y = atoi(line.c_str());
        Punto P(x,y);
        Arp[i]=P;
        i++;
    }
    arch.close();

    int num;
    list<Punto> solucion;
    cout<<"si desea eliminar puntos internos, pulse 1. De lo contrario pulse otro numero"<<endl;
    cin>>num;
    Punto Nube[N];
    if (num==1){
        Elim_P_interiores(Arp, Nube, N);
        Graham_Scan(solucion, Nube, N);
    }
    else
        Graham_Scan(solucion, Arp, N);
    cout<<"----solucion-----"<<endl;
    list<Punto>:: iterator it;
    for(it=solucion.begin(); it!=solucion.end(); it++)
        cout <<*it<<endl;
}
