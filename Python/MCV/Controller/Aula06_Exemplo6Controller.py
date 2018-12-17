# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'Aula06_Exemplo6Form.ui'
#
# Created: Tue Aug 23 12:51:19 2016
#      by: PyQt4 UI code generator 4.11.3
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtWidgets
import threading
import time

class Controler(object):
    view = None
    model = None
    
    def __init__(self, view, model):
        self.view  = view
        self.model = model
    
    
    def cria_Thread(self):
        
        mutex = threading.Lock()
        thread1 = threading.Thread(target = self.print_name, args = ("Thread-1", 5, mutex))
        thread2 = threading.Thread(target = self.print_name, args = ("Thread-2", 3, mutex))
        thread3 = threading.Thread(target = self.print_name, args = ("Thread-3", 1, mutex))
        thread1.start()
        thread2.start()
        thread3.start()
        
    def print_name(self, name, delay, mutex):
        #mutex.acquire()
        count=0
        while count < 3:
            time.sleep(delay)
            count += 1
            item = QtWidgets.QListWidgetItem( self.model.texto + " " + name)
            self.view.listWidget.addItem(item)
            
        item = QtWidgets.QListWidgetItem("Finish " + name)
        self.view.listWidget.addItem(item)
        #mutex.release()    
