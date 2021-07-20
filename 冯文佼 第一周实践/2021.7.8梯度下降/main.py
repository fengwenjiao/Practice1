
from numpy import *

# 数据集大小 即20个数据点
m = 20
# x的坐标以及对应的矩阵
X0 = ones((m, 1))  # 生成一个m行1列的向量，也就是x0，全是1
X1 = arange(1, m+1).reshape(m, 1)  # 生成一个m行1列的向量，也就是x1，从1到m
X = hstack((X0, X1))  # 按照列堆叠形成数组，其实就是样本数据
# 对应的y坐标
Y = array([
    3, 4, 5, 5, 2, 4, 7, 8, 11, 8, 12,
    11, 13, 13, 16, 17, 18, 17, 19, 21
]).reshape(m, 1)
# 学习率
alpha = 0.01

# 定义代价函数
# 损失函数（loss function）或代价函数（cost function）是将随机事件或其有关随机变量的取值映射为非负实数以表示该随机事件的“风险”或“损失”的函数
def cost_function(theta, X, Y):
    diff = dot(X, theta) - Y  # dot() 数组需要像矩阵那样相乘，就需要用到dot()
    return (1 / (2 * m)) * dot(diff.transpose(), diff)#J(theta)

# 定义代价函数对应的梯度函数
def gradient_function(theta, X, Y):
    diff = dot(X, theta) - Y
    return (1 / m) * dot(X.transpose(), diff)#▲J(theta)
    # 梯度下降迭代

def gradient_descent(X, Y, alpha):
    # 将[1,1]变为2行1列的形式
    theta = array([1, 1]).reshape(2, 1)
    # 得到代价函数的初始梯度
    gradient = gradient_function(theta, X, Y)
    # 不断迭代的过程
    while not all(abs(gradient) <= 1e-5):
        # 更新迭代公式
        theta = theta - alpha * gradient
        # 更新迭代所用的梯度
        gradient = gradient_function(theta, X, Y)
    return theta

# 梯度下降最终的结果
optimal = gradient_descent(X, Y, alpha)
print('optimal:', optimal)
print('cost function:', cost_function(optimal, X, Y)[0][0])

# 根据数据画出对应的图像
def plot(X, Y, theta):
    import matplotlib.pyplot as plt
    ax = plt.subplot(111)  # 这是我改的
    ax.scatter(X, Y, s=30, c="red", marker="s")
    plt.xlabel("X")
    plt.ylabel("Y")
    x = arange(0, 21, 0.2)  # x的范围
    y = theta[0] + theta[1]*x
    ax.plot(x, y)
    plt.show()

plot(X1, Y, optimal)