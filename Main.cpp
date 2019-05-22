#include<stdio.h>
#include "Ponto.h"
#include <math.h>
#include <cstdlib>
#include <vector>

using namespace std;

double CalculaA(Ponto P1, Ponto P2)
{
	return ((P1.Y - P2.Y) / (P1.X - P2.X));
}

double CalculaB(Ponto P1, double A)
{
	return (P1.Y - (P1.X*A));
}

double CalculaY(Ponto P1, double A, double B)
{
	return ((P1.X*A) + B);
}

double CalculaX(Ponto P1, double A, double B)
{
	return ((P1.Y - B) / A);
}

vector<double> CalculaPontos(double X1, double X2)
{
	vector<double> retorno((int)floor(X2) - (int)floor(X1) + 2);
	retorno[0] = X1;
	for (int i = (int)ceil(retorno[0]); i < floor(X2) - floor(X1) + 1; i++)
	{
		retorno[i] = i;
	}

	retorno[(int)floor(X2) - (int)floor(X1) + 1] = X2;

	return retorno;
}

vector<Ponto> CalculaPontosEmXY(Ponto P1, Ponto P2,double a, double b)
{
	int index = 0;
	vector<Ponto> retorno(((int)floor(P2.X) - (int)floor(P1.X)) + ((int)floor(P2.Y) - (int)floor(P1.Y)) + 2);
	retorno[0] = P1;
	retorno[retorno.size()-1]=P2;
	for (int i = (int)ceil(retorno[0].X); i < floor(P2.X) - floor(P1.X) + 1; i++)
	{
		retorno[i] = * new Ponto(i, 0);
		retorno[i].Y = CalculaY(retorno[i], a, b);
		index++;
	}

	for (int i = (int)ceil(P1.Y); i < floor(P2.Y) - floor(P1.Y) + 1; i++)
	{
		index++;
		retorno[index] = *new Ponto(0, i);
		retorno[index].X = CalculaX(retorno[index], a, b);
	}

	return retorno;
}

int main(int argc, char *argv[])
{
	Ponto *p1 = new Ponto(0.8, 0.8);
	Ponto *p2 = new Ponto(2.7, 1.3);

	double a = CalculaA(*p1, *p2);
	double b = CalculaB(*p1, a);


	/*exemplo de calculo do Y quando soh tem o valor de X*/
	Ponto *p3 = new Ponto(2.7, 0);
	double Y = CalculaY(*p3, a, b);
	/*exemplo de calculo de X quando soh tem o valor de Y*/
	p3->Y = 1.3;
	p3->X = 0;
	double X = CalculaX(*p3, a, b);

	/*Calculo do vetor com os pontos de interessem em X */
	vector<double> PontosEmX;
	PontosEmX = CalculaPontos(p1->X, p2->X);
	/*com este vetor de pontos de X basta aplicar no methodo CalculaY, para descobrir os Y correspondentes.*/

	/* fazer o mesmo para obter os pontos de Y*/
	vector<double> PontosEmY;
	PontosEmY = CalculaPontos(p1->Y, p2->Y);

	/*lista com os pontos a serem calculados, agora basta ordenar pelos valores de X*/
	/*Todo: este algoritmo funciona para quando P1 é menor que P2*/
	vector<Ponto> Pontos;
	Pontos = CalculaPontosEmXY(*p1, *p2, a, b);

}