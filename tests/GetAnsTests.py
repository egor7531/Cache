import random

numTests = 10

for i in range(1, numTests + 1):
    nameFile = "testsFiles/test" + f'{i :02}' + ".txt"
    hits = 0
    with open(nameFile, 'r') as file:
        sizeCache, numElems = map(int, file.readline().split())

        cache = []
        for page in file:
            page = int(page)
    
            if page in cache:
                cache.remove(page)
                hits += 1
            else:
                if len(cache) == sizeCache:
                    cache.pop()

            cache.insert(0, page) 
    
    nameFile = "testsFiles/testAns" + f'{i :02}' + ".txt"
    file = open(nameFile, 'w')
    file.write(str(hits))
    file.close