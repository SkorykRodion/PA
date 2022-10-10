import random


def create_file(n, max):
    with open("test.bin", "wb") as file:
        for i in range(0, int((n*1024*1024)/32)):
            file.write(random.randint(0, max+1).to_bytes(32, byteorder='big'))


def display_file(name):
    with open(name, "rb") as file:
        num = file.read(32)
        while num:
            print(int.from_bytes(num, "big"))
            num = file.read(32)

