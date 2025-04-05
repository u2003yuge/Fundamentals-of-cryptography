import matplotlib.pyplot as plt
plt.rcParams['font.family'] = 'SimHei'
plt.rcParams['axes.unicode_minus'] = False # 解决坐标轴负号显示问题
# 读取数据文件
with open('exam2.txt', 'r') as f:
    lines = f.readlines()

# 将每行数据转换为整数列表
data = [list(map(int, line.strip().split())) for line in lines]

# 创建x轴数据（0到65535）
x = list(range(1,65536))

# 创建画布和坐标轴
plt.figure(figsize=(15, 8))

# 绘制三条折线
for i in range(0,4):
    plt.plot(x, data[i][1:], label=f'{i+3}轮加密')

plt.yscale("log")
# 添加标签和图例
plt.xlabel('输入异或值', fontsize=18)
plt.ylabel('输出异或值最多相同对数', fontsize=18)
plt.title('不同输入异或下输出异或值最多相同对数', fontsize=24)
plt.legend(fontsize=16)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
# 调整布局并保存图片
plt.tight_layout()
plt.savefig('exam2_log.png', dpi=300)

# 关闭图形释放内存
plt.close()