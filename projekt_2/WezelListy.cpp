#include "StdAfx.h"
#include "WezelListy.h"
#include <stdio.h> 
#include <iostream>

using namespace std;

WezelListy::WezelListy()
{
	wierzcholek_docelowy = 0;
	waga = 0;
	nastepny = NULL;
}

WezelListy::~WezelListy()
{
	//cout <<"Zadzialal destruktor wezla listy"<<endl;

}