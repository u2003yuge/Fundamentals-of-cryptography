import numpy as np
import matplotlib.pyplot as plt

plt.rcParams['font.family'] = 'SimHei'
plt.rcParams['axes.unicode_minus'] = False # 解决坐标轴负号显示问题
# 读取数据文件
with open('test.txt', 'r') as f:
    data = [list(map(float, line.strip().split())) for line in f.readlines()]

# 生成横坐标数组（10到1000均匀分布）
n_points = len(data[0])
x = np.arange(10, 251)

# 定义线条颜色和标签
colors = ['blue', 'green', 'red']
labels = ['弱攻击对', '标准攻击对', '强攻击对']

# 创建图形
plt.figure(figsize=(10, 6))

# 绘制三条折线
for i, (y_values, color, label) in enumerate(zip(data, colors, labels)):
    plt.plot(x, y_values, color=color, label=label, zorder=2)

# 绘制水平参考线
# plt.axhline(9500, color='gray', linestyle='--', linewidth=1, zorder=1)
# plt.axhline(9900, color='gray', linestyle='--', linewidth=1, zorder=1)
for y in [5000,9500, 9900]:
    plt.axhline(y, color='gray', linestyle='--', linewidth=1, zorder=1)
    # 添加水平线数值标签
    plt.text(
        x=40,  # 标签显示在右边界
        y=y, 
        s=str(y),
        ha='left',        # 右对齐
        va='center',       # 垂直居中
        color='gray', 
        backgroundcolor='white',  # 白色背景防止覆盖
        fontsize=10,
        zorder=4
    )
def find_intersections(x_arr, y_arr, target_y):
    """查找折线与水平线的交点"""
    intersections = []
    for i in range(len(y_arr)):
        # 检查当前点是否直接位于目标线上
        if y_arr[i] == target_y:
            intersections.append((x_arr[i], target_y))
        
        # 检查线段是否跨越目标线
        if i < len(y_arr)-1:
            y1, y2 = y_arr[i], y_arr[i+1]
            x1, x2 = x_arr[i], x_arr[i+1]
            
            # 处理跨越的情况
            if (y1 < target_y < y2) or (y2 < target_y < y1):
                t = (target_y - y1) / (y2 - y1)
                x_interp = x1 + t * (x2 - x1)
                intersections.append((x_interp, target_y))
    return intersections

# 查找并标记所有交点
targets = [5000,9500, 9900]
for idx, (y_values, color) in enumerate(zip(data, colors)):
    for target in targets:
        points = find_intersections(x, y_values, target)
        if points:
            x_points = [p[0] for p in points]
            y_points = [p[1] for p in points]
            plt.scatter(
                x_points, y_points, 
                color=color, 
                edgecolors='black',
                s=20,
                zorder=3,
                marker='x'
                # label=f'Intersections (Line {idx+1})' if target == targets[0] else ""
            )
            # 标记交点数值
            for xi, yi in points:
                # 在交点上方显示数值
                plt.text(xi, yi +100,'%.1f' % xi, fontsize=14, color='black', ha='center', va='bottom', zorder=4)

# 设置坐标轴范围和标签
plt.xlim(10, 250)
plt.legend(fontsize=16)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.xlabel('攻击对数', fontsize=18)
plt.ylabel('密钥正确次数', fontsize=18)
plt.title('不同攻击对数下密钥正确次数', fontsize=24)

# 显示图例和网格
# plt.legend()
# plt.grid(True, linestyle='--', alpha=0.7)
plt.tight_layout()
plt.savefig('test_max_vis.png', dpi=300)
plt.show()