import os
import re
from pathlib import Path
import subprocess
import time
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


positive_directories = ["../big_number_tests_positive", "../positive_tests", "../small_number_tests_positive"]
directories = ["../big_number_tests", "../big_number_tests_positive", "../impossible_tests", "../positive_tests", "../random_tests", "../small_number_tests", "../small_number_tests_positive"]

ss_monte_carlo_directories = directories
ss_greedy_directories = directories
ss_backtracking_positive_directories = positive_directories
ss_dp_directories = positive_directories
ss_backtracking_directories = ["../impossible_tests"]

executables_dict = {"./ss_dp" : ss_dp_directories, "./ss_greedy" : ss_greedy_directories, 
                    "./ss_monte_carlo" : ss_monte_carlo_directories, "./ss_backtracking" : ss_backtracking_directories, 
                    "./ss_backtracking_positive" : ss_backtracking_positive_directories}

MONTE_CARLO_ITERATIONS = 100000

results_dic = {}



def plot_and_save_image(data):
    for i, (file_name, values) in enumerate(data.items()):
        if i >= 5:
            break
        iterations = [v['iterations'] for v in values.values()]
        errors = [v['error'] for v in values.values()]


        iterations = np.array(iterations)
        errors = np.array(errors, dtype=float)


        sorted_indices = np.argsort(iterations)
        iterations = iterations[sorted_indices]
        errors = errors[sorted_indices]

        plt.plot(iterations, errors, marker='o', label=file_name)


        plt.xlabel('Iterations')
        plt.ylabel('Error')
        plt.title(f'Monte Carlo Simulation - Plot {i}')


        plt.legend()


        plt.ylim(min(errors) - 100, max(errors) + 1000)


        # plt.yscale('log')

        plt.savefig(f'plot_{i}.png', format='png', bbox_inches='tight')


        plt.close()




def generate_table(results_dic):
    rows = []
    for file, algorithms in results_dic.items():
        row = {"File": file}
        row.update(algorithms)
        rows.append(row)

    df = pd.DataFrame(rows)

    df = df.fillna("N/A")

    print(df)

    df.to_csv("../execution_times.csv", index=False)
    print("Table saved to execution_times.csv")




def extract_number(filename):
    match = re.search(r'(\d+)', filename)
    return int(match.group(0)) if match else 0


def main():
    for executable, directories in executables_dict.items():
        for directory in directories:
            directory_path = Path(directory)
            files = sorted([file.name for file in directory_path.iterdir()], key=lambda x: extract_number(x)) # list of sorted files from each directory(strings)
            for file in files:
                if file not in results_dic and (file == "big_number_file0.txt" or file == "positive_file0.txt" or file == "random_file0.txt" or file == "small_number_file0.txt" or file == "small_number_positive_file0.txt"):
                    results_dic[file] = {}
                if executable == "./ss_monte_carlo" and files[0] == file and file != "impossible_file0.txt" and file != "big_number_positive_file0.txt":
                    #start_time = time.time()
                    for i in range(1000, 96000, 5000):
                        result = subprocess.run([executable, (directory[3:] + "/" + file), str(i)], capture_output=True, text=True, check=True)
                    #end_time = time.time() - start_time
                        value_list = result.stdout.strip().split(" ")
                        results_dic[file][str((i - 1000) / 5000) + "."] = {"iterations" : i, "error" : value_list[1]}
    plot_and_save_image(results_dic)
                #else:
                #    start_time = time.time()
                #    result = subprocess.run([executable, (directory[3:] + "/" + file)], capture_output=True, text=True, check=True)
                ##    end_time = time.time() - start_time
                #    results_dic[file][executable[5:]] = end_time
    #generate_table(results_dic)
    print(results_dic)










if __name__ == "__main__":
    main()