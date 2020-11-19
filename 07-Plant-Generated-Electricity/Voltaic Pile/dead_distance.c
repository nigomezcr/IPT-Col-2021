void distance()
{
  TCanvas *c = new TCanvas();
  TLegend *legend = new TLegend(0.1, 0.1, 0.25, 0.35);
  //TGraphErrors *dead10 = new TGraphErrors();
  TGraph *distance = new TGraph();

  fstream file;
  file.open("distance.csv", ios::in);


  while(1)
    {
      int n = distance-> GetN();
      double t, V1, V2;
      file >> t >> V1 >> V2;

      distance -> SetPoint(n, t, V1);
      if (file.eof()) break ;
    }

   file.close();


   distance -> SetTitle("Distance dependence on 'live' earth");
   distance -> GetXaxis() -> SetTitle("t [min]");
   distance -> GetYaxis() -> SetTitle("Value");

   //humidity1 -> GetYaxis() -> SetRangeUser(0,1000);

   distance -> SetMarkerStyle(21);
   distance -> SetMarkerColor(02);
   distance -> Draw("AP");


  legend -> AddEntry(distance, "0.7cm", "p");

  //c -> Print("depth_dependence.pdf");


}
