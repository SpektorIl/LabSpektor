#include <iostream>
#include "PCA.cpp"

int main()
{
	matrix a;
	a = fromfiletxt("data.txt");
	PCA::NIPALS(a);
	return 0;
}
