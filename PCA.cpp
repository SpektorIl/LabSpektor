#include "PCA.h"
#include <cmath>
#include <vector>
#include<cassert>


matrix PCA::centering(matrix m) 
{
	vector<double> sum(m.column);
	for (int i = 0; i < m.column; i++)
	{
		sum[i] = 0;
		for (int j = 0; j < m.row; j++)
		{
			sum[i] += m.mtx[j][i];
		}
	}
	
	for (int i = 0; i < m.column; i++)
	{
		for (int j = 0; j < m.row; j++)
		{
			m.mtx[j][i] -= sum[i]/m.row;
		}
	}

	return m;
};

matrix PCA::norm(matrix m)
{
	double sum = 0;
	matrix s(1, m.column);
	matrix temp = centering(m);
	for (int i = 0; i < temp.column; i++)
	{
		for (int j = 0; j < temp.row; j++)
		{
			sum += temp.mtx[j][i] * temp.mtx[j][i];
		}
		s.mtx[0][i] = sqrt(sum / temp.row);
		sum = 0;
	}
	return s;
};

matrix PCA::scaling(matrix m) 
{
	matrix a(m.row, m.column);
	matrix temp = centering(m);
	matrix s = norm(temp);
	for (int i = 0; i < temp.column; i++)
	{
		for (int j = 0; j < temp.row; j++)
		{
			a.mtx[j][i] = temp.mtx[j][i] / s.mtx[0][i];
		}
	}
	return a;
};

matrix PCA::NIPALS(matrix X)
{ 
	double eps = 0.00000001;
	matrix D;
	D = X;
	D = scaling(D);


	matrix E;
	E = D;
	matrix P(1, E.column);
	matrix T(1, E.row);

	for (int h = 1; h <= min(E.row, E.column); h++)
	{
		matrix t(1, E.row);
		matrix d;
		matrix p;
		t.fill({ transpose(E).mtx[h - 1] });
		do
		{

			p = t * E * (1 / (t * transpose(t)).mtx[0][0]);
			p = p * (1 / vnorm(p));
			matrix t_old = t;
			t = transpose((E * transpose(p)) * (1 / ((p * transpose(p)).mtx[0][0])));
			d = t_old - t;

		} 
		while(vnorm(d) > eps);

		E = E - transpose(t) * p;

		if (h == 1)
		{
			P = p;
			T = t;
		}
		else 
		{
			P.mtx.push_back(p.mtx[0]);
			P.row++;
			T.mtx.push_back(t.mtx[0]);
			T.row++;
		}
	}

	dispersion(deviation(E));
	leverage(T);
	std::cout <<"matrix of loadings" << endl;
	std::cout << transpose(P) << endl;
	std::cout << "matrix of scores" << endl;
	std::cout << transpose(T) << endl;
	std::cout << "residue matrix" << endl;
	std::cout << E << endl;
	std::cout << "As you can see the matrix is calculated correctly:" << endl;
	std::cout << D -(transpose(T) * P + E) << std::endl;
	std::cout << endl;
	return D;
};

double PCA::leverage(matrix T) 
{
	matrix help =  transpose(T) * T;
	long double h = 0;
	long double sum = 0;
	std::cout << "Leverages:" << endl;
	for (int i = 0; i < T.row; i++)
	{
		h = 0;
		matrix t(1, T.column);
		t.fill({ T.mtx[i] });
		for (int j = 0; j < help.row; j++)
		{
			h += t.mtx[0][j] * t.mtx[0][j] / help.mtx[j][j];
		}
		sum += h;
		std::cout << "h["<<i+1<<"] = "<< h << endl;
	}
	cout << "h0 = " << sum / T.column << endl;
	return 0;
};

vector<double> PCA::deviation(matrix E) 
{
	vector<double> dev(E.column);
	double dev_sum = 0;
	std::cout << "Deviations:" << endl;
	for (int i = 0; i < E.column; i++)
	{
		double sum = 0;
		for (int j = 0; j < E.column; j++)
		{
			sum += E.mtx[i][j] * E.mtx[i][j];
		}
		dev[i] = sum;
		dev_sum += sum;
		cout << "v[" << i + 1 << "] = " << sum << endl;
	}
	cout << "v[0] = " << dev_sum / E.column << endl;
	return dev;
};

vector<double> PCA::dispersion(vector<double> dev)
{
	vector<double> disp(dev.size());
	double dis_sum = 0;
	std::cout << "Dispersions:" << endl;
	for (int i = 0; i < dev.size(); i++)
	{
		dis_sum += dev.at(i);
		cout << "d[" << i + 1 << "] = " << dev.at(i) << endl;
	}
	cout << "d[0] = " << dis_sum / dev.size() << endl;
	return disp;
};