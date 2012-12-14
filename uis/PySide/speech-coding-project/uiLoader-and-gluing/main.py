#!/usr/bin/python
# -*- coding: utf-8 -*-
from PySide import QtCore, QtGui, QtDeclarative

class Console(QtCore.QObject):
  @QtCore.Slot(str)
  @QtCore.Slot('double')
  def output(self, s):
    print s
  @QtCore.Slot(str)
  def outputStr(self, s):
    print s

  @QtCore.Slot('double')
  def outputFloat(self, x):
    print x

if __name__ == '__main__':
  import sys

  app = QtGui.QApplication(sys.argv)
  view = QtDeclarative.QDeclarativeView()

   # instantiate the Python object
  con = Console()
   # expose the object to QML
  context = view.rootContext()
  context.setContextProperty("con", con)

  view.setSource(QtCore.QUrl('view.qml'))
  view.show()
  sys.exit(app.exec_())