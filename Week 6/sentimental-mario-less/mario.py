while True:
    try:
        height = int(input("Height: "))
        if 0 < height <= 8:
            break
    except ValueError:
        print("Vui lòng nhập một số nguyên hợp lệ.")

for i in range(1, height + 1):
    # In khoảng trắng
    print(" " * (height - i), end="")
    # In dấu #
    print("#" * i)
