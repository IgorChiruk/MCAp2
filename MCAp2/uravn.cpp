#include "pch.h"
#include "uravn.h"


void uravn::addV(V v)
{
	ur.push_back(v);
}

void uravn::uprostit()
{
	bool q = true;
	while (q)
	{
		q = false;
		for (int i = 0; i < ur.size(); i++)
		{
			for (int j = i+1; j < ur.size(); j++) 
			{
				if (ur[i].x == ur[j].x && ur[i].y == ur[j].y)
				{
					q = true;
					ur[i].koef = ur[i].koef + ur[j].koef;
					ur.erase(ur.begin()+j);
					break;
				}
			}
			if (q) { break; }
		}
	}
}

uravn::uravn(int a, int b)
{
	x = a;
	y = b;
}


uravn::~uravn()
{
}
