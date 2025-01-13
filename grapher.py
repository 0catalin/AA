import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import os

df = pd.read_csv('execution_times.csv')

impossible_files = df[df['File'].str.contains('impossible')]

backtracking_values = impossible_files['backtracking'].tolist()

array = list(range(0, 32))

plt.plot(array, backtracking_values)
plt.xlabel('Size of set')
plt.ylabel('Time for execution (s)')
plt.title('Execution times for impossible tests using backtracking')
plt.savefig('bt_by_time.png')