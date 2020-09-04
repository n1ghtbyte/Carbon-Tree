import serial

# Serial port of Arduino
# on Windows it will be "COM5" format
# on Mac it will be "/dev/cu.usbmodemxxx" format
arduino_port = "/dev/cu.usbmodem14101"
# arduino baud
baud = 9600
# name of the csv file generated
fileName="data.csv"
# how many samples to collect
samples = 50
#
print_labels = False


#
ser = serial.Serial(arduino_port, baud)
print("Connected to Arduino port:" + arduino_port)
# You can use the input parameter “w” to write a new file or “a” to append to an existing file.
file = open(fileName, "w")
print("Created file " + "'" + fileName + "'")

line = 0

while line <= samples:

    # incoming = ser.read(9999)
    # if len(incoming) > 0:
    if print_labels:
        if line == 0:
            print("Printing Column Headers")
        else:
            print("Line " + str(line) + ": writing...")
    getData = str(ser.readline())
    data = getData[2:][:-5]
    print(data)

    file = open(fileName, "a")
    file.write(data + "\n") #write data with a newline
    line = line+2

print("Data collection complete!")
file.close()

