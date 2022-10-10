from fileGeneration import *
from adaptiveSort import *
import time


def main():
    #розмір у мегабайтах та максимальне значення числа
    create_file(30, 2**32)

    start_time = time.time()
    natural_marge_sort("test.bin")
    print("---  Done in %s seconds ---" % (time.time() - start_time))


if __name__ == '__main__':
    main()


