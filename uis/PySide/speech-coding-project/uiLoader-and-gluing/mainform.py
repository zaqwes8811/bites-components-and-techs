#! /usr/bin/env python3
# -*- coding: utf-8 -*-
from PySide import QtCore, QtGui  # подключает основные модули PyQt
from PySide.QtUiTools import QUiLoader 
from PySide.QtGui import QWidget, QVBoxLayout
from PySide.QtCore import QFile
 
# прототип главной формы
class MainForm(QtGui.QDialog):
     # конструктор
    def __init__(self):
        super(MainForm, self).__init__()
        loader = QUiLoader()
        file = QFile("un.ui")
        file.open(QFile.ReadOnly)
        myWidget = loader.load(file, self)
        file.close()

        #layout = QVBoxLayout()
        #layout.addWidget(myWidget)
        #self.setLayout(layout)

    def setLabelText(self):
        self.label.setText("New label text")
		
class MyWidget(QWidget):
    def __init__(self, parent):
        #super(QWidget, self).__init__(parent)
        QWidget.__init__(self)
        loader = QUiLoader(parent)
        file = QFile("un.ui")
        file.open(QFile.ReadOnly)
        
        myWidget = loader.load(file, self)
        file.close()
 
        myWidget.show()

        layout = QVBoxLayout()
        layout.addWidget(myWidget)
        self.setLayout(layout)
        self.show()
		
        window =  QWidget()
        button1 =  QtGui.QPushButton("One")
        window.show()
        layout =  QVBoxLayout()
        layout.addWidget(button1)
        window.setLayout(layout)
        #window.show()