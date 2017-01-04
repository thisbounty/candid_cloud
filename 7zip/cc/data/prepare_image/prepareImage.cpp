#include <stdio.h>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv ) {
    if ( argc < 2 ) {
        printf("usage: PrepareImage <Image_Path> <optional threshold 0-100, defalt 40>\n");
        return -1;
    }
	double threshold_val = 102.0;
	if ( argc == 3) {
		threshold_val = atoi(argv[2])*255/100;
	}

    Mat image, grayscale, thresholded, out;
    image = imread( argv[1], 1 );

    if ( !image.data ) {
        printf("No image data \n");
        return -1;
    }
    cvtColor(image, grayscale, COLOR_BGR2GRAY);
     
    threshold(grayscale, thresholded, threshold_val, 255.0, 0);

    medianBlur(thresholded, out, 23);
    imwrite("res.png", out);

    return 0;
}
