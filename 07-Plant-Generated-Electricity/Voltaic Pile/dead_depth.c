void depth_dependence()
{
  TCanvas *c = new TCanvas();
  TLegend *legend = new TLegend(0.1, 0.1, 0.25, 0.35);
  //TGraphErrors *dead10 = new TGraphErrors();
  TGraph *depth_07 = new TGraph();
  TGraph *depth_25 = new TGraph();
  TGraph *depth_32 = new TGraph();
  TGraph *depth_41 = new TGraph();
  TGraph *depth_53 = new TGraph();

  fstream file;
  file.open("depths.csv", ios::in);


  while(1)
    {
      int n = depth_07-> GetN();
      double t, V_07, V_25, V_32, V_41, V_53;
      file >> t >> V_07 >> V_25 >> V_32 >> V_41 >> V_53;

      depth_07 -> SetPoint(n, t, V_07);
      depth_25 -> SetPoint(n,t,V_25);
      depth_32 -> SetPoint(n,t,V_32);
      depth_41 -> SetPoint(n,t,V_41);
      depth_53 -> SetPoint(n,t,V_53);

      if (file.eof()) break ;
    }

   file.close();


	//TF1 *fit= new TF1("fit", "A", 0, 90);



   depth_53 -> SetTitle("'Live' Earth, dependence with plates depth");
   depth_53 -> GetXaxis() -> SetTitle("t [min]");
   depth_53 -> GetYaxis() -> SetTitle("V [mV]");
   depth_53 -> GetYaxis() -> SetRangeUser(0,1000);

//	depth_07 -> Fit("A");

   depth_07 -> SetMarkerStyle(21);
   depth_07 -> SetMarkerColor(01);
   depth_25 -> SetMarkerStyle(21);
   depth_25 -> SetMarkerColor(02);
   depth_32 -> SetMarkerStyle(21);
   depth_32 -> SetMarkerColor(03);
   depth_41 -> SetMarkerStyle(21);
   depth_41 -> SetMarkerColor(04);
   depth_53 -> SetMarkerStyle(21);
   depth_53 -> SetMarkerColor(06);

  //depth_53 -> Draw("AP");
  //depth_41 -> Draw("AP");
  //depth_32 -> Draw("AP");
  depth_25 -> Draw("AP");
  //depth_07 -> Draw("P");

  legend -> AddEntry(depth_07, "0.7cm", "p");
  legend -> AddEntry(depth_25, "2.5cm", "p");
  legend -> AddEntry(depth_32, "3.2cm", "p");
  legend -> AddEntry(depth_41, "4.2cm", "p");
  legend -> AddEntry(depth_53, "5.3cm", "p");
  legend -> Draw();

  c -> Print("depth_dependence.pdf");


}
