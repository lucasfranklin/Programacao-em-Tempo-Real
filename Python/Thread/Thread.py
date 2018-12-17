import threading
import time

import os
clear = lambda: os.system('cls')

class myThread (threading.Thread):
    name = None
    delay = None
     
    def __init__(self, name, delay):
        threading.Thread.__init__(self)
        self.name = name
        self.delay = delay
        
    def run(self):
        print_name(self)


def print_name(self):
    count=0
    while count < 3:
        time.sleep(self.delay)
        count += 1
        print(self.name)
        print("\n")


clear()

# Create new threads
thread1 = myThread("Thread-1", 1)
thread2 = myThread("Thread-2", 1)
thread3 = myThread("Thread-3", 1)

thread1.start()
thread2.start()
thread3.start()

