# -*- coding: utf-8 -*-
from PySide.QtCore import *
from PySide.QtGui import *

import sys

app = QApplication(sys.argv)

def callback_int(value_as_int):
    print 'int value changed:', repr(value_as_int)

def callback_unicode(value_as_unicode):
    print 'unicode value changed:', repr(value_as_unicode)

spinbox = QSpinBox()
spinbox.connect(SIGNAL('valueChanged(int)'), callback_int) 
spinbox.valueChanged.connect(callback_unicode) 
spinbox.show()

sys.exit(app.exec_())