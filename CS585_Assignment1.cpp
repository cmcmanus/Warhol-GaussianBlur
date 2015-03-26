/**
	CS585_Assignment1.cpp
	@author:
	@version:

	CS585 Image and Video Computing Fall 2014
	Assignment 1
	--------------
	This program:
		a) Creates an Warhol-style pop art filter of an input image and writes it to an output image 
		b) //TODO
	--------------
*/

#include "stdafx.h"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

//TODO: Please make sure the arguments and return value of your function signatures match those of your function definitions
void myWarhol(Mat&, Mat&);
void myModification(Mat&, Mat&);

int main()
{
	Mat image; Mat gray_frame;
	image = imread("selfie.jpg", CV_LOAD_IMAGE_COLOR);

	// resize the large image
	Mat resized = Mat::zeros(image.rows/2, image.cols/2, CV_8UC1);
	int y = image.rows / 2;
	int x = image.cols / 2;
	Size size(x, y);
	resize(image, resized, size);
	image = resized;

	namedWindow( "Image View Original", 1 );
	imshow("Image View Original", image);
	
	// creates the destination matrix
	Mat warhol = Mat::zeros(image.rows, image.cols, CV_8UC3);
	myWarhol(image, warhol);

	namedWindow("Warhol Image", 1);
	imshow("Warhol Image", warhol);
	imwrite("warhol.jpg", warhol);

	Mat blur = Mat::zeros(image.rows, image.cols, CV_8UC3);
	myModification(image, blur);

	namedWindow("Gaussian Blur", 1);
	imshow("Gaussian Blur", blur);
	imwrite("gaussian.jpg", blur);

	char key = waitKey(0);
	return 0;
}

// using the myGrayScale function from lab 1
//Creates a grayscale image from a color image.
void myGrayScale(Mat& src, Mat& dst) {
	//Different algorithms for converting color to grayscale: http://www.johndcook.com/blog/2009/08/24/algorithms-convert-color-grayscale/
	dst = Mat::zeros(src.rows, src.cols, CV_8UC1); //Returns a zero array of same size as src mat, and of type CV_8UC1
	for (int i = 0; i < src.rows; i++){
		for (int j = 0; j < src.cols; j++){
			//For each pixel, compute the average intensity of the 3 color channels
			Vec3b intensity = src.at<Vec3b>(i,j); //Vec3b is a vector of 3 uchar (unsigned character)
			int avg = (intensity[0] + intensity[1] + intensity[2])/3;
			dst.at<uchar>(i,j) = avg;
		}
	} 
	//cvtColor (src, dst, CV_BGR2GRAY); //cvtColor documentation: http://docs.opencv.org/modules/imgproc/doc/miscellaneous_transformations.html
}

// creates the warhol image
void myWarhol(Mat& src, Mat& dst) {

	Mat gray = Mat::zeros(src.rows, src.cols, CV_8UC1);
	myGrayScale(src, gray);

	// creates a new resized image with half the number of columns and half the number of rows
	Mat resized = Mat::zeros(src.rows/2, src.cols/2, CV_8UC1);
	int y = src.rows / 2;
	int x = src.cols / 2;
	Size size(x, y);
	resize(gray, resized, size);

	
	// iterates through the pixels of the resized, gray source and puts a color in the four new pixels of each of the destinations based on the intensity
	for (int i = 0; i < resized.rows; i++){
		for (int j = 0; j < resized.cols; j++){
			int intensity = resized.at<uchar>(i, j);
			if (intensity < 65){
				// sets the first image color
				dst.at<Vec3b>(i, j) = Vec3b(255, 0, 255);
				// sets second image
				dst.at<Vec3b>(i+resized.rows, j) = Vec3b(255, 255, 0);
				// sets third image
				dst.at<Vec3b>(i, j+resized.cols) = Vec3b(32,165,218);
				// sets fourth image
				dst.at<Vec3b>(i + resized.rows, j+resized.cols) = Vec3b(0,255,127);
			} else if (intensity < 128){
				// sets the first image color
				dst.at<Vec3b>(i, j) = Vec3b(0,140,255);
				// sets second image
				dst.at<Vec3b>(i+resized.rows, j) = Vec3b(219,112,147);
				// sets third image
				dst.at<Vec3b>(i, j+resized.cols) = Vec3b(45,82,160);
				// sets fourth image
				dst.at<Vec3b>(i + resized.rows, j+resized.cols) = Vec3b(222,196,176);
			} else if (intensity < 193){
				// sets the first image color
				dst.at<Vec3b>(i, j) = Vec3b(128,128,0);
				// sets second image
				dst.at<Vec3b>(i+resized.rows, j) = Vec3b(60,20,220);
				// sets third image
				dst.at<Vec3b>(i, j+resized.cols) = Vec3b(34,139,34);
				// sets fourth image
				dst.at<Vec3b>(i + resized.rows, j+resized.cols) = Vec3b(80,127,255);
			} else {
				// sets the first image color
				dst.at<Vec3b>(i, j) = Vec3b(211,85,186);
				// sets second image
				dst.at<Vec3b>(i+resized.rows, j) = Vec3b(63,133,205);
				// sets third image
				dst.at<Vec3b>(i, j+resized.cols) = Vec3b(47,255,173);
				// sets fourth image
				dst.at<Vec3b>(i + resized.rows, j+resized.cols) = Vec3b(154,250,0);
			}
		}
	}
}

// creates a gaussian blur effect
void myModification(Mat& src, Mat& dst) {
	//TODO	

	// creates the guassian matrix for to be used for the blur
	double gaussian[9][9] = {{1.79106360847764e-8, 5.931188088149993e-7, 0.000007225666306368065, 0.000032383189711158964, 0.000053390853689904875, 0.000032383189711158964, 0.000007225666306368065, 5.931188088149993e-7, 1.79106360847764e-8},
	{5.931188088149993e-7, 0.00001964139741910877, 0.0002392812054380594, 0.0010723839631490409, 0.0017680622504015115, 0.0010723839631490409, 0.0002392812054380594, 0.00001964139741910877, 5.931188088149993e-7},
	{0.000007225666306368065, 0.0002392812054380594, 0.0029150418401588836, 0.013064311154617904, 0.021539407687663305, 0.013064311154617904, 0.0029150418401588836, 0.0002392812054380594, 0.000007225666306368065},
	{0.000032383189711158964, 0.0010723839631490409, 0.013064311154617904, 0.058550180513145256, 0.0965329280153539, 0.058550180513145256, 0.013064311154617904, 0.0010723839631490409, 0.000032383189711158964},
	{0.000053390853689904875, 0.0017680622504015115, 0.021539407687663305, 0.0965329280153539, 0.15915589174187697, 0.0965329280153539, 0.021539407687663305, 0.0017680622504015115, 0.000053390853689904875},
	{0.000032383189711158964, 0.0010723839631490409, 0.013064311154617904, 0.058550180513145256, 0.0965329280153539, 0.058550180513145256, 0.013064311154617904, 0.0010723839631490409, 0.000032383189711158964},
	{0.000007225666306368065, 0.0002392812054380594, 0.0029150418401588836, 0.013064311154617904, 0.021539407687663305, 0.013064311154617904, 0.0029150418401588836, 0.0002392812054380594, 0.000007225666306368065},
	{5.931188088149993e-7, 0.00001964139741910877, 0.0002392812054380594, 0.0010723839631490409, 0.0017680622504015115, 0.0010723839631490409, 0.0002392812054380594, 0.00001964139741910877, 5.931188088149993e-7},
	{1.79106360847764e-8, 5.931188088149993e-7, 0.000007225666306368065, 0.000032383189711158964, 0.000053390853689904875, 0.000032383189711158964, 0.000007225666306368065, 5.931188088149993e-7, 1.79106360847764e-8}};

	// creates the blur
	dst = Mat::zeros(src.rows, src.cols, CV_8UC3);
	for (int i = 0; i < src.rows; i++){
		for (int j = 0; j < src.cols; j++){
			//cout << i << " " << j << endl;
			double r=0, g=0, b = 0;
			
			// combining pixels within a 4 pixel radius
			for (int gi = -4; gi < 5; gi++){
				for (int gj = -4; gj < 5; gj++){
					int newi = min(src.rows-1, max(0, gi+i));
					int newj = min(src.cols-1, max(0, gj+j));

					// each pixel is multiplied by the proper value in the matrix
					double gausval = gaussian[gi+4][gj+4];
					Vec3b pixel = src.at<Vec3b>(newi, newj);
					b += gausval * pixel[0];
					g += gausval * pixel[1];
					r += gausval * pixel[2];
				}
			}

			dst.at<Vec3b>(i, j) = Vec3b((int)b, (int)g, (int)r);
		}
	}
}
