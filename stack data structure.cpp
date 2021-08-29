#include <iostream>

template<typename tip>

class Stek{
    int broj_elemenata;
    tip*pok;
    int vrh1;
    public:
    Stek(int n=1000000)
    {
        vrh1=-1;
        broj_elemenata=n;
        pok=new tip[n];
    }
    ~Stek(){
        //for(int i=0;i<broj_elemenata;i++)
        delete[] pok;
    }
    //kontruktor kopije i operator dodjele
    Stek(const Stek<tip> &el) :vrh1(el.vrh1),broj_elemenata(el.broj_elemenata)

   {
      pok=new tip[el.vrh1+1];
        for(int i=0;i<=vrh1;i++)
        pok[i]=el.pok[i];

    }
     Stek& operator=(const Stek &el)
    {
        //samododjela
        if(&el==this)
        return *this;
        delete[] pok;
    vrh1=el.vrh1;
    broj_elemenata=el.broj_elemenata;
    pok=new tip[el.vrh1+1];

    for(int i=0;i<=vrh1;i++)
    pok[i]=el.pok[i];

    return *this;
    }
    tip &vrh()
    {
        if(vrh1==-1) throw("Nema elemenata u steku");
        else
        return pok[vrh1];
    }
    void brisi(){
        vrh1=-1;
    }
    tip skini()
    {
        if(vrh1==-1)
        throw ("Stek je prazan");

        return pok[vrh1--];
    }
    void stavi(const tip& el)
    {
        vrh1++;
        pok[vrh1]=el;
    }
    //inspektor
    int brojElemenata()
    {
        return vrh1+1;
    }
};

//test funkcije
void testfunkcijastavi()
{
    Stek<int>s;
    for(int i=1;i<6;i++)
    s.stavi(i);
    std::cout<<"Broj elemenata je: "<<s.brojElemenata()<<std::endl;
    std::cout<<"Element na vrhu je: "<<s.vrh()<<std::endl;

}
void testobrisi()
{
    Stek<int>s;
    for(int i=1;i<6;i++)
    s.stavi(i);
    std::cout<<"Prije brisanja elemnti su: "<<s.brojElemenata();
    s.brisi();
    std::cout<<std::endl;
    std::cout<<"Poslije brisanja broj elemenata je: "<<s.brojElemenata()<<std::endl;
}
void navrhu()
{
    Stek<int> s;
    for(int i=1;i<3;i++)
    s.stavi(i);
    std::cout<<"Element vrha je : "<<s.vrh()<<std::endl;
}
void funkcijabrojelemenata()
{
    Stek<int>s;
    for(int i=0;i<4;i++)
    s.stavi(i);
    s.skini();
    s.skini();
    std::cout<<"Broj elemenata na kraju je: "<<s.brojElemenata()<<std::endl;
}
void testkopirajucegkonst()
{
    Stek<int>s;

    for(int i=1;i<5;i++)
    s.stavi(i);

    Stek<int>s1(s);
    std::cout<<"Element na vrhu s je "<<s.vrh()<<",a element na vrhu s1 je "<<s1.vrh()<<std::endl;
}
void testoperatoradodjele()
{
     Stek<int>s;
     Stek<int>s2;

    for(int i=1;i<5;i++)
    s.stavi(i);
    s2=s;
    //Stek<int>s1(s);
    std::cout<<"Element na vrhu s je "<<s.vrh()<<",a element na vrhu s1 je "<<s2.vrh()<<std::endl;
}

int main() {

   testfunkcijastavi();
   testobrisi();
   navrhu();
   funkcijabrojelemenata();
   testkopirajucegkonst();
    testoperatoradodjele();

    return 0;
}

