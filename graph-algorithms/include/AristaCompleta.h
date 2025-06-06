#ifndef ARISTACOMPLETA_H
#define ARISTACOMPLETA_H


template <typename C>
class AristaCompleta
{
    public:
        AristaCompleta(int v1, int v2, const C & cost);
        //~AristaCompleta();
        int devolverVertice1() const;
        int devolverVertice2() const;
        const C & devolverCosto() const;
    private:
        int v1;
        int v2;
        C costo;
};

template<typename C>
AristaCompleta<C>::AristaCompleta(int v1, int v2, const C & cost){
    this->v1=v1;
    this->v2=v2;
    this->costo=cost;
}

template<typename C>
int AristaCompleta<C>::devolverVertice1() const{
    return(this->v1);
}

template<typename C>
int AristaCompleta<C>::devolverVertice2() const{
    return(this->v2);
}

template<typename C>
const C & AristaCompleta<C>::devolverCosto() const{
    return(this->costo);
}

#endif // ARISTACOMPLETA_H
