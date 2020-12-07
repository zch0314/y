#include "nurbs.h"
#include "pys.h"
#include <Eigen/Eigen>
#include <iostream>

using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::cout;
using std::endl;

const static double Pi = 3.141592653589793;

int main(void) {
    cout << "开始计算" << endl;
    Pys plt("./src/iga");
    int p = 2;              //设置B样条基函数的阶数（NURBS样条基函数）
    int n = 7;              //设置B样条基函数的个数（NURBS样条基函数）
    VectorXd nd(n + p + 1); //设置B样条基函数的节点
    nd << 0, 0, 0, 1, 2, 3, 4, 5, 5, 5;
    //给定绘图的点,用于绘制B样条基函数和NURBS基函数图像
    int num = 101;
    VectorXd xis = VectorXd::LinSpaced(num, 0, 5.0 - 1e-5);
    //创建一维NURBS基函数
    Nurbs N;
    N.setNode(nd, p);
    MatrixXd Nis(num, n);
    VectorXd w(n); //NURBS权重
    w << 1, 1, 1, 1, 1, 1, 1;
    N.setWeight(w);
    for (int i = 0; i < num; ++i) {
        Nis.row(i) = N(xis(i)).transpose();
    }
    plt("plots", "save_NURBS_data", xis, Nis, p);
    
    return 0;
}