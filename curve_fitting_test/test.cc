#include <iostream>

int main() {
  std::cout << "input goal height (m): " << std::endl;
  float n;
  while (std::cin >> n) {
    // std::cout << "order 1 input value: "
    //           << 1.001065684196832 * n + 1747.706562309206 << std::endl;
    //     std::cout << "order 2 input value: "
    //               << -7.0862e-07 * n * n + 1.0269 * n - 352.8437 <<
    //               std::endl;
    std::cout << "order 1 input long value: " << 1 * n + 2400
              << std::endl;

    // std::cout << "original order 2 input long value: "
    //           << -5.945928918576826e-07 * n * n + 1.019168444428466 * n + 2400
    //           << std::endl;

    std::cout << "order 2 input long value: "
              << -5.80e-07 * n * n + 1.02 * n + 1150 << std::endl;

    // std::cout << "another order 2 input long value: "

    //           << -6.01608904441557e-07 * n * n + 1.018018429694138 * n + 2400
    //           << std::endl;

    // std::cout << "order 3 input value: "
    //           << 1.949188366577558e-11 * n * n * n -
    //                  1.420066932973219e-06 * n * n + 1.028354045940646 * n +
    //                  1435.180646173912
    //           << std::endl;
    //     std::cout << "order 4 intput value: "
    //               << -2.328153341177014e-16 * n * n * n * n +
    //                      4.888084498187594e-11 * n * n * n -
    //                      2.6882741232279e-06 * n * n + 1.051955604240908 * n
    //                      - 91.70270696657235
    //               << std::endl;
    //     std::cout << "order 5 intput value: "
    //               << -1.385436534961135e-19 * n * n * n * n * n +
    //                      1.068868048367459e-14 * n * n * n * n -
    //                      2.613299175017711e-10 * n * n * n +
    //                      1.125964094266972e-06 * n * n + 1.032984648178772 *
    //                      n - -65.03876305770382
    //               << std::endl;
  }

  return 0;
}