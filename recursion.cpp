#include <iostream>

int fib2_0(int n,int prosli=1,int pretprosli=0,int rezultat=0){
if (n<=1) return rezultat;
else if(n==0)
return 0;
else {
    rezultat = pretprosli+prosli;
    pretprosli = prosli;
    prosli = rezultat;
    return fib2_0(n-1,prosli,pretprosli,rezultat); //repna
}
}
int nzd(int x,int y){
    if(y==0) return x;
    else if(y>0)
    return nzd(y,x%y);
}
int main() {
    std::cout << "Pripremna Zadaca Za Vjezbu 5, Zadatak 1";
    return 0;
}

