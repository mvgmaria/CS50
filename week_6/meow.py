def main():
    for _ in range(3):  # by convention, we can use the _ as a variable that we don't really have to use later, instead of 'i'
        meow()


def meow():
    print("meow")

if __name__ = "__main__": # useful, even if not here
    main()

# we use the main function at the top as a prototype, to be able to keep the meow function bellow, and then even if we create the main function, it will work because the program is not going to read the meow until the last line where we actually call main() (also, we call it main by convention, could me anything)
