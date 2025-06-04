try:
    n = int(input("Input: "))
except ValueError:
    print("Not integer")
else:
    print("Integer")

# it is standard that in the try block we have as little code as possible, as to not overload with statement that aren't strictly going to raise the error we are trying to catch, that's why we put the print statement at the end in the else block, instead of in the try one
