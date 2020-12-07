/**
 * NURBS基函数类
 * @author zch
 * */
#ifndef NURBS_H
#define NURBS_H

#include "bs.h"
#include <Eigen/Eigen>
#include <vector>
using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::vector;

class Nurbs {
private:
    unsigned N = 0;           //记录nurbs基函数的维度
    unsigned nodeNum = 1;     //节点的总个数
    vector<Bs> bss;           //存储B样条基函数
    bool isNotSetNode = true; //判断是否给节点向量赋值
    MatrixXd weight;          //NURBS权重

public:
    //通过迭代的方法设置NURBS样条基函数的节点矢量
    template <class... U>
    bool setNode(VectorXd nd, int p_, U... args) {
        if (isNotSetNode) {
            bss.push_back(Bs(nd, p_)); //添加B样条基函数
            return setNode(args...);
        }
        return false;
    }

private:
    bool setNode() {
        isNotSetNode = false;
        N = bss.size();
        for (auto it : bss) {
            nodeNum *= it.getN();
        }
        return true;
    }

public:
    Nurbs();
    ~Nurbs();
    bool setWeight(VectorXd w_);                //设置NURBS权重
    VectorXd operator()(double xi);             //计算一维NURBS样条基函数值
    VectorXd operator()(double xi, double eta); //计算二维NURBS样条基函数指
    VectorXd operator[](double xi);             //一维NURBS样条基函数导数
    VectorXd Diff_xi(double xi, double eta);    //对变量xi的偏微分
    VectorXd Diff_eta(double xi, double eta);   //对变量eta的偏微分
};

#endif