#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
using namespace std;
using namespace cv;

string path_ = "/home/shish/storage/";
string file_name_ = "guanghe.txt";

int main() {
  //数据输入
  fstream fin(path_ + file_name_);
  if (!fin.is_open()) {
    cout << "Opening file error..." << endl;
    exit(1);
  } else {
    std::cout << "OK" << std::endl;
  }

  vector<Point2i> PointData;
  for (string line; getline(fin, line);) {
    if (line.empty()) break;
      auto pos = line.find(',');
    // if (pos == line.end()){
      std::cout << pos << std::endl;
      Point2i point2i_(stoi(line.substr(0, pos)),
                       stoi(line.substr(pos + 1, line.size() - pos)));
      PointData.push_back(point2i_);
    // }
  }
  for (auto a:PointData) {
std::cout<<"res: "<< a.x <<" "<<a.y<<std::endl;
  }
  return 0;
}