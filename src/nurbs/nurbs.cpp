/**
 * Nurbs类成员函数
 * @author zch
 * */

#include "nurbs.h"
#include <cmath>
#include <iostream>
using std::cout;
using std::endl;

Nurbs::Nurbs() {
}

Nurbs::~Nurbs() {
}

bool Nurbs::setWeight(VectorXd w_) {
    weight = w_.transpose();
    return weight.cols() == nodeNum;
}

VectorXd Nurbs::operator()(double xi) {
    VectorXd y(nodeNum);
    if (N == 1) {
        VectorXd bx = bss[0](xi);
        unsigned nx = bss[0].getN();
        double W = (weight * bx)(0);
        for (int i = 0; i < nx; ++i) {
            y(i) = bx(i) * weight(0, i) / W;
        }
    }
    return y;
}

VectorXd Nurbs::operator()(double xi, double eta) {
    VectorXd y(nodeNum);
    if (N == 2) {
        VectorXd bx = bss[0](xi);
        VectorXd by = bss[1](eta);
        unsigned nx = bss[0].getN();
        unsigned ny = bss[1].getN();
        VectorXd tmp(nodeNum);
        for (int i = 0; i < nx; ++i) {
            tmp.segment(i * ny, ny) = bx(i) * by;
        }
        double W = (weight * tmp)(0);
        for (int i = 0; i < nx; ++i) {
            for (int j = 0; j < ny; ++j) {
                y(i * ny + j) = bx(i) * by(j) * weight(0, i * ny + j) / W;
            }
        }
    }
    return y;
}

VectorXd Nurbs::operator[](double xi) {
    VectorXd y(nodeNum);
    if (N == 1) {
        VectorXd bx = bss[0](xi);
        VectorXd dBx = bss[0][xi];
        double W = (weight * bx)(0);
        double dW = (weight * dBx)(0);
        y = (dBx * W - bx * dW) / (W * W);
    }
    return y;
}

VectorXd Nurbs::Diff_xi(double xi, double eta) {
    VectorXd y(nodeNum);
    if (N == 2) {
        VectorXd bx = bss[0](xi);
        VectorXd dBx = bss[0][xi];
        VectorXd by = bss[1](eta);
        unsigned nx = bss[0].getN();
        unsigned ny = bss[1].getN();
        VectorXd Wtmp(nodeNum);
        VectorXd dWtmp(nodeNum);
        for (int i = 0; i < nx; ++i) {
            Wtmp.segment(i * ny, ny) = bx(i) * by;
            dWtmp.segment(i * ny, ny) = dBx(i) * by;
        }
        double W = (weight * Wtmp)(0);
        double dW = (weight * dWtmp)(0);
        for (int i = 0; i < nx; ++i) {
            for (int j = 0; j < ny; ++j) {
                y(i * ny + j) = weight(0, i * ny + j) * by(j) *
                                (dBx(i) * W - bx(i) * dW) / (W * W);
            }
        }
    }
    return y;
}

VectorXd Nurbs::Diff_eta(double xi, double eta) {
    VectorXd y(nodeNum);
    if (N == 2) {
        VectorXd bx = bss[0](xi);
        VectorXd by = bss[1](eta);
        VectorXd dBy = bss[1][xi];
        unsigned nx = bss[0].getN();
        unsigned ny = bss[1].getN();
        VectorXd Wtmp(nodeNum);
        VectorXd dWtmp(nodeNum);
        for (int i = 0; i < nx; ++i) {
            Wtmp.segment(i * ny, ny) = bx(i) * by;
            dWtmp.segment(i * ny, ny) = bx(i) * dBy;
        }
        double W = (weight * Wtmp)(0);
        double dW = (weight * dWtmp)(0);
        for (int i = 0; i < nx; ++i) {
            for (int j = 0; j < ny; ++j) {
                y(i * ny + j) = weight(0, i * ny + j) * bx(i) *
                                (dBy(j) * W - by(j) * dW) / (W * W);
            }
        }
    }
    return y;
}