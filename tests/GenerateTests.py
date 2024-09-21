import random

numTests = int(input("Enter the number of tests: " ))

for i in range(1, numTests + 1):
    nameFile = "testsFiles/test" + f'{i :02}' + ".txt"
    file = open(nameFile, 'w')

    sizeCache = int(input("Enter the cache size: " ))
    numElems = int(input("Enter the number of pages: " ))

    testStr = str(sizeCache) + " " + str(numElems) + "\n"

    for j in range(numElems):
        testStr += str(random.randint(1, numElems)) + "\n"

    file.write(testStr)
    file.close()

    print("test: ", i, " generated")
