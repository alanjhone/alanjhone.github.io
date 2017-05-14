#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace cv;

// #define STEP 10
// #define JITTER 5
// #define RAIO 5
#define STEP 5
#define JITTER 3
#define RAIO 3

int top_slider = 10;
int top_slider_max = 200;

char TrackbarName[50];

Mat image, border;

int main(int argc, char** argv){
  vector<int> yrange;
  vector<int> xrange;

  Mat frame, points;

  int width, height, gray;
  int x, y;

  image= imread(argv[1],CV_LOAD_IMAGE_COLOR);
  srand(time(0));

  if(!image.data){
	cout << "nao abriu" << argv[1] << endl;
    cout << argv[0] << " imagem.jpg";
    exit(0);
  }

  width=image.size().width;
  height=image.size().height;

  xrange.resize(height/STEP);
  yrange.resize(width/STEP);

  iota(xrange.begin(), xrange.end(), 0);
  iota(yrange.begin(), yrange.end(), 0);

  for(uint i=0; i<xrange.size(); i++){
    xrange[i]= xrange[i]*STEP+STEP/2;
  }

  for(uint i=0; i<yrange.size(); i++){
    yrange[i]= yrange[i]*STEP+STEP/2;
  }

  points = Mat(height, width, CV_8UC3, Scalar(255, 255, 255));

  random_shuffle(xrange.begin(), xrange.end());

  for(auto i : xrange){
    random_shuffle(yrange.begin(), yrange.end());
    for(auto j : yrange){
      x = i+rand()%(2*JITTER)-JITTER+1;
      y = j+rand()%(2*JITTER)-JITTER+1;
      Vec3b val = image.at<Vec3b>(x,y);
      circle(points,
             cv::Point(y,x),
             RAIO,
             CV_RGB(val[2],val[1],val[0]),
             -1,
             CV_AA);
    }
  }

  imshow("pontilhismo", points);
  imwrite("pontilhismo.jpg", points);

  for(auto i : xrange){
    random_shuffle(yrange.begin(), yrange.end());
    for(auto j : yrange){
      x = i+rand()%(2*JITTER)-JITTER+1;
      y = j+rand()%(2*JITTER)-JITTER+1;
      Vec3b val = image.at<Vec3b>(x,y);
      circle(points,
             cv::Point(y,x),
             RAIO,
             CV_RGB(val[2],val[1],val[0]),
             -1,
             CV_AA);
    }
  }

  imshow("cannypoints", points);
  waitKey();


  imwrite("cannypoints.jpg", points);


    
  return 0;
}