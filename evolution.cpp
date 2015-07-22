#include <iostream>
#include <fstream>
#include <cstdlib>
#include "randNormal.h"

using namespace std;

void simulateEvolution(double timeStep, int lengthOfTheTimeSeries, double *varX, double *averageX)
{


      /*Lorenz model parameters*/
  double sigma = 10.0;
  double rho = 28.0;
  double beta = 8./3.;
  double eps = 0.001; //Amplitude of the noise
  double x = drand48();
  double y = drand48();
  double z = drand48();
  double xbar = 0.0; double xsqbar = 0.0;
  int k=0;
  fstream xOutputFile("xValues.datout", ios::out | ios::binary);

      for(int t=0;t<lengthOfTheTimeSeries;t++)
    {
      /*Displays percentage*/
            if(t%(lengthOfTheTimeSeries/100)==0)
	{
	  k++; cout << k << "%\r"; fflush(stdout);
	  }
      /*Compute lorenz model*/
      x = x + timeStep*sigma*(y-x) + x*eps*randNormal();
      y = y + timeStep*(x*(rho-z) - y) + y*eps*randNormal();
      z = z + timeStep*(x*y - beta*z) + z*eps*randNormal();
      //xOutputFile << x;
      xbar += x;
      xsqbar += x*x;
    }
      xbar /= lengthOfTheTimeSeries;
	xsqbar /= lengthOfTheTimeSeries;
      *varX = xbar*xbar - xsqbar;
      *averageX = xbar;
      xOutputFile.close();
}
