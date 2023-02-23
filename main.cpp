#include <iostream>
#include "conio.h"
using namespace std;

double f(double x)//f(x)
{
	return x+1;
}
double p(double x)//p(x)
{  
	return 3;
}
double q(double x)//q(x)
{ 
	return -(1 / x);
}

int main()
{
	double	x0 = 1.2, xn = 1.5;//Наш отрезок
	double a0 = 1, a1 = 0;//Коэффициенты первого условия
	double b0 = 2, b1 = 1;//Коэффициенты второго условия
	double A = 1, B = 0.5;//Начальные условия
	int n;
	cout << "Amount of points: ";
	cin >> n;
	double *x = new double[n + 1];//Точки
	double *y = new double[n + 1];
	
	double h = (xn - x0) / n; 
	for (int i = 0; i <= n; i++) 
		x[i] = x0 + h * i; 

	double** sistema = new double*[n + 1];//Матрица системы уравнений 
	for (int i = 0; i < n + 1; i++) 
		sistema[i] = new double[n + 2];

	for (int i = 0; i < n + 1; i++) 
		for (int j = 0; j < n + 1; j++) 
			sistema[i][j] = 0;

	//Метод сеток
	for (int i = 1; i < n; i++)//Формирование трехдиагональной матрицы
	{    
		for (int j = 0; j < n + 1; j++)
		{
			if (j == i - 1)
			{
				sistema[i][j] = 1;
			}
			else if (i == j)
			{
				sistema[i][j] = h * h * q(x[i]) - h * p(x[i]) - 2;
			}
			else if (j == i + 1)
			{
				sistema[i][j] = 1 + h * p(x[i]);
			}
		}
		sistema[i][n + 1] = h * h * f(x[i]);
	}
	sistema[0][0] = h * a0 - a1;
	sistema[0][1] = a1;
	sistema[0][n + 1] = A * h;
	sistema[n][n - 1] = -b1;
	sistema[n][n] = h * b0 + b1;
	sistema[n][n + 1] = B * h;

	cout << "\nMatrix of the system of equations:\n"; 
	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < n + 2; j++)
		{
			cout << sistema[i][j] << (j == n ? "\t= " : " ");		
		}
		cout << endl;
	}
	cout << "[Continue]";
	getch();
	cout << endl << endl;
	
	//Метод прогонки
	double	*X = new double[n], *V = new double[n];//Прогоночные коэффициенты 
	X[0] = -sistema[0][1] / sistema[0][0];	
	V[0] = sistema[0][n + 1] / sistema[0][0];	

	for (int i = 1; i < n; i++)
	{
		double temp = sistema[i][i - 1] * X[i - 1] + sistema[i][i];
		X[i] = -sistema[i][i + 1] / temp;
		V[i] = (sistema[i][n + 1] - sistema[i][i - 1] * V[i - 1]) / temp;
	}

	cout << "\nSweep coefficients: " << endl;
	cout << "X:  ";
	for (int i = 0; i < n; i++) 
		cout << X[i] << ";  ";

	cout << "\nV:  ";
	for (int i = 0; i < n; i++) 
		cout << V[i] << ";  ";
	cout << endl << "[Continue]" << endl;
	getch();
	
	//Обратный ход метода прогонки
	y[n] = (sistema[n][n + 1] - sistema[n][n - 1] * V[n - 1]) / (sistema[n][n - 1] * X[n - 1] + sistema[n][n]);
	for (int i = n - 1; i >= 0; i--)   
		y[i] = X[i] * y[i + 1] + V[i];  

	cout << "\n\nSolutions of the boundary value problem: " << endl;
	for (int i = 0; i < n + 1; i++)
	{
		cout << "y(" << x[i] << ") = " << y[i] << endl;
	}
	cout << "[End]";
	getch();
	system("pause");
}
