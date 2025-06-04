from cs50 import get_int

user_input = get_int("Height: ")

while True:
    if (user_input not in range(1, 9)):
        print("Please input a number from 1 to 8")
        user_input = get_int("Height: ")
    else:
        break

counter = 1
nother_counter = user_input-1
for _ in range(user_input):
    print(" " * nother_counter + "#" * counter, end="  ")
    print("#" * counter)
    nother_counter -= 1
    counter += 1
