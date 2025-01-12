import random
import sys
import os
import shutil

DIRECTORY_NAME = "big_number_tests_positive"


def main():
    if len(sys.argv) != 2:
        sys.exit("You must enter an integer as the first argument and only have 1 argument!")
    try:
        number_of_files_generated = int(sys.argv[1])
    except ValueError:
        sys.exit("The 2nd argument must be an integer")
    
    try:
        os.mkdir(DIRECTORY_NAME)
    except FileExistsError:
        shutil.rmtree(DIRECTORY_NAME)
        os.mkdir(DIRECTORY_NAME)
    
    for i in range(number_of_files_generated):
        N = random.randint(1, 1000)
        T = random.randint(1, 100000)
        file_name = f"./{DIRECTORY_NAME}/big_number_positive_file{i}.txt"
        with open(file_name, "w") as file:
            print(N, T, file = file)
            for _ in range(N):
                print(random.randint(100000, 1000000), file = file)

                






    
    





if __name__ == "__main__":
    main()