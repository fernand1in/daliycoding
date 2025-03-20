import numpy as np

# 生成测试信号
fs = 1000  # 采样频率
t = np.linspace(0, 1, fs)  # 时间数组
f1, f2, f3 = 50, 100, 150  # 信号频率
signal = np.sin(2 * np.pi * f1 * t) + 0.5 * np.sin(2 * np.pi * f2 * t) + 0.2 * np.sin(2 * np.pi * f3 * t)

# 添加噪声
noise = 0.1 * np.random.randn(len(t))
signal += noise

# 保存信号数据
np.savetxt('signal_data.txt', np.column_stack((t, signal)), header='Time Signal')

# 计算频谱
fft_result = np.fft.fft(signal)
freq = np.fft.fftfreq(len(signal), 1/fs)
magnitude = np.abs(fft_result)

# 保存频谱数据
np.savetxt('spectrum_data.txt', np.column_stack((freq, magnitude)), header='Frequency Magnitude')

print("频谱图测试数据已生成并保存为 'signal_data.txt' 和 'spectrum_data.txt'")