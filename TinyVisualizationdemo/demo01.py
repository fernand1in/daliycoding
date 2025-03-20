import sys
import sqlite3
import numpy as np
# import matplotlib.pyplot as plt
# from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
# from matplotlib.figure import Figure

from PyQt6.QtWidgets import QApplication, QWidget, QMessageBox
from PyQt6.QtCore import Qt, QPointF
from register_window import Ui_RegisterForm
from signon import Ui_Form  # 登录界面的 UI 类
from sysmain import Ui_mainForm  # 主窗口的 UI 类
from PyQt6 import QtCharts
from PyQt6.QtMultimedia import QMediaDevices, QAudioInput, QAudioFormat, QAudioSource #实现音频读入功能所需的依赖
from PyQt6.QtWidgets import QFileDialog  # 实现保存功能所需的依赖
from PyQt6.QtCore import QTimer

class QmyWidget(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)  # 调用父类构造函数，创建QWidget窗口
        self.ui = Ui_Form()  # 创建登录界面的 UI 对象
        self.ui.setupUi(self)  # 设置 UI
        self.ui.pushButton.clicked.connect(self.login) # 绑定登录按钮的点击事件
        self.ui.pushButton_2.clicked.connect(self.open_register_window)  # 绑定注册按钮的点击事件

    # 按下注册按钮
    def open_register_window(self):
        self.register_window = QWidget()
        self.register_ui = Ui_RegisterForm()
        self.register_ui.setupUi(self.register_window)
        self.register_ui.pushButton_register.clicked.connect(self.register_user)
        self.register_window.show()

    def register_user(self):
        username = self.register_ui.lineEdit_username.text()
        password = self.register_ui.lineEdit_password.text()


        # 连接数据库并插入用户信息
        conn = sqlite3.connect('users.db')
        cursor = conn.cursor()
        try:
            cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)",
                           (username, password))
            conn.commit()
            QMessageBox.information(self.register_window, "注册成功", "用户注册成功！")
            self.register_window.close()
        except sqlite3.Error as e:
            QMessageBox.warning(self.register_window, "注册失败", f"注册失败：{e}")
        finally:
            conn.close()

    def login(self):
        username = self.ui.lineEdit.text()
        password = self.ui.lineEdit_2.text()

        # 连接数据库并验证用户信息
        conn = sqlite3.connect('users.db')
        cursor = conn.cursor()
        cursor.execute("SELECT * FROM users WHERE username = ? AND password = ?", (username, password))
        user = cursor.fetchone()
        conn.close()

        if user:
            self.close()
            self.open_main_window()
        else:
            QMessageBox.warning(self, "登录失败", "用户名或密码错误！")

    def open_main_window(self):
        # 创建主窗口
        self.main_window = QWidget()
        self.main_ui = Ui_mainForm()
        self.main_ui.setupUi(self.main_window)
        self.main_window.setWindowTitle("脑电数据分析工具")
        # tab1 的
        self.main_ui.pushButton_start.clicked.connect(self.init_audio_visualization)
        self.main_ui.pushButton_clear.clicked.connect(self.clear_audio_visualization)
        self.main_ui.pushButton_stop.clicked.connect(self.stop_audio_visualization)
        self.main_ui.pushButton_save.clicked.connect(self.save_audio_visualization)

        #tab2
        self.main_ui.pushButton_load_1d.clicked.connect(self.load_1d_signal)
        self.main_ui.pushButton_pushButton_load_2d.clicked.connect(self.load_2d_signal)
        self.main_ui.pushButton_stop_2.clicked.connect(self.stop_signal_visualization)
        self.main_ui.pushButton_save_2.clicked.connect(self.save_signal_visualization)
        self.main_window.show()

    def init_audio_visualization(self):
        # 创建音频图表
        self.chart_audio = QtCharts.QChart()
        # self.series_audio = QtCharts.QLineSeries()
        self.series_audio = QtCharts.QSplineSeries()  # 使用样条曲线系列
        self.chart_audio.addSeries(self.series_audio)
        self.chart_audio.legend().hide()
        self.audio_axisX = QtCharts.QValueAxis()
        self.audio_axisX.setRange(0, 2000)
        self.audio_axisX.setLabelFormat("%g")
        # self.audio_axisX.setTitleText("Samples")
        self.audio_axisY = QtCharts.QValueAxis()
        self.audio_axisY.setRange(-1, 1)
        # self.audio_axisY.setTitleText("Audio level")
        self.chart_audio.addAxis(self.audio_axisX, Qt.AlignmentFlag.AlignBottom)
        self.chart_audio.addAxis(self.audio_axisY, Qt.AlignmentFlag.AlignLeft)
        self.series_audio.attachAxis(self.audio_axisX)
        self.series_audio.attachAxis(self.audio_axisY)

        # 创建音频输入设备
        self.inputDevice = QMediaDevices.defaultAudioInput()
        # self.chart_audio.setTitle("Data from the microphone (" + self.inputDevice.description() + ')')
        self.formatAudio = QAudioFormat()
        self.formatAudio.setSampleRate(8000)
        self.formatAudio.setChannelCount(1)
        self.formatAudio.setSampleFormat(QAudioFormat.SampleFormat.UInt8)
        self.m_audioSource = QAudioSource(self.inputDevice, self.formatAudio)
        self.m_audioSource.setBufferSize(200)
        self.ioDevice = self.m_audioSource.start()
        self.ioDevice.readyRead.connect(self.do_IO_readyRead)

        # 初始化音频数据缓冲区
        self.sampleCount = 2000
        # 减少采样点可以使得间距更大
        self.m_buffer = [QPointF(mm, 0) for mm in range(self.sampleCount)]

        # 将图表添加到主窗口的 QChartView 控件中
        self.main_ui.QChartView.setChart(self.chart_audio)
        # 初始化暂停标志
        self.is_paused = False


    # 实现清空功能
    def clear_audio_visualization(self):
        self.chart_audio = QtCharts.QChart()
        self.series_audio = QtCharts.QLineSeries()
        self.chart_audio.addSeries(self.series_audio)
        self.chart_audio.legend().hide()
        self.audio_axisX = QtCharts.QValueAxis()
        self.audio_axisX.setRange(0, 2000)
        self.audio_axisX.setLabelFormat("%g")
        # self.audio_axisX.setTitleText("Samples")
        self.audio_axisY = QtCharts.QValueAxis()
        self.audio_axisY.setRange(-1, 1)
        # self.audio_axisY.setTitleText("Audio level")
        self.chart_audio.addAxis(self.audio_axisX, Qt.AlignmentFlag.AlignBottom)
        self.chart_audio.addAxis(self.audio_axisY, Qt.AlignmentFlag.AlignLeft)
        self.series_audio.attachAxis(self.audio_axisX)
        self.series_audio.attachAxis(self.audio_axisY)
        self.main_ui.QChartView.setChart(self.chart_audio)

    def stop_audio_visualization(self):
        # 效果一 四个按钮
        # 切换暂停状态
        # self.is_paused = True
        # 效果二 三个按钮
        self.is_paused = not self.is_paused
        if self.is_paused:
            self.main_ui.pushButton_stop.setText("继续")
        else:
            self.main_ui.pushButton_stop.setText("暂停")

    # 在类QmyWidget中添加以下方法
    def save_audio_visualization(self):
        # 弹出文件保存对话框
        file_path, _ = QFileDialog.getSaveFileName(
            self.main_window,
            "保存图表",
            "",
            "PNG图片 (*.png);;JPEG图片 (*.jpeg *.jpg)"
        )

        if file_path:
            # 获取当前图表视图的截图
            pixmap = self.main_ui.QChartView.grab()
            # 保存图片到指定路径
            success = pixmap.save(file_path)
            if success:
                QMessageBox.information(self.main_window, "保存成功", "图表已成功保存！")
            else:
                QMessageBox.warning(self.main_window, "保存失败", "无法保存文件，请检查路径和权限。")

    def do_IO_readyRead(self):
        if self.is_paused:  # 如果暂停标志为True，则不更新图表
            return
        bytes = self.m_audioSource.bytesAvailable()
        buffer = self.ioDevice.read(bytes)
        maxSize = len(buffer)

        # 移动曲线
        start = 0
        resolution = 4
        availableSamples = int(maxSize / resolution)
        if availableSamples < self.sampleCount:
            start = self.sampleCount - availableSamples
            for s in range(start):
                self.m_buffer[s].setY(self.m_buffer[s + availableSamples].y())
                
        # 添加新的点
        tmp = 0
        for ss in range(start, self.sampleCount):
            v = buffer[tmp]
            tmp += resolution
            self.m_buffer[ss].setY((v - 128) / 128 * 2)
            #  乘以一个值来使得波峰更大

        self.series_audio.replace(self.m_buffer)
    # 一维可视化
    def load_1d_signal(self):
        file_path, _ = QFileDialog.getOpenFileName(
            self.main_window,
            "打开一维信号文件",
            "",
            "文本文件 (*.txt);;CSV文件 (*.csv)"
        )

        if file_path:
            try:
                # 读取文件数据
                data = np.loadtxt(file_path)
                self.sampleCount = len(data)
                self.m_buffer = [QPointF(i, data[i]) for i in range(self.sampleCount)]

                # 创建新图表和系列（专用于一维信号）
                self.series_1d = QtCharts.QSplineSeries()
                self.chart_1d = QtCharts.QChart()
                self.chart_1d.addSeries(self.series_1d)
                self.chart_1d.legend().hide()

                # 设置坐标轴
                self.axisX_1d = QtCharts.QValueAxis()
                self.axisX_1d.setRange(0, 100)  # 初始显示前100个数据点
                self.axisY_1d = QtCharts.QValueAxis()
                self.axisY_1d.setRange(min(data), max(data))

                # 将坐标轴关联到图表

                self.chart_1d.addAxis(self.axisX_1d, Qt.AlignmentFlag.AlignBottom)
                self.chart_1d.addAxis(self.axisY_1d, Qt.AlignmentFlag.AlignLeft)
                self.series_1d.attachAxis(self.axisX_1d)
                self.series_1d.attachAxis(self.axisY_1d)

                # 更新数据点
                self.series_1d.replace(self.m_buffer)

                # 将图表设置到 tab_2 的 graphicsView
                self.main_ui.graphicsView.setChart(self.chart_1d)

                self.is_paused = False#初始化暂停标志

                # 初始化定时器，用于动态更新图表
                self.timer_1d = QTimer(self.main_window)
                self.timer_1d.timeout.connect(self.update_1d_chart)
                self.current_start = 0
                self.timer_1d.start(100)  # 每50毫秒更新一次

            except Exception as e:
                QMessageBox.warning(self.main_window, "读取失败", f"无法读取文件：{e}")

        # 二维信号可视化

    def load_2d_signal(self):
        file_path, _ = QFileDialog.getOpenFileName(
            self.main_window,
            "打开二维信号文件",
            "",
            "文本文件 (*.txt);;CSV文件 (*.csv)"
        )
        if file_path:
            try:
                # 读取文件数据
                data = np.loadtxt(file_path)
                if data.ndim != 2 or data.shape[1] != 2:
                    raise ValueError("文件数据不是二维信号格式（每行应包含两个值）")

                self.sampleCount = data.shape[0]
                self.m_buffer_x = [QPointF(i, data[i][0]) for i in range(self.sampleCount)]
                self.m_buffer_y = [QPointF(i, data[i][1]) for i in range(self.sampleCount)]

                # 创建新图表和系列（专用于二维信号）
                self.series_2d_x = QtCharts.QSplineSeries()
                self.series_2d_y = QtCharts.QSplineSeries()
                self.series_2d_x.setName("X 信号")
                self.series_2d_y.setName("Y 信号")

                self.chart_2d = QtCharts.QChart()
                self.chart_2d.addSeries(self.series_2d_x)
                self.chart_2d.addSeries(self.series_2d_y)
                self.chart_2d.legend().setVisible(True)

                # 设置坐标轴
                self.axisX_2d = QtCharts.QValueAxis()
                self.axisX_2d.setRange(0, 100)  # 初始显示前100个数据点
                self.axisY_2d = QtCharts.QValueAxis()
                self.axisY_2d.setRange(min(min(data[:, 0]), min(data[:, 1])), max(max(data[:, 0]), max(data[:, 1])))

                # 将坐标轴关联到图表
                self.chart_2d.addAxis(self.axisX_2d, Qt.AlignmentFlag.AlignBottom)
                self.chart_2d.addAxis(self.axisY_2d, Qt.AlignmentFlag.AlignLeft)
                self.series_2d_x.attachAxis(self.axisX_2d)
                self.series_2d_x.attachAxis(self.axisY_2d)
                self.series_2d_y.attachAxis(self.axisX_2d)
                self.series_2d_y.attachAxis(self.axisY_2d)

                # 更新数据点
                self.series_2d_x.replace(self.m_buffer_x)
                self.series_2d_y.replace(self.m_buffer_y)

                # 将图表设置到 tab_2 的 graphicsView
                self.main_ui.graphicsView.setChart(self.chart_2d)

                self.is_paused = False  # 初始化暂停标志

                if self.is_paused:
                    self.main_ui.pushButton_stop_2.setText("继续")
                else:
                    self.main_ui.pushButton_stop_2.setText("暂停")

                    # 初始化定时器，用于动态更新图表
                self.timer_2d = QTimer(self.main_window)
                self.timer_2d.timeout.connect(self.update_2d_chart)
                self.current_start = 0
                self.timer_2d.start(50)  # 每50毫秒更新一次

            except Exception as e:
                QMessageBox.warning(self.main_window, "读取失败", f"无法读取文件：{e}")
    def update_1d_chart(self):
        if hasattr(self, 'axisX_1d') and hasattr(self, 'sampleCount'):
            # 移动显示窗口
            self.current_start += 1
            if self.current_start >= self.sampleCount:
                self.current_start = 0

            self.axisX_1d.setRange(self.current_start, self.current_start + 100)

        # 更新二维信号图表
    def update_2d_chart(self):
        if hasattr(self, 'axisX_2d') and hasattr(self, 'sampleCount'):
            # 移动显示窗口
            self.current_start += 1
            if self.current_start >= self.sampleCount:
                self.current_start = 0

            self.axisX_2d.setRange(self.current_start, self.current_start + 100)

    def stop_signal_visualization(self):
        self.is_paused = not self.is_paused
        if self.is_paused:
            self.main_ui.pushButton_stop_2.setText("继续")
            if hasattr(self, 'timer_1d') and self.timer_1d.isActive():
                self.timer_1d.stop()
            if hasattr(self, 'timer_2d') and self.timer_2d.isActive():
                self.timer_2d.stop()
        else:
            self.main_ui.pushButton_stop_2.setText("暂停")
            if hasattr(self, 'timer_1d'):
                self.timer_1d.start(50)
            if hasattr(self, 'timer_2d'):
                self.timer_2d.start(50)
    def save_signal_visualization(self):
        file_path, _ = QFileDialog.getSaveFileName(
            self.main_window,
            "保存信号可视化",
            "",
            "PNG图片 (*.png);;JPEG图片 (*.jpeg *.jpg)"
        )
        if file_path:
            # 获取当前 graphicsView 的截图
            pixmap = self.main_ui.graphicsView.grab()
            # 保存图片到指定路径
            success = pixmap.save(file_path)
            if success:
                QMessageBox.information(self.main_window, "保存成功", "信号可视化已成功保存！")
            else:
                QMessageBox.warning(self.main_window, "保存失败", "无法保存文件，请检查路径和权限。")


if __name__ == '__main__':
    app = QApplication(sys.argv)
    myWidget = QmyWidget()
    myWidget.show()
    sys.exit(app.exec())