from matplotlib import pyplot as plt
import pandas as pd

x = [1, 2, 3]
y = [1, 8, 27 ]
plt.plot(x,y)
axes = plt.gca()
axes.set_xlim([0,10])
axes.set_ylim([0,30])
plt.title("f(x) = x**3")
plt.xlabel("x")
plt.ylabel("y")
plt.legend(["the derivative funtion of f(x) is '3x**2'"])
plt.show()
