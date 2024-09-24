import random

numTests = int(open("./tests/NumberTests.txt", 'r').read())

for i in range(1, numTests + 1):
    nameFile = "tests/testsFiles/" + f'{i :02}' + ".txt"
    file = open(nameFile, 'w')

    sizeCache = int(input("Enter the cache size: " ))
    numElems = int(input("Enter the number of pages: " ))

    testStr = str(sizeCache) + " " + str(numElems) + "\n"

    for j in range(numElems):
        testStr += str(random.randint(1, numElems)) + "\n"

    file.write(testStr)
    file.close()

    print("test: ", i, " generated")
    print("-------------------------------------")
