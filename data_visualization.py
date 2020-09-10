# Importing the libraries
import pandas as pd
import matplotlib.pyplot as plt

# Transforming the .csv files into dataset variables
sample_data = pd.read_csv('data.csv')
sample_data2 = pd.read_csv('data2.csv')


def graph_time_gas(gas):
    '''
    Plots graphics using data from two datasets.
    '''
    if gas == 'CO2':
        plt.plot(sample_data.TIME, sample_data.CO2)
        plt.plot(sample_data2.TIME, sample_data2.CO2)
        
    elif gas == 'CO':
        plt.plot(sample_data.TIME, sample_data.CO)
        plt.plot(sample_data2.TIME, sample_data2.CO)
        
    elif gas == 'PM10':
        plt.plot(sample_data.TIME, sample_data.PM10)    
        plt.plot(sample_data2.TIME, sample_data2.PM10)
        
    elif gas== 'PM25':
        plt.plot(sample_data.TIME, sample_data.PM25)
        plt.plot(sample_data2.TIME, sample_data2.PM25)
        
    elif gas== 'PM100':
        plt.plot(sample_data.TIME, sample_data.PM100)
        plt.plot(sample_data2.TIME, sample_data2.PM100)
        
    elif gas== 'NO2':
        plt.plot(sample_data.TIME, sample_data.NO2)
        plt.plot(sample_data2.TIME, sample_data2.NO2)
    
    plt.xlabel('Time')
    plt.ylabel(str(gas))
    plt.title('{}/Time'.format(gas))
    plt.legend(['Dataset 1', 'Dataset 2'])
    plt.show()

# Ploting the graphics for each gas using the two datasets
graph_time_gas('CO2')
graph_time_gas('CO')
graph_time_gas('Pm10')
graph_time_gas('PM25')
graph_time_gas('PM100')
graph_time_gas('NO2')

