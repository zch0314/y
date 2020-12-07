/** 
 * 定义B样条基函数及其导数方法
 * @author zch
 * */

#ifndef BS_H
#define BS_H
#include <Eigen/Eigen>
#include <iostream>

using Eigen::VectorXd;
using std::cout;
using std::endl;
class Bs {
private:
    int n;         //基函数的个数
    int p;         //基函数的阶数
    VectorXd node; //节点矢量
public:
    Bs();
    Bs(VectorXd nd, unsigned p_);
    ~Bs();
    int getN(void) const { return n; }
    int getP(void) const { return p; }
    void setNode(VectorXd nd, unsigned p_);      //设置节点向量
    double B_i_p(int i, int p_now, double xi);   //计算第i个B样条基函数的值
    VectorXd operator()(double xi);              //计算p阶的B样条基函数的值
    VectorXd operator()(double xi, unsigned p_); //计算p_阶的B样条基函数
    double dB_i_p(int i, double xi);
    VectorXd operator[](double xi); //计算p阶B样条积函数的导数
};

#endif