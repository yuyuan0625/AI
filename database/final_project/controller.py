from os import system
from PyQt5 import QtCore, QtWidgets
from PyQt5.QtGui import QImage, QPixmap
from PyQt5.QtWidgets import QFileDialog
from PyQt5.QtCore import QThread, pyqtSignal,Qt, QTimer
import time
from GUI_DBMS import Ui_MainWindow
import mysql.connector

# connect withe the myTable database
connection = mysql.connector.connect(host = 'localhost',
                         port = '3306',
                         user = 'root',
                         password = '0000',
                         database = 'dbms')


class MainWindow_controller(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__() # in python3, super(Class, self).xxx = super().xxx
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.setup_control()
        self.s = ""
        self.y = ""
        
    def setup_control(self):
        self.ui.price_slider.valueChanged.connect(self.getslidervalue)
        self.ui.pushButton.clicked.connect(self.query)
    def getslidervalue(self):        
        self.ui.price_display.setText(f"{self.ui.price_slider.value()}")
    def query(self):
        crsor = connection.cursor()
        s_type = self.ui.type_list.currentText()
        s_top = self.ui.topping_list.currentText()  
        s_region = self.ui.region_list.currentText()
        s_p_int = self.ui.price_slider.value()     
        if s_type=="":
            s_type = "in (SELECT DISTINCT type FROM drinks)"
        else:
            s_type = "='"+s_type+"'"

        if s_top == "":
            s_top = "in (SELECT DISTINCT toppings FROM drinks)"
        else:
            s_top = "='"+s_top+"'"
            
        if self.ui.caffeine.isChecked():
            s_caffeine = "= 0"
        else:
            s_caffeine = "in (SELECT DISTINCT caffeine FROM drinks)"           
        
        if s_region == "":
            s_region = "全台"
        else:
            s_region = s_region
            
        if s_p_int == 0:
            s_price = "100"
        else: 
            s_price = str(self.ui.price_slider.value())

        s_sql = "SELECT * FROM menu WHERE drinkName in (SELECT drinkName FROM drinks WHERE type " + s_type + " and toppings " + s_top +\
        " and caffeine " + s_caffeine + ") and storeName in (SELECT storeName FROM store WHERE region = '" + s_region + "' or region = '全台' )and price < " + s_price
        crsor.execute(s_sql)
        text = ""
        # print(crsor.type)
        # for (storeName,drinkName) in crsor:
        #     text+=str(storeName)+"\n"+str(drinkName)
        #---------------------------------------------------
        # print(crsor.)
        for (storeName,drinkName,temperature,capacity,price) in crsor:
            # print("%s\t%s\t%s\n" %(storeName,drinkName,price))
            if(len(str(drinkName))>=4):
                text+=str(storeName)+"        \t"+str(drinkName)+" \t"+str(price)+"\n"
            else:
                text+=str(storeName)+"        \t"+str(drinkName)+"\t\t"+str(price)+"\n"
        self.ui.label.setText(text)
        
        # print(self.ui.type_list.currentText())
        # print(self.ui.topping_list.currentText())
        # print(self.ui.region_list.currentText()) 
        # print(self.ui.caffeine.isChecked())
        # print(self.ui.price_slider.value())
        # return s
    # def display():   
        
        
if __name__ == '__main__':
    import sys
    app = QtWidgets.QApplication(sys.argv)
    window = MainWindow_controller()

    # window.regionChanged();
    window.show()
    sys.exit(app.exec_())
