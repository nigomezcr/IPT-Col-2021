#include <fractal_dimension.h>
#include <fstream>
#include <math.h>

unsigned int box_counting(std::vector<cv::Point> &y, unsigned int deltax, unsigned int deltay, unsigned int epsilon, unsigned int xmin, unsigned int ymin){
  //Create the matrix for the box_counting
  unsigned int my_array[deltax*deltay] = {}, value;

  //Find in which square the pixel of the image is
  for(size_t i=0; i<y.size(); i++){
    value = ((y[i].x-xmin)/epsilon)*deltay + ((y[i].y-ymin)/epsilon);
    my_array[(int)value] = 1;
  }

  //Count the number of squares where is, at least, one pixel
  unsigned int N = 0;
  unsigned int div = epsilon*epsilon*0.5;  
  for(size_t i=0; i<deltax*deltay; i++){N += my_array[i];}

  return N;
}


void axes_min_max(std::vector<cv::Point> &y, unsigned int &xmin, unsigned int &xmax, unsigned int &ymin, unsigned int &ymax){
  //Set the extreme values
  ymin = 1e6, ymax = 0, xmin = 1e6, xmax = 0;

  //Find the maximum and minimum in each axes
  for(size_t i=0; i<y.size(); i++){
    ymin = ((ymin < y[i].y) ? ymin : y[i].y);    ymax = ((ymax > y[i].y) ? ymax : y[i].y);
    xmin = ((xmin < y[i].x) ? xmin : y[i].x);    xmax = ((xmax > y[i].x) ? xmax : y[i].x);
  }
}


void print_FD(std::string name, std::vector<cv::Point> &y){
  //Find the extreme values
  unsigned int ymin, ymax, xmin, xmax, deltax, deltay;
  axes_min_max(y, xmin, xmax, ymin, ymax);
  deltax = xmax - xmin;  deltay = ymax - ymin;

  //Print the epsilon and the box_counting
  std::ofstream fout(name);
  for(unsigned int i=1; i<30; i++){fout << i << '\t' << box_counting(y, (deltax/i)+1, (deltay/i)+1, i, xmin, ymin) << std::endl;}
  fout.close();
}


void print_image(std::string name, std::vector<cv::Point> &y){
  std::ofstream fout(name);
  for(size_t i=0; i<y.size(); i++){fout << y[i].x << '\t' << y[i].y << std::endl;}
  fout.close();
}
