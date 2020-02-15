#include "pch.h"
#include <iostream>
#include "X.h"
#include "uravn.h"
#include "V.h"

void change_value_on_masV(int x,int y,double value);
void izv_v();
int findX(int a,int b);
void slozhit(int a,int b,double x, double **mas);
void znachtochki(int x,int y,double a);

vector <V> tochki;
vector<uravn>masUR;
vector<X>masx;
int hh, GRneizvest, SRneizvest = 0, tochekquality = 0, neizvQuality = 0;
double h;
int main()
{
	setlocale(LC_ALL, "RUS");

	

	cout << "Ведите шаг h:" << endl;
	cin >> hh;
	h = (double)hh;
	GRneizvest = hh - 2;
	for (int i = 3; i < hh; i++)
	{
		SRneizvest = SRneizvest + (i - 2);
	}
	neizvQuality = GRneizvest + SRneizvest;
	tochekquality = ((hh + 1) / 2)*hh;


	for (int i = 0; i < hh; i++)
	{
		for (int j = 0; j < hh - i; j++)
		{
			V tochka(i, j, 1);
			tochki.push_back(tochka);
		}
	}
	tochki[0].value = 2.05;
	tochki[0].podschet();

	for (int i = 0; i < hh; i++)
	{
		change_value_on_masV(i, h - 1 - i, 2.0);
	}

	for (int i = 1; i < hh - 1; i++)
	{
		change_value_on_masV(i, 0, 2.0);
	}

	for (int i = tochki.size() - 1; i >= 0; i--)
	{
		if (tochki[i].isV)
		{
			if (tochki[i].x != 0)
			{
				int k = tochki[i].x;
				int m = tochki[i].y;
				double kv = pow(h - 1, 2);
				uravn q(k, m);
				V tochka1(k + 1, m, ((h - 1) / 2)*cos(k*(1 / (h - 1)) + m * (1 / (h - 1))));
				q.addV(tochka1);

				V tochka2(k - 1, m, -1 * ((h - 1) / 2)*cos(k*(1 / (h - 1)) + m * (1 / (h - 1))));
				q.addV(tochka2);

				V tochka3(k + 1, m, kv);
				q.addV(tochka3);

				V tochka4(k, m, -2 * kv);
				q.addV(tochka4);

				V tochka5(k - 1, m, kv);
				q.addV(tochka5);

				V tochka6(k, m + 1, kv);
				q.addV(tochka6);

				V tochka7(k, m, -2 * kv);
				q.addV(tochka7);

				V tochka8(k, m - 1, kv);
				q.addV(tochka8);

				V tochka9(-1, -1, (k*(1 / (h - 1))) - (m*(1 / (h - 1))));
				tochka9.podschet();
				q.addV(tochka9);

				q.uprostit();
				masUR.push_back(q);
			}
			else
			{
				int k = tochki[i].x;
				int m = tochki[i].y;
				uravn q(k, m);

				V tochka1(1, m, (h - 1));
				q.addV(tochka1);

				V tochka2(0, m, (0 - (h - 1) - 0.2));
				q.addV(tochka2);

				V tochka3(-1, -1, -0.6);
				tochka3.podschet();
				q.addV(tochka3);

				q.uprostit();
				masUR.push_back(q);
			}
		}
	}

	izv_v();

	for (int i = tochki.size() - 1; i >= 0; i--)
	{
		if (tochki[i].isV)
		{
			X xx(tochki[i].x, tochki[i].y);
			masx.push_back(xx);
		}
	}

	for (int i = 0; i < masx.size(); i++)
	{
		for (int j = 0; j < neizvQuality; j++)
		{
			masx[i].xxx.push_back(0);
		}
	}

	for (int i = 0; i < masUR.size(); i++)
	{
		for (int j = 0; j < masUR[i].ur.size() - 1; j++)
		{
			int q = findX(masUR[i].ur[j].x, masUR[i].ur[j].y);
			masx[q].xxx[i] = masUR[i].ur[j].koef;
		}

	}

//#######################################################################

	//Строка, столбец
	double **mas = new double*[neizvQuality]; //создание
	for (int i = 0; i < neizvQuality; i++)
	{
		mas[i] = new double[(neizvQuality + 1)];
	}


	for (int i = 0; i < masx.size(); i++)//заполнение центра
	{
		for (int j = 0; j < masx[i].xxx.size(); j++)
		{
			mas[j][i] = masx[i].xxx[j];
		}
	}

	for (int i = 0; i < neizvQuality; i++) //заполнение правой части
	{
			mas[i][neizvQuality]=masUR[i].ur[masUR[i].ur.size() - 1].itog;
	}

	for (int i = 0; i < neizvQuality; i++) 
	{
		for (int j = 0; j < neizvQuality+1; j++)
		{
			printf("%7.2f",mas[i][j]);
		}
		cout << endl;
	}
//####################################################################################################################3
//метод Гаусса
	//.................................нижняя часть матрицы....................................
	for (int i = 0; i < neizvQuality; i++)
	{
		if (mas[i][i] == 0) 
		{
			for (int j = i + 1; j < neizvQuality; j++) 
			{
				if (mas[j][i] != 0) 
				{
					slozhit(j,i,1,mas);
					slozhit(i, j, -1, mas);
				}
			}
		}

		if (mas[i][i] != 0) 
		{
			for (int j = i + 1; j < neizvQuality; j++)
			{
				if (mas[j][i] != 0)
				{
					slozhit(i, j,(0-(mas[j][i]/mas[i][i])), mas);
				}
			}
		}
	}
	//.................................верхняя часть матрицы....................................
	for (int i = neizvQuality-1; i >=0; i--)
	{
		if (mas[i][i] == 0)
		{
			for (int j = i - 1; j >=0; j--)
			{
				if (mas[j][i] != 0)
				{
					mas[j][i] = 0;
				}
			}
		}

		if (mas[i][i] != 0)
		{
			for (int j = i - 1; j >= 0; j--)
			{
				if (mas[j][i] != 0)
				{
					slozhit(i, j, (0-(mas[j][i] / mas[i][i])), mas);
				}
			}
		}
	}
	//.................................................................................................
	cout <<"Матрица после преобразований:"<< endl;
	for (int i = 0; i < neizvQuality; i++)
	{
		for (int j = 0; j < neizvQuality + 1; j++)
		{
			printf("%7.2f", mas[i][j]);
		}
		cout << endl;
	}

	for (int i = 0; i < neizvQuality; i++) 
	{
		int q = 0;
		for (int j = 0; j < neizvQuality; j++) 
		{
			mas[i][j] = ((int)mas[i][j] * 100)/100;
			if (mas[i][j] != 0) 
			{

				q = q + 1;
			}
		}
		cout << "В " << i<<" строке " <<q<<" ненулевых элементов"<< endl;
	}

	for (int i = 0; i < neizvQuality; i++) 
	{
		znachtochki(masx[i].XV,masx[i].YV,(mas[i][neizvQuality]/mas[i][i]));
	}

	for (int i = 0; i < tochki.size(); i++)
	{
		cout << "V " <<tochki[i].x<<" "<<tochki[i].y<<" = "<<tochki[i].itog<< endl;
	}

	ofstream out;
	out.open("d:\\156.txt");

	for (int i = 0; i < tochki.size(); i++)
	{
		out << "V " << tochki[i].x << " " << tochki[i].y << " = " << tochki[i].itog << endl;
	}

	tochki.size();
	masx.size();
	masUR.size();
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void change_value_on_masV(int x, int y, double value)
{
	for (int i = 0; i <= tochki.size(); i++) 
	{
		if (tochki[i].x == x && tochki[i].y == y)
		{
			tochki[i].value = value;
			tochki[i].podschet();
			break;
		}
	}
}

void izv_v()
{
	for (int i = 0; i < masUR.size(); i++) 
	{
		for (int j = 0; j < masUR[i].ur.size(); j++) 
		{
			for (int q = 0; q < tochki.size(); q++) 
			{
				if(masUR[i].ur[j].x==tochki[q].x && masUR[i].ur[j].y == tochki[q].y)
				{
					if (!tochki[q].isV) { masUR[i].ur[j].noV(); masUR[i].ur[j].value = 2; }
				}
			}
		}
	}

	for (int i = 0; i < masUR.size(); i++)
	{
		bool q = true;
		while (q)
		{
			q = false;
			for (int j = 0; j < masUR[i].ur.size(); j++)
			{
				if(!masUR[i].ur[j].isV)
				{
					if (masUR[i].ur[j].x != -1)
					{
						masUR[i].ur[j].podschet();
						masUR[i].ur[masUR[i].ur.size() - 1].itog = masUR[i].ur[masUR[i].ur.size() - 1].itog - masUR[i].ur[j].itog;
						masUR[i].ur.erase(masUR[i].ur.begin() + j);
						q = true;
					}
					break;
				}
			}
		}
	}


}

int findX(int a, int b)
{
	int q;
	for (int i = 0; i < masx.size(); i++) 
	{
		if (masx[i].XV == a && masx[i].YV == b) { q = i; break; }
	}
	return q;
}
//а-строка которую прибавляем, b-к которой прибавляем
void slozhit(int a, int b, double x, double **mas)
{
	double temp;

	for (int i = 0; i <= neizvQuality; i++) 
	{
		temp = mas[a][i];
		temp = temp * x;
		mas[b][i] = mas[b][i] + temp;
		//if (mas[b][i] < 0.01) { mas[b][i] = 0; }
	}
}

void znachtochki(int x, int y, double a)
{
	for (int i = 0; i < tochki.size(); i++) 
	{
		if (tochki[i].x == x && tochki[i].y == y) { tochki[i].value = a; tochki[i].podschet();  break; }
	}
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////