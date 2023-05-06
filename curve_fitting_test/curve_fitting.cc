#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;
using namespace std;

Mat polyfit(vector<Point2i>& in_Point2d, int n);
constexpr int kPoint2iSize = 58;
constexpr double kZoomScale = 0.022;
int main() {
  //数据输入
  Point2i in[kPoint2iSize] = {
      Point2i(882, 520),     Point2i(1399, 1060),   Point2i(1838, 1510),
      Point2i(2407, 2120),   Point2i(2936, 2650),   Point2i(3512, 3260),
      Point2i(4127, 3890),   Point2i(4676, 4450),   Point2i(5336, 5140),
      Point2i(6099, 5830),   Point2i(6595, 6440),   Point2i(7099, 6950),
      Point2i(7771, 7360),   Point2i(8401, 8260),   Point2i(9102, 8960),
      Point2i(9779, 9670),   Point2i(10194, 10100), Point2i(10736, 10640),
      Point2i(11405, 11300), Point2i(12075, 12000), Point2i(12792, 12710),
      Point2i(13459, 13390), Point2i(14178, 14120), Point2i(14908, 14850),
      Point2i(15590, 15510), Point2i(16360, 16280), Point2i(17085, 17000),
      Point2i(17814, 17720), Point2i(18467, 18380), Point2i(19148, 19060),
      Point2i(19838, 19750), Point2i(20436, 20350), Point2i(21073, 20990),
      Point2i(21758, 21670), Point2i(12142, 12060), Point2i(22157, 22070),
      Point2i(21872, 21790), Point2i(21558, 21470), Point2i(21226, 21140),
      Point2i(20896, 20810), Point2i(20498, 20410), Point2i(19751, 19660),
      Point2i(18671, 18590), Point2i(16917, 16830), Point2i(15143, 15070),
      Point2i(13381, 13320), Point2i(11165, 11070), Point2i(7996, 7840),
      Point2i(5906, 5700),   Point2i(3546, 3250),   Point2i(3579, 3280),
      Point2i(6012, 5830),   Point2i(9051, 8900),   Point2i(11995, 11910),
      Point2i(15969, 14910), Point2i(17261, 17180), Point2i(19594, 19520),
      Point2i(22487, 22410)};

  vector<Point2i> in_Point2d(begin(in), end(in));

  // n:多项式阶次
  int n;
  cout << "intput n: " << endl;
  cin >> n;
  cout << "n= " << n << endl;
  Mat mat_k = polyfit(in_Point2d, n);

  Mat raw(500, 500, CV_32FC3, Scalar::all(0));
  Mat one(500, 640, CV_32FC3, Scalar::all(0));
  //画出原始散点
  for (int i = 0; i < kPoint2iSize - 1; ++i) {
    Point2d ipt = in[i] * kZoomScale;
    circle(raw, ipt, 1, Scalar(255, 255, 255), CV_FILLED, CV_AA);
    circle(one, ipt, 1, Scalar(255, 255, 255), CV_FILLED, CV_AA);
  }

  imshow("raw", raw);
  waitKey(1);

  //计算结果可视化,画出拟合曲线
  Mat out(500, 500, CV_32FC3, Scalar::all(0));
  Mat bias(500, 500, CV_32FC3, Scalar::all(0));
  int index_ = 0;
  Point2i img_bias;
  vector<double> bias_vec{0};

  cout << "sizeof in: " << in[kPoint2iSize - 1].x << endl;
  for (double i = in[0].x; i < in[kPoint2iSize - 1].x; i += 200) {
    Point2i ipt;
    Point2i tmp = in[index_];
    ipt.x = i * kZoomScale;
    img_bias.x = ipt.x;
    ipt.y = 0;
    for (float j = 0; j < n + 1; ++j) {
      ipt.y += mat_k.at<double>(j, 0) * pow(i, j);
    }
    ipt.y *= kZoomScale;
    if (abs(ipt.y - tmp.y * kZoomScale < 500.)) {
      img_bias.y = abs(ipt.y - tmp.y * kZoomScale);
      bias_vec.push_back(img_bias.y);
      // cout << "bias [" << index_ << "]: " << img_bias.y << endl;
    }
    circle(out, ipt, 1, Scalar(0, 0, 255), CV_FILLED, CV_AA);
    circle(one, ipt, 1, Scalar(0, 0, 255), CV_FILLED, CV_AA);
    // circle(bias, img_bias, 1, Scalar(0, 0, 255), CV_FILLED, CV_AA);
  }

  double sum = std::accumulate(begin(bias_vec), end(bias_vec), 0.0);
  double mean = sum / bias_vec.size();  //均值

  double accum = 0.0;
  std::for_each(std::begin(bias_vec), std::end(bias_vec),
                [&](const double d) { accum += (d - mean) * (d - mean); });

  double stdev = sqrt(accum / (bias_vec.size() - 1));  //标准方差

  // cout << "mean: " << mean << " ,stddev: " << stdev << endl;

  imshow("resule", out);
  waitKey(1);

  imshow("one", one);
  waitKey();

  // cout << "result2:" << -0.1631 * 0.97 * 0.97 + 0.9696 * 0.97 + 0.00378 <<
  // endl; cout << "result3:"
  //      << -0.171 * 0.97 * 0.97 * 0.97 + 1.0161 * 0.97 * 0.97 - 0.07511 * 0.97
  //      +
  //             0.04041
  //      << endl;
  cout << "mat_k(0,0)" << mat_k.at<double>(0, 0);
  return 0;
}

Mat polyfit(vector<Point2i>& in_Point2d, int n) {
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
  cout << mat_k << endl;
  return mat_k;
}
