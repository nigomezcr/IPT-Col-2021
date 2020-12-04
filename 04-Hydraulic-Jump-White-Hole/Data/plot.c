#include <TGraph.h>
#include <TGraphErrors.h>
#include <TF1.h>

void plot()
{
  TGraphErrors gr("./Data_Vidrio_17-11.csv");  
  gr.SetTitle("Vidrio 17-11;"
	      "Radio (cm);"
	      "Flujo (L/min)");
  gr.SetMarkerStyle(kOpenCircle);
  gr.SetMarkerColor(kBlue);
  gr.SetLineColor(kBlue);

  TF1 f("Linear law", "[0]*x + [1]", 0.5, 10.5);
  f.SetLineColor(kRed); f.SetLineStyle(2);
  gr.Fit(&f);
  
  gr.DrawClone("A*");
  gr.Print();
}
