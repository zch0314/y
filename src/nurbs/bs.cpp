/**
 * Bs类的成员函数
 * @author zch
 * */

#include "bs.h"

Bs::Bs() {
}
Bs::Bs(VectorXd nd, unsigned p_) {
    setNode(nd, p_);
}
Bs::~Bs() {
}
void Bs::setNode(VectorXd nd, unsigned p_) {
    // nd(nd.size() - 1) = nd(nd.size() - 1) + 1e-5;
    node = nd;
    p = p_;
    n = nd.size() - p - 1;
}

double Bs::B_i_p(int i, int p_now, double xi) {
    double y;
    if (p_now >= 1) {
        double L1 = node(i - 1 + p_now) - node(i - 1);
        double L2 = node(i + p_now) - node(i);
        L1 = abs(L1) < 1e-16 ? 1.0 : L1;
        L2 = abs(L2) < 1e-16 ? 1.0 : L2;
        y = (xi - node(i - 1)) / L1 * B_i_p(i, p_now - 1, xi) +
            (node(i + p_now) - xi) / L2 * B_i_p(i + 1, p_now - 1, xi);
    } else {
        if (node(i - 1) <= xi && xi < node(i)) {
            y = 1.0;
        } else {
            y = 0;
        }
    }
    return y;
}

VectorXd Bs::operator()(double xi) {
    VectorXd y(n);
    for (int i = 1; i <= n; ++i) {
        y(i - 1) = B_i_p(i, p, xi);
    }
    return y;
}

VectorXd Bs::operator()(double xi, unsigned p_) {
    int nt = n + (p - p_); //阶数每多一阶，基函数将少一个
    VectorXd y(nt);
    if (p_ <= p) {
        for (int i = 1; i <= nt; ++i) {
            y(i - 1) = B_i_p(i, p_, xi);
        }
    }
    return y;
}

double Bs::dB_i_p(int i, double xi) {
    double L1 = node(i - 1 + p) - node(i - 1);
    double L2 = node(i + p) - node(i);
    L1 = abs(L1) < 1e-16 ? 1.0 : L1;
    L2 = abs(L2) < 1e-16 ? 1.0 : L2;
    return p / L1 * B_i_p(i, p - 1, xi) - p / L2 * B_i_p(i + 1, p - 1, xi);
}

VectorXd Bs::operator[](double xi) {
    VectorXd y(n);
    for (int i = 1; i <= n; ++i) {
        y(i - 1) = dB_i_p(i, xi);
    }
    return y;
}