#ifndef TPLBP_H_INCLUDED
#define TPLBP_H_INCLUDED
#include<opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define t 50
using namespace std;
using namespace cv;
int image_width(unsigned char *buffer);
int image_height(unsigned char *buffer);
int sma_LBP(int x,int y,int *s,unsigned char **p2);
int jump(int *x,int *y,int corex,int corey);
void TPLBP(unsigned char *buffer, int width, int height);
void Img2Csv(unsigned char *buffer, int filesize);
void TPLBP_show(Mat result);
Mat TPLBP(Mat scr);
Mat LBP(Mat scr);
int mat_small_lbp(int x,int y,int *s,Mat temp);

#endif // TPLBP_H_INCLUDED
