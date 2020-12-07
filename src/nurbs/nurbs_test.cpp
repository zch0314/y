#include "bs.h"
#include "nurbs.h"
#include "pys.h"
#include <Eigen/Eigen>
#include <cmath>
#include <iostream>

using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::cout;
using std::endl;
const static double Pi = 3.141592653589793;

void nurbs1(Pys &plt) {
    int p = 2;              //设置B样条基函数的阶数（NURBS样条基函数）
    int n = 7;              //设置B样条基函数的个数（NURBS样条基函数）
    VectorXd nd(n + p + 1); //设置B样条基函数的节点
    // nd << 0, 0, 0, 0, 1, 2, 3, 4, 4, 4, 4;
    // nd << 0, 0, 0, 1, 2, 3, 3, 4, 4, 4;
    nd << 0, 0, 0, 1, 2, 3, 4, 5, 5, 5;
    //创建一个B样条基函数
    Bs B(nd, p);
    //给定绘图的点,用于绘制B样条基函数和NURBS基函数图像
    int num = 101;
    VectorXd xis = VectorXd::LinSpaced(num, 0, 5.0 - 1e-5);
    MatrixXd Bis(num, n);
    for (int i = 0; i < num; ++i) {
        Bis.row(i) = B(xis(i)).transpose();
    }
    plt("plots", "save_B_data", xis, Bis, p);
    MatrixXd dBis(num, n);
    for (int i = 0; -i < num; ++i) {
        dBis.row(i) = B[xis(i)].transpose();
    }
    plt("plots", "save_dB_data", xis, dBis, p);

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
    // //绘制NURBS图像
    VectorXd Px = VectorXd::LinSpaced(n, 0, Pi * 5 / 4.0); //节点横坐标
    VectorXd Py1 = Px.array().sin();                       //节点纵坐标
    VectorXd x = Nis * Px;
    VectorXd y1 = Nis * Py1;
    VectorXd Py2 = Py1;
    Py2(3) = Py2(3) - 0.6;
    VectorXd y2 = Nis * Py2;
    plt("plots", "save_N_curve_data", Px, Py1, Py2, x, y1, y2);
}

void nurbs2(Pys &plt) {
    int p = 2;
    int n1 = 5;
    int q = 2;
    int n2 = 5;
    VectorXd ndx(8); //设置B样条基函数的节点
    ndx << 0, 0, 0, 1.0, 2.0, 3.0, 3.0, 3.0;
    VectorXd ndy = ndx;
    VectorXd w2 = VectorXd::Ones(n1 * n2);
    Nurbs N2;
    N2.setNode(ndx, p, ndy, q);
    N2.setWeight(w2);
    int num = 31;
    VectorXd xis = VectorXd::LinSpaced(num, 0, 3.0 - 1e-5);
    VectorXd etas = VectorXd::LinSpaced(num, 0, 3.0 - 1e-5);
    //给定控制点
    MatrixXd P(3, n1 * n2);
    VectorXd C(3);
    C << 3, 2, 6;
    int k = 0;
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < n2; ++j) {
            P(0, k) = i;
            P(1, k) = j;
            P(2, k++) = C(2) - sqrt(pow(i - C(0), 2) + pow(j - C(1), 2)) * 0.2;
        }
        // if (i == 2) {
        //     P(1, k - 5) += 0.6;
        //     P(1, k - 1) -= 0.6;
        // }
    }

    //绘制二维曲面
    MatrixXd sx(num, num), sy(num, num), sz(num, num);
    for (int i = 0; i < num; ++i) {
        for (int j = 0; j < num; ++j) {
            MatrixXd N2_tmp = N2(xis(i), etas(j));
            sx(i, j) = (P.row(0) * N2_tmp)(0);
            sy(i, j) = (P.row(1) * N2_tmp)(0);
            sz(i, j) = (P.row(2) * N2_tmp)(0);
        }
    }
    plt("plots", "save_N_surface_data", sx, sy, sz, n1, n2, P);
}

int main(void) {
    cout << "Test the nurbs plot" << endl;

    Pys plt("./src/nurbs"); //通过类初始化Python解释器
    // nurbs1(plt);
    nurbs2(plt);

    return 0;
}