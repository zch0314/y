/**
 * 打开python解释器，调用matplotlib绘图
 * @author zch
 * */
#ifndef PYS_H
#define PYS_H
#include <Eigen/Eigen>
#include <Python.h>
#include <iostream>
#include <list>
#include <string>
// #include
using Eigen::VectorXd;
using std::cout;
using std::endl;
using std::list;
using std::string;

class Pys {
private:
    list<PyObject *> argLsts;

public:
    Pys(string path) {
        // 初始化python解释器
        Py_Initialize();
        if (!Py_IsInitialized()) {
            throw "Open Python error!";
        }
        //导入模块
        PyRun_SimpleString("import sys");
        string str = "sys.path.append('" + path + "')";
        PyRun_SimpleString(str.c_str());
        cout << "The Python interpreter has been started!" << endl;
    }

    ~Pys() {
        // 结束python解释器
        Py_Finalize();
        cout << "Close the Python interpreter!" << endl;
    }
    //可以传递任意多个Eigen参数
    template <class T, class... U>
    void operator()(string module, string dict, T &lst, U... lsts) {
        argLsts.push_back(cpp2pyo(lst));
        (*this)(module, dict, lsts...); //进行递归,相当于调用operator()函数
    }
    //结束递归
    void operator()(string module, string dict) {
        int n = argLsts.size();
        PyObject *argList = PyTuple_New(n);
        int i = 0;
        for (auto it : argLsts) {
            PyTuple_SetItem(argList, i++, it);
        }
        PyObject *pModule = PyImport_ImportModule(module.c_str());
        if (!pModule) {
            throw "Cannot open python file!";
        }
        PyObject *pDict = PyModule_GetDict(pModule);
        if (!pDict) {
            throw "Cannot get dict!";
        }
        PyObject *fun = PyDict_GetItemString(pDict, dict.c_str());
        PyObject_CallObject(fun, argList); //调用python函数
        Py_DECREF(fun);
        argLsts.clear(); //清空参数链表
    }
    // 传入字符串类型
    PyObject *cpp2pyo(string s) {
        PyObject *lst = PyList_New(1);
        PyList_SetItem(lst, 0, Py_BuildValue("s", s.c_str()));
        return lst;
    }
    //传入浮点数
    PyObject *cpp2pyo(double d) {
        PyObject *lst = PyList_New(1);
        PyList_SetItem(lst, 0, Py_BuildValue("d", d));
        return lst;
    }
    //将向量传入PyObject变量
    PyObject *cpp2pyo(VectorXd &v) {
        PyObject *lst = PyList_New(v.size());
        for (int i = 0; i < v.size(); ++i) {
            PyList_SetItem(lst, i, Py_BuildValue("d", v(i)));
        }
        return lst;
    }
    //将矩阵传入PyObject变量
    PyObject *cpp2pyo(MatrixXd &m) {
        PyObject *lst = PyList_New(0);
        int rs = m.rows();
        int cs = m.cols();
        for (int i = 0; i < rs; ++i) {
            PyObject *temp = PyList_New(cs);
            for (int j = 0; j < cs; ++j) {
                PyList_SetItem(temp, j, Py_BuildValue("d", m(i, j)));
            }
            PyList_Append(lst, temp);
        }
        return lst;
    }
};

#endif