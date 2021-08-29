#include <iostream>
//#include<cstdlib>

template <typename Tip>
class Lista {
public:
 Lista() {} // Podrazumijevani konstruktor
 virtual ~Lista() {} // Bazni destruktor
 virtual void obrisi()= 0;
 virtual int brojElemenata() const=0;
 virtual Tip trenutni()const=0;
 virtual Tip& trenutni()=0;
 //virtual bool Umetni(const InfoTip&)= 0; // Umetanje elementa
 //virtual bool Dodaj(const InfoTip&)= 0; // Dodavanje na kraj
 //virtual InfoTip Izbaci() = 0; // Izbacivanje tekuæeg elementa
 virtual void pocetak() = 0; // Pozicioniranje na poèetak
 virtual void kraj() = 0; // Pozicioniranje na kraj
 virtual bool prethodni() = 0; // Pozicioniranje na prethodni
 virtual bool sljedeci() = 0; // Pozicioniranje na sljedeæi
 //virtual void IdiNaPoziciju(int pos) =0; // Pozicioniranje na i-tu poz.
 virtual void dodajIspred(const Tip &el)=0;
 virtual void dodajIza(const Tip &el)=0;
 virtual Tip operator[](int el) const=0;
 virtual Tip& operator[](int el)=0;

};

template<typename tip>
class NizLista:public Lista<tip>
{
 protected:
 tip *pok;
 int kapacitet;
 int duzina;
 int tekuci;
 public:

~NizLista(){delete []pok;}
//kontruktor
NizLista(int size=20)
{
 kapacitet=size;
 duzina=tekuci=0;
 pok=new tip[kapacitet];
}
//kontruktor kopije
NizLista(const NizLista<tip>& el):kapacitet(el.kapacitet),duzina(el.duzina),tekuci(el.tekuci)
{
 pok=new tip[el.kapacitet];
 for(int i=0;i<el.duzina;i++)
 pok[i]=el.pok[i];
}

NizLista<tip>& operator=(const NizLista<tip>& el)
{
 //if(el==this) return *this;
 delete[] pok;
 kapacitet=(el.kapacitet);
 duzina=(el.duzina);
 tekuci=(el.tekuci);
 pok=new tip[el.kapacitet];
 for(int i=0;i<el.duzina;i++)
 pok[i]=el.pok[i];
 return *this;
}
int brojElemenata() const override
{
 return duzina;
}
//dvije verzije
tip trenutni()const override
{
 return pok[tekuci];
}
tip& trenutni()
{
 return pok[tekuci];
}
void pocetak()
{
 if(duzina<=0)
 throw("prazna lista");
 else
 tekuci=0;

}
void kraj()
{
 if(duzina<=0)
 throw("prazna lista");
 else
 tekuci=duzina-1;
}

bool prethodni()
{
 if(tekuci==0){
 return false;}
 else
 tekuci--;

 return true;
}

bool sljedeci()
{
 if(tekuci==duzina-1){
 return false;}
 else
 tekuci++;

 return true;
}

tip operator [](int i) const
{
 if(i<0 || i>duzina)
 throw("Neispravan indeks");
 return pok[i];
}
tip &operator[](int i)
{
  if(i<0 || i>duzina)
 throw("Neispravan indeks");
 return pok[i];
}
void obrisi(){
 for(int i=tekuci;i<duzina-1;i++) pok[i]=pok[i+1];
 duzina--;

}
void dodajIspred(const tip& el)
{
 if(duzina==0)
 {
  pok[0]=el;
  duzina++;
  return;
 }

 if(duzina==kapacitet)
 {
  tip* prosiri;
  prosiri=new tip[2*kapacitet];
  kapacitet=2*kapacitet;
  for(int i=0;i<duzina;i++)
  prosiri[i]=pok[i];

  duzina++;
  //presipanje
  delete [] pok;
  pok=prosiri;
 } else
 {
  for(int j=duzina;j>tekuci;j--)
  pok[j]=pok[j-1];

  pok[tekuci]=el;
  duzina++;
  tekuci++;
 }
}
void dodajIza(const tip& el)
{
 if(duzina==0)
 {
  pok[0]=el;
  duzina++;
  return;
 }

 if(duzina==kapacitet)
 {
  tip* prosiri;
  prosiri=new tip[2*kapacitet];
  kapacitet=2*kapacitet;
  for(int i=0;i<duzina;i--)
  prosiri[i]=pok[i];

  duzina++;
  //presipanje
  delete [] pok;
  pok=prosiri;
 } else
 {
  for(int j=duzina;j>tekuci;j--)
  pok[j]=pok[j-1];

  pok[tekuci+1]=el;
  duzina++;
  //tekuci++;
 } }

};





template<typename tip>
class JednostrukaLista: public Lista<tip>
{
 private:
 struct Cvor
 {
  tip element;
  Cvor *sljedeci=nullptr;
 };
 int duzina;
 Cvor *Pocetak;
 Cvor *Kraj;
 Cvor *Tekuci;
 public:
 JednostrukaLista():duzina(0),Pocetak(0),Kraj(0),Tekuci(0){}
 //destruktor
 ~JednostrukaLista()
 {
  while(Pocetak!=nullptr)
  {
   Tekuci=Pocetak;
   Pocetak=Pocetak->sljedeci;
   delete Tekuci;
  }
  Pocetak=Kraj=Tekuci=0;
 }
 //kontruktor kopije i operator dodjele

 int brojElemenata() const override
 {
  return duzina;
 }
 tip trenutni() const override
 {
  if(duzina<=0)
  throw("Nema elemenata u listi");
  else
  return Tekuci->element;
 }
 tip& trenutni()
 {
  if(duzina<=0)
  throw("Nema elemenata u listi");
  else
  return Tekuci->element;
 }
 bool sljedeci()
 {
  if(Tekuci==Kraj) return false;
  else
  {
   Tekuci=Tekuci->sljedeci;
   return true;
  }
 }
 bool prethodni()
 {
  if(Tekuci==Pocetak) return false;
  if(duzina!=0){
   Cvor *pret=Pocetak;
   while(pret->sljedeci!=Tekuci)
   pret=pret->sljedeci;

   Tekuci=pret;
   return true;
  }
 }

 void pocetak(){
  Tekuci=Pocetak;
 }
 void kraj()
 {
  Tekuci=Kraj;
 }
 tip operator[](int i) const override
 {
  Cvor *temp=Pocetak;
  for(int j=0;j<i;j++)
  {
   if(temp!=Kraj) temp=temp->sljedeci;
  }
  return temp->element;
 }
  tip& operator[](int i)
 {
  Cvor *temp=Pocetak;
  for(int j=0;j<i;j++)
  {
   if(temp!=Kraj) temp=temp->sljedeci;
  }
  return temp->element;
 }
 void dodajIspred(const tip& el)
 {
  Cvor *novi=new Cvor();
  novi->element=el;
  if(duzina==0)
  {
   Pocetak=novi;
   Kraj=novi;
   Tekuci=novi;
   novi->sljedeci=0;
   duzina++;
  }
  //prvi
  else if(Tekuci==Pocetak)
  {
   novi->sljedeci=Pocetak;
   Pocetak=novi;
   duzina++;
  }
  else
  {
   Cvor* temp(Pocetak);
   while(temp!=Kraj && temp->sljedeci!=Kraj&& temp->sljedeci!=Tekuci){
   temp=temp->sljedeci;}
   novi->sljedeci=temp->sljedeci;
   temp->sljedeci=novi;
   duzina++;
  }
 }
  void dodajIza(const tip& el)
 {
  Cvor *novi=new Cvor();
  novi->element=el;
  if(duzina==0)
  {
   Pocetak=novi;
   Kraj=novi;
   Tekuci=novi;
   novi->sljedeci=0;
   duzina++;
  }
  //prvi
  else if(Tekuci==Kraj)
  {
   Tekuci->sljedeci=novi;
   novi->sljedeci=0;
   Kraj=novi;
   duzina++;
  }
  else
  {
   Cvor* temp(Pocetak);
   novi->sljedeci=Tekuci->sljedeci;
   Tekuci->sljedeci=novi;

   duzina++;
  }
 }

 void obrisi()
 {
  if(duzina==0)
  {
   throw("Prazna lista");
  }
  else if(Tekuci==Kraj)
  {
   Cvor *temp(Pocetak);
   if(Pocetak!=Kraj)
   {
    while(temp->sljedeci!=Kraj)
    temp=temp->sljedeci;
   }
   delete Kraj;
   Kraj=temp;
   Tekuci=Kraj;
   if(duzina-1!=0){
   Tekuci->sljedeci=nullptr;}
   duzina--;}
   else if(Tekuci==Pocetak)
   {
    Pocetak=Pocetak->sljedeci;
    delete Tekuci;
    Tekuci=Pocetak;
    duzina--;
   }
   else
   {
    Cvor *pomocni;
    pomocni=Pocetak;

    while(pomocni!=Kraj && pomocni->sljedeci!=Kraj &&pomocni->sljedeci!=Tekuci)
    pomocni=pomocni->sljedeci;


    auto pom=Tekuci->sljedeci;
    delete Tekuci;
    pomocni->sljedeci=pom;//element gdje je bio atm postaje sljedeci
    Tekuci=pomocni->sljedeci;
    duzina--;
   }
   if(duzina==0)
   {
    Tekuci=0;
    Kraj=0;
    Pocetak=0;
   }

  }};

 void testbrojelemenata()
 {
  NizLista<int>pomoc;
  pomoc.dodajIspred(2);
  pomoc.dodajIza(3);
  pomoc.dodajIspred(5);
  std::cout<<"Broj elemenata liste je: "<<pomoc.brojElemenata()<<std::endl;
 }
 void nizlistadodajiza_test()
 {
  NizLista<int>pomoc;
  for(int i=0;i<2;i++)
  pomoc.dodajIza(2);

  pomoc.dodajIza(3);
  std::cout<<"NizLista je: "<<std::endl;
  for(int i=0;i<3;i++)
  std::cout<<pomoc[i]<<std::endl;
  std::cout<<std::endl;


 }
  void nizlistadodajispred_test()
 {
  NizLista<int>pomoc;
  for(int i=0;i<2;i++)
  pomoc.dodajIspred(2);

  pomoc.dodajIspred(3);
  std::cout<<"NizLista je: "<<std::endl;
  for(int i=0;i<3;i++)
  std::cout<<pomoc[i]<<std::endl;
  std::cout<<std::endl;
 }
 void testobrisinizlista()
 {
  NizLista<int>pomoc;
  for(int i=0;i<3;i++)
  pomoc.dodajIspred(2);
  pomoc.obrisi();
  pomoc.obrisi();
  for(int i=0;i<1;i++)
  std::cout<<pomoc[i];

 }
 int testoperatorniz(int i)
 {
  NizLista<int>pomoc;
  pomoc.dodajIspred(1);
  pomoc.dodajIspred(2);
  pomoc.obrisi();
  return pomoc[i];
 }
 void sljedecinizl()
 {
   NizLista<int>pomoc;
  pomoc.dodajIspred(1);
  pomoc.dodajIspred(2);
  pomoc.obrisi();
  std::cout<<"Sljedeci niz lista: "<<pomoc.sljedeci();
 }
  void prethodninizl()
 {
   NizLista<int>pomoc;
  pomoc.dodajIspred(1);
  pomoc.dodajIspred(2);
  pomoc.obrisi();
  std::cout<<"Prethodni niz lista: "<<pomoc.prethodni();
 }
void trenutninizlista()
{
  NizLista<int>pomoc;
  pomoc.dodajIspred(1);
  pomoc.dodajIspred(2);
   pomoc.dodajIspred(3);
  pomoc.obrisi();
  std::cout<<"Trenutni niz lista: "<<pomoc.trenutni();
}

void sljedecijlista()
{
  NizLista<int>pomoc;
  pomoc.dodajIspred(1);
  pomoc.dodajIspred(2);
  pomoc.obrisi();
  std::cout<<"Sljedeci jednostruke liste: "<<pomoc.sljedeci();
}
void prethodnijlista()
{
  NizLista<int>pomoc;
  pomoc.dodajIspred(1);
  pomoc.dodajIspred(2);
  pomoc.obrisi();
  std::cout<<"Prethodni jednostruke liste: "<<pomoc.prethodni();
}
void trenutnijlista()
{
  NizLista<int>pomoc;
  pomoc.dodajIspred(1);
  pomoc.dodajIspred(2);
   pomoc.dodajIspred(3);
  pomoc.obrisi();
  std::cout<<"Trenutni jednostruke listea: "<<pomoc.trenutni();
}
 void testbrojelemenatajednostrukeliste()
 {
  JednostrukaLista<int>pomoc;
  pomoc.dodajIspred(2);
  pomoc.dodajIza(3);
  pomoc.dodajIspred(5);
  std::cout<<"Broj elemenata jednostruke liste je: "<<pomoc.brojElemenata()<<std::endl;
 }
  void jednostrukalistadodajiza()
 {
  JednostrukaLista<int>pomoc;
  for(int i=0;i<2;i++)
  pomoc.dodajIza(2);

  pomoc.dodajIza(3);
  std::cout<<"Jednostruka lista je: "<<std::endl;
  for(int i=0;i<3;i++)
  std::cout<<pomoc[i]<<std::endl;
  std::cout<<std::endl;


 }

int main() {
    testbrojelemenata();
    nizlistadodajiza_test();
    nizlistadodajispred_test();
    testobrisinizlista();
    int p=testoperatorniz(0);
    std::cout<<"Operator niz lista: "<<p;
    sljedecinizl();
    prethodninizl();
    trenutninizlista();
    sljedecijlista();
    prethodnijlista();
    trenutnijlista();
    testbrojelemenatajednostrukeliste();
    jednostrukalistadodajiza();
    return 0;
}
