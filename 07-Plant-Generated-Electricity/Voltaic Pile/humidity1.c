void humidity1()
{
  TCanvas *c = new TCanvas();
  TLegend *legend = new TLegend(0.1, 0.1, 0.25, 0.35);
  //TGraphErrors *dead10 = new TGraphErrors();
  TGraph *humidity1 = new TGraph();

  fstream file;
  file.open("humidity1.csv", ios::in);


  while(1)
    {
      int n = humidity1-> GetN();
      double t, V;
      file >> t >> V;

      humidity1 -> SetPoint(n, t, V);
      if (file.eof()) break ;
    }

   file.close();


   humidity1 -> SetTitle("Humidity on 'live' earth");
   humidity1 -> GetXaxis() -> SetTitle("t [min]");
   humidity1 -> GetYaxis() -> SetTitle("Value");
   humidity1 -> GetYaxis() -> SetRangeUser(0,1000);

   humidity1 -> SetMarkerStyle(21);
   humidity1 -> SetMarkerColor(01);
   humidity1 -> Draw("AP");


  legend -> AddEntry(humidity1, "0.7cm", "p");

  //c -> Print("depth_dependence.pdf");


}
