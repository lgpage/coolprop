
#include "Spline.h"
#include "MatrixMath.h"
#include "CPExceptions.h"
#include "CoolPropTools.h"

SplineClass::SplineClass()
{
	Nconstraints = 0;
	A.resize(4, std::vector<double>(4, 0));
	B.resize(4,0);
}
bool SplineClass::build()
{
	if (Nconstraints == 4)
	{
		std::vector<double> abcd = linsolve_Gauss_Jordan(A,B);
		a = abcd[0];
		b = abcd[1];
		c = abcd[2];
		d = abcd[3];
        return true;
	}
	else
	{
		throw ValueError(format("Number of constraints[%d] is not equal to 4",Nconstraints));
	}
}
bool SplineClass::add_value_constraint(double x, double y)
{
	int i = Nconstraints;
	if (i == 4)
		return false;
	A[i][0] = x*x*x;
	A[i][1] = x*x;
	A[i][2] = x;
	A[i][3] = 1;
	B[i] = y;
	Nconstraints++;
	return true;
}
bool SplineClass::add_derivative_constraint(double x, double dydx)
{
	int i = Nconstraints;
	if (i == 4)
		return false;
	A[i][0] = 3*x*x;
	A[i][1] = 2*x;
	A[i][2] = 1;
	A[i][3] = 0;
	B[i] = dydx;
	Nconstraints++;
	return true;
}
double SplineClass::evaluate(double x)
{
	return a*x*x*x+b*x*x+c*x+d;
}