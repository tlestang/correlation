#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
  double modelTimeStep;
  int lengthOfTimeSeries;

  simulateEvolution(); //Not written yet.

  double E, integral, x;
  double tau;
  for(int nbrOfPointsInBlock=1;nbrOfPointsInBlock<lengthOfTimeSeries/10;nbrOfPointsInBlock++);
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
	E = intergal - nbrOfPointsInBlock*averageX;
	E = E*E;
	tau += E;
      } /*End of loop on blocks*/
    tau /= (2*varX*nbrOfPointsInBlock*modelTimeStep*nbrOfPointsInBlock);
    tauOutputFile << nbrOfPointsInBlock << " " << tau << endl;
  } /*End of loop on points in a block*/