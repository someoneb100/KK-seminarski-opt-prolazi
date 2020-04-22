#include <stdio.h>
#include <stdlib.h>

const int globalnoCetiri = 4;
int vraca5();
int mnoziCisto(int a, int b);
int mnoziSaCetiriPrljavo(int a);
int mnoziSaSestsSTDLIB(int a);
int rekurzivnaSuma1(int a);
int rekurzivnaSuma2(int a);
int granajucaBazna(int a, int b);
int granajucaCista(int a);
int granajucaPrljava(int a);
int sumaPetlja(int *a);

int main() {
  int broj1 = mnoziCisto(vraca5(), 3);
  int broj2 = mnoziSaCetiriPrljavo(broj1);
  int broj3 = mnoziSaSestsSTDLIB(broj2);
  int broj4 = rekurzivnaSuma1(broj3);
  int broj5 = granajucaBazna(broj4, broj3);
  int rezultat = sumaPetlja(&broj5);
  printf("%d je broj testa!\n", rezultat);
  return 0;
}

int vraca5(){ return 5; }
int mnoziCisto(int a, int b){ return a*b; }
int mnoziSaCetiriPrljavo(int a){ return globalnoCetiri*a; }
int mnoziSaSestsSTDLIB(int a){ return atoi("6")*a; }
int rekurzivnaSuma1(int a){
  if(a <= 0) return 0;
  return a+rekurzivnaSuma2(a-1);
}
int rekurzivnaSuma2(int a){
  if(a <= 0) return 0;
  return a+rekurzivnaSuma1(a-1);
}
int granajucaBazna(int a, int b){ return a>b?granajucaCista(a):granajucaPrljava(b); }
int granajucaCista(int a){ return mnoziCisto(vraca5(), rekurzivnaSuma2(a)); }
int granajucaPrljava(int a){ return rekurzivnaSuma1(mnoziSaCetiriPrljavo(vraca5()))+a; }
int sumaPetlja(int *a){
  int suma = 0;
  for(; (*a)>0; (*a)--) suma += *a;
  return suma;
}
