#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include<numeric>
using namespace cv;
using namespace std;

Mat polyfit(vector<Point2f>& in_Point2d, int n);

// 缩放，用以调整曲线在640*480范围
constexpr double kZoomScale = 0.028;
constexpr int kHighestOrder = 5;
std::string path_ = "/home/wzl/storage/";
std::string file_name_ = "deviation.txt";
int main() {
  //数据输入
  std::fstream fin(path_ + file_name_);
  if (!fin.is_open()) {
    std::cout << "Opening file error..." << std::endl;
    exit(1);
  } else {
    std::cout << "Load file: " << file_name_ << std::endl;
  }

  std::vector<Point2f> PointData;
  for (std::string line; getline(fin, line);) {
    if (line.empty()) break;
    auto pos = line.find(',');
    Point2f Point2f_(std::stof(line.substr(0, pos)),
                     std::stof(line.substr(pos + 1, line.size() - pos)));
    std::cout << Point2f_.x << " " << Point2f_.y << std::endl;
    PointData.push_back(Point2f_);
  }
  const int kPoint2fSize = PointData.size();

  for (int n = 1; n <= kHighestOrder; n++) {
    Mat mat_k = polyfit(PointData, n);

    // n:多项式阶次
    // int n;
    // cout << "intput n: " << endl;
    // cin >> n;
    // cout << "n= " << n << endl;
    // Mat mat_k = polyfit(PointData, n);

    // Mat raw(800, 800, CV_32FC3, Scalar::all(0));

    //画原始散点
    // for (int i = 0; i < kPoint2fSize - 1; ++i) {
    //   Point2d ipt = PointData[i];
    //   circle(raw, ipt * kZoomScale, 1, Scalar(255, 255, 255));
    // }

    // imshow("raw", raw);
    // waitKey(1);

    //计算结果可视化,画出拟合曲线 
    // Mat rawAndFittedCurve(800, 800, CV_32FC3, Scalar::all(0));
    // Mat biasCurve(800, 800, CV_32FC3, Scalar::all(0));
    Point2f fittedPoint;
    vector<double> biasSet{0};

    for (int i = 0; i < kPoint2fSize; i++) {
      Point2f pt;
      pt.x = PointData[i].x;
      pt.y = PointData[i].y;
      fittedPoint.x = pt.x;
      fittedPoint.y = 0;

      for (int j = 0; j < n + 1; j++) {
        fittedPoint.y += mat_k.at<double>(j, 0) * pow(PointData[i].x, j);
      }
      // if (abs(pt.y - fittedPoint.y < 1000)) {
      biasSet.push_back(pt.y - fittedPoint.y);
      // }
      // circle(rawAndFittedCurve, pt * kZoomScale, 1, Scalar(255, 0, 0));
      // circle(rawAndFittedCurve, fittedPoint * kZoomScale, 1, Scalar(0, 0,
      // 255));
    }

    double allBiasSum = std::accumulate(biasSet.begin(), biasSet.end(), 0);
    double biasMean = allBiasSum / biasSet.size();
    double variance = 0;
    for_each(biasSet.begin(), biasSet.end(), [&](const double data) {
      variance += (data - biasMean) * (data - biasMean);
    });
    double stdev = sqrt(variance / (biasSet.size() - 1));

    cout << "bias mean: " << biasMean << "\tstand deviation: " << stdev << endl
         << endl;

    // imshow("resule", rawAndFittedCurve);
    // waitKey();
  }
  return 0;
}

Mat polyfit(vector<Point2f>& in_Point2d, int n) {
  cout << endl << "n = " << n << endl;
  int size = in_Point2d.size();
  //所求未知数个数
  int x_num = n + 1;
  //构造矩阵U和Y
  Mat mat_u(size, x_num, CV_64F);
  Mat mat_y(size, 1, CV_64F);

  for (int i = 0; i < mat_u.rows; ++i)
    for (int j = 0; j < mat_u.cols; ++j) {
      mat_u.at<double>(i, j) = pow(in_Point2d[i].x, j);
    }

  for (int i = 0; i < mat_y.rows; ++i) {
    mat_y.at<double>(i, 0) = in_Point2d[i].y;
  }

  //矩阵运算，获得系数矩阵K
  Mat mat_k(x_num, 1, CV_64F);
  mat_k = (mat_u.t() * mat_u).inv() * mat_u.t() * mat_y;
  for (int i = x_num - 1; i >= 0; i--) {
    cout << "k" << x_num - i - 1 << " = " << mat_k.at<double>(0, i) << "  ";
  }
  cout << endl;
  return mat_k;
}
