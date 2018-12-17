# -*- coding: utf-8 -*-
"""
Created on Mon Aug 08 11:16:30 2016

@author: Hugo
"""

import threading
import time

import os
clear = lambda: os.system('cls')

global nomeImpresso

my_mutex = threading.Lock()  

def print_time( threadName, delay):
   
   global nomeImpresso
   global my_mutex 
   
   count = 0
   my_mutex.acquire()  
   while count < 10:
      nomeImpresso = threadName
      count += 1
      time.sleep(delay)
      print "%s: %s" % (nomeImpresso,  threadName)

   
   print('Finish ',threadName )
   my_mutex.release()  




clear()

thread1 = threading.Thread(target=print_time, args=("Thread-1", 3 ))
thread2 = threading.Thread(target=print_time, args=("Thread-2", 2 ))

thread1.start()
thread2.start()