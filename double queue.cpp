#include <iostream>

template<typename tip>
struct Cvor{
    tip element;
    Cvor* prethodni=nullptr;
    Cvor* sljedeci=nullptr;
};

template<typename tip>
class DvostraniRed{
    int broj_elemenata;
    Cvor<tip>*pocetak;
    Cvor<tip>*kraj;
    public:
    DvostraniRed(){
        broj_elemenata=0;
        pocetak=nullptr;
        kraj=nullptr;
    }
    ~DvostraniRed(){
        Cvor<tip>*temp(pocetak);
        while(pocetak!=nullptr)
        {
            temp=pocetak;
            if(pocetak!=nullptr)
            pocetak=pocetak->sljedeci;
            delete temp;
        }
        pocetak=nullptr;
        kraj=nullptr;
        broj_elemenata=0;
    }

    //kontruktor kopije i operator dodjele
    DvostraniRed(const DvostraniRed<tip>&el ){
        broj_elemenata=el.broj_elemenata;
        Cvor<tip>*temp1=el.pocetak;
        Cvor<tip>*temp2=nullptr;

        while(temp1!=nullptr){
            Cvor<tip>*temp3=new Cvor<tip>();
            temp3->prethodni=nullptr;
            temp3->sljedeci=nullptr;
            temp3->element=temp1->element;
            if(temp2==nullptr) pocetak=temp3;
            else{
                temp2->sljedeci=temp3;
                temp3->prethodni=temp2;
            }
            if(temp1==el.kraj) kraj=temp3;
            temp2=temp3;
            temp1=temp1->sljedeci;
        }

    }

     DvostraniRed&operator =(const DvostraniRed<tip>&el ){
         if(&el==this) return *this;
         Cvor<tip>*pomocni(pocetak);
         brisi();
         broj_elemenata=el.broj_elemenata;
        Cvor<tip>*temp1=el.pocetak;
        Cvor<tip>*temp2=nullptr;

        while(temp1!=nullptr){
            Cvor<tip>*temp3=new Cvor<tip>();
            temp3->prethodni=nullptr;
            temp3->sljedeci=nullptr;
            temp3->element=temp1->element;
            if(temp2==nullptr) pocetak=temp3;
            else{
                temp2->sljedeci=temp3;
                temp3->prethodni=temp2;
            }
            if(temp1==el.kraj) kraj=temp3;
            temp2=temp3;
            temp1=temp1->sljedeci;
        }
        return *this;

    }
    void brisi(){
         Cvor<tip>*temp(pocetak);
        while(pocetak!=nullptr)
        {
            temp=pocetak;
            if(pocetak!=nullptr)
            pocetak=pocetak->sljedeci;
            delete temp;   //brisanje??
        }
        pocetak=nullptr;
        kraj=nullptr;
        broj_elemenata=0;

    }
    tip &celo(){
        if(broj_elemenata<=0) throw ("Red je prazan");
        else
        return pocetak->element;
    }
    tip &vrh(){
        if(broj_elemenata<=0) throw ("Red je prazan");
        else
        return kraj->element;

    }
    int brojElemenata() const{
        return broj_elemenata;
    }
    tip skiniSaCela(){
        if(broj_elemenata<=0) throw("Prazan red");
        if(broj_elemenata==1){
            tip pomoc(pocetak->element);
            delete pocetak;
            pocetak=kraj=nullptr;
            broj_elemenata--;
            return pomoc;
        }
        else{
             tip pomoc(pocetak->element);
             Cvor<tip>*temp(pocetak);
             if(pocetak!=nullptr) pocetak=pocetak->sljedeci;
             delete temp;
             pocetak->prethodni=nullptr;


            broj_elemenata--;
            return pomoc;

        }

    }
    tip skiniSaVrha(){
          if(broj_elemenata<=0) throw("Prazan red");
        if(broj_elemenata==1){
            tip pomoc(pocetak->element);
            delete pocetak;
            pocetak=kraj=nullptr;
            broj_elemenata--;
            return pomoc;
        }
        else{
             tip pomoc;
             if(kraj!=nullptr) pomoc=kraj->element;
             auto temp(kraj);
             if(kraj!=nullptr) kraj=kraj->prethodni;
             if(kraj!=nullptr) kraj->sljedeci=nullptr;

             delete temp;


            broj_elemenata--;
            return pomoc;

        }

    }
void staviNaVrh(const tip&el){
    if(broj_elemenata==0){
        Cvor<tip>*novi=new Cvor<tip>();
        novi->element=el;
        pocetak=novi;
        kraj=novi;
        pocetak->sljedeci=nullptr;
        pocetak->prethodni=nullptr;
        broj_elemenata++;

    }
    else if(broj_elemenata==1){
        Cvor<tip>*novi=new Cvor<tip>();
        novi->element=el;
        broj_elemenata++;
        pocetak->sljedeci=novi;
        kraj=novi;
        kraj->sljedeci=nullptr;
        kraj->prethodni=pocetak;

    }
    else{
        Cvor<tip>*novi=new Cvor<tip>();
        novi->element=el;
        broj_elemenata++;
        auto temp(kraj);
        if(kraj!=nullptr) kraj->sljedeci=novi;
        kraj=novi;
        kraj->sljedeci=nullptr;
        kraj->prethodni=temp;
    }
}

void staviNaCelo(const tip&el){
    if(broj_elemenata==0){
        Cvor<tip>*novi=new Cvor<tip>();
        novi->element=el;
        pocetak=novi;
        kraj=novi;
        pocetak->sljedeci=nullptr;
        pocetak->prethodni=nullptr;
        broj_elemenata++;
        return;
    }

    else{
        Cvor<tip>*novi=new Cvor<tip>();
        novi->element=el;
        broj_elemenata++;
        auto temp(pocetak);
        temp->prethodni=novi;
        pocetak=novi;
        pocetak->sljedeci=temp;
        pocetak->prethodni=nullptr;
    }
}
};

void testkopirajuci(){
    DvostraniRed<int>red;
    for(int i=1;i<=50;i++)
        red.staviNaCelo(i);
    DvostraniRed<int>red2(red);
    std::cout<<"Test kopirajuceg konstrukotra,broj elemenata reda2: "<<red2.brojElemenata()<<std::endl;
}
void testdodjele(){
    DvostraniRed<int>red;
    for(int i=1;i<=50;i++)
        red.staviNaCelo(i);
    DvostraniRed<int>red2;
    red2=red;
    std::cout<<"Test operatora dodjele,broj elemenata reda2: "<<red2.brojElemenata()<<std::endl;
}
void  testcelo(){
DvostraniRed<int>red;
for(int i=0;i<6;i++)
    red.staviNaCelo(i);
std::cout<<"Element na celu je: "<<red.celo()<<std::endl;
}
void testvrh(){
DvostraniRed<int>red;
for(int i=3;i<10;i++)
    red.staviNaVrh(i);
std::cout<<"Element na vrh je: "<<red.vrh()<<std::endl;
}
void teststavinacelo(){
DvostraniRed<int>red;
for(int i=0;i<6;i++)
red.staviNaCelo(i);
std::cout<<"Broj elemenata  je: "<<red.brojElemenata()<<std::endl;
}
void teststavinavrh(){
DvostraniRed<int>red;
for(int i=0;i<6;i++)
red.staviNaVrh(i);
std::cout<<"Broj elemenata  je: "<<red.brojElemenata()<<std::endl;
}
void testbrisi(){
    DvostraniRed<int>red;
for(int i=0;i<6;i++)
red.staviNaCelo(i);
red.brisi();
red.brisi();
std::cout<<"Broj elemenata  je: "<<red.brojElemenata()<<std::endl;
}
void testskiniSaCela(){
     DvostraniRed<int>red;
for(int i=0;i<6;i++)
red.staviNaCelo(i);
red.skiniSaCela();
//red.brisi();
std::cout<<"Broj elemenata  je: "<<red.brojElemenata()<<std::endl;
}
void testskiniSaVrha(){
     DvostraniRed<int>red;
for(int i=0;i<6;i++)
red.staviNaVrh(i);
red.skiniSaVrha();
//red.brisi();
std::cout<<"Broj elemenata  je: "<<red.brojElemenata()<<std::endl;
}


int main()
{
    testbrisi();
    testkopirajuci();
    testdodjele();
    testcelo();
    testvrh();
    teststavinacelo();
    teststavinavrh();
    testskiniSaCela();
    testskiniSaVrha();    return 0;
}
