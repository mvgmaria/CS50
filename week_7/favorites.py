import csv

with open("favorites.csv","r") as file:
    # reader = csv.reader(file)
    # next(reader) #to skip the headers
    # for row in reader
    #     favorite = row[1] # this way of locating the index is subject to changes in the csv, so thats why we are going to use the following method
    #     print(favorite)

    reader = csv.DictReader(file)
    # scratch,c,python = 0,0,0
    counts = {} # if we make a dictionary in which the key is the language and the value is the count, we can use fewer lines of code to get to the same result
    for row in reader: # no need to explictly skip the headers, it will do so automatically
        # print(row["language"])
        favorite = row["language"]
        # if favorite == "Scratch":
        #     scratch += 1
        # if favorite == "C":
        #     c += 1
        # if favorite == "Python":
        #     python += 1

        if favorite in counts: # if the key is not in the dictionary yet, i can't add the value
            counts[favorite] += 1
        else:
            counts[favorite] = 1 # so if the key is there, i will add 1 to the count, and if not I will create the key like so and asign it a value of one (so as not to get a KeyError)

# print(f"Scratch: {scratch}")
# print(f"C: {c}")
# print(f"Pyhon: {python}")

for favorite in sorted(counts, key=counts.get, reverse=True): # alphabetically by default, but we can add a key, in this case with .get we are getting the values of the counts (reverse to get from biggest to smallest)
    print(f"{favorite}: {counts[favorite]}")

