# ============================
# 绘制NURBS样条函数相关图像(3D)
# @author zch
# ============================
from mayavi import mlab
import pickle
import numpy as np
import os

# 设置保存数据和图片的路径并创建文件夹
path_data = './data/nurbs/'
path_figure = './figure/nurbs/'
os.makedirs(path_figure, exist_ok=True)


def plot_Nsurface(sx, sy, sz, P):
    fig = mlab.figure(size=(1600, 1200), bgcolor=(1, 1, 1),
                      fgcolor=(0, 0, 0), figure='N_surface')
    mlab.clf(figure=None)
    s = mlab.mesh(sx, sy, sz,line_width=0.3)
    mlab.axes(xlabel='x', ylabel='y', zlabel='z')
    mlab.outline(s)
    Px = P[0, :]
    Py = P[1, :]
    Pz = P[2, :]
    mlab.points3d(Px, Py, Pz,scale_factor = 0.1)
    Px=np.reshape(Px,(5,5))
    Py=np.reshape(Py,(5,5))
    Pz=np.reshape(Pz,(5,5))
    mlab.mesh(Px,Py,Pz,representation='wireframe',line_width=1)

    mlab.savefig(path_figure+'N_surface.png')
    mlab.show()


if __name__ == "__main__":
    with open(path_data+'N_surface_data.pkl', 'rb') as f:
        sx, sy, sz, P = pickle.load(f)
        plot_Nsurface(np.array(sx), np.array(sy), np.array(sz), np.array(P))
