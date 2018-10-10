/*	Example for homework.
	Input image standard : 24bits bmp image(gray level image).
	Function Description:
	1. image_width¡GGet bmp image width.
	2. image_height : Get bmp image height.
	3. LBP(Local Binary Pattern) : Computing image feature(texture).
	4. Img2Csv : Image pixel record to csv file.
*/
#include<opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define t 50
using namespace cv;
int image_width(unsigned char *buffer);
int image_height(unsigned char *buffer);
void TPLBP(unsigned char *buffer, int width, int height);
void Img2Csv(unsigned char *buffer, int filesize);
int sma_LBP(int x,int y,int *s,unsigned char **p2);
int jump(int *x,int *y,int corex,int corey);


int main()
{
	FILE *image = fopen("Lena_gray_24.bmp","rb");
    fseek(image,0,SEEK_END);
    long filesize = ftell(image);
    rewind(image);
    unsigned char *buffer = (unsigned char*)malloc(filesize * sizeof(unsigned char));
	fread(buffer, filesize, 1, image);
    fclose(image);
    //*******************************************************************************Get image width and height
    int width = image_width(buffer);
    int height = image_height(buffer);
    //*******************************************************************************image feature(Just needed revise this function)
    TPLBP(buffer, width, height);
    //*******************************************************************************Save to *.csv file
    Img2Csv(buffer, (int)filesize);

    free(buffer);

	return 0;
}

int image_width(unsigned char *buffer)
{
	int width = (long)buffer[18] +
               ((long)buffer[19] << 8) +
               ((long)buffer[20] << 16) +
               ((long)buffer[21] << 24);

    return width;
}

int image_height(unsigned char *buffer)
{
	int height = (long)buffer[22] +
                ((long)buffer[23] << 8) +
                ((long)buffer[24] << 16) +
                ((long)buffer[25] << 24);

    return height;
}

void TPLBP(unsigned char *buffer, int width, int height)
{
    int a ;
    int add=0;
    scanf("%d",&a);
	int x,
	    y,
	    x1,
	    y1,
	    z,
	    h,
		first = 0,
		second = -1,
		third = 0;
	unsigned char **pixel_2 ;

	pixel_2 = (unsigned char**)malloc((height + 8) * sizeof(unsigned char*));

	for(x = 0; x < height+8; x++)
		pixel_2[x] = (unsigned char*)malloc((width +8) * sizeof(unsigned char));

	unsigned char **pixel_lbp = (unsigned char**)malloc(height * sizeof(unsigned char*));
	for(x = 0; x < height; x++)
		pixel_lbp[x] = (unsigned char*)malloc(width * sizeof(unsigned char));



	for(x = 0; x < height+8; x++)
	{
		for(y = 0; y < width+8; y++)
    		pixel_2[x][y] = 0;
	}

	for(x = 4; x < height; x++)
	{
		for(y = 4; y < width; y++)
		{
			first += 1;
    		pixel_2[x][y] = buffer[54+(first-1)*3];
		}
	}

	for(x = 4; x <= height+4; x++)
	{
		for(y = 4; y < width+4; y++)
		{
		    int sum=0;  //
		    int x2=x-3,y2=y-3;
		    int sum0,sum1,sum2;
			sma_LBP(x,y,&sum0,pixel_2);
			for(int i=0;i<8;i++)
            {
                int x3=x2,y3=y2;
                sma_LBP(x2,y2,&sum1,pixel_2);
                for(int j=0;j<a;j++)
                {
                    jump(&x3,&y3,x,y);
                }
                    sma_LBP(x3,y3,&sum2,pixel_2);
                    int a1=abs(sum1-sum0);
                    int a2=abs(sum2-sum0);
                    int a3;
                    if ((a1-a2)>t)
                    {
                        a3=1;
                    }
                    else if ((a1-a2)<t)
                    {
                        a3=0;
                    }
                    sum+=a3*pow(2,7-i);
                    jump(&x2,&y2,x,y);
            }
                pixel_lbp[x][y] =sum;
                sum=0;
					}
				}
system("pause");

Mat result;
result.create(height,width,CV_8UC3);

  	/*After LBP calculate then write to original input data*/
	for(x = 0; x < height; x++)
    {
    	for(y = 0; y < width; y++)
    	{
    	    result.at<Vec3b>(y,x)[0]=pixel_lbp[x][y];
            result.at<Vec3b>(y,x)[1]=pixel_lbp[x][y];
            result.at<Vec3b>(y,x)[2]=pixel_lbp[x][y];
            third += 1;
            buffer[54+(third-1)*3] = pixel_lbp[x][y];
    		buffer[55+(third-1)*3] = pixel_lbp[x][y];
    		buffer[56+(third-1)*3] = pixel_lbp[x][y];
		}
	}

imshow("result",result);
waitKey(0);
	for(x = 0; x < height+3; x++)
		free(pixel_2[x]);
	for(x = 0; x < height; x++)
		free(pixel_lbp[x]);
	free(pixel_2);
	free(pixel_lbp);
}

void Img2Csv(unsigned char *buffer, int filesize)
{
	/*FILE *LBPcsv = fopen("yes.csv", "wb");
    fprintf(LBPcsv, "LBP_mode1\n");
    int pixel,counT=0;
    for(pixel = 54; pixel < (int)filesize; pixel+=3)
    {   if((counT%512)=0)
        fprintf(LBPcsv, "%lf\n", (float)buffer[pixel]);


    	fprintf(LBPcsv, "%lf", (float)buffer[pixel]);
        counT++;
	}
	fclose(LBPcsv);*/
	FILE *lena_BMP = fopen("lena.csv", "wb");
    fprintf(lena_BMP, "lena_mode1\n");
    int pixel;
    int num=0;
    for(pixel = 54; pixel < (int)filesize; pixel+=3)
    {
        num++;
        if(num%512 == 0)    fprintf(lena_BMP, "%lf\n", (float)buffer[pixel]);
    	else fprintf(lena_BMP, "%lf,", (float)buffer[pixel]);
	}
	fclose(lena_BMP);
}

int jump(int *x,int *y,int core_x,int core_y)

{
            int a=*x-core_x;
            int b=*y-core_y;
            if((a==-3)&&(b==-3))
            {
                *y+=3;
                return 0;
            }
            if((a==-3)&&(b==0))
            {
                *y+=3;
                return 0;
            }
            if((a==-3)&&(b==3))
            {
                *x+=3;
                return 0;
            }
            if((a==0)&&(b==3))
            {
                *x+=3;
                return 0;
            }
            if((a==3)&&(b==3))
            {
                *y-=3;
                return 0;
            }
            if((a==3)&&(b==0))
            {
                *y-=3;
                return 0;
            }
            if((a==3)&&(b==-3))
            {
                *x-=3;
                return 0;
            }
            if((a==0)&&(b==0))
            {
                *x-=3;
                return 0;


            }



}

int sma_LBP(int x,int y,int *s,unsigned char **p2)
{
                int num=0;
                int mask_33[9];
                for(int x1 = x-1; x1 <= x+1; ++x1)
                {
                    for(int y1 = y-1; y1 <= y+1; ++y1)
                    {
                        int a1=p2[x1][y1];
                        int b1=p2[x][y];
                        if (a1>=b1)
                        mask_33[num] = 1;
                        else if(a1 <b1)
                        mask_33[num] = 0;
                        num++;
                        if(num == 8)
                        {
                            *s=0;
                            *s += (mask_33[0] == 1) ? pow(2, 7):0;
                            *s += (mask_33[1] == 1) ? pow(2, 6):0;
                            *s += (mask_33[2] == 1) ? pow(2, 5):0;
                            *s += (mask_33[5] == 1) ? pow(2, 4):0;
                            *s += (mask_33[8] == 1) ? pow(2, 3):0;
                            *s += (mask_33[7] == 1) ? pow(2, 2):0;
                            *s += (mask_33[6] == 1) ? pow(2, 1):0;
                            *s += (mask_33[3] == 1) ? pow(2, 0):0;
                        }
                    }
            }
}


 /** pixel_lbp[x-1][y-1] = temp1;*/
/**
#include <iostream>
#include <opencv\cv.h>
#include <opencv\highgui.h>

using namespace std;
using namespace cv;
int main()
{

	//Mat frame;
	VideoCapture cap(0);
	if (!cap.isOpened()){
		return -1;
	}
	//cap.read(Mat frame);
	Mat src = Mat(cap.read(Mat frame));
	imshow("window", src);
    imwrite("nowon"src);


/**while(1)
{

if (waitKey(1) == 'c') {    	//連續按c跳脫
			break;
		}
}



		waitKey(30);
	}
*/
