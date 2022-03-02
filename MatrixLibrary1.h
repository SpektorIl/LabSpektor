#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <math.h>
#ifdef MATRIXLIBRARY1_EXPORTS
#define MATRIXLIBRARY1_API __declspec(dllexport)
#else
#define MATRIXLIBRARY1_API __declspec(dllimport)
#endif

using namespace std;


//Для ЛР1
class MATRIXLIBRARY1_API matrix
{
public:
	int row;
	int column;
	vector<vector<double>> mtx;
	matrix(void);
	matrix(int r, int col);
	int fill(vector<vector<double>> temp0);
	friend ostream& operator<< (ostream& out, const matrix mtx0);
	friend ofstream& operator<< (ofstream& out, const matrix mtx0);
	friend ifstream& operator>> (ifstream& in, matrix& mtx0);
	void tofilebin(const char* fileName);
	matrix& fromfilebin(const char* fileName);
	matrix& operator =(matrix b);
	matrix operator +(matrix b);
	matrix operator -(matrix b);
	matrix operator* (matrix b);
	matrix operator *(double c);
	friend matrix Adamar(matrix a, matrix b);
};

extern "C" MATRIXLIBRARY1_API matrix operator*(double c, matrix a);


class MATRIXLIBRARY1_API unitmtx :public matrix
{
public:
	unitmtx();
	unitmtx(int size);
};

class MATRIXLIBRARY1_API diagmtx :public matrix
{
	double d_value;
	diagmtx();
	diagmtx(int size, double diagonal_value);
};

class MATRIXLIBRARY1_API utrimtx :public matrix
{
	utrimtx();
	utrimtx(int size);
	int fill(vector<vector<double>> temp0);
};

class MATRIXLIBRARY1_API dtrimtx :public matrix
{
	dtrimtx();
	dtrimtx(int size);
	int  fill(vector<vector<double>> temp0);
};

class MATRIXLIBRARY1_API simmtx :public matrix
{
	simmtx();
	simmtx(int size);
	int fill(vector<vector<double>> temp0);
};

//для ЛР2
extern "C" MATRIXLIBRARY1_API double trace(matrix a);

extern "C" MATRIXLIBRARY1_API double detGauss(matrix a);

extern "C" MATRIXLIBRARY1_API double scalar(matrix a, matrix b);

extern "C" MATRIXLIBRARY1_API double vnorm(matrix a);

extern "C" MATRIXLIBRARY1_API double vnorm(matrix a);

extern "C" MATRIXLIBRARY1_API double mnorm(matrix a);

//для ЛР3

extern "C" MATRIXLIBRARY1_API double radangle(matrix a, matrix b);

extern "C" MATRIXLIBRARY1_API double degangle(matrix a, matrix b);

extern "C" MATRIXLIBRARY1_API int mrank(matrix a);

extern "C" MATRIXLIBRARY1_API matrix transpose(matrix a);

extern "C" MATRIXLIBRARY1_API matrix reverse(matrix a);


//для ЛР4
extern "C" MATRIXLIBRARY1_API void tofiletxt(matrix a, const char* fileName);

extern "C" MATRIXLIBRARY1_API matrix fromfiletxt(const char* fileName);