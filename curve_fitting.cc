#include <iostream>
#include <vector>
#include <fstream>
#include "/usr/include/eigen3/Eigen/Dense"
 using namespace Eigen;
 int main()
{
    // 打开数据文件
    std::ifstream file("data.txt");
    if (!file) {
        std::cerr << "无法打开文件！" << std::endl;
        return 1;
    }
     // 读取数据点
    int n = 0; // 数据点数
    double x, y;
    std::vector<double> x_vec, y_vec; // 存储x和y
    while (file >> x >> y) {
        ++n;
        x_vec.push_back(x);
        y_vec.push_back(y);
    }
     // 计算不同次数多项式拟合的系数
    for (int degree = 1; degree <= 5; ++degree) {
        // 构造矩阵A和向量b
        MatrixXd A(n, degree + 1);
        VectorXd b(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= degree; ++j) {
                A(i, j) = std::pow(x_vec[i], j);
            }
            b(i) = y_vec[i];
        }
        // 求解最小二乘问题
        VectorXd coeff = A.colPivHouseholderQr().solve(b);
        // 输出结果
        std::cout << degree << "次项式系数: ";
        for (int i = degree; i >= 0; --i) {
            std::cout << static_cast<double>(coeff(i)) << " ";
        }
        std::cout << std::endl;
    }
     return 0;
}