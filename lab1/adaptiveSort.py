import shutil


def next_num(file):
    pos = file.tell()
    num = file.read(32)
    file.seek(pos)
    return num


def split_file(name_a, name_b, name_c):
    number_of_seq=1
    with open(name_a, "rb") as a, open(name_b, "wb") as b, open(name_c, "wb") as c:
        current = a.read(32)
        b.write(current)
        while current:
            if next_num(a)<current:
                number_of_seq+=1
            current = a.read(32)
            if number_of_seq%2 == 1:
                b.write(current)
            else:
                c.write(current)
        return number_of_seq-1


def merge_file(name_a, name_b, name_c):
    with open(name_a, "wb") as a, open(name_b, "rb") as b, open(name_c, "rb") as c:
        num_b =b.read(32)
        num_c =c.read(32)

        while num_b or num_c:

            if num_b and not num_c:
                while num_b:
                    a.write(num_b)
                    num_b = b.read(32)

            elif num_c and not num_b:
                while num_c:
                    a.write(num_c)
                    num_c = c.read(32)

            elif next_num(b) >= num_b and next_num(c) >= num_c:
                if num_b<num_c:
                    a.write(num_b)
                    num_b = b.read(32)
                else:
                    a.write(num_c)
                    num_c =c.read(32)

            elif next_num(b) >= num_b and next_num(c) < num_c:
                while next_num(b) >= num_b:
                    if (num_c>num_b):
                        a.write(num_b)
                        num_b = b.read(32)
                    else:
                        a.write(num_c)
                        num_c=c.read(32)
                        while next_num(b) >= num_b:
                            a.write(num_b)
                            num_b = b.read(32)

            elif next_num(c) >= num_c and next_num(b) < num_b:
                while next_num(c) >= num_c:
                    if(num_b>num_c):
                        a.write(num_c)
                        num_c = c.read(32)
                    else:
                        a.write(num_b)
                        num_b = b.read(32)
                        while next_num(c) >= num_c:
                            a.write(num_c)
                            num_c = c.read(32)

            else:
                if num_b<num_c:
                    a.write(num_b)
                    num_b = b.read(32)
                    a.write(num_c)
                    num_c = c.read(32)
                else:
                    a.write(num_c)
                    num_c =c.read(32)
                    a.write(num_b)
                    num_b = b.read(32)


def natural_marge_sort(file_name):
    is_sorted = False
    while not is_sorted:
        num = split_file(file_name, "B.bin", "C.bin")
        if(num!=1):
            merge_file(file_name, "B.bin", "C.bin")
        else:
            shutil.copyfile("B.bin", file_name)
            is_sorted = True
