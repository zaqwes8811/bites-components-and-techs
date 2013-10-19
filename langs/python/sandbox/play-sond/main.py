#!/bin/python
# -*- coding: utf-8 -*-
import sys
from PySide import QtCore, QtGui, QtDeclarative
from PySide.QtCore import QObject, SIGNAL, SLOT, Qt
from PySide.QtGui import QFileDialog



# точка входа
def main():
  """app = QtGui.QApplication(sys.argv)

  # Создание QML формы
  view = QtDeclarative.QDeclarativeView()
  view.setSource(QtCore.QUrl("form.qml"))
  view.setResizeMode(QtDeclarative.QDeclarativeView.SizeRootObjectToView)
  view.show()
  
  # передача объекта в QML
  con = Console()
  context = view.rootContext()
  context.setContextProperty("con", con)
  
  # запуск
  app.exec_() """
if __name__ == "__main__":
#  sys.exit(main())
  main()
