// projekt_2.cpp : main project file.

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <time.h>
#include <stdio.h>      
#include <stdlib.h>
#include "GrafLista.h"
#include "GrafMacierz.h"


using namespace std;
void MenuDijkstra()
{
int V = 0;
float G = 0.0;

	int x, c, y = -1;
	cout <<"Podaj ilosc wierzcholkow: "; cin >> V;
	cout <<endl;
	cout <<"Podaj gestosc: (0.0 - 1.0) "; cin >> G;
	cout <<endl;
	
	GrafLista Graf_L_Dijkstra(V, true);
	GrafMacierz Graf_M_Dijkstra(V, true);
	Graf_L_Dijkstra.LosujGraf(V, G, true);
	Graf_L_Dijkstra.ZapiszDoPliku("temp.txt", true);
	//Graf_M_Dijkstra.LosujGraf(V, G, true);
	Graf_M_Dijkstra.WczytajZPliku("temp.txt", true);
	Dijkstra Dijkstra_L(V);
	Dijkstra_M Dijkstra_M(V);
	
	
	while (c!=0)
	{	
		cout << endl;
		cout << "Podaj liczbe, aby uzyc opcji menu:" << endl;
		cout << "1 - Wyswietl graf listowo" << endl;
		cout << "2 - Wykonaj algorytm Dijkstry na liscie" << endl;
		cout << "3 - Zapisz ten graf do pliku" << endl;
		cout << "4 - Wczytaj graf z pliku (GrafLista.txt)" << endl;

		cout << "5 - Wyswietl graf macierzowo" << endl;
		cout << "6 - Wykonaj algorytm Dijkstry na macierzy" << endl;
		cout << "7 - Zapisz ten graf do pliku" << endl;
		cout << "8 - Wczytaj graf z pliku (GrafMacierz.txt)" << endl;

		cout << "0 - opusc menu" << endl;
		cout << endl;
		cout<<"Wybor: ";
		cin >>c;
		switch(c)
		{
			
			case 1:
				Graf_L_Dijkstra.WypiszListe(true);
				break;
			case 2:
				
				Dijkstra_L.SzukajSciezkiDijkstra(0, V-1, Graf_L_Dijkstra);
				break;
			
			case 3:
				Graf_L_Dijkstra.ZapiszDoPliku(true);
				cout <<"Zapisano do pliku"<<endl;
				break;
		 
			case 4:
				Graf_L_Dijkstra.WczytajZPliku(true);
				cout <<"Wczytano z pliku"<<endl;
				break;


			case 5:
				Graf_M_Dijkstra.WypiszMacierz();
				break;

			case 6:
				Dijkstra_M.SzukajSciezkiDijkstra(0, V-1, Graf_M_Dijkstra);
				break;
			
			case 7:
				Graf_M_Dijkstra.ZapiszDoPliku();
				cout <<"Zapisano do pliku"<<endl;
				break;

			case 8:
				Graf_M_Dijkstra.WczytajZPliku("GrafMacierz.txt", true);
				cout <<"Wczytano z pliku"<<endl;
				break;
			case 0:
				break;
			default:
			cout <<"Zla opcja"<<endl;
			break;
		}

	}


}

void MenuPrim()
{
int V = 0;
float G = 0.0;

	int x, c, y = -1;
	cout <<"Podaj ilosc wierzcholkow: "; cin >> V;
	cout <<endl;
	cout <<"Podaj gestosc: (0.0 - 1.0) "; cin >> G;
	cout <<endl;
	
	GrafLista Graf_L_MST(V, false);
	GrafMacierz Graf_M_MST(V, false);
	Graf_L_MST.LosujGraf(V, G, false);
	Graf_L_MST.ZapiszDoPliku("temp.txt", false);
	//Graf_M_MST.LosujGraf(V, G, false);
	Graf_M_MST.WczytajZPliku("temp.txt", false);
	MST MST_L(V);
	MST_M MST_M(V);
	
	
	while (c!=0)
	{	
		cout << endl;
		cout << "Podaj liczbe, aby uzyc opcji menu:" << endl;
		cout << "1 - Wyswietl graf listowo" << endl;
		cout << "2 - Tworz MST dla listy" << endl;
		cout << "3 - Zapisz ten graf do pliku" << endl;
		cout << "4 - Wczytaj graf z pliku (GrafLista.txt)" << endl;

		cout << "5 - Wyswietl graf macierzowo" << endl;
		cout << "6 - Tworz MST dla macierzy" << endl;
		cout << "7 - Zapisz ten graf do pliku" << endl;
		cout << "8 - Wczytaj graf z pliku (GrafMacierz.txt)" << endl;

		cout << "0 - opusc menu" << endl;
		cout<<"Wybor: ";
		cin >>c;
		switch(c)
		{
			
			case 1:
				Graf_L_MST.WypiszListe(false);
				break;
			case 2:
				
				MST_L.TworzMSTPrim(Graf_L_MST);
				MST_L.WypiszListe();
				break;
			
			case 3:
				Graf_L_MST.ZapiszDoPliku(false);
				cout <<"Zapisano do pliku"<<endl;
				break;
		 
			case 4:
				Graf_L_MST.WczytajZPliku(false);
				MST_L.V = Graf_L_MST.V;
				MST_L.TablicaDrzewa.resize(MST_L.V);
				cout <<"Wczytano z pliku"<<endl;
				break;


			case 5:
				Graf_M_MST.WypiszMacierz();
				break;

			case 6:
				MST_M.TworzMSTPrim(Graf_M_MST);
				MST_M.WypiszListe();
				break;
			
			case 7:
				Graf_M_MST.ZapiszDoPliku();
				cout <<"Zapisano do pliku"<<endl;
				break;

			case 8:
				Graf_M_MST.WczytajZPliku("GrafMacierz.txt", false);
				MST_M.V_M = Graf_M_MST.V_M;
				MST_M.TablicaDrzewa.resize(MST_M.V_M);
				cout <<"Wczytano z pliku"<<endl;
				break;
			default:
			cout <<"Zla opcja"<<endl;
			break;
		}

	}


}

void main()
{

	srand (time(NULL));


	int x, c, y = -1;
	cout <<"Podaj liczbe, aby uzyc opcji menu:"<<endl;
	cout <<"1 - przejdz do menu algorytmu Prima dla MST"<<endl;
	cout <<"2 - przejdz do menu algorytmu Dijkstry dla wyszukiwania sciezki"<<endl;
	cout <<"0 - opusc menu"<<endl;
	

	while (c!=0)
	{	cout<<"Wybor: ";
		cin >>c;
		switch(c)
		{
			case 1:
			MenuPrim();
			break;
   
			case 2:
			MenuDijkstra();
			break;
		 
			default:
			cout <<"Zla opcja"<<endl;
			break;
		}

	}

	getch();
}

