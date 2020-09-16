import serial
import matplotlib.pyplot as plt

plt.ion()


def graph_NO2():
    iNO2 = 0
    xNO2 = list()
    yNO2 = list()

    ser_NO2 = serial.Serial('COM6', 9600)
    ser_NO2.close()
    ser_NO2.open()
    while True:
        data = ser_NO2.readline()
        print(data.decode())
        xNO2.append(iNO2)
        yNO2.append(data.decode())

        plt.scatter(iNO2, float(data.decode()), color='r')
        iNO2 += 1
        plt.show()
        plt.pause(0.5)


def graph_CO():
    iCO = 0
    xCO = list()
    yCO = list()

    ser_CO = serial.Serial('COM6', 9600)
    ser_CO.close()
    ser_CO.open()
    while True:
        data = ser_CO.readline()
        print(data.decode())
        xCO.append(iCO)
        yCO.append(data.decode())

        plt.scatter(iCO, float(data.decode()), color='g')
        iCO += 1
        plt.show()
        plt.pause(0.5)


def graph_CO2():
    iCO2 = 0
    xCO2 = list()
    yCO2 = list()

    ser_CO2 = serial.Serial('COM6', 9600)
    ser_CO2.close()
    ser_CO2.open()
    while True:
        data = ser_CO2.readline()
        print(data.decode())
        xCO2.append(iCO2)
        yCO2.append(data.decode())

        plt.scatter(iCO2, float(data.decode()), color='b')
        iCO2 += 1
        plt.show()
        plt.pause(0.5)


graph_NO2()
graph_CO()
graph_CO2()
