#include <TChain.h>
#include <TTree.h>

#include <string>
#include <iostream>
#include <fstream>

void chain(string filelistName)
{
    TChain* chain = new TChain("EventNtuple/ntuple");
    string filename;
    while(getline(filelistName,filename))
    {
      cout << "Adding file: " << filename << ". " << endl;
      chain->Add(filename);
    }
    cout << "File Chain Size: " << chain->size() << "files." << endl;

}

//function 2

void TChainPractice(string filelistName)
{
  chain(filelistName);
  //cout << "File Chain Size: " << chain.size() << "files." << endl;
  //look to pass variables between functions (change in scope)
  //function 2 (filelistName);
}

