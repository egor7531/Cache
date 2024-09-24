import random

numTests = int(open("./tests/NumberTests.txt", 'r').read())

for i in range(1, numTests + 1):

    nameFile = "tests/testsFiles/" + f'{i :02}' + ".txt"
    hits = 0

    with open(nameFile, 'r') as file:
        sizeCache, numElems = map(int, file.readline().split())

        cache = []
        for page in file:
            page = int(page)
    
            isHit = False
            for cacheElem in cache:
                if page == cacheElem[0]:

                    index = 0
                    for index in range(len(cache)):
                        if cacheElem[1] + 1 >= cache[index][1]:
                            break
                    cache.insert(index, [page, cacheElem[1] + 1]) 
                    cache.remove(cacheElem)
                    hits += 1
                    isHit = True
                    break

            if not(isHit):
                flag = False
                if len(cache) == sizeCache:
                    cache.pop()
                
                index = 0
                for index in range(len(cache)):
                    if cache[index][1] == 1:
                        break
                cache.insert(index, [page, 1])

    nameFile = "tests/testsFiles/Answer/LFU/" + f'{i :02}' + ".txt"
    file = open(nameFile, 'w')
    file.write(str(hits))
    file.close