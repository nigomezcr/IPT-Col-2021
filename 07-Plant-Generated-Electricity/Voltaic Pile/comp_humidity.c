void humidity2()
{
  TCanvas *c = new TCanvas();
  TLegend *legend = new TLegend(0.1, 0.1, 0.25, 0.35);
  //TGraphErrors *dead10 = new TGraphErrors();
  TGraph *humidity = new TGraph();
  TGraph *voltage = new TGraph();
  TH1F *hist_hum = new TH1F("Hum", "Humidity on compost; % humidity; Entries", 100, 40 , 80);
  TH1F *hist_volt = new TH1F("Volt", "Voltage on compost; V [mV]; Entries", 100, 1300, 2300);

  fstream file;
  file.open("humidity2-2.csv", ios::in);


  //TF1 *fit_h= new TF1("fit humidity", "gaus", 950, 1025);
  //TF1 *fit_V= new TF1("fit voltage", "gaus", 950, 1025);

  while(1)
    {
      int n = humidity-> GetN();
      double t, H, V;
      file >> t >> H >>V;

      humidity-> SetPoint(n, t, H);
      voltage-> SetPoint(n, t, V);
      hist_hum -> Fill(H);
      hist_volt -> Fill(V);
      if (file.eof()) break ;
    }

   file.close();

/*
   humidity -> SetTitle("Humidity on compost");
   humidity -> GetXaxis() -> SetTitle("t [min]");
   humidity -> GetYaxis() -> SetTitle("%");
   humidity -> GetYaxis() -> SetRangeUser(0,100);
   humidity -> SetMarkerStyle(21);
   humidity -> SetMarkerColor(01);
   humidity -> SetMarkerSize(0.5);
   humidity -> Draw("AP");
*/
  hist_hum -> SetFillColor(01);
  //hist_hum -> Fit("fit", "R");
  hist_hum -> Draw();
/*
   voltage -> SetTitle("Voltage on compost");
   voltage -> GetXaxis() -> SetTitle("t [min]");
   voltage -> GetYaxis() -> SetTitle("V [mV]");
   //voltage -> GetYaxis() -> SetRangeUser(0,100);
   voltage -> SetMarkerStyle(21);
   voltage -> SetMarkerColor(02);
   voltage -> SetMarkerSize(0.5);
   voltage -> Draw("AP");
*/
  hist_volt -> SetFillColor(02);
  //hist_hum -> Fit("fit", "R");
  hist_volt -> Draw();


  c -> Print("hist_volt2.pdf");


}
