#pragma once
#include "MatrixLibrary.cpp"

class PCA
{
public:
	static matrix centering(matrix m);
	static matrix norm(matrix m);
	static matrix scaling(matrix m);
	static matrix NIPALS(matrix X);
	static double leverage(matrix T);
	static vector<double> deviation(matrix E);
	static vector<double> dispersion(vector<double> dev);
};
