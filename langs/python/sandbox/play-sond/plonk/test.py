#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from PySide import QtCore, QtGui
from PySide.phonon import Phonon

# запуск
if __name__ == '__main__':
  app = QtCore.QCoreApplication(sys.argv)
  app.setApplicationName('plonk')
  try:
    mediaObject = Phonon.MediaObject(app)
    mediaObject.setCurrentSource(Phonon.MediaSource("/home/zaqwes/Projects/GitRepos/plonk/bluzz.wav"))
    audioOutput = Phonon.AudioOutput(Phonon.MusicCategory, app)
    path = Phonon.createPath(mediaObject, audioOutput)
    mediaObject.play()
    #player = plonkPlayer(app, cutoff=prelistenTime)  # конструируем
    #player.play()  # это не тот play(), который библиотечный
    sys.exit(app.exec_())
  except Exception, (e):
    #logging.exception(e)
    app.quit()
