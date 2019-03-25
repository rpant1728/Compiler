f = open("test1.c", "r")
contents = f.read()
lines = contents.split("\n")
for line in lines:
    line = line.replace('''"''', '''\"''')
    print(line+"\\"+"n", end="")

