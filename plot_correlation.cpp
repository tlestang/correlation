#include <iostream>
#include <cstdlib>
#include <fstream>
#include "evolution.h"


using namespace std;

int main()
{
  double modelTimeStep = 0.001;
  int lengthOfTimeSeries = 10000;
  double *varX, *averageX;

  simulateEvolution(modelTimeStep, lengthOfTimeSeries, varX, averageX);

  double E, integral, x;
  double tau;
  int nbrOfBlocks;
  fstream x_file("xValues.datout", ios::in | ios::binary);
  fstream tauOutputFile("tauValues.datout", ios::out);
  
  for(int nbrOfPointsInBlock=1;nbrOfPointsInBlock<lengthOfTimeSeries/10;nbrOfPointsInBlock++)
  {
    tau = 0.0;
    nbrOfBlocks = lengthOfTimeSeries/nbrOfPointsInBlock;
    for(int blockLabel=0;blockLabel<nbrOfBlocks;blockLabel++)
      {
	integral = 0.0;
	for(int i=0;i<nbrOfPointsInBlock;i++)
	  {
	    x_file >> x; integral += x;
	  }
	integral = integral*modelTimeStep;
	E = integral - nbrOfPointsInBlock**averageX;
	E = E*E;
	tau += E;
      } /*End of loop on blocks*/
    tau /= (2**varX*nbrOfPointsInBlock*modelTimeStep*nbrOfPointsInBlock);
    tauOutputFile << nbrOfPointsInBlock << " " << tau << endl;
  } /*End of loop on points in a block*/

  tauOutputFile.close(); x_file.close();
}
