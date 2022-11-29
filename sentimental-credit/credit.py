# TODO
from cs50 import get_int, get_string

number = get_int("Number: ")

list_1, list_2 = [], []
n, m = 100, 10
sum_1, sum_2 = 0, 0

for i in range(8):      # 16-digit -> max 8 time
    digit_1 = int((number % n) / (n / 10))
    digit_1 *= 2
    list_1.append(digit_1)
    n *= 100

    if digit_1 < 10:
        sum_1 += digit_1
    else:
        sum_1 += (1 + digit_1 % 10)


for i in range(8):
    digit_2 = int((number % m) / (m / 10))
    list_2.append(digit_2)
    m *= 100

    sum_2 += digit_2

# print(list_1)
# print(list_2)
# print(sum_1)
# print(sum_2)

if ((sum_1 + sum_2) % 10 == 0) and ((int(number % 10000000000000000 / 10000000000000) == 34 or\
                                    int(number % 10000000000000000 / 10000000000000) == 37)):

    print("AMEX\n")

elif ((sum_1 + sum_2) % 10 == 0) and ((int(number % 100000000000000000 / 100000000000000) > 50 and\
                                       int(number % 100000000000000000 / 100000000000000) < 56)):

    print("MASTERCARD\n")

elif ((sum_1 + sum_2) % 10 == 0) and ((int(number % 100000000000000000 / 1000000000000000) == 4 or\
                                       int(number % 100000000000000 / 1000000000000) == 4)):

    print("VISA\n")

else:
    print("INVALID\n")