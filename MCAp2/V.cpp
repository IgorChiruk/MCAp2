#include "pch.h"
#include "V.h"


void V::noV()
{
	isV = false;
}

void V::podschet()
{
	isV = false;
	itog = value * koef;
}


V::V(int a,int b,double k)
{
	koef = k;
	x = a;
	y = b;
}



V::V(int a, int b, int k)
{
	koef = (double)k;
	x = a;
	y = b;
}

V::~V()
{
}
