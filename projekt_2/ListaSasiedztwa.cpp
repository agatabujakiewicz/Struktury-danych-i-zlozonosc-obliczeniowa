#include "StdAfx.h"
#include "ListaSasiedztwa.h"
#include <stdio.h> 
#include <iostream>

using namespace std;

ListaSasiedztwa::ListaSasiedztwa()
{
	glowa = NULL;


}

ListaSasiedztwa::~ListaSasiedztwa()
{
	//cout << "Zadzialal destruktor listy sasiedztwa" << endl;
	WezelListy *temp = glowa;
	while (temp != NULL)
	{
		WezelListy *next = temp->nastepny;
		delete temp;
		temp = next;
		
	}
}


