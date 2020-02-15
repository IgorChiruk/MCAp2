#pragma once
#include "V.h"
class uravn
{
public:
	vector <V> ur;
	int x, y;
	void addV(V v);
	void uprostit();
	uravn(int a,int b);
	~uravn();
};

