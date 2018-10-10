#include"TPLBP.h"
#include"cam.h"

int main()
{
    VideoCapture cap=opencam(0);
    cap.set(CV_CAP_PROP_FRAME_WIDTH,320);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,240);
    Mat frame,lbp_result,tplbp_result;
    while(1)
    {
        cap>>frame;
        cvtColor(frame, frame, CV_BGR2GRAY);
        lbp_result =LBP(frame);
        tplbp_result =TPLBP(frame);
        imshow("frame",frame);
        imshow("LBP",lbp_result);
        imshow("TPLBP",tplbp_result);
        waitKey(10);
    }

//	FILE *image = fopen("Lena_gray_24.bmp","rb");
//    fseek(image,0,SEEK_END);
//    long filesize = ftell(image);
//    rewind(image);
//    unsigned char *buffer = (unsigned char*)malloc(filesize * sizeof(unsigned char));
//	fread(buffer, filesize, 1, image);
//    fclose(image);
//    //*******************************************************************************Get image width and height
//    int width = image_width(buffer);
//    int height = image_height(buffer);
//    //*******************************************************************************image feature(Just needed revise this function)
//    TPLBP(buffer, width, height);
//    //*******************************************************************************Save to *.csv file
//    Img2Csv(buffer, (int)filesize);
//    free(buffer);
    return 0;
}
