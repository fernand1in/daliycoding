import numpy as np

# 生成二维信号数据
x = np.linspace(0, 10, 1500)
y1 = np.sin(x)  # 第一维信号（正弦波）
y2 = np.cos(x)  # 第二维信号（余弦波）

# 将两维信号组合成二维信号数据
data = np.column_stack((y1, y2))

# 保存为文本文件
np.savetxt('2d_signal_data.txt', data)

print("二维信号数据已生成并保存为 '2d_signal_data.txt'")