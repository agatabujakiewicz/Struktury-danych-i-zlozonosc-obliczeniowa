#include "StdAfx.h"
#include "GrafLista.h"
#include "GrafMacierz.h"
#include "ListaSasiedztwa.h"
#include "WezelListy.h"
#include <iostream>
#include <stdio.h> 

using namespace std;
const int nieskonczonosc = 32849324;

Dijkstra::Dijkstra(int ilosc_wierzcholkow)
{
	
  dojscie = new int[ilosc_wierzcholkow];
  poprzednicy = new int[ilosc_wierzcholkow];
  QS =new bool[ilosc_wierzcholkow];//tablica wierzcholkow odwiedzonych jest typu bool, bo jeden wierzcholek moze byc albo odwiedzony, albo nie  
  Stos = new int[ilosc_wierzcholkow];           
  stos_ptr = 0;                     


  for(int i = 0; i < ilosc_wierzcholkow; i++)
  {
    dojscie[i] = nieskonczonosc;
    poprzednicy[i] = -1;
    QS[i] = false;
  }
}

Dijkstra::~Dijkstra()
{
	delete[] dojscie;
	delete[] poprzednicy;
	delete[] QS;
	delete[] Stos;
}

Dijkstra_M::~Dijkstra_M()
{
	delete[] dojscie;
	delete[] poprzednicy;
	delete[] QS;
	delete[] Stos;
}

Dijkstra_M::Dijkstra_M(int ilosc_wierzcholkow)
{

	
	dojscie = new int[ilosc_wierzcholkow];            
  poprzednicy = new int[ilosc_wierzcholkow];           
  QS = new bool[ilosc_wierzcholkow];//tablica wierzcholkow odwiedzonych jest typu bool, bo jeden wierzcholek moze byc albo odwiedzony, albo nie         
  Stos = new int[ilosc_wierzcholkow];         
  stos_ptr = 0;                     

  for(int i = 0; i < ilosc_wierzcholkow; i++)
  {
    dojscie[i] = nieskonczonosc;
    poprzednicy[i] = -1;
    QS[i] = false;
  }
}
void Dijkstra::SzukajSciezkiDijkstra(int poczatek, int koniec, GrafLista Graf)
{
		dojscie[poczatek] = 0;
		int ilosc_wierzcholkow = Graf.V;	
		int j = 0;
		int u = 0;

	for(int i = 0; i < ilosc_wierzcholkow; i++)
	{
  
	
		 for(j = 0; QS[j]; j++);
			for(u = j++; j < ilosc_wierzcholkow; j++)
			if(!QS[j] && (dojscie[j] < dojscie[u])) u = j;
			QS[u] = true;
		
			WezelListy *temp;
		
			for(temp = Graf.TablicaSkierowana[i].glowa; temp; temp = temp->nastepny)
			if(!QS[temp->wierzcholek_docelowy] && (dojscie[temp->wierzcholek_docelowy] > dojscie[u] + temp->waga))
			{
				 dojscie[temp->wierzcholek_docelowy] = dojscie[u] + temp->waga;
				 poprzednicy[temp->wierzcholek_docelowy] = u;
			} 
		
	} 
	
	for(int i = 0; i < ilosc_wierzcholkow; i++)
	{
		cout << i << ": ";
		for(j = i; j > -1; j = poprzednicy[j]) Stos[stos_ptr++] = j;
		while(stos_ptr) cout << Stos[--stos_ptr] << " ";
		cout << "Koszt sciezki: " << dojscie[i] << endl;
	}


}

void Dijkstra_M::SzukajSciezkiDijkstra(int poczatek, int koniec, GrafMacierz Graf)
{
		dojscie[poczatek] = 0;
		int ilosc_wierzcholkow = Graf.V_M;	
		int j = 0;
		int u = 0;

	  for(int i = 0; i < ilosc_wierzcholkow; i++)
	  {
		  for(j = 0; QS[j]; j++);
			for(u = j++; j < ilosc_wierzcholkow; j++)
			  if(!QS[j] && (dojscie[j] < dojscie[u])) u = j;
				QS[u] = true;
			
		int g = 0;
   
		for(g = 0; g< ilosc_wierzcholkow; g++)
			if(!QS[g] &&  Graf.Macierz[g][u] == 1 && (dojscie[g] > dojscie[u] + Graf.MacierzWag[g][u]))
			{
				dojscie[g] = dojscie[u] + Graf.MacierzWag[g][u];
				poprzednicy[g] = u;
			} 
	  } 
	
	  for(int i = 0; i < ilosc_wierzcholkow; i++)
	  {
		  cout << i << ": ";
		  for(j = i; j > -1; j = poprzednicy[j]) Stos[stos_ptr++] = j;
			while(stos_ptr) cout << Stos[--stos_ptr] << " ";
				cout << "Koszt sciezki: " << dojscie[i] << endl;
	  } 

}