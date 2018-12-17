# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'Aula06_Exemplo4Form.ui'
#
# Created: Tue Aug 23 10:30:12 2016
#      by: PyQt4 UI code generator 4.11.3
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtWidgets
import sys
sys.path.insert(0, './Model')
import Aula06_Exemplo6Model

sys.path.insert(0, './Controller')
import Aula06_Exemplo6Controller

sys.path.insert(0, './View')
import Aula06_Exemplo6Design

class model(Aula06_Exemplo6Model.Model):
    def __init__(self):
        super(self.__class__, self).__init__()

class controller(Aula06_Exemplo6Controller.Controler):
    def __init__(self, view, model):
        super(self.__class__, self).__init__(view, model)
 
class interface(QtWidgets.QMainWindow, Aula06_Exemplo6Design.Ui_MainWindow):
    controllerObj = None
    modelObj = None
    
    def __init__(self):
        super(self.__class__, self).__init__()
        self.setupUi(self)

        self.modelObj = model()

        self.controllerObj = controller(self,  self.modelObj)

        
        self.pbCriaThread.clicked.connect(self.controllerObj.cria_Thread)


def main():

    app = QtWidgets.QApplication(sys.argv)
    form = interface()
    form.show()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()

