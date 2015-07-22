#include <iostream>
#include <cstdlib>
#include <fstream>
#include "evolution.h"


using namespace std;

int main()
{
  double modelTimeStep = 0.001;
  int lengthOfTimeSeries = 10000000;
  double varX, averageX;

  simulateEvolution(modelTimeStep, lengthOfTimeSeries, &varX, &averageX);

  double E, integral, x;
  double tau;
  int nbrOfBlocks; int nbrOfPointsInBlock;

  fstream tauOutputFile("tauValues.datout", ios::out);

  int l =0;
  cout << "Simulation over" << endl;
  for(int nbrOfBlocks=10;nbrOfBlocks<=lengthOfTimeSeries/10;nbrOfBlocks=nbrOfBlocks+10)
  {
    cout << "Number of blocks : " << nbrOfBlocks <<" / " << lengthOfTimeSeries/10 << "\r"; fflush(stdout);
    tau = 0.0;
    nbrOfPointsInBlock = lengthOfTimeSeries/nbrOfBlocks;
    fstream x_file("xValues.datout", ios::in | ios::binary);
    for(int blockLabel=0;blockLabel<nbrOfBlocks;blockLabel++)
      {
	integral = 0.0;
	for(int i=0;i<nbrOfPointsInBlock;i++)
	  {
	    x_file >> x; integral += x;
	  }
	integral = integral*modelTimeStep;
	E = integral - nbrOfPointsInBlock*modelTimeStep*averageX;
	E = E*E;
	tau += E;
      } /*End of loop on blocks*/
    tau /= (2*varX*nbrOfBlocks*modelTimeStep*nbrOfPointsInBlock);
    tauOutputFile << nbrOfPointsInBlock << " " << tau << endl;
     x_file.close();
  } /*End of loop on points in a block*/

  tauOutputFile.close();
}
