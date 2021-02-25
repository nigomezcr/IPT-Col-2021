void corral()
{
  //Define de histogram
  
  //TH2F *hist = new TH2F("hist", "Distribution", 50, -.3, .3, 50, -.3, .3);
  TH1F *histx = new TH1F("histx", "Distribution x", 100, -.3, .3);
  TH1F *histy = new TH1F("histy", "Distribution y", 50, -.3, .3);
  //Create a canvas to put the histogram on
  TCanvas *c = new TCanvas();

  //Open file
  fstream file;
  file.open("data-set1.csv", ios::in);

  //Fill the histogram with the file values
  double valuex;
  double valuey;
  while(1)
    {
      file >> valuex >> valuey;
      //std::cout << valuex << std::endl;
      //hist -> Fill(valuex, valuey);
      histx -> Fill(valuex);
      histy -> Fill(valuey);
      if(file.eof()) break;
    }

  file.close();
  
   //Label de axes
  histy -> GetXaxis() -> SetTitle("y position");
  histy -> GetYaxis() -> SetTitle("P");
  histy -> SetFillColor(kGreen);
  //hist -> GetZaxis() -> SetTitle("Probability");
  //hist -> SetOption("SURF2");

  //Draw the histogram
  histy -> Draw();
}
