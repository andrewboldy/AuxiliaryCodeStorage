//------------------------------------------------------------------------------
//Sphere Sampler
//Written by Andrew Boldy
//------------------------------------------------------------------------------
//This program is written to randomly sample elements from a 2-sphere with radius r=1 embedded in 3-D space.
//To do this effectively, we need to randomly select two variables, one theta and one phi with theta running 0 to pi and phi running 0 to 2pi.
//The differential element of a sphere's solid angle is dOmega=sin(theta)*dtheta*dphi
//Output will include histograms over each element.
//------------------------------------------------------------------------------
//Progress Notes:
//-->Investigated the values of M_PI and 2*M_PI tp determine the level of precision using cout. Printed out the following:
//    Value of the Constant PI stored in cmath: 3.14159
//    Value of 2 times the stored pi in cmath: 6.28319
//Deeming this viable until told otherwise.
//------------------------------------------------------------------------------

//Inclusions

//C++ Inclusions
#include <random>
#include <cmath>
#include <iostream>
#include <stdlib.h>


//ROOT Inclusions
#include "TH1F.h"
#include "TCanvas.h"
#include "TPad.h"

//Mu2e Inclusions

//Personal Inclusions

void sphereSampler()
{
  //define global variable limits and a number of points to be included in the sample.
  float phiMin = 0;
  float phiMax = 2*M_PI;
  float thetaMin = 0;
  float thetaMax = M_PI;
  float numPoints = 1000;
  float r = 1;

  //Create the variable number of points (ON-PAUSE)
  //cout << "Type the number of points you would like to have in this sample." << endl;
  //cin >> numPoints >> endl;

//Create the setup for the random number generator
std::random_device rd; //create an instance of a random device for seeding
std::mt19937 gen(rd()); //standard mersenne_twister generator seeded by rd
//std::uniform_real_distribution<float> disPhi(phiMin,phiMax);
//std::uniform_real_distribution<float> disTheta(thetaMin,thetaMax);
std::uniform_real_distribution<float> dis(0.0,1.0);

//Create the histograms
TH1F* phiHist = new TH1F("phi", "Phi Values", 1000, -0.5, phiMax+0.5);
TH1F* thetaHist = new TH1F("theta", "Theta Values", 1000, -0.5, thetaMax+0.5);

//Create the Canvases
TCanvas* c1 = new TCanvas("c1","c1");
c1->Divide(2,1);
  //Create a random number for each variable
  for (int i = 0; i < numPoints; i++)
  {
    //float phi = disPhi(gen);
    float u1 = dis(gen);
    float u2 = dis(gen);
    //float phi = disPhi(gen);
    //float theta = disTheta(gen);
    float phi = acos(1-2*u2);
    phiHist->Fill(phi);
    float theta = 2*M_PI*u1;
    thetaHist->Fill(theta);
    cout << "Phi Value Number " << i+1 << ": " << phi << endl;
    cout << "Theta Value Number " << i+1 << ": " << theta << endl;
    float x = r*cos(theta)*sin(phi);
    float y = r*sin(theta)*sin(phi);
    float z = r*cos(phi);
    float magnitude = sqrt(x*x+y*y+z*z);
    cout << "Distance of point from origin: " << magnitude << endl;
  }
  c1->cd(1);
  phiHist->Draw();
  c1->cd(2);
  thetaHist->Draw();
  c1->SaveAs("sphericalSampleHists.pdf");
}
