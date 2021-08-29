#include <iostream>

template <typename tip>
class Red
{
protected:
    tip *pok;
    int pocetak;
    int kraj;
    int kapacitet;
//void operator =(const Red &red); // Zaštita za dodjelu
public:
    Red (int n=1000000)
    {
       pok=new tip[n];
       pocetak=-1;
       kraj=-1;
       kapacitet=n;
    }
    Red(const Red<tip>& element)
    {
        kapacitet=element.kapacitet;
        pocetak=element.pocetak;
        kraj=element.kraj;
        if(element.pok!=0){
            pok=new tip[kapacitet];
            for(int i=pocetak;i<=kraj;i++)
            pok[i]=element.pok[i];
        }
    }
     Red &operator=(const Red<tip>& element)
    {
        if(&element==this)
        return *this;
        delete[] pok;
        kapacitet=element.kapacitet;
        pocetak=element.pocetak;
        kraj=element.kraj;
        if(element.pok!=0){
            pok=new tip[kapacitet];
            for(int i=pocetak;i<=kraj;i++)
            pok[i]=element.pok[i];
        }
        return *this;
    }
    ~Red() {
        pocetak=-1;
        kraj=-1;
        if(kapacitet!=0)
        delete[] pok;
    }
    void brisi ()
    {
        pocetak=-1;
        kraj=-1;
    }
    void stavi (const tip&element){
        if(pocetak==-1)
        {
            pocetak++;
            kraj++;
            pok[0]=element;
        }
        else
        {
            kraj=(kraj+1)%kapacitet;
            pok[kraj]=element;
        }

    }



    tip skini (){
        if(pocetak==-1 && kraj==-1)
        throw("lista prazna");
        tip pomocni=pok[pocetak];
        if(pocetak==kraj){
            pocetak=-1;
            kraj=-1;
        }
        else{
            pocetak=(pocetak+1)%kapacitet;
        }
        return pomocni;
    }
    tip& celo () {
        if(pocetak==-1 && kraj==-1)
        throw ("prazna lista");
        else
        return pok[pocetak];
    }
    int brojElemenata (){
        if(pocetak==-1 && kraj==-1)
        return 0;
        //throw("nema duzine");
        else
        return ((kraj+kapacitet)-pocetak)%kapacitet+1;
    }

};

//testovi provjere funkcijja
void stavitest()
{
    Red<int>r;
    for(int i=0;i<6;i++)
    r.stavi(i);
    std::cout<<"Broj elemenata je:"<<r.brojElemenata()<<", a celo je"<<r.celo();
}
void brisitest()
{
    Red<int>r;
    for(int i=0;i<5;i++)
    r.stavi(i);
    r.brisi();//prazno
    std::cout<<"Broj elemenata nakon brisanja je: "<<r.brojElemenata();
}
void celotest()
{
    Red<int>r;
    for(int i=3;i<=9;i++)
    r.stavi(i);
    std::cout<<"Element na vrhu je: "<<r.celo();
}
void testskini(){
    Red<int>r;
    for(int i=0;i<3;i++)
    r.stavi(i);
    r.skini();
    std::cout<<"Test funkcije skini: "<<r.brojElemenata();
}
void testbrojel(){
      Red<int>r;
    for(int i=3;i<=9;i++)
    r.stavi(i);
    std::cout<<"Broj elemenata je: "<<r.brojElemenata();
}
void testdodjele(){
    Red<int>s1;
    Red<int>s2;
    for(int i=0;i<6;i++)
    s1.stavi(i);
    s2=s1;
    std::cout<<"Broj elemenata u s2 je: "<<s2.brojElemenata();
}


int main()
{
    stavitest();
    brisitest();
    celotest();
    testskini();
    testbrojel();
    testdodjele();
    return 0;
}
