#! /usr/bin/env python3
# -*- coding: utf-8 -*-
#
import sys
from PySide import QtCore, QtGui  # ���������� �������� ������ PyQt
from PySide.QtUiTools import QUiLoader 
from PySide.QtGui import QWidget, QVBoxLayout, QPushButton
from PySide.QtCore import QFile
import mainform
 
def main():
    app = QtGui.QApplication(sys.argv)  # ������ �������� ������ ���������

   # loader = QUiLoader()
   # file = QFile("un.ui")
  #  file.open(QFile.ReadOnly)
   # myWidget = loader.load(file)
  #  file.close()

   # layout = QVBoxLayout()
   # layout.addWidget(myWidget)
    #myWidget.setLayout(layout)
  #  myWidget.show()
    window =  QWidget()
    button1 =  QPushButton("One")
    button2 =  QPushButton("Two")
    button3 =  QPushButton("Three")
    button4 =  QPushButton("Four")
    button5 =  QPushButton("Five")

    layout =  QVBoxLayout()

    layout.addWidget(button1)
    layout.addWidget(button2)
    layout.addWidget(button3)
    layout.addWidget(button4)
    layout.addWidget(button5)

    window.setLayout(layout)
    window.show()
    #qwg = QWidget()
    form = mainform.MyWidget(None)

    form.show()  # ��� ������� �� ����������� ������� ����� � �����������
    app.exec_()  # ��������� ����������
if __name__ == "__main__":
  sys.exit(main())
  
