# 使用plt.show()过程中出现阻塞的问题

在使用matplotlib的过程中，通常会画很多图，但在使用了plt.show()后会发生阻塞。因为matplotlib库的显示模式默认为阻塞模式（block)，需要程序继续运行就需要关闭图片窗口，如果需要动态展示多张图片就需要使用交互模式（interactive），就需要在程序中使用plt.ion()这个函数，即使在脚本中遇到plt.show(),代码还会继续执行。

例子：

~~~python
    import matplotlib.pyplot as plt
    plt.ion()    # 打开交互模式
    # 同时打开两个窗口显示图片
    plt.figure()  #图片一
    plt.imshow(i1)
    plt.figure()    #图片二
    plt.imshow(i2)
    # 显示前关掉交互模式
    plt.ioff()
    plt.show()
~~~



# 三维绘图工具mayavi

安装：

>   pip install mayavi

示例

~~~python
# Create the data.
from numpy import pi, sin, cos, mgrid
dphi, dtheta = pi/250.0, pi/250.0
[phi,theta] = mgrid[0:pi+dphi*1.5:dphi,0:2*pi+dtheta*1.5:dtheta]
m0 = 4; m1 = 3; m2 = 2; m3 = 3; m4 = 6; m5 = 2; m6 = 6; m7 = 4;
r = sin(m0*phi)**m1 + cos(m2*phi)**m3 + sin(m4*theta)**m5 + cos(m6*theta)**m7
x = r*sin(phi)*cos(theta)
y = r*cos(phi)
z = r*sin(phi)*sin(theta)

# View it.
from mayavi import mlab
s = mlab.mesh(x, y, z)
mlab.show()
~~~

