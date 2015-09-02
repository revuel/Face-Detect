// Práctica 2: Detección de rostros
// Sistemas de Visión artificial en Robots
// Javier Morales. 2014-2015
// UFV


#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


String face_cascade_name = "haarcascade_frontalface_alt.xml";
CascadeClassifier face_cascade;
string window_name = "Face Detector";
int face_size = 50;
RNG rng(12345);


int main(int argc, char** argv)
{
	if (argc != 2)
	{
		cout << " Usage: facedetect image_name" << endl;
		return -1;
	}

	Mat image, img_gray;
	std::vector<Rect> faces;

	//-- 1.Read the Image
	image = imread(argv[1], IMREAD_COLOR); // Read the file
	if (!image.data) // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	cvtColor(image, img_gray, CV_BGR2GRAY);
	equalizeHist(img_gray, img_gray);

	//-- 2. Load the cascade
	if (!face_cascade.load(face_cascade_name)){ printf("--(!)Error loading\n"); return -1; };

	//-- 3. Detect faces
	face_cascade.detectMultiScale(img_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

	for (size_t i = 0; i < faces.size(); i++)
	{
		Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
		ellipse(image, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
	}

	namedWindow(window_name, WINDOW_AUTOSIZE); // Create a window for display.
	imshow(window_name, image); // Show our image inside it.

	waitKey(0); // Wait for a keystroke in the window
	return 0;
}