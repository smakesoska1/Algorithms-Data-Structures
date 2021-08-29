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
 int Max(int a,int b){
     if(a>b)
     return a;
     return b;
 }

 template<typename tipkljuca,typename tipvrijednost>
 class AVLStabloMapa:public Mapa<tipkljuca,tipvrijednost>
 {
     struct Cvor{
         int balans;
         tipkljuca kljuc;
         tipvrijednost vrijednost;
         Cvor* desni;
         Cvor* lijevi;
         Cvor* roditelj;
         Cvor(const tipkljuca &kljuc,const tipvrijednost &vrijednost,Cvor* desni,Cvor* lijevi,Cvor* roditelj):balans(0),kljuc(kljuc),vrijednost(vrijednost),desni(desni),lijevi(lijevi),roditelj(roditelj){}
     };
     int velicina;
     Cvor* pocetak;
     tipvrijednost varijabla;

        Cvor* trazi(Cvor* korijen,const tipkljuca &kkljuc) const{
        if(korijen==nullptr || kkljuc==korijen->kljuc)
        return korijen;
        if(kkljuc<korijen->kljuc)
        return trazi(korijen->lijevi,kkljuc);
        return trazi(korijen->desni,kkljuc);
    }

     void umetni(Cvor*& rez,Cvor* poc,const tipkljuca &kkljuc,const tipvrijednost &vrijednost){
        if(rez==nullptr){
            rez=new Cvor(kkljuc,vrijednost,nullptr,nullptr,poc);
            velicina++;
        }
        else if(kkljuc>rez->kljuc){
            umetni(rez->desni,rez,kkljuc,vrijednost);
            if(visina(rez->desni)-visina(rez->lijevi)==2){
                if(kkljuc>rez->desni->kljuc)
                rez=lijevaRotacija(rez);
                else
                rez=dvostrukaLRotacija(rez);
            }
        }
          else if(kkljuc<rez->kljuc){
            umetni(rez->lijevi,rez,kkljuc,vrijednost);
            if(visina(rez->lijevi)-visina(rez->desni)==2){
                if(kkljuc<rez->lijevi->kljuc)
                rez=desnaRotacija(rez);
                else
                rez=dvostrukaRLRotacija(rez);
            }
        }
        rez->balans=Max(visina(rez->lijevi),visina(rez->desni))+1;

    }

      void obrisiStablo(Cvor *pocetak){
        if(pocetak){

            obrisiStablo(pocetak->lijevi);
            obrisiStablo(pocetak->desni);
            delete pocetak;
        }
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
        cc=new Cvor(drugi->kljuc,drugi->vrijednost,nullptr,nullptr,roditelj);
        kopiraj(cc->lijevi,drugi->lijevi,cc);
        kopiraj(cc->desni,drugi->desni,cc);
        velicina++;

    }

    int visina(Cvor* cvor){
        if(cvor==nullptr)
        return -1;
        return cvor->balans;
    }

    Cvor* lijevaRotacija(Cvor*&cvor){
        Cvor* pomocni1=cvor->desni;
        Cvor* pomocni2=pomocni1->lijevi;

        cvor->desni=pomocni2;
        pomocni1->lijevi=cvor;
        cvor->balans=Max(visina(cvor->lijevi),visina(cvor->desni))+1;
        pomocni1->balans=Max(visina(pomocni1->desni),cvor->balans)+1;

        return pomocni1;
    }

    Cvor* desnaRotacija(Cvor*&cvor){
        Cvor* pomocni1=cvor->lijevi;
        Cvor* pomocni2=cvor->lijevi->desni;

        pomocni1->desni=cvor;
        cvor->lijevi=pomocni2;

        cvor->balans=Max(visina(cvor->lijevi),visina(cvor->desni))+1;
        pomocni1->balans=Max(visina(pomocni1->lijevi),cvor->balans)+1;

        return pomocni1;
    }

    Cvor* dvostrukaLRotacija(Cvor *&cvor){
        cvor->desni=desnaRotacija(cvor->desni);
        return lijevaRotacija(cvor);
    }

      Cvor* dvostrukaRLRotacija(Cvor *&cvor){
        cvor->lijevi=lijevaRotacija(cvor->lijevi);
        return desnaRotacija(cvor);
    }

    public:
    AVLStabloMapa():Mapa<tipkljuca,tipvrijednost>(),pocetak(nullptr),velicina(0){}
    ~AVLStabloMapa(){
        obrisiStablo(pocetak);
    }

    void obrisi() override{
        obrisiStablo(pocetak);
        pocetak=nullptr;
        velicina=0;
    }
    void obrisi(const tipkljuca &kljuc)override{
        obrisiCvor(pocetak,kljuc);
        velicina--;
    }

    int brojElemenata() const override{
        return velicina;
    }

    //kopirajuci konstruktr i operator dodjele
    AVLStabloMapa(const AVLStabloMapa &bsm){
        kopiraj(pocetak,bsm.pocetak,nullptr);
        this->velicina=bsm.velicina;
    }

     AVLStabloMapa& operator=(const AVLStabloMapa &bsm){
         if(this==&bsm)
         return *this;
         obrisiStablo(pocetak);
         pocetak=nullptr;
        kopiraj(pocetak,bsm.pocetak,nullptr);
        this->velicina=bsm.velicina;
        return *this;
    }

    //operator [] konstantna i nekonstantna verzijaaa

    tipvrijednost operator[](const tipkljuca &kljuc)const override{
        Cvor* element=trazi(pocetak,kljuc);
        if(element==nullptr)
            return tipvrijednost();
            return element->vrijednost;

    }

     tipvrijednost &operator[](const tipkljuca &kljuc) override{
         umetni(pocetak,nullptr,kljuc,tipvrijednost());
         Cvor *cvor=trazi(pocetak,kljuc);
         varijabla=tipvrijednost();
         if(cvor==nullptr){
             return varijabla;
         }
         return cvor->vrijednost;
     }
 };


int main() {
   BinStabloMapa<int,int>bsm;
   AVLStabloMapa<int,int>avlsm;

   for(int i=0;i<4000;i++){
       bsm[i]=i;
       avlsm[i]=i;
   }
   clock_t vrijeme1,vrijeme2,ukupno;
   vrijeme1=clock();
   vrijeme2=clock();

   /*dodavanje elementa*/

 vrijeme1=clock();
 for(int i=4000;i<5000;i++){
     bsm[i]=i;
     vrijeme2=clock();
     ukupno=(vrijeme2-vrijeme1)/(CLOCKS_PER_SEC/1000.);

 }
    std::cout<<"BinarnoStabloMapa dodavanje elementa vrijeme je "<<ukupno<<" ms"<<std::endl;

    vrijeme1=clock();
 for(int i=4000;i<5000;i++){
     avlsm[i]=i;
     vrijeme2=clock();
     ukupno=(vrijeme2-vrijeme1)/(CLOCKS_PER_SEC/1000.);

 }
   std::cout<<"AVLStabloMapa dodavanje elementa vrijeme je "<<ukupno<<" ms"<<std::endl;

   /*Sto se tice dodavanja elementa AVLStabloMapa ima bolje performanse u odnosu na BinarnoStabloMapa*/

   /*Pristup elementu*/

   vrijeme1=clock();
   std::cout<<bsm[3879]<<" ";
   std::cout<<bsm[879]<<" ";
   std::cout<<bsm[689]<<" ";
   std::cout<<bsm[687]<<" ";
   std::cout<<bsm[1879]<<" ";
   std::cout<<bsm[2879]<<" ";
   std::cout<<bsm[3379]<<" ";
   std::cout<<bsm[179]<<" ";
   vrijeme2=clock();
     ukupno=(vrijeme2-vrijeme1)/(CLOCKS_PER_SEC/1000.);
     std::cout<<"BinarnoStabloMapa pristup elementu je: "<<ukupno<<" ms"<<std::endl;

     vrijeme1=clock();
   std::cout<<avlsm[3879]<<" ";
   std::cout<<avlsm[879]<<" ";
   std::cout<<avlsm[689]<<" ";
   std::cout<<avlsm[687]<<" ";
   std::cout<<avlsm[1879]<<" ";
   std::cout<<avlsm[2879]<<" ";
   std::cout<<avlsm[3379]<<" ";
   std::cout<<avlsm[179]<<" ";
   vrijeme2=clock();
     ukupno=(vrijeme2-vrijeme1)/(CLOCKS_PER_SEC/1000.);
     std::cout<<"AVLStabloMapa pristup elementu je: "<<ukupno<<" ms"<<std::endl;

   /*Sto se tice pristupa elementu AVLStabloMapa ima bolje performanse u odnosu na BinarnoStabloMapa*/

   /*Brisanje elementa*/

   vrijeme1=clock();
   for(int i=2600;i<3500;i++)
   bsm.obrisi(i);
   vrijeme2=clock();
    ukupno=(vrijeme2-vrijeme1)/(CLOCKS_PER_SEC/1000.);
     std::cout<<"BinarnoStabloMapa brisanje elementa je: "<<ukupno<<" ms"<<std::endl;


   vrijeme1=clock();
   for(int i=2600;i<3500;i++)
   avlsm.obrisi(i);
   vrijeme2=clock();
    ukupno=(vrijeme2-vrijeme1)/(CLOCKS_PER_SEC/1000.);
     std::cout<<"AVLStabloMapa brisanje elementa je: "<<ukupno<<" ms"<<std::endl;

      /*Sto se tice brisanja elementa AVLStabloMapa ima bolje performanse u odnosu na BinarnoStabloMapa*/

    return 0;
}
