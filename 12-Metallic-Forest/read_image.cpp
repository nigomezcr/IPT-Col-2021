#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "fractal_dimension.h"

int main(int argc, char *argv[])
{
  // Transform the name into its main part
  std::string name(argv[1]);
  std::size_t pos;
  pos = name.find("/");
  while (pos < name.size()){
    pos = name.find("/");
    name.erase(0,pos+1);
  }
  pos = name.find(".");
  name.erase(pos);

  cv::Mat img, gray, bw;
  // Read the image
  img = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
  if(!img.data){std::cout<< "Could not find the image";      return -1;}

  // Transform it to gray scale
  cv::cvtColor(img, gray, CV_BGR2GRAY);

  // Transform to binary matrix
  threshold(gray, bw, 40, 255, CV_THRESH_OTSU | CV_THRESH_BINARY_INV);
  //threshold(gray, bw, 40, 255, CV_THRESH_OTSU);

  // Find the pixels that are white
  std::vector<cv::Point> white_pixels;
  cv::findNonZero(bw, white_pixels);

  //Get the data for find the FD
  print_FD("Powls_Images/Escenary1/Data_FD_Dendrite1/" + name + ".csv", white_pixels);

  //Get the points of the figure
  print_image("Powls_Images/Escenary1/Data_FD_Dendrite1/" + name + "_image.csv", white_pixels);

  /* Show image */
  cv::namedWindow("window", CV_WINDOW_AUTOSIZE );
  imshow("window", bw);
  cv::waitKey(10*1e3);

  return 0;
}
