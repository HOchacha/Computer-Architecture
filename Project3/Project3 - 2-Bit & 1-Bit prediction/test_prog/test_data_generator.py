import random
def create_matrix_init_file(size=120, filename="init_matrix120x120.h"):
    with open(filename, "w") as f:
        f.write("{\n")
        for i in range(size):
            for j in range(size):
                f.write(f"matrix1[{i}][{j}] = {hex(random.randint(0, int(0x10000)))};\n")

def create_matrix_append_file(size=120, filename="init_matrix120x120.h"):
    with open(filename, "a") as f:
        f.write("{\n")
        for i in range(size):
            for j in range(size):
                f.write(f"matrix2[{i}][{j}] = {hex(random.randint(0, int(0x10000)))};\n")

create_matrix_init_file()
create_matrix_append_file()