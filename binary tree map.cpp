#include <iostream>
#include<utility>
#include<string>
#include<vector>

//genericka
template<typename tipkljuca,typename tipvrijednost>
class Mapa
{
public:
    Mapa() {}
    virtual ~Mapa() {}
    virtual void obrisi()=0;
    virtual void obrisi(const tipkljuca &kljuc)=0;
    virtual int brojElemenata() const=0;
    virtual tipvrijednost &operator[](const tipkljuca &kljuc)=0;
    virtual tipvrijednost operator[](const tipkljuca &kljuc)const=0;

};

template<typename tipkljuca,typename tipvrijednost>
class BinStabloMapa:public Mapa<tipkljuca,tipvrijednost>
{
    private:
    class Cvor{
        public:
        tipkljuca kljuc;
        tipvrijednost element;
        Cvor* lijevi;
        Cvor* desni;
        Cvor* roditelj;
        Cvor(const tipkljuca &kljuc,const tipvrijednost &element,Cvor* desni,Cvor* lijevi,Cvor *roditelj):kljuc(kljuc),element(element),desni(desni),lijevi(lijevi),roditelj(roditelj){}

    };
    int velicina;
    Cvor *pocetak;

    Cvor* trazi(Cvor* korijen,const tipkljuca &kkljuc) const{
        if(korijen==nullptr || kkljuc==korijen->kljuc)
        return korijen;
        if(kkljuc<korijen->kljuc)
        return trazi(korijen->lijevi,kkljuc);
        return trazi(korijen->desni,kkljuc);
    }

    bool obrisiCvor(Cvor*&rez,const tipkljuca &kkljuc){
        Cvor *poc=rez;
        Cvor *q=nullptr;
        Cvor *pomocni=nullptr;
        Cvor *pp=nullptr;
        Cvor *rp=nullptr;

        while(poc!=nullptr && kkljuc!=poc->kljuc){
            q=poc;
            if(kkljuc<poc->kljuc){
                poc=poc->lijevi;
            }
            else
            poc=poc->desni;
        }
        if(poc==0)
        return false;
        if(poc->lijevi==nullptr)
        rp=poc->desni;
        else if(poc->desni==nullptr)
        rp=poc->lijevi;
        else{
            pp=poc;
            rp=poc->lijevi;
            pomocni=rp->desni;
            while(pomocni!=nullptr){
                pp=rp;
                rp=pomocni;
                pomocni=rp->desni;
            }
            if(pp!=poc){
                pp->desni=rp->lijevi;
                rp->lijevi=poc->lijevi;
            }
            rp->desni=poc->desni;
        }
        if(q==0)
        pocetak=rp;
        else if(poc==q->lijevi)
        q->lijevi=rp;
        else
        q->desni=rp;
        delete poc;
        return true;
    }

    void kopiraj(Cvor *& cc,Cvor *drugi,Cvor *roditelj){
        if(drugi==nullptr)
        return;
        cc=new Cvor(drugi->kljuc,drugi->element,nullptr,nullptr,roditelj);
        kopiraj(cc->lijevi,drugi->lijevi,cc);
        kopiraj(cc->desni,drugi->desni,cc);
        velicina++;

    }

    void obrisiStablo(Cvor *pocetak){
        if(pocetak){

            obrisiStablo(pocetak->lijevi);
            obrisiStablo(pocetak->desni);
            delete pocetak;
        }
    }

    Cvor* umetni(Cvor*& rez,Cvor* poc,const tipkljuca &kkljuc,const tipvrijednost &vrijednost){
        if(rez==nullptr){
            rez=new Cvor(kkljuc,vrijednost,nullptr,nullptr,poc);
            velicina++;
            return rez;
        }
        if(rez->kljuc==kkljuc)
        return rez;
        if(kkljuc>rez->kljuc)
        return umetni(rez->desni,rez,kkljuc,vrijednost);
        return umetni(rez->lijevi,rez,kkljuc,vrijednost);
    }
    public:
    BinStabloMapa():Mapa<tipkljuca,tipvrijednost>(),velicina(0),pocetak(nullptr){}
    BinStabloMapa(const BinStabloMapa &bsm){
        kopiraj(pocetak,bsm.pocetak,nullptr);
        this->velicina=bsm.velicina;
    }

    BinStabloMapa& operator =(const BinStabloMapa &bsm){
        if(this==&bsm)
        return *this;
        obrisiStablo(pocetak);
        pocetak=nullptr;
        kopiraj(pocetak,bsm.pocetak,nullptr);
        this->velicina=bsm.velicina;
        return *this;
    }
    //destruktorr
    ~BinStabloMapa(){obrisiStablo(pocetak);
    pocetak=nullptr;}

    int brojElemenata()const override {return velicina;}

    //konstantna i nekonstantna verzija operatora dodjele
    tipvrijednost operator[] (const tipkljuca &kkljuc) const override{
        Cvor *el=trazi(pocetak,kkljuc);
        if(el==nullptr)
        return tipvrijednost();
        return el->element;
    }

      tipvrijednost& operator[] (const tipkljuca &kkljuc) override{
        Cvor* cc=umetni(pocetak,nullptr,kkljuc,tipvrijednost());
        return cc->element;
    }

    void obrisi() override{
        obrisiStablo(pocetak);
        pocetak=nullptr;
        velicina=0;
    }
    void obrisi(const tipkljuca &kkljuc) override{
        obrisiCvor(pocetak,kkljuc);
        velicina--;
    }



};
template<typename tipkljuca,typename tipvrijednost>
class NizMapa:public Mapa<tipkljuca,tipvrijednost>
{
private:
    std::pair<tipkljuca,tipvrijednost>*niz;
    int kapacitet;
    int velicina;
public:
    NizMapa():kapacitet(3000), velicina(0)
    {
        niz=new std::pair<tipkljuca,tipvrijednost>[kapacitet];

    }

    ~NizMapa()
    {
        delete [] niz;
    }
    int brojElemenata() const override
    {
        return velicina;
    }
    void obrisi() override
    {
        velicina=0;
    }
    //kontruktor kopije
    NizMapa(const NizMapa<tipkljuca,tipvrijednost> &mapa):kapacitet(mapa.kapacitet),velicina(mapa.brojElemenata())
    {
        niz=new std::pair<tipkljuca,tipvrijednost>[kapacitet];
        for(int i=0; i<velicina; i++) {
            niz[i].first=mapa.niz[i].first;
            niz[i].second=mapa.niz[i].second;
        }

    }
    //operator dodjele
    NizMapa<tipkljuca,tipvrijednost> &operator=(const NizMapa<tipkljuca,tipvrijednost> &mapa)
    {
        if(&mapa==this)
            return *this;
        delete[] niz; //bisanje

        kapacitet=mapa.kapacitet;
        velicina=mapa.velicina;

        niz=new std::pair<tipkljuca,tipvrijednost>[kapacitet];
        for(int i=0; i<velicina; i++) {
            niz[i].first=mapa.niz[i].first;
            niz[i].second=mapa.niz[i].second;
        }

        return *this;


    }

    tipvrijednost &operator[](const tipkljuca &kljuc) override
    {
        for(int i=0; i<velicina; i++) {
            if(niz[i].first==kljuc)
                return niz[i].second;
        }
        if(velicina==kapacitet) {
            kapacitet=kapacitet*2;
            std::pair<tipkljuca,tipvrijednost>* nizzz=new std::pair<tipkljuca,tipvrijednost>[kapacitet];
            for(int i=0; i<velicina; i++) {
                nizzz[i].first=niz[i].first;
                nizzz[i].second=niz[i].second;
            }

            delete[] niz;
            niz=nizzz;
            nizzz=nullptr;
        }

        niz[velicina].first=kljuc;
        niz[velicina].second=tipvrijednost();
        velicina++;
        return niz[velicina-1].second;
    }

    //druga verzija
    tipvrijednost operator[](const tipkljuca &kljuc)const override
    {
        for(int i=0; i<velicina; i++) {
            if(niz[i].first==kljuc)
                return niz[i].second;
        }
        return tipvrijednost();
    }

    void obrisi(const tipkljuca &kljuc) override
    {
        for(int i=0; i<velicina; i++) {
            if(niz[i].first==kljuc) {
                niz[i].first=niz[velicina-1].first;
                niz[i].second=niz[velicina-1].second;

                velicina--;
                return;
            }
        }
        throw("Nema kljuca");
    }
};
void testMain(){
    BinStabloMapa<int,int> bsm;
    NizMapa<int,int>nm;

    for(int i=0;i<5000;i++){
        nm[i]=i;
        bsm[i]=i;
    }
    clock_t vrijeme1,vrijeme2;
    //pristupanje elementima bsm i nm vrijeme mjerenje
    vrijeme1=clock();
    std::cout<<nm[400]<<std::endl;
    vrijeme2=clock();
   double ukupnov=(vrijeme2-vrijeme1)/(CLOCKS_PER_SEC/1000.);
   std::cout<<"NizMapa- pristupanje nekom elementu: "<<ukupnov<<" ms."<<std::endl;

    vrijeme1=clock();
    std::cout<<bsm[400]<<std::endl;
    vrijeme2=clock();
    ukupnov=(vrijeme2-vrijeme1)/(CLOCKS_PER_SEC/1000.);
   std::cout<<"BinarnoStabloMapa- pristupanje nekom elementu: "<<ukupnov<<" ms."<<std::endl;
   /*kad je rijec o pristupanju elementu BinarnoStabloMapa ima bolje performanse!*/

   vrijeme1=clock();
    nm[5500]=478;
    vrijeme2=clock();
    ukupnov=(vrijeme2-vrijeme1)/(CLOCKS_PER_SEC/1000.);
   std::cout<<"NizMapa- dodavanje nekog elementa: "<<ukupnov<<" ms."<<std::endl;

    vrijeme1=clock();
    bsm[5500]=478;
    vrijeme2=clock();
   ukupnov=(vrijeme2-vrijeme1)/(CLOCKS_PER_SEC/1000.);
   std::cout<<"BinarnoStabloMapa- dodavanje nekog elementa: "<<ukupnov<<" ms."<<std::endl;
   /*kad je rijec o dodavanju novog elementa NizMapa ima bolje performanse !*/



}


int main()
{
    testMain();

    return 0;
}
