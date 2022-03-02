// MatrixLibrary1.cpp : Определяет экспортируемые функции для DLL.
//

#include "pch.h"
#include "framework.h"
#include "MatrixLibrary1.h"

// Конструктор для экспортированного класса.
matrix::matrix(void)
{
	row = 1;
	column = 1;

	vector <double> temp;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			temp.push_back(0);
		}
		mtx.push_back(temp);
	}
}

matrix::matrix(int r, int col)
{
	row = r;
	column = col;

	try {
		if ((column <= 0) || (row <= 0))
		{
			throw exception("Matrix parametrs must me positive integers!");
		}
	}
	catch (exception& ex)
	{
		cerr << ex.what() << endl;
		exit(0);
	}

	vector <double> temp;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			temp.push_back(0);
		}
		mtx.push_back(temp);
		temp = {};
	}
}

//-----------------------------------------------//
//экспортируемые функции ЛР 1

 //удобный ввод матрицы
int matrix::fill(vector<vector<double>> temp0)
{
	try
	{
		for (unsigned int i = 1; i < temp0.size(); i++)
		{
			if (temp0.at(i).size() != temp0.at(0).size())
			{
				throw "Wrong matrix parametrs";;
			}
		}
		if ((temp0.size() != row) || (temp0.at(0).size() != column))

		{
			throw "Wrong matrix parametrs";
		}
	}
	catch (const char* exception)
	{
		cerr << "Error: " << exception << endl;
		return -1;
	}
	vector <double> temp;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			temp.push_back(temp0[i][j]);
		}
		mtx.at(i) = temp;
		temp = {};
	}
	return 0;
}

//произведение  Адамара
matrix Adamar(matrix a, matrix b)
{
	try
	{
		if ((a.column != b.column) || (a.row != b.row))
		{
			throw exception("Matrixes do not match in Adamar multiplication");
		}
	}
	catch (exception ex)
	{
		cout << "Error:" << ex.what() << endl;
		exit(0);
	}
	matrix c(a.row, a.column);
	for (int i = 0; i < a.row; i++)
	{
		for (int j = 0;j < a.column; j++)
		{
			c.mtx[i][j] = a.mtx[i][j] * b.mtx[i][j];
		}
	}
	return c;
}
//вывод в поток
ostream& operator << (ostream& out, const matrix mtx0)
{
	for (int i = 0; i < mtx0.row; i++)
	{
		for (int j = 0; j < mtx0.column; j++)
		{

			out << setw(16) << mtx0.mtx[i][j];

		}
		if (i != mtx0.row - 1)
		{
			out << std::endl;
		}
	}
	return out;
}
//-----------------------------------------------//
//операторы
//=
matrix& matrix::operator =(matrix b)
{
	for (int i = 0; i < this->row; i++)
	{
		this->mtx[i].clear();
	}
	this->mtx.clear();
	this->row = b.row;
	this->column = b.column;
	vector <double> temp;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			temp.push_back(b.mtx[i][j]);
		}
		mtx.push_back(temp);
		temp = {};
	}
	return *this;
}

//+
matrix matrix::operator +(matrix b)
{
	try
	{
		if ((row != b.row) || (column != b.column))
		{
			throw "Matrixes do not match sizes";
		}
	}
	catch (const char* ex)
	{
		cerr << "Error: " << ex << endl;
		matrix a;
		exit(0);
	}

	matrix c(row, column);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			c.mtx[i][j] = this->mtx[i][j] + b.mtx[i][j];
		}
	}
	return c;
}

//-
matrix matrix::operator -(matrix b)
{
	try
	{
		if ((row != b.row) || (column != b.column))
		{
			throw "Matrixes do not matsh sizes";
		}
	}
	catch (const char* ex)
	{
		cerr << "Error: " << ex << endl;
		matrix a;
		exit(0);
	}

	matrix c(row, column);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			c.mtx[i][j] = this->mtx[i][j] - b.mtx[i][j];
		}
	}
	return c;
}

//умножение на матрицу
matrix matrix::operator* (matrix b)
{
	try
	{
		if (column != b.row)
		{
			throw  "Wrong sizes of the matrixes";
		}
	}
	catch (const char* ex)
	{
		cerr << "Error: " << ex << endl;
		exit(0);
	}
	matrix c(row, b.column);
	double elem = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < b.column; j++)
		{
			for (int k = 0; k < column; k++)
			{
				elem += this->mtx[i][k] * b.mtx[k][j];
			}
			c.mtx[i][j] = elem;
			elem = 0;
		}
	}
	return c;
}

//умножение на число справа
matrix matrix::operator *(double c)
{
	matrix temp(row, column);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			temp.mtx[i][j] = this->mtx[i][j] * c;

		}
	}
	return temp;
}

//умножение на число слева
matrix operator*(double c, matrix a)
{
	matrix temp(a.row, a.column);
	for (int i = 0; i < a.row; i++)
	{
		for (int j = 0; j < a.column; j++)
		{
			temp.mtx[i][j] = a.mtx[i][j] * c;
		}
	}
	return temp;
}

//-----------------------------------------------//
//matrix types//
//-----------------------------------------------//


//-----------------------------------------------//
//unitary//
unitmtx::unitmtx()
{
	mtx[0][0] = 1;
}

unitmtx::unitmtx(int size) : matrix(size, size)
{
	for (int i = 0; i < row; i++)
	{
		mtx[i][i] = 1;
	}
}
//-----------------------------------------------//
//diagonally//
diagmtx::diagmtx()
{
	d_value = 0;
}

diagmtx::diagmtx(int size, double diagonal_value) : matrix(size, size)
{
	d_value = diagonal_value;
	for (int i = 0; i < row; i++)
	{
		mtx[i][i] = d_value;
	}
}
//-----------------------------------------------//
//upper trangle//
utrimtx::utrimtx()
{
}

utrimtx::utrimtx(int size) : matrix(size, size)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = i;j < column; j++)
		{
			mtx[i][j] = 1;
		}
	}
}

int utrimtx::fill(vector<vector<double>> temp0)
{
	try
	{
		for (unsigned int i = 1; i < temp0.size() - 1; i++)
		{
			if (temp0.at(i).size() != temp0.at(i + 1).size() + 1)
			{
				throw "Wrong matrix parametrs";;
			}
		}
		if ((temp0.size() != row) || (temp0.at(0).size() != column))

		{
			throw "Wrong matrix parametrs";
		}
	}
	catch (const char* exception)
	{
		cerr << "Error: " << exception << endl;
		return -1;
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = i; j < column; j++)
		{
			mtx[i][j] = temp0[i][j - i];
		}
	}
	return 0;
}
//-----------------------------------------------//
//down trangle//
dtrimtx::dtrimtx()
{
}

dtrimtx::dtrimtx(int size) : matrix(size, size)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0;j <= i; j++)
		{
			mtx[i][j] = 1;
		}
	}
}
int dtrimtx::fill(vector<vector<double>> temp0)
{
	try
	{
		for (int i = 0; i < row - 1; i++)
		{
			if (temp0.at(i).size() != temp0.at(i + 1).size() - 1)
			{
				throw "Wrong matrix parametrs";;
			}
		}
		if ((temp0.size() != row) || (temp0.at(row - 1).size() != column))

		{
			throw "Wrong matrix parametrs";
		}
	}
	catch (const char* exception)
	{
		cerr << "Error: " << exception << endl;
		return -1;
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			mtx[i][j] = temp0[i][j];
		}
	}
	return 0;
}
//-----------------------------------------------//
//simmetrical//
simmtx::simmtx()
{
}

simmtx::simmtx(int size) : matrix(size, size)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0;j < column; j++)
		{
			mtx[i][j] = 1;
		}
	}
}
int simmtx::fill(vector<vector<double>> temp0)
{
	try
	{
		for (unsigned int i = 1; i < temp0.size() - 1; i++)
		{
			if (temp0.at(i).size() != temp0.at(i + 1).size() + 1)
			{
				throw "Wrong matrix parametrs";;
			}
		}
		if ((temp0.size() != row) || (temp0.at(0).size() != column))

		{
			throw "Wrong matrix parametrs";
		}
	}
	catch (const char* exception)
	{
		cerr << "Error: " << exception << endl;
		return -1;
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = i; j < column; j++)
		{
			mtx[i][j] = temp0[i][j - i];
			mtx[j][i] = temp0[i][j - i];
		}
	}
	return 0;
}
//-----------------------------------------------//


//-----------------------------------------------//
//Функции Для лабораторной работы 2//
//-----------------------------------------------//
//след матрицы
double trace(matrix a)
{
	double trc = 1;
	for (int i = 0; i < a.row; i++)
	{
		trc *= a.mtx[i][i];
	}
	return trc;
}


//определитель матрицы
double detGauss(matrix a)
{
	try
	{
		if (a.column != a.row)
		{
			throw exception("Matrix should be squared to find its determinant!");
		}
	}
	catch (exception& ex)
	{
		cerr << ex.what() << endl;
		exit(0);
	}
	double det = 1;
	vector<double> temp;
	for (int i = 0; i < a.row; i++)
	{
		int k = i;
		while (a.mtx[k][i] == 0 && k != a.row - 1)
		{
			k++;
		}

		if (a.mtx[k][i] == 0)
		{
			return 0;
		}
		else
		{
			if (i != k)
			{
				temp = a.mtx[i];
				a.mtx[i] = a.mtx[k];
				a.mtx[k] = temp;
			}
		}
		for (int l = i + 1; l < a.row; l++)
		{
			double coef = a.mtx[l][i] / a.mtx[i][i];
			for (int m = i; m < a.column; m++)
			{
				a.mtx[l][m] = a.mtx[l][m] - a.mtx[i][m] * coef;
			}
		}
	}

	for (int i = 0; i < a.row;i++)
	{
		det *= a.mtx[i][i];
	}
	return det;
}

//скалярное произведение векторов
double scalar(matrix a, matrix b)
{
	try
	{
		if ((a.column != 1) && (a.row != 1) || (b.column != 1) && (b.row != 1) || ((a.column * (a.column > a.row) + a.row * (a.row > a.column)) != (b.column * (b.column > b.row) + b.row * (b.row > b.column))))
		{
			throw exception("One of the inputted matrixes is not a vector or they don't have the same parameters!");
		}
	}
	catch (exception& ex)
	{
		cerr << "Error! :" << ex.what() << endl;
		exit(0);
	}
	double scl = 0;
	if (a.row > a.column)
	{
		if (b.row > b.column)
		{
			for (int i = 0; i < a.row; i++)
			{
				scl += a.mtx[i][0] * b.mtx[i][0];
			}
			return scl;
		}
		else
		{
			for (int i = 0; i < a.row; i++)
			{
				scl += a.mtx[i][0] * b.mtx[0][i];
			}
			return scl;
		}
	}
	else
	{
		if (b.row > b.column)
		{
			for (int i = 0; i < a.column; i++)
			{
				scl += a.mtx[0][i] * b.mtx[i][0];
			}
			return scl;
		}
		else
		{
			for (int i = 0; i < a.column; i++)
			{
				scl += a.mtx[0][i] * b.mtx[0][i];
			}
			return scl;
		}
	}
}

//норма вектора
double vnorm(matrix a)
{
	try
	{
		if ((a.column != 1) && (a.row != 1))
		{
			throw exception("inputted matrix is not a vector!");
		}
	}
	catch (exception& ex)
	{
		cerr << "Error! :" << ex.what() << endl;
		exit(0);
	}

	return sqrt(scalar(a, a));
}

//норма матрицы
double mnorm(matrix a)
{
	double mnrm = 0;
	for (int i = 0; i < a.row; i++)
	{
		for (int j = 0;j < a.column; j++)
		{
			mnrm += a.mtx[i][j] * a.mtx[i][j];
		}
	}

	return sqrt(mnrm);
}

//-----------------------------------------------//
//Функции Для лабораторной работы 3//
//-----------------------------------------------//
#define Pi 3.14159265

//угол в радианах
double radangle(matrix a, matrix b)
{
	return acos((scalar(a, b) / (vnorm(b) * vnorm(a))));
}

//угол в градусах
double degangle(matrix a, matrix b)
{
	return 180 * acos((scalar(a, b) / (vnorm(b) * vnorm(a)))) / Pi;
}

//ранг матрицы
int mrank(matrix a)
{
	vector<double> temp;
	int rank = 0;
	int i = 0;
	int j = 0;
	while ((i < a.row) && (j < a.column))
	{
		int k = i;
		while (a.mtx[k][j] == 0 && k != a.row - 1)
		{
			k++;
		}

		if (a.mtx[k][j] == 0)
		{
			j++;
		}
		else
		{
			if (i != k)
			{
				temp = a.mtx[i];
				a.mtx[i] = a.mtx[k];
				a.mtx[k] = temp;
			}
			for (int l = i + 1; l < a.row; l++)
			{
				double coef = a.mtx[l][i] / a.mtx[i][i];
				for (int m = i; m < a.column; m++)
				{
					a.mtx[l][m] = a.mtx[l][m] - a.mtx[i][m] * coef;
				}
			}
			rank++;
			i++;
			j++;
		}

	}
	return rank;
}

//транспозиция матрицы
matrix transpose(matrix a)
{
	try
	{
		if (a.column != a.row)
		{
			throw exception("Matrix is not square!");
		}
	}
	catch (exception& ex)
	{
		cerr << "Error!: " << ex.what() << endl;
		exit(0);
	}

	double temp = 0;

	for (int i = 0; i < a.row; i++)
	{
		for (int j = i + 1; j < a.column; j++)
		{
			temp = a.mtx[i][j];
			a.mtx[i][j] = a.mtx[j][i];
			a.mtx[j][i] = temp;
		}
	}
	return a;
}


//обратная матрица
matrix reverse(matrix a)
{
	double det = detGauss(a);
	try
	{
		if (det == 0)
		{
			throw exception("Matrix is not reversable!");
		}
	}
	catch (exception& ex)
	{
		cerr << "Error!: " << ex.what() << endl;
		exit(0);
	}
	if (a.row == 1)
	{
		a.mtx[0][0] = 1 / a.mtx[0][0];
		return a;
	}
	else
	{
		matrix c(a.row, a.column);
		for (int i = 0; i < a.row; i++)
		{
			for (int j = 0; j < a.column; j++)
			{
				matrix help(a.row - 1, a.column - 1);
				for (int k = 0; k < a.row - 1; k++)
				{
					for (int n = 0; n < a.column - 1; n++)
					{
						if ((k < i) && (n < j))
						{
							help.mtx[k][n] = a.mtx[k][n];
						}
						else if ((k < i) && (n >= j))
						{
							help.mtx[k][n] = a.mtx[k][n+1];
						}
						else if ((k >= i) && (n < j))
						{
							help.mtx[k][n] = a.mtx[k+1][n];
						}
						else
						{
							help.mtx[k][n] = a.mtx[k+1][n+1];
						}
					}
				}
				if (((j + i) % 2 == 1))
				{
					c.mtx[i][j] = (-1) * detGauss(help);
				}
				else
				{
					c.mtx[i][j] = detGauss(help);
				}
				
			}
		}
		return ((1 / det) * transpose(c));
	}
}
//-------------------------------------------//

//------------------------------------------//
//Для Лабораторной Работы 4//
//------------------------------------------//

//Ввод в текстовый файл
ifstream& operator>> (ifstream& in, matrix& mtx0)
{
	double an = 0;
	char c;
	vector<vector<double>> temp;
	vector<double> temp0;
	int rowCounter = 0, i = 0;
	while (!in.eof())
	{
		in.imbue(locale("Russian"));
		in >> an;
		temp0.push_back(an);
		if (!in.eof())
		{
			in.get(c);
			if (c == '\n')
			{
				temp.push_back(temp0);
				i++;
				temp0 = {};
			}
		}
	}
	temp.push_back(temp0);
	try
	{
		for (unsigned int i = 1; i < temp.size(); i++)
		{
			if (temp.at(i).size() != temp.at(0).size())
			{
				throw exception("Wrong matrix parameters in file");
			}
		}
	}
	catch (exception& exception)
	{
		cerr << "Error: " << exception.what() << endl;
		exit(0);
	}
	matrix a(temp.size(), temp.at(0).size());
	mtx0 = a;
	for (int i = 0;i < a.row; i++)
	{
		for (int j = 0; j < a.column; j++)
		{
			mtx0.mtx[i][j] = temp[i][j];
		}
	}
	return in;
}

//вывод в текстовый файл
ofstream& operator << (ofstream& out, const matrix mtx0)
{
	for (int i = 0; i < mtx0.row; i++)
	{
		for (int j = 0; j < mtx0.column; j++)
		{

			out << setw(16) << mtx0.mtx[i][j];

		}
		if (i != mtx0.row - 1)
		{
			out << std::endl;
		}
	}
	return out;
}

//функции для красивого ввода и вывода в/из текстовый(ого) файл(а) лишь по имени файла
void tofiletxt(matrix a, const char* fileName)
{
	ofstream File;
	File.open(fileName);
	File.imbue(locale("Russian"));
	File << a;
	File.close();
}

matrix fromfiletxt(const char* fileName)
{
	ifstream File;
	File.exceptions(ifstream::badbit | ifstream::failbit);
	try
	{
		File.open(fileName, ifstream::in);
	}
	catch (const exception& ex)
	{
		cerr << ex.what() << " File could not be opened!" << endl;
		exit(0);
	}
	matrix a;
	File >> a;
	File.close();
	return a;
}

//методы для бинарного ввода и вывода
void matrix::tofilebin(const char* fileName)
{
	ofstream File;
	File.open(fileName, ios_base::out | ios_base::binary);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			File.write((char*)&mtx[i][j], sizeof(double));

			if (j != column - 1)
			{
				File.write(" ", sizeof(char));
			}
		}
		if (i != row - 1)
		{
			File.write("\n", sizeof(char));
		}
	}
	File.close();
}

matrix& matrix::fromfilebin(const char* fileName)
{
	ifstream File;
	File.open(fileName, ios_base::in | ios_base::binary | ios_base::ate);
	File.exceptions(ifstream::badbit | ifstream::failbit);
	try
	{
		if (!File.is_open())
		{
			throw exception("file did not open!");
		}
	}
	catch (const exception& ex)
	{
		cerr << ex.what() << " File could not be opened!" << endl;
		exit(0);
	}
	double num;
	vector<vector<double>> temp;
	vector<double> temp0;
	char c;
	int size = File.tellg(), bytes = 0;
	File.seekg(0, ios_base::beg);
	int rowCounter = 0;
	while (bytes != size)
	{
		File.read((char*)&num, sizeof(double));
		bytes += sizeof(double);
		temp0.push_back(num);
		if (bytes != size)
		{
			File.read((char*)&c, sizeof(char));
			bytes++;
			if (c == '\n')
			{
				rowCounter++;
				temp.push_back(temp0);
				temp0 = {};
			}
		}
	}
	temp.push_back(temp0);
	try
	{
		for (unsigned int i = 1; i < temp.size(); i++)
		{
			if (temp.at(i).size() != temp.at(0).size())
			{
				throw exception("Wrong matrix parameters in file");
			}
		}
	}
	catch (exception& exception)
	{
		cerr << "Error: " << exception.what() << endl;
		exit(0);
	}
	rowCounter++;
	matrix a(rowCounter, temp.at(0).size());
	*this = a;
	for (int i = 0;i < a.row; i++)
	{
		for (int j = 0; j < a.column; j++)
		{
			this->mtx[i][j] = temp[i][j];
		}
	}
	File.close();
	return *this;
}
//-------------------------------------------//