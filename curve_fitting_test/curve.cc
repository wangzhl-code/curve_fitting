#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;
using namespace std;

Mat polyfit(vector<Point>& in_point, int n);

int main() {
  //数据输入
  Point in[71] = {
      Point(0.05, 0.217), Point(0.06, 0.237), Point(0.07, 0.245),
      Point(0.08, 0.252), Point(0.09, 0.268), Point(0.1, 0.268),
      Point(0.11, 0.281), Point(0.12, 0.28),  Point(0.13, 0.304),
      Point(0.15, 0.323), Point(0.16, 0.342), Point(0.17, 0.337),
      Point(0.18, 0.357), Point(0.19, 0.358), Point(0.2, 0.376),
      Point(0.21, 0.376), Point(0.22, 0.394), Point(0.23, 0.411),
      Point(0.24, 0.411), Point(0.27, 0.442), Point(0.29, 0.459),
      Point(0.3, 0.472),  Point(0.31, 0.488), Point(0.32, 0.501),
      Point(0.33, 0.502), Point(0.34, 0.518), Point(0.36, 0.547),
      Point(0.37, 0.557), Point(0.38, 0.556), Point(0.39, 0.571),
      Point(0.4, 0.581),  Point(0.42, 0.596), Point(0.43, 0.612),
      Point(0.44, 0.616), Point(0.45, 0.635), Point(0.46, 0.636),
      Point(0.47, 0.649), Point(0.48, 0.662), Point(0.49, 0.669),
      Point(0.5, 0.688),  Point(0.51, 0.692), Point(0.52, 0.7),
      Point(0.54, 0.715), Point(0.55, 0.742), Point(0.56, 0.739),
      Point(0.57, 0.754), Point(0.58, 0.771), Point(0.59, 0.78),
      Point(0.61, 0.801), Point(0.62, 0.811), Point(0.64, 0.828),
      Point(0.65, 0.835), Point(0.66, 0.843), Point(0.68, 0.86),
      Point(0.69, 0.868), Point(0.70, 0.886), Point(0.73, 0.924),
      Point(0.74, 0.928), Point(0.75, 0.936), Point(0.77, 0.957),
      Point(0.78, 0.976), Point(0.79, 0.975), Point(0.8, 0.995),
      Point(0.81, 0.999), Point(0.82, 1.011), Point(0.84, 1.025),
      Point(0.85, 1.04),  Point(0.86, 1.052), Point(0.87, 1.061),
      Point(0.88, 1.065), Point(0.89, 1.085)};

  vector<Point> in_point(begin(in), end(in));

  // n:多项式阶次
  int n = 9;
  Mat mat_k = polyfit(in_point, n);

  //计算结果可视化
  Mat out(2000, 2000, CV_8UC3, Scalar::all(0));

  //画出拟合曲线
  // for (int i = in[0].x; i < in[size(in)-1].x; ++i)
  for (int i = in[0].x; i < in[70].x; ++i) {
    Point2d ipt;
    ipt.x = i;
    ipt.y = 0;
    for (int j = 0; j < n + 1; ++j) {
      ipt.y += mat_k.at<double>(j, 0) * pow(i, j);
    }
    circle(out, ipt, 1, Scalar(255, 255, 255), CV_FILLED, CV_AA);
  }

  //画出原始散点
  // for (int i = 0; i < size(in); ++i)
  for (int i = 0; i < 71; ++i) {
    Point ipt = in[i];
    circle(out, ipt, 3, Scalar(0, 0, 255), CV_FILLED, CV_AA);
  }

  imshow("9", out);
  waitKey(0);

  return 0;
}

Mat polyfit(vector<Point>& in_point, int n) {
  int size = in_point.size();
  //所求未知数个数
  int x_num = n + 1;
  //构造矩阵U和Y
  Mat mat_u(size, x_num, CV_64F);
  Mat mat_y(size, 1, CV_64F);

  for (int i = 0; i < mat_u.rows; ++i)
    for (int j = 0; j < mat_u.cols; ++j) {
      mat_u.at<double>(i, j) = pow(in_point[i].x, j);
    }

  for (int i = 0; i < mat_y.rows; ++i) {
    mat_y.at<double>(i, 0) = in_point[i].y;
  }

  //矩阵运算，获得系数矩阵K
  Mat mat_k(x_num, 1, CV_64F);
  mat_k = (mat_u.t() * mat_u).inv() * mat_u.t() * mat_y;
  cout << mat_k << endl;
  return mat_k;
}
