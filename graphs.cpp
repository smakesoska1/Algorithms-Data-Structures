#include <iostream>
#include<vector>
#include<string>

using namespace std;

template <typename tip>
class Grana;

template <typename tip>
class GranaIterator;

template <typename tip>
class Cvor;

template<typename tip>
class UsmjereniGraf
{

public:
    UsmjereniGraf() {}
    UsmjereniGraf(int broj) {}
    virtual ~UsmjereniGraf() {}
    virtual int dajBrojCvorova()const=0;
    virtual void postaviBrojCvorova(int broj)=0;
    virtual void dodajGranu(int polazni,int dolazni,float tezina=0)=0;
    virtual void obrisiGranu(int polazni,int dolazni)=0;
    virtual void postaviTezinuGrane(int polazni,int dolazni,float tezina=0)=0;
    virtual float dajTezinuGrane(int polazni,int dolazni)=0;
    virtual bool postojiGrana(int polazni,int dolazni)=0;
    virtual void postaviOznakuCvora(int rednibroj,tip oznaka)=0;
    virtual tip dajOznakuCvora(int rednibroj)=0;
    virtual void postaviOznakuGrane(int dolazni,int polazni,tip oznaka)=0;
    virtual tip dajOznakuGrane(int polazni,int dolazni)=0;
    virtual Grana<tip> dajGranu(int polazni,int dolazni)=0;
    virtual Cvor<tip> dajCvor(int rednibroj)=0;
    virtual GranaIterator<tip> dajGranePocetak()=0;
    virtual GranaIterator<tip>dajGraneKraj()=0;

};

//implementacija klasa cvor grana granaitearator
template<typename tip>
class Cvor
{
    UsmjereniGraf<tip>*c;
    int rednibroj;
public:
    Cvor(UsmjereniGraf<tip>*graf,int rednibroj):c(graf),rednibroj(rednibroj) {}
    int dajRedniBroj()const
    {
        return rednibroj;
    }
    tip dajOznaku() const
    {
        return c->dajOznakuCvora(rednibroj);
    }
    void postaviOznaku(tip oznaka)
    {
        c->postaviOznakuCvora(rednibroj,oznaka);
    }
};

template<typename tip>
class Grana
{
    UsmjereniGraf<tip> *g;
    int polazni, dolazni;
public:
    Grana(UsmjereniGraf<tip>*grana,int polazni,int dolazni):g(grana),polazni(polazni),dolazni(dolazni) {}
    float dajTezinu()
    {
        return g->dajTezinuGrane(polazni,dolazni);

    }
    void postaviTezinu(int tezina)
    {
        g->postaviTezinuGrane(polazni,dolazni,tezina);
    }

    tip dajOznaku() const
    {
        return g->dajOznakuGrane(polazni,dolazni);
    }
    void postaviOznaku(tip oznaka)
    {
        g->postaviOznakuGrane(polazni,dolazni,oznaka);
    }

    Cvor<tip> dajPolazniCvor() const
    {
        return g->dajCvor(polazni);
    }
    Cvor<tip> dajDolazniCvor() const
    {
        return g->dajCvor(dolazni);
    }


};

template<typename tip>
class GranaIterator
{
    UsmjereniGraf<tip> *graf;
    int polazni;
    int dolazni;
public:
    GranaIterator(UsmjereniGraf<tip>* graf,int polazni,int dolazni):graf(graf),polazni(polazni),dolazni(dolazni) {}
    Grana<tip>operator*()
    {
        return graf->dajGranu(polazni,dolazni);
    }

    bool operator==(const GranaIterator &x) const
    {
        if(x.polazni==polazni && x.dolazni==dolazni && x.graf==graf )
            return true;
        return false;
    }

    bool operator !=(const GranaIterator &x) const
    {
        return !(*this==x);
    }

    //prefiksni i postifiksni operator ++
    GranaIterator operator++(int)
    {
        GranaIterator pomocni(*this);
        ++(*this);
        return pomocni;
    }

    GranaIterator& operator++()
    {
        int pomocni1(0);
        int pomocni2(0);
        bool tu_je(false);

        for(int i=0; i<graf->dajBrojCvorova(); i++) {
            for(int j=0; j<graf->dajBrojCvorova(); j++) {
                if(i<polazni || (i==polazni && j<=dolazni))
                    continue;
                if(graf->postojiGrana(i,j)==true) {
                    pomocni1=i;
                    pomocni2=j;
                    tu_je=true;
                }
                if(tu_je==true) break;
            }
            if(tu_je==true)
                break;
        }
        if(tu_je==false) {
            pomocni1=graf->dajBrojCvorova()-1;
            pomocni2=pomocni1;
        }

        this->polazni=pomocni1;
        this->dolazni=pomocni2;
        return *this;

    }


};




template<typename tip>
class MatricaGraf: public UsmjereniGraf<tip>
{
    struct Granas {
        tip oznakaGrane;
        float tezinaGrane;
        bool postojiGrana=false;
    };
    std::vector<tip>cvorovi;
    std::vector<std::vector<Granas>>matSusjed;
public:
    MatricaGraf() {}
    MatricaGraf(int brojCvorova)
    {
        cvorovi.resize(brojCvorova);
        matSusjed.resize(brojCvorova);
        for(int i=0; i<matSusjed.size(); i++) {
            matSusjed[i].resize(brojCvorova);
        }
    }

    ~MatricaGraf() {}
    int dajBrojCvorova() const override
    {
        return matSusjed.size();
    }
    void postaviBrojCvorova(int broj) override
    {
        if(broj<matSusjed.size())
            throw("Izuzetak");
        matSusjed.resize(broj);
        for(int i=0; i<matSusjed.size(); i++) {
            matSusjed[i].resize(broj);
        }
    }

    void dodajGranu(int polazni,int dolazni,float tezina) override
    {
        matSusjed[polazni][dolazni].tezinaGrane=tezina;
        matSusjed[polazni][dolazni].postojiGrana=1;
    }

    void obrisiGranu(int polazni,int dolazni) override
    {
        matSusjed[polazni][dolazni].postojiGrana=false;
        matSusjed[polazni][dolazni].tezinaGrane=0;
    }

    void postaviTezinuGrane(int polazni,int dolazni,float tezina=0) override
    {
        if(matSusjed[polazni][dolazni].postojiGrana)
            matSusjed[polazni][dolazni].tezinaGrane=tezina;
    }

    float dajTezinuGrane(int polazni,int dolazni) override
    {
        return matSusjed[polazni][dolazni].tezinaGrane;
    }
    bool postojiGrana(int polazni,int dolazni)
    {
        return matSusjed[polazni][dolazni].postojiGrana;
    }
    void postaviOznakuCvora(int rednibroj,tip oznaka)override
    {
        cvorovi[rednibroj]=oznaka;
    }
    tip dajOznakuCvora(int rednibroj) override
    {
        return cvorovi[rednibroj];
    }

    void postaviOznakuGrane(int polazni,int dolazni,tip oznaka)
    {
        matSusjed[polazni][dolazni].oznakaGrane=oznaka;
    }
    tip dajOznakuGrane(int polazni,int dolazni)override
    {
        return matSusjed[polazni][dolazni].oznakaGrane;
    }

    Grana<tip> dajGranu(int polazni,int dolazni) override
    {
        return Grana<tip>(this,polazni,dolazni);
    }

    Cvor<tip> dajCvor(int rednibroj) override
    {
        return Cvor<tip>(this,rednibroj);
    }

    GranaIterator<tip>dajGranePocetak()override
    {
        int a,b;
        bool ima=false;
        for(int i=0; i<dajBrojCvorova(); i++) {
            for(int j=0; j<dajBrojCvorova(); j++) {
                if(postojiGrana(i,j)) {
                    a=i;
                    b=j;
                    ima=true;
                }
                if(ima)
                    break;
            }
            if(ima)
                break;
        }
        return GranaIterator<tip>(this,a,b);
    }


    GranaIterator<tip> dajGraneKraj()override
    {
        return GranaIterator<tip>(this,dajBrojCvorova()-1,dajBrojCvorova()-1);
    }
};



int main()
{
    //main
    UsmjereniGraf<std::string> *g = new MatricaGraf<std::string>(4);
    cout << g->dajCvor(0).dajRedniBroj() << "; ";
    g->postaviOznakuCvora(1, "aaa");
    g->dajCvor(2).postaviOznaku("bbb");
    for (int i = 0; i < 4; i++)
        cout << "(" << i << ")" << g->dajOznakuCvora(i) << "," << g->dajCvor(i).dajOznaku() << ";";
    delete g;
    return 0;
}
