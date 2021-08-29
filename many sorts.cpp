#include <iostream>
#include<fstream>
#include<vector>
#include<string>
#include<ctime>

template<typename tip>
void bubble_sort(tip* niz,int vel){
    //od kraja
    for(int i=vel-1;i>=1;i--){
        for(int j=1;j<=i;j++){
            if(niz[j-1]>niz[j]){
                tip pomocni=niz[j-1];
                niz[j-1]=niz[j];
                niz[j]=pomocni;
            }
        }
    }
}

template<typename tip>
void selection_sort(tip* niz,int vel){
    for(int i=0;i<vel-1;i++){
        tip min=niz[i];
        int pmin=i;
        for(int j=i+1;j<vel;j++){
            if(niz[j]<min){
            min=niz[j];
            pmin=j;}
        }
        niz[pmin]=niz[i];
        niz[i]=min;
    }
}

template<typename tip>
int particija(tip* niz,int prvi,int zadnji){
    tip pivot=niz[prvi];
    int p=prvi+1;

    while(p<=zadnji && niz[p]<pivot)
    p=p+1;

    for(int i=p+1;i<=zadnji;i++){
        if(niz[i]<pivot){
            tip pomocni=niz[p];
            niz[p]=niz[i];
            niz[i]=pomocni;
            p=p+1;
        }
    }

    tip pomocni=niz[prvi];
    niz[prvi]=niz[p-1];
    niz[p-1]=pomocni;
    return p-1;
}

template<typename tip>
void q(tip *niz,int prvi,int zadnji){
    if(prvi<zadnji){
        int j=particija(niz,prvi,zadnji);
        q(niz,prvi,j-1);
        q(niz,j+1,zadnji);
    }
}


template<typename tip>
void quick_sort(tip* niz,int vel){
    q(niz,0,vel-1);

}

//implementacija merge sort-podijeli pa vladaj
//smanjivanje na manje dijelove dok se ne rijesi direktno
template<typename tip>
void merge(tip* niz,int l,int p,int q,int u){
    int v=u-l+1;
    tip* novi=new tip[v];
int i=0;
int j=q-l;
int k=l;

for(int m=0;m<=u-l;m++){
    novi[m]=niz[l+m];
}
while(i<=p-l && j<=u-l){
    if(novi[i]<novi[j]){
        niz[k]=novi[i];
        i=i+1;
    }
    else{
         niz[k]=novi[j];
        j=j+1;

    }
    k=k+1;
}
while(i<=p-l){
    niz[k]=novi[i];
    k=k+1;
    i=i+1;
}
while(j<=u-l){
    niz[k]=novi[j];
    k=k+1;
    j=j+1;
}
delete [] novi;
}
template<typename tip>
void m(tip* niz,int l,int u){
    if(u>l){
        int p=(l+u-1)/2;
        int q=p+1;
        m(niz,l,p);
        m(niz,q,u);
        merge(niz,l,p,q,u);
    }
}
template<typename tip>
void merge_sort(tip* niz,int vel){
    m(niz,0,vel-1);
}

void ucitaj(std::string filename,int*&niz,int &vel){
    std::vector<int>vektor;
    std::ifstream ulaz(filename);
    int broj;

    //upisivanje brojeva

    while(ulaz){
        ulaz>>broj;
        if(ulaz)
        vektor.push_back(broj);
    }

    vel=vektor.size();
    //dinamicka alokacija niza
    niz=new int[vel];
    for(int i=0;i<vel;i++){
        niz[i]=vektor[i]; //presipanje
    }
}
void generisi(std::string filename,int vel){
    srand(time(NULL));
    std::ofstream izlaz(filename);
    for(int i=0;i<vel;i++)
    izlaz<<rand()<<" "; //random upisi generisanje
}

