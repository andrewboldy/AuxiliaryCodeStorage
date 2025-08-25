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
#include "TH2F.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TGraph2D.h"

//Mu2e Inclusions

//Personal Inclusions

void sphereSampler()
{
  //define global variable limits and a number of points to be included in the sample.
  float phiMin = 0;
  float phiMax = 2*M_PI;
  float thetaMin = 0;
  float thetaMax = M_PI;
  float numPoints = 1e6;
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
TH1F* phiHist = new TH1F("phiHist", "Phi Values", 100, 0, phiMax);
TH1F* thetaHist = new TH1F("thetaHist", "Theta Values", 100, 0, thetaMax);
TH2F* bothAngleHist = new TH2F("bothAngleHist", "Theta vs. Phi", 360, 0, phiMax,180,0,thetaMax);
bothAngleHist->GetXaxis()->SetTitle("Phi (azimuth)");
bothAngleHist->GetYaxis()->SetTitle("Theta (polar)");
bothAngleHist->SetOption("COLZ"); // color-coded
TGraph2D* scatter3D = new TGraph2D(numPoints);

//Create the Canvases
TCanvas* c1 = new TCanvas("c1","c1");
c1->Divide(2,2);
  //Create a random number for each variable
  for (int i = 0; i < numPoints; i++)
  {
    //float phi = disPhi(gen);
    float u1 = dis(gen);
    float u2 = dis(gen);
    //float phi = disPhi(gen);
    //float theta = disTheta(gen);
    float theta = acos(1-2*u2);
    float phi = 2*M_PI*u1;
    phiHist->Fill(phi);
    thetaHist->Fill(theta);
    bothAngleHist->Fill(phi,theta);
    float x = r*cos(phi)*sin(theta);
    float y = r*sin(phi)*sin(theta);
    float z = r*cos(theta);
    float magnitude = sqrt(x*x+y*y+z*z);
    scatter3D->SetPoint(i, x, y, z);
    if (i<10)
    {
      cout << "Phi Value Number " << i+1 << ": " << phi << endl;
      cout << "Theta Value Number " << i+1 << ": " << theta << endl;
      cout << "Radial Distance " << i+1 << ": " << magnitude << endl;
    }
  }

  c1->cd(1);
  phiHist->Draw();
  c1->cd(2);
  thetaHist->Draw();
  c1->cd(3);
  bothAngleHist->Draw();
  c1->SaveAs("sphericalSampleHists.pdf");

  TCanvas* c3D = new TCanvas("c3D", "3D Scatter", 800, 600);
  scatter3D->SetMarkerStyle(20);   // small filled circles
  scatter3D->SetMarkerSize(0.8);
  scatter3D->SetTitle("3D Scatter of Points on Sphere;X;Y;Z");
  scatter3D->Draw("P");

  // Save the 3D scatter as a PDF
  c3D->SaveAs("sphere3Dscatter.pdf");
}

