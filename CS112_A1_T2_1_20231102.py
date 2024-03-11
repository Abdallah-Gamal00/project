# file: CS112_A1_T2_1_20231102
# Purpose: 100 Game in python two players start from 0 and alternatively add numbers from 1 to 10 to the sum.the player who reaches 100 win
# Author: Abdallah Gamal Rabie
# ID: 20231102
# Date: 20 Feb 2024

def game():
    print("**welcome to (100Game)**")
    print("please select number from(1,2,3,4,5,6,7,8,9,10)")
    total = 0
    while True:
        # to make input integer
        def make_integer():
            while True:
                try:
                    user_input = input("player(1) please enter a number: ")
                    integer_value = int(user_input)
                    break
                except ValueError:
                    print("Please enter a valid integer.")
            return integer_value

        num1 = make_integer()
        # if number less than 1 or bigger than 10
        while num1 < 1 or num1 > 10:
            print("please select from (1,2,3,4,5,6,7,8,9,10)")
            num1 = make_integer()
        #if user enter number that make total bigger than 100
        if total >= 91 and total < 100:
            while True:
                if total == 91 and num1 > 9:
                    print("please select number from(1,2,3,4,5,6,7,8,9)")
                    num1 = make_integer()
                    continue

                elif total == 92 and num1 > 8:
                    print("please select number from(1,2,3,4,5,6,7,8)")
                    num1 = make_integer()
                    continue

                elif total == 93 and num1 > 7:
                    print("please select number from(1,2,3,4,5,6,7)")
                    num1 = make_integer()
                    continue

                elif total == 94 and num1 > 6:
                    print("please select number from(1,2,3,4,5,6)")
                    num1 = make_integer()
                    continue

                elif total == 95 and num1 > 5:
                    print("please select number from(1,2,3,4,5)")
                    num1 = make_integer()
                    continue

                elif total == 96 and num1 > 4:
                    print("please select number from(1,2,3,4)")
                    num1 = make_integer()
                    continue

                elif total == 97 and num1 > 3:
                    print("please select number from(1,2,3)")
                    num1 = make_integer()
                    continue

                elif total == 98 and num1 > 2:
                    print("please select number from(1,2)")
                    num1 = make_integer()
                    continue

                elif total == 99 and num1 > 1:
                    print("please select number from(1)")
                    num1 = make_integer()
                    continue
                break

        total += num1
        print("score=",total)
        if total == 100:
            print("***player(1) is winner***")
            break

        # to make input integer
        def make_integer():
            while True:
                try:
                    user_input = input("player(2) please enter a number: ")
                    integer_value = int(user_input)
                    break
                except ValueError:
                    print("Please enter a valid integer.")
            return integer_value

        num2 = make_integer()
        # if number less than 1 or bigger than 10
        while num2 < 1 or num2 > 10:
            print("please select from (1,2,3,4,5,6,7,8,9,10)")
            num2 = make_integer()
        # if user enter number that make total bigger than 100

        if total >= 91 and total < 100:
            while True:
                if total == 91 and num2 > 9:
                    print("please select number from(1,2,3,4,5,6,7,8,9)")
                    num2 = make_integer()
                    continue

                elif total == 92 and num2 > 8:
                    print("please select number from(1,2,3,4,5,6,7,8)")
                    num2 = make_integer()
                    continue

                elif total == 93 and num2 > 7:
                    print("please select number from(1,2,3,4,5,6,7)")
                    num2 = make_integer()
                    continue

                elif total == 94 and num2 > 6:
                    print("please select number from(1,2,3,4,5,6)")
                    num2 = make_integer()
                    continue

                elif total == 95 and num2 > 5:
                    print("please select number from(1,2,3,4,5)")
                    num2 = make_integer()
                    continue

                elif total == 96 and num2 > 4:
                    print("please select number from(1,2,3,4)")
                    num2 = make_integer()
                    continue

                elif total == 97 and num2 > 3:
                    print("please select number from(1,2,3)")
                    num2 = make_integer()
                    continue

                elif total == 98 and num2 > 2:
                    print("please select number from(1,2)")
                    num2 = make_integer()
                    continue

                elif total == 99 and num2 > 1:
                    print("please select number from(1)")
                    num2 = make_integer()
                    continue
                break

        total += num2
        print("score =",total)
        if total == 100:
            print("***player(2) is winner***")
            break


# menu to chose what do you want
while True:
    print("A)start game\n""B) Exit program")
    choice1 = input("Please enter your choice (A/B):").upper()
    if choice1 == "A":
        game()
        print()
        print("Do you want to play again?\n")
    elif choice1 == "B":
        print()
        print("Exit program")
        break
    else:
        print("Please select a valid choice")
