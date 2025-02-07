import sys
from PyQt6.QtWidgets import QApplication, QWidget, QMessageBox
from PyQt6.QtCore import Qt, QPointF
from signon import Ui_Form  # 登录界面的 UI 类
from sysmain import Ui_mainForm  # 主窗口的 UI 类
from PyQt6 import QtCharts
from PyQt6.QtMultimedia import QMediaDevices, QAudioInput, QAudioFormat, QAudioSource

class QmyWidget(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)  # 调用父类构造函数，创建QWidget窗口
        self.ui = Ui_Form()  # 创建登录界面的 UI 对象
        self.ui.setupUi(self)  # 设置 UI

        self.initUI()  # 初始化界面

    def initUI(self):
        # 绑定登录按钮的点击事件
        self.ui.pushButton.clicked.connect(self.login)

    def login(self):
        # 获取用户名和密码
        username = self.ui.lineEdit.text()
        password = self.ui.lineEdit_2.text()

        # 模拟登录验证
        if username == "admin" and password == "******":
            self.close()  # 关闭登录窗口
            self.open_main_window()  # 打开主窗口
        else:
            QMessageBox.warning(self, "登录失败", "用户名或密码错误！")

    def open_main_window(self):
        # 创建主窗口
        self.main_window = QWidget()
        self.main_ui = Ui_mainForm()
        self.main_ui.setupUi(self.main_window)

        self.main_ui.pushButton_start.clicked.connect(self.init_audio_visualization)

        self.main_window.show()

    def init_audio_visualization(self):
        # 创建音频图表
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

    def do_IO_readyRead(self):
        # Returns the amount of audio data available to read in bytes.
        bytes = self.m_audioSource.bytesAvailable()
        # Reads at most maxSize bytes from the device, and returns the data read as a QByteArray.
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


if __name__ == '__main__':
    app = QApplication(sys.argv)
    myWidget = QmyWidget()
    myWidget.show()
    sys.exit(app.exec())