#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;

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
  Pocetak=Kraj=nullptr;
  Tekuci=0;
 }
 //kontruktor kopije i operator dodjele
 JednostrukaLista<tip>& operator= (const JednostrukaLista<tip>& el) {
        while(Pocetak!=Kraj) {
            Tekuci=Pocetak;
            Pocetak=Pocetak->sljedeci;
            delete Tekuci;

        }
        delete Kraj;
        Cvor *n;
        Cvor *l;
        Cvor* pomoc2;
        pomoc2=0;
        l=el.Pocetak;
        duzina=el.duzina;
        while(l!=el.Kraj) {
            n=new Cvor;
            n->x=l->x;
            if(l==el.Pocetak) {
                Pocetak=n;
            } else {
                pomoc2->sljedeci=n;
            }
            pomoc2=n;
            if(l==el.atm) {
                Tekuci=n;
            }
            l=l->sljedeci;
        }
        Kraj=pomoc2;

        return *this;
    }
    JednostrukaLista(const JednostrukaLista<tip>& el) {
        Cvor* elementt;
        Cvor* nesto;
        nesto=0;
        elementt=el.Pocetak;
        duzina=el.duzina;
        while(elementt!=el.Kraj) {
            Cvor* n;
            n=new Cvor;
            n->elementt=elementt->elementt;
            if(elementt==el.Pocetak) {
                Pocetak=n;
            } else {
                nesto->sljedeci=n;
            }
            nesto=n;
            if(nesto==el.Tekuci) {
                Tekuci=n;
            }
            elementt=elementt->sljedeci;
        }
        Kraj=nesto;

    }

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
  Cvor *novi=new Cvor;
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


  template<typename tip>
  class Red{
   JednostrukaLista<tip>red;
   public:
   Red(){}
   int brojElemenata(){
    return red.brojElemenata();
   }
   void brisi(){
    while(red.brojElemenata()){
     red.obrisi();
    }
   }
   void stavi(const tip &el){
    if(brojElemenata())
    red.kraj();
    red.dodajIza(el);
   }
   tip& celo(){
    if(!(red.brojElemenata()))
    throw("izuzetakkk");
    red.pocetak();
    return red.trenutni();
   }
   tip skini(){
    if(!(red.brojElemenata()))
    throw("izuzetakkk");
    red.pocetak();
    tip pomocni=red.trenutni();
    red.obrisi();
    return pomocni;
   }
  };

  void radixSort(vector<int> &a){
   Red<int> red[10];
   int decimal=0;
   if(a.size()==0)
   return;
   int max=a[0];
   for(int i=0;i<a.size();i++){
    if(a[i]>max)
    max=a[i];
   }
   do{
    decimal++;
    max=max/10;
   }while(max>0);

   int p=1;
   for(int k=1;k<=decimal;k++){
    for(int i=0;i<a.size();i++){
    red[(a[i]/p)%10].stavi(a[i]);}

    int j=0;
    for(int i=0;i<10;i++){
     while(red[i].brojElemenata()){
      a[j]=red[i].skini();
      j++;
     }
    }p=p*10;
   }
  }
  int roditelj(int i){
   return (i-1)/2;
  }
  int desnoDijete(int i){
   return i*2+2;

  }

  int lijevoDijete(int i){
   return 2*i+1;
  }
  bool List(int vel,int i){
   return i>=vel/2 && i<vel;
  }

  void popravi_dolje(vector<int> &a,int i,int vel){
   while(!List(vel,i)){
    int veci=lijevoDijete(i);
    int desno=desnoDijete(i);
    if(desno<vel && a[desno]>a[veci]){
     veci=desno;
    }
    if(a[i]>a[veci])
    return;

    int pomoc=a[i];
    a[i]=a[veci];
    a[veci]=pomoc;
    i=veci;
   }
  }

  void popravi_gore(vector<int> &a,int i){
  while(i!=0 && a[i]>a[roditelj(i)]){
    int pomoc=a[i];
   a[i]=a[roditelj(i)];
    a[roditelj(i)]=pomoc;
    i=roditelj(i);
   }
  }


  void stvoriGomilu(vector<int> &a){
   for(int i=a.size()/2;i>=0;i--){
    popravi_dolje(a,i,a.size());
   }
  }

  void umetniUGomilu(vector<int> &a,int umetnuti,int &velicina){
   a.push_back(umetnuti);
   velicina++;
   popravi_gore(a,velicina-1);
  }

  int izbaciPrvi(vector<int> &a,int &velicina){
   velicina--;
   int pomocni=a[0];
   a[0]=a[velicina];
   a[velicina]=pomocni;
   if(velicina!=0){
    popravi_dolje(a,0,velicina);
   }
   return a[velicina];
  }

  void gomilaSort(vector<int> &a){
   stvoriGomilu(a);
   int vel=a.size();
   for(int i=0;i<=a.size()-2;i++)
   izbaciPrvi(a,vel);
  }

  int main(){
   return 0;}
