#ifndef FRACTAL_DIMENSION_H
#define FRACTAL_DIMENSION_H

#include <vector>
#include <opencv2/opencv.hpp>
#include <string>

/* This function give us the number of "boxes" containing the fractal */
unsigned int box_counting(std::vector<cv::Point> &y, unsigned int deltax, unsigned int deltay, unsigned int epsilon, unsigned int xmin, unsigned int ymin);


/* This function find the min and max in each axes */
void axes_min_max(std::vector<cv::Point> &y, unsigned int &xmin, unsigned int &xmax, unsigned int &ymin, unsigned int &ymax);


/* This function print in name the values of box counting in each epsilon */
void print_FD(std::string name, std::vector<cv::Point> &y);


/* This function print the points of the figure */
void print_image(std::string name, std::vector<cv::Point> &y);


#endif
