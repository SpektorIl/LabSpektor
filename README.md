# LabSpektor
 this is a test release of the lab
 Lab consists of two parts
 
 1.Matrix Library

Functioning classes:
1. class matrix(can be used to create matrices and vectors)
2. unitmtx(unit matrix)
3. diagmtx(diagonal matrix)
4. utrimtx and dtrimtx(upper and down triangle matrices)
5. simmtx(simmetrical matrix)

Operators made for all of them:
1.matrix& operator =(matrix b);
2.	matrix operator +(matrix b);
	3.matrix operator -(matrix b);
	4.matrix operator* (matrix b);(matrix multiplication)
	5.matrix operator *(double c);(scalar multiplication)

methods:
1.fill(vector<vector<double>> temp0); // rather useful way for inputting martices
 
functions:
 1. matrix Adamar(matrix a, matrix b);//Adamar multiplication
 2.double trace(matrix a); //finds the ttrace of the matrix
 3. double scalar(matrix a, matrix b); //scalar multiplication of vectors
4. double vnorm(matrix a);//vector norm
 5.double mnorm(matrix a);//matrix norm
 6. double radangle(matrix a, matrix b); double degangle(matrix a, matrix b);//finds the angle between two vectors, returns values in radians and degrees
 7.matrix transpose(matrix a);//matrix transposition
 8.matrix reverse(matrix a); // reverse matrix
 
 means of writing and reading to/from files:
 binary files
 void tofilebin(const char* fileName);// binary writing
	matrix& fromfilebin(const char* fileName);//binary reading
 
 any stream reading/writing are also implemented
 ostream& operator<< (ostream& out, const matrix mtx0);
	ofstream& operator<< (ofstream& out, const matrix mtx0);
	ifstream& operator>> (ifstream& in, matrix& mtx0);
 
 regular txt files reading/writing
 void tofiletxt(matrix a, const char* fileName);//writing to
 matrix fromfiletxt(const char* fileName);//reading from
 
2.PCA Functions
 Implemented a functional class for PCA methods
 methods:
 matrix centering(matrix m);//centering
matrix norm(matrix m);//updated norm function
	matrix scaling(matrix m);//all purpose scaling scaling
	matrix NIPALS(matrix X);//Nipals algorithms, main function of the class
	double leverage(matrix T);//method for finding leverages
	vector<double> deviation(matrix E);//storing vector of deviations
	vector<double> dispersion(vector<double> dev);//storing vecrtor of dispersions
