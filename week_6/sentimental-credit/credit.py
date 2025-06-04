# American Express uses 15-digit numbers, MasterCard uses 16-digit numbers, and Visa uses 13- and 16-digit numbers.
# All American Express numbers start with 34 or 37; most MasterCard numbers start with 51, 52, 53, 54, or 55 (they also have some other potential starting numbers which we won’t concern ourselves with for this problem); and all Visa numbers start with 4.
# Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
# Add the sum to the sum of the digits that weren’t multiplied by 2.
# If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!
# AMEX\n or MASTERCARD\n or VISA\n or INVALID\n

user_card = int(input("Please, input your credit card number: "))

length = len(str(user_card))


def valid_card(card_number):
    global card_num_list
    if length in (13, 15, 16):
        card_num_list = []
        counter = length
        rest = card_number

        for _ in range(length):
            new_num = int(rest / 10**(counter-1))
            rest = int(card_number % 10**(counter-1))
            counter -= 1
            card_num_list.append(new_num)

        reversed_list = []
        nother_counter = 1
        for i in card_num_list:
            nother_new_num = card_num_list[length-nother_counter]
            nother_counter += 1
            reversed_list.append(nother_new_num)

        selected_index_nums = reversed_list[1:length:2]

        not_selected_index_nums = reversed_list[0:length:2]

        selected_total = 0
        for x in selected_index_nums:
            op = x*2
            op_len = len(str(op))
            if op_len == 1:
                selected_total += op
            else:
                new_op = int(op / 10)
                rest_op = op % 10
                selected_total += new_op
                selected_total += rest_op

        not_selected_total = 0
        for y in not_selected_index_nums:
            not_selected_total += y

        total = selected_total + not_selected_total

        if total % 10 == 0:
            return True


def check_bank(card_number):
    if length == 15 and card_num_list[0] == 3 and card_num_list[1] in (4, 7):
        print("AMEX")
    elif length == 16 and card_num_list[0] == 5 and card_num_list[1] in range(1, 6):
        print("MASTERCARD")
    elif length in (13, 16) and card_num_list[0] == 4:
        print("VISA")
    else:
        print("INVALID")


if valid_card(user_card):
    check_bank(user_card)
else:
    print("INVALID")
