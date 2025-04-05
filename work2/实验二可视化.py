import matplotlib.pyplot as plt

plt.rcParams['font.family'] = 'SimHei'
plt.rcParams['axes.unicode_minus'] = False # 解决坐标轴负号显示问题
# 读取数据文件
with open('out.txt', 'r') as f:
    lines = f.readlines()

# 将每行数据转换为整数列表
data = [list(map(int, line.strip().split())) for line in lines]

# 创建x轴数据（0到65535）
x = list(range(1,65536))

# 创建画布和坐标轴
plt.figure(figsize=(15, 8))

# 绘制三条折线
labels = ['正确密钥', '相似猜测', '全零猜测']
for i in range(0,3):
    plt.plot(x, data[i][1:], label=labels[i])

# 添加标签和图例
plt.xlabel('输出异或值', fontsize=20)
plt.ylabel('频数', fontsize=20)
plt.title('不同猜测密钥的输出异或值分布', fontsize=24)
plt.legend(fontsize=18)
plt.xticks(fontsize=18)
plt.yticks(fontsize=18)
plt.legend(fontsize=18)

# 调整布局并保存图片
plt.tight_layout()
plt.savefig('exam1.png', dpi=300)

# 关闭图形释放内存
plt.close()