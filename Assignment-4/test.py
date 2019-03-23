f = open("test.c", "r")
contents = f.read()
lines = contents.split("\n")
for line in lines:
    print(line+"\\"+"n", end="")

