# Form implementation generated from reading ui file 'register_window.ui'
#
# Created by: PyQt6 UI code generator 6.7.1
#
# WARNING: Any manual changes made to this file will be lost when pyuic6 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt6 import QtCore, QtGui, QtWidgets


class Ui_RegisterForm(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(800, 600)
        Form.setMinimumSize(QtCore.QSize(800, 600))
        Form.setMaximumSize(QtCore.QSize(800, 600))
        self.label_username = QtWidgets.QLabel(parent=Form)
        self.label_username.setGeometry(QtCore.QRect(220, 230, 158, 78))
        font = QtGui.QFont()
        font.setPointSize(15)
        self.label_username.setFont(font)
        self.label_username.setObjectName("label_username")
        self.lineEdit_username = QtWidgets.QLineEdit(parent=Form)
        self.lineEdit_username.setGeometry(QtCore.QRect(310, 250, 271, 41))
        self.lineEdit_username.setObjectName("lineEdit_username")
        self.label_password = QtWidgets.QLabel(parent=Form)
        self.label_password.setGeometry(QtCore.QRect(220, 310, 158, 78))
        font = QtGui.QFont()
        font.setPointSize(15)
        self.label_password.setFont(font)
        self.label_password.setObjectName("label_password")
        self.lineEdit_password = QtWidgets.QLineEdit(parent=Form)
        self.lineEdit_password.setGeometry(QtCore.QRect(310, 330, 271, 41))
        self.lineEdit_password.setObjectName("lineEdit_password")
        self.pushButton_register = QtWidgets.QPushButton(parent=Form)
        self.pushButton_register.setGeometry(QtCore.QRect(320, 440, 191, 71))
        self.pushButton_register.setObjectName("pushButton_register")

        self.retranslateUi(Form)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "Form"))
        self.label_username.setText(_translate("Form", "用户名"))
        self.label_password.setText(_translate("Form", "密码"))
        self.pushButton_register.setText(_translate("Form", "注册"))
from PyQt6.QtCharts import QChartView
