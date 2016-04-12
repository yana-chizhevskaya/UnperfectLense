#include "../Maths/Quadratic.h"
#include <iostream>
using namespace std;
double* Quadratic(double a, double b, double c) {
	double * root = new double[2];
	double D = (b*b) - 4 * (a*c);
	//cout << "a b c  " << c << endl;
	//cout << "D  " << D << endl;
	if (D<0)
	{
		return NULL;
	}
	else if (D == 0)
	{
		double x0 = -b / (2 * a);

	}
	else
	{
		double d = sqrt(D);
		root[0] = (-b + d) / (2 * a);
		root[1] = (-b - d) / (2 * a);

	}
	return root;
}