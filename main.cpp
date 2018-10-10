#include"TPLBP.h"
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
