#define _CRT_SECURE_NO_WARNINGS 
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "rk4.h"
#include "winbgi2.h"

void rhs_fun(double t, double *X, double *F);
double energia(double* X);

double g=9.81;			//przyspieszenie ziemskie
double k1;				//wpolczynniki sprezystosci
double k2;
double l;				//dlugosc wahadla
double m;				//masa kulki

void main()
{
	double alfa0;			//kat wychylenia
	double omega0=1.5;			//predkosc katowa
	double FR[2];				//tablica zapisujaca prawe strony rownan
	double tk=15;
	double t;
	double h=0.1;				//krok calkowania

	printf("podaj dlugosc wahadla l: \n ");
	scanf("%lf", &l);
	printf("podaj wspolczynnik sprezystosci sprezyny 1 k1: \n ");
	scanf("%lf", &k1);
	printf("podaj wspolczynnik sprezystosci sprezyny 2 k2: \n ");
	scanf("%lf", &k2);
	printf("podaj mase kulki m: \n ");
	scanf("%lf", &m);
	printf("podaj kat wychylenia wahadla alfa: \n ");
	scanf("%lf", &alfa0);

	double XR[2]={omega0,alfa0};			//tablica wartosci zmiennych zaleznych
	graphics(800,600);
	scale(-10,-10,100,100);

	for (t=0; t<=tk; t+=h)
	{

		vrk4(t,XR,h,2,rhs_fun,FR);
		printf("t = %lf\t  omega = %lf\t alfa  = %lf\t E = %lf\n\n", t,  XR[0], XR[1], energia(XR)); 
		

		setcolor(RED);
		point(t,XR[1]);						//wykres zaleznosci kata alfa od t
		//point(t,XR[0]);						//wykres zaleznoci predkosci omega od t
		//point(XR[1],XR[0]);					//wykres zaleznosci predkosci omega od kata alfa
		//point(t,energia(XR));					//wykres energii mechanicznej od t

		XR[0]=FR[0];
		XR[1]=FR[1];
		
		
		
	}
wait();
}

void rhs_fun(double t, double *X, double *F)
{
	double prawa_str[2];
	prawa_str[0]= (-((g/l)*sin(X[1]))-((k1/m)*sin(X[1]*cos(X[1]))-((k2/m)*sin(X[1])*cos(X[1]))));
	prawa_str[1]= X[0];
	F[0]=prawa_str[0];
	F[1]=prawa_str[1];
}

double energia(double* X)
{
	return (((m*l*l)/2)*X[0]*X[0]+m*g*l*(1-cos(X[1])))+((k1*(l*sin(X[1]))*(l*sin(X[1])))/2)+((k2*(l*sin(X[1])*(l*sin(X[1])))/2));
}