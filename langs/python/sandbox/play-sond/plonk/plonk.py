#!/usr/bin/env python
# -*- coding: utf-8 -*-
# A short script to listen or prelisten to audio.
# Install as a helper in dolphin, so you don't have
# to run a full program just to hear what that
# audio file really is.

# The code is licensed under the GPL, version 2 or later
# Copyright Håvard Gulldahl <havard@gulldahl.no>, 2009

""" 
MyQuestion :
  создаются ли потоки
  работает похоже только с KDE
  Как я понял работает так - в коммандной строке передаем файлы
    их по порядку проигрывает - интерфейс пользователя непонятно какой
  dbus - похоже подает какие-то сообщения
"""

import sys, os.path
import dbus
#from PyQt4 import QtCore, QtGui
#from PyQt4.phonon import Phonon
from PySide import QtCore, QtGui
from PySide.phonon import Phonon

class plonkPlayer(object):
  popuplog = []  # свойство

  # наподобие конструктора
  def __init__(self, app, cutoff=None):
    self.cutoff = cutoff

    # необходимое для проигрывания
    self.player = Phonon.MediaObject(app) 
    # self.player.setCurrentSource(Phonon.MediaSource("/mymusic/barbiegirl.wav"))
    self.speaker = Phonon.AudioOutput(Phonon.MusicCategory, app)  # The AudioOutput class is used to 
      # send data to audio output devices.
    self.wire = Phonon.createPath(self.player, self.speaker)  # соединяем плеер с устройством проигрывания
    #

    app.connect(self.player, QtCore.SIGNAL('totalTimeChanged(qint64)'), self.nowPlaying)
    self.player.setTickInterval(1000) # emit tick() every second
    app.connect(self.player, QtCore.SIGNAL('tick(qint64)'), self.tick)
    self.display = dbus.SessionBus().get_object("org.kde.knotify", "/Notify")

  # очередь проигрывания
  def enqueue(self, soundSources):
    for source in soundSources:
      self.player.enqueue(Phonon.MediaSource(source))

  # проигрываем
  def play(self):
    self.player.play()
    #print "interval: %s" % self.player.tickInterval()

  #
  def nowPlaying(self, totaltime=1):
    sound = unicode(self.player.currentSource().url().toString())
    if sound in self.popuplog: return # we've already showed a popup for this clip
    verb = self.cutoff and "Prelistening to %ss of" % self.cutoff or "Playing"
    msg = "%s %s... (%s)" % (verb, os.path.basename(sound), self.formatTime(totaltime))
      # странный занчек процента
 #method int org.kde.KNotify.event(QString event, QString fromApp, 
 #QVariantList contexts, QString text, QByteArray pixmap, QStringList actions, qlonglong winId)
    i = self.display.event("notification", "kde", [], msg, [0,0,0,0], [], 0, dbus_interface="org.kde.KNotify")
    self.popuplog.append(sound)
    timeout = self.cutoff*1000 - 500
    if timeout > totaltime:
      #print "timeout (%s) > totaltime (%s)" % (timeout, totaltime)
      timeout = totaltime - 500
    QtCore.QTimer.singleShot(timeout, lambda: self.closeNowPlaying(i))

  # 
  def closeNowPlaying(self, noteid):
    self.display.closeNotification(noteid)

  # форматирование времени
  def formatTime(self, millisecs):
    secs = millisecs/1000 % 60
    mins = int(millisecs/1000) / 60
    return '%.2i:%.2i' % (mins, secs)

  # какой-то такт
  def tick(self, millisecs):
    #print "tick: %s" % millisecs
    if self.cutoff is None: return
    if millisecs > self.cutoff*1000:
      #end of prelisten reached
      next = self.next()
      if next is not None:
        self.player.setCurrentSource(next)
        self.player.play()
      else:
        self.player.stop()
        self.player.emit(QtCore.SIGNAL('finished()'))

  # похоже вызыв следующего трека
  def next(self):
    queue = self.player.queue()
    #print "q: %s" % repr(queue)
    if len(queue) == 0: return None
    for q in queue:
      if q != self.player.currentSource():
        return q
    return None

####################

# уже не класс
def gui():
  app = QtGui.QApplication(sys.argv)
  return app

def cli():
  app = QtCore.QCoreApplication(sys.argv)
  return app

# запуск
if __name__ == '__main__':
  if len(sys.argv) == 1:
    print "Usage: %s <audio file(s)>" % sys.argv[0]
    sys.exit(1) 
  app = cli()
  app.setApplicationName('plonk')
  prelistenTime = 10 # prelisten 10 seconds of each clip
  if 'plonkplay' in sys.argv[0].lower():
    prelistenTime = None # play the whole clip
  try:
    player = plonkPlayer(app, cutoff=prelistenTime)  # конструируем
    player.enqueue(sys.argv[1:])  # со второго до конца
    player.play()  # это не тот play(), который библиотечный
    app.connect(player.player, QtCore.SIGNAL('finished()'), app.quit)
    sys.exit(app.exec_())
  except Exception, (e):
    #logging.exception(e)
    app.quit()

# Qt Phonon reference:
# http://doc.trolltech.com/4.4/phonon-mediaobject.html
# PyQt4.Phonon reference:
# http://www.riverbankcomputing.co.uk/static/Docs/PyQt4/html/phonon-mediaobject.html
# knotify reference:
# http://api.kde.org/4.x-api/kdelibs-apidocs/kdeui/html/classKNotification.html
# knotify dbus interfacing:
# http://mvidner.blogspot.com/2008/06/knotify-client.html

