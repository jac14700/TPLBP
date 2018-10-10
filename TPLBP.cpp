#include"TPLBP.h"
Mat TPLBP(Mat scr)
{
    int x,y,x1,y1,z,h,a =2, first =0, second =-1, third =0, add =0, height =scr.size().height, width =scr.size().width;
    Mat temp,result;
    result.create( height,width,CV_8U);
	temp.create(height+8,width+8,CV_8U);
	scr.copyTo(temp(cv::Rect(3,3,scr.cols, scr.rows)));
	for(x = 4; x < width+4; x++)
	{
		for(y = 4; y < height+4; y++)
		{
		    int sum=0;
		    int x2=x-3,y2=y-3;
		    int sum0,sum1,sum2;
			mat_small_lbp(x,y,&sum0,temp);
			for(int i=0;i<8;i++)
            {
                int x3=x2,y3=y2;
                mat_small_lbp(x2,y2,&sum1,temp);
                for(int j=0;j<a;j++)
                {
                  jump(&x3,&y3,x,y);
                }
                mat_small_lbp(x3,y3,&sum2,temp);
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
            }//end for
            result.at<uchar>(y-4,x-4) =(uchar)sum;
            sum=0;
		}//end for
	}//end for
    return result;
}

Mat LBP(Mat scr)
{
    int x,y, height =scr.size().height, width =scr.size().width;
    Mat temp,result;
    result.create( height,width,CV_8U);
	temp.create(height+2,width+2,CV_8U);
	scr.copyTo(temp(cv::Rect(1,1,scr.cols, scr.rows)));
	for(x = 1; x < width+1; x++)
	{
		for(y = 1; y < height+1; y++)
		{
		    int sum=0;
		    mat_small_lbp(x,y,&sum,temp);
			result.at<uchar>(y-1,x-1) =(uchar)sum;
		}//end for
	}//end for
    return result;
}
void TPLBP(unsigned char *buffer, int width, int height)
{
    int x,y,x1,y1,z,h,a =2, first =0, second =-1, third =0, add =0;
    Mat result;
	unsigned char **pixel_2 ;
	pixel_2 = (unsigned char**)malloc((height + 8) * sizeof(unsigned char*));

	for(x = 0; x < height+8; x++)
		pixel_2[x] = (unsigned char*)malloc((width +8) * sizeof(unsigned char));

	unsigned char **pixel_lbp = (unsigned char**)malloc(height * sizeof(unsigned char*));
	for(x = 0; x < height; x++)
		pixel_lbp[x] = (unsigned char*)malloc(width * sizeof(unsigned char));

	for(x = 0; x < height+8; x++)
		for(y = 0; y < width+8; y++)
    		pixel_2[x][y] = 0;
	for(x = 4; x < height+4; x++)
		for(y = 4; y < width+4; y++)
		{
			first += 1;
    		pixel_2[x][y] = buffer[54+(first-1)*3];
		}
	for(x = 4; x < height+4; x++)
	{
		for(y = 4; y < width+4; y++)
		{
		    int sum=0;
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
            }//end for
            pixel_lbp[x-4][y-4] =sum;
            sum=0;
		}//end for
	}//end for
    system("pause");
    result.create(height,width,CV_8UC3);
    for(x = width-1; x >= 0; x--)
    {
        for(y = height-1; y >= 0 ; y--)
        {
            result.at<Vec3b>(x,y)[0]=pixel_lbp[y][x];
            result.at<Vec3b>(x,y)[1]=pixel_lbp[y][x];
            result.at<Vec3b>(x,y)[2]=pixel_lbp[y][x];
        }
    }
    TPLBP_show(result);

	for(x = 0; x < height+3; x++)
		free(pixel_2[x]);
	for(x = 0; x < height; x++)
		free(pixel_lbp[x]);
	free(pixel_2);
	free(pixel_lbp);
}
void TPLBP_show(Mat result)
{
    Point2f src_center(result.cols/2.0F, result.rows/2.0F);
    Mat rot_mat = getRotationMatrix2D(src_center, 90, 1.0);
    Mat dst;
    warpAffine(result, dst, rot_mat, result.size());
    imshow("result",dst);
    waitKey(0);

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


void Img2Csv(unsigned char *buffer, int filesize)
{
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

int mat_small_lbp(int x,int y,int *s,Mat temp)
{
    int num=0;
    int mask_33[9];
    for(int x1 = x-1; x1 <= x+1; ++x1)
    {
        for(int y1 = y-1; y1 <= y+1; ++y1)
        {
            int a1=(int)temp.at<uchar>(y1,x1);
            int b1=(int)temp.at<uchar>(y,x);
            if(y==505)
            cerr<<"a1:"<<a1<<"\tb1"<<b1<<"\n";
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
