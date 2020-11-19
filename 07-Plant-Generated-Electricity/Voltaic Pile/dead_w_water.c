void dead_earth()
{
  TCanvas *c = new TCanvas();
  TLegend *legend = new TLegend(0.1, 0.1, 0.25, 0.35);
  TGraphErrors *dead10 = new TGraphErrors();
  TGraph *dead20 = new TGraph();
  TGraph *dead30 = new TGraph();
  TGraph *dead40 = new TGraph();
  TGraph *dead50 = new TGraph();

  fstream file10, file20, file30, file40, file50;
  file10.open("DeadE_10ml.csv", ios::in);
  file20.open("DeadE_20ml.csv", ios::in);
  file30.open("DeadE_30ml.csv", ios::in);
  file40.open("DeadE_40ml.csv", ios::in);
  file50.open("DeadE_50ml.csv", ios::in);

  while(1)
    {
      int n = dead10-> GetN();
      double t, V;
      file10 >> t >> V;
      dead10 -> SetPoint(n, t, V);
      dead10 -> SetPointError(n,0.5,1);
      if (file10.eof()) break ;
    }
   while(1)
    {
      double t, V;
      file20 >> t >> V;
      dead20 -> SetPoint(dead20 -> GetN(), t, V);
      if (file20.eof()) break ;
    }
  while(1)
    {
      double t, V;
      file30 >> t >> V;
      dead30 -> SetPoint(dead30 -> GetN(), t, V);
      if (file30.eof()) break ;
    }
  while(1)
    {
      double t, V;
      file40 >> t >> V;
      dead40 -> SetPoint(dead40 -> GetN(), t, V);
      if (file40.eof()) break ;
    }
  while(1)
    {
      double t, V;
      file50 >> t >> V;
      dead50 -> SetPoint(dead50 -> GetN(), t, V);
      if (file50.eof()) break ;
    }

   file10.close();
   file20.close();
   file30.close();
   file40.close();
   file50.close();


   dead10 -> SetTitle("'Dead' Earth Measurements");
   dead10 -> GetXaxis() -> SetTitle("t [min]");
   dead10 -> GetYaxis() -> SetTitle("V [mV]");

   dead10 -> SetMarkerStyle(22);
   dead10 -> SetMarkerColor(01);
   dead20 -> SetMarkerStyle(22);
   dead20 -> SetMarkerColor(02);
   dead30 -> SetMarkerStyle(22);
   dead30 -> SetMarkerColor(03);
   dead40 -> SetMarkerStyle(22);
   dead40 -> SetMarkerColor(04);
   dead50 -> SetMarkerStyle(22);
   dead50 -> SetMarkerColor(06);

  dead10 -> Draw("AP");
  dead20 -> Draw("P");
  dead30 -> Draw("P");
  dead40 -> Draw("P");
  dead50 -> Draw("P");

  legend -> AddEntry(dead10, "+10ml", "p");
  legend -> AddEntry(dead20, "+20ml", "p");
  legend -> AddEntry(dead30, "+30ml", "p");
  legend -> AddEntry(dead40, "+40ml", "p");
  legend -> AddEntry(dead50, "+50ml", "p");
  legend -> Draw();

  c -> Print("dead_earth.pdf");




}
