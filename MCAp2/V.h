#pragma once
class V
{
public:
	bool isV=true;
	double koef=1;
	double value=1;
	double itog = 0;
	int x, y;
	void noV();
	void podschet();
	V(int a,int b,double k);
	V(int a, int b, int k);
	~V();
};

