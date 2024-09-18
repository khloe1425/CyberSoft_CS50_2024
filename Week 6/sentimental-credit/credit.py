while True:
    try:
        credit_card_number = int(input("Number: "))
        if credit_card_number > 0:
            break
    except ValueError:
        print("Vui lòng nhập số hợp lệ.")

sum_doubled = 0
temp_number = credit_card_number
count = 0

# Tính tổng dựa trên thuật toán Luhn
while temp_number > 0:
    digit = temp_number % 10
    if count % 2 == 1:
        doubled = digit * 2
        while doubled > 0:
            sum_doubled += doubled % 10
            doubled //= 10
    else:
        sum_doubled += digit
    temp_number //= 10
    count += 1

# Kiểm tra số hợp lệ
if sum_doubled % 10 == 0:
    if (340000000000000 <= credit_card_number < 350000000000000) or \
       (370000000000000 <= credit_card_number < 380000000000000):
        print("AMEX")
    elif 5100000000000000 <= credit_card_number < 5600000000000000:
        print("MASTERCARD")
    elif (4000000000000 <= credit_card_number < 5000000000000) or \
         (4000000000000000 <= credit_card_number < 5000000000000000):
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")
