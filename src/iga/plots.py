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
path_data = './data/iga/'
path_figure = './figure/iga/'
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


def save_NURBS_data(x, y, p):  # 保存NURBS样条基函数图像
    with open(path_data+'NURBS_data.pkl', 'wb')as f:
        pickle.dump([x, y, p], f)
        print('Have saved NURBS_data.pkl  ')
    plot_B(x, y, p, 'N')


# 绘图函数


def plot_B(x, y, p, kd):  # 绘制B样条基函数和NURBS基函数
    fig = plt.figure(figsize=[10/2.54, 6/2.54], dpi=250)
    ax = fig.add_subplot(111)
    t = np.array(y)
    ysp = np.max(t)-np.min(t)
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


if __name__ == "__main__":
    with open(path_data+'NURBS_data.pkl', 'rb') as f:
        x, y, p = pickle.load(f)
        plot_B(x, y, p, 'N')
    plt.show()
