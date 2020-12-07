# =======================================
# 绘图脚本，并且将计算结果保存到二进制文件中
# @author zch
# =======================================
import matplotlib.pyplot as plt
import numpy as np
import pickle
import os
import datetime
from numpy.core.defchararray import array
from numpy.lib.arraypad import pad
import scipy.io as sio

# 设置保存数据和图片的路径并创建文件夹
path_data = './data/nurbs/'
path_figure = './figure/nurbs/'
os.makedirs(path_data, exist_ok=True)
os.makedirs(path_figure, exist_ok=True)

# 时间戳
curr_time = datetime.datetime.now()
time_str = curr_time.strftime('%Y-%m-%d %H:%M:%S')
print('time: '+time_str)


def save_data(*args):
    if np.size(args) > 1:
        with open(path_data+args[0][0]+'.pkl', 'wb') as f:
            pickle.dump([x for x in args], f)


def save_B_data(x, y, p):  # 保存B样条基函数数据，并绘图
    with open(path_data+'B_data.pkl', 'wb') as f:  # Python 3: open(..., 'wb')
        pickle.dump([x, y, p], f)
        print('Have saved B_data.pkl  ')
    plot_B(x, y, p, 'B')


def save_dB_data(x, y, p):  # 保存B样条基函数数据，并绘图
    with open(path_data+'dB_data.pkl', 'wb') as f:  # Python 3: open(..., 'wb')
        pickle.dump([x, y, p], f)
        print('Have saved dB_data.pkl  ')
    plot_B(x, y, p, 'dB')


def save_NURBS_data(x, y, p):  # 保存NURBS样条基函数图像
    with open(path_data+'NURBS_data.pkl', 'wb')as f:
        pickle.dump([x, y, p], f)
        print('Have saved NURBS_data.pkl  ')
    plot_B(x, y, p, 'N')


def save_N_curve_data(Px, Py1, Py2, x, y1, y2):  # 保存NURBS样条曲线
    with open(path_data+'N_curve_data.pkl', 'wb') as f:
        pickle.dump([Px, Py1, Py2, x, y1, y2], f)
        print('Have saved N_curve_data.pkl  ')
    plot_Ncurve(Px, Py1, x, y1, 'N_curve1')
    plot_Ncurve(Px, Py2, x, y2, 'N_curve2')


def save_N_surface_data(sx, sy, sz, nx, ny, P):
    # 保存为matlab变量
    sio.savemat(path_data+'N_surface_data.mat',
                {'sx': sx, 'sy': sy, 'sz': sz, 'nx': nx, 'ny': ny, 'P': P})
    print('Have saved N_surface_data.mat')
    with open(path_data+'N_surface_data.pkl', 'wb')as f:
        pickle.dump([sx, sy, sz, P], f)
        print('Have saved N_surface_data.pkl')


# 绘图函数


def plot_B(x, y, p, kd):  # 绘制B样条基函数和NURBS基函数
    fig = plt.figure(figsize=[10/2.54, 6/2.54], dpi=250)
    ax = fig.add_subplot(111)
    t = np.array(y)
    ysp=np.max(t)-np.min(t);
    for i in range(0, np.size(t, 1)):
        lbs = r'$\mathrm{%s_{%d,%d}(\it{\xi})}$' % (kd, (i+1), p[0])
        ax.plot(x, t[:, i], label=lbs, lw=1.5)
        ind = np.argmax(t[:, i])
        if i == 0:
            ax.annotate(lbs, xy=(x[ind]+0.1, t[ind, i]-0.07*ysp))
        elif i == np.size(t, 1)-1:
            ax.annotate(lbs, xy=(x[ind]-0.7, t[ind, i]-0.07*ysp))
        else:
            ax.annotate(lbs, xy=(x[ind]-0.4, t[ind, i]+0.03*ysp))
    ax.set_xlabel(r'$\mathrm{\it{\xi}}$')
    ax.set_ylabel(r'$\mathrm{%s_{\it{i,p}}(\it{\xi})}$' % kd)
    ax.set_xlim(0, round(np.max(x)))
    ax.set_ylim(np.min(y), np.max(y))
    
    for label in ax.get_xticklabels()+ax.get_yticklabels():
        label.set_font('Times New Roman')
    fig.subplots_adjust(left=0.13, bottom=0.195, right=0.96,
                        top=0.96, hspace=0.1, wspace=0.1)
    fig.savefig(path_figure+kd+'_fun.png')


def plot_Ncurve(Px, Py, x, y, fglb):  # 绘制NURBS样条
    fig = plt.figure(figsize=[7.25/2.54, 5/2.54], dpi=250)  # 添加画布
    fig.subplots_adjust(left=0.16, bottom=0.21, right=0.96,
                        top=0.96, hspace=0.1, wspace=0.1)
    ax = fig.add_subplot(111)  # 添加图像
    ax.scatter(Px, Py, s=20, marker='o', color='b',
               label=r'$\mathrm{\bf P_{\it i}}$')
    for i in range(0, np.size(Px)):  # 添加点的注释
        ax.annotate(r'$\mathrm{\bf P_{\it %d}}$' %
                    (i+1), xy=(Px[i]-0.1, Py[i]+0.1))
    ax.plot(x, y, lw=1, color='r', label=r'$\mathrm{NURBS}$')
    ax.set_xlabel(r'$\mathrm{\it x}$')
    ax.set_ylabel(r'$\mathrm{\it y}$')
    ax.set_xlim(x[0]-0.1, x[-1]+0.1)
    ax.set_ylim(-1.4, 2)
    ax.legend(loc='lower left')
    for label in ax.get_xticklabels()+ax.get_yticklabels():
        label.set_font('Times New Roman')
    fig.savefig(path_figure+fglb+'.png')


if __name__ == "__main__":
    with open(path_data+'B_data.pkl', 'rb') as f:
        x, y, p = pickle.load(f)
        plot_B(x, y, p, 'B')
    # with open(path_data+'NURBS_data.pkl', 'rb') as f:
    #     x, y, p = pickle.load(f)
    #     plot_B(x, y, p, 'N')
    # with open(path_data+'N_curve_data.pkl', 'rb')as f:
    #     Px, Py1, Py2, x, y1, y2 = pickle.load(f)
    #     plot_Ncurve(Px, Py1, x, y1, 'N_curve1')
    #     plot_Ncurve(Px, Py2, x, y2, 'N_curve2')
    with open(path_data+'dB_data.pkl', 'rb') as f:
        x, y, p = pickle.load(f)
        sio.savemat(path_data+'dB_data.mat', {'x': x, 'y': y})
        plot_B(x, y, p, 'dB')
    plt.show()
