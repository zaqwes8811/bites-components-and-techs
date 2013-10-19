#!/usr/bin/env python
# -*- coding: utf-8 -*-
import pyaudio
import wave
import sys

chunk = 1024

if len(sys.argv) < 2:
    print "Plays a wave file.\n\n" +\
          "Usage: %s filename.wav" % sys.argv[0]
    sys.exit(-1)

wf = wave.open(sys.argv[1], 'rb')

p = pyaudio.PyAudio()

# open stream
stream = p.open(format =
                p.get_format_from_width(wf.getsampwidth()),
                channels = wf.getnchannels(),
                rate = wf.getframerate(),
                output = True)

# my
print p.get_host_api_info_by_index(0)

# read data
data = wf.readframes(chunk)

# play stream
while data != '':
    stream.write(data)
    data = wf.readframes(chunk)
    # print "tick\n"  # сообщения о происходящем можно посылать
    # возможно можно передвигаться по файлу

stream.close()
p.terminate()
