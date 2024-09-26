import random

numTests = int(open("./tests/NumberTests.txt", 'r').read())

for i in range(1, numTests + 1):

    nameFile = "tests/testsFiles/" + f'{i :02}' + ".txt"
    hits = 0
    
    with open(nameFile, 'r') as file:
        sizeCache, numElems = map(int, file.readline().split())

        pages = []
        for page in file:
            pages += list(map(int, page.split()))
        
        cache = []
        index = 0
        while len(pages) != 0:
            
            if len(cache) < sizeCache:
                if pages[0] in cache:
                    hits += 1
                else:
                    cache.insert(0, pages[0])
                pages.pop(0)

            else:
                if pages[0] in cache:
                    hits += 1
                else:
                    lateIndex = -1
                    isHit = False
                    for k in range(len(cache)):
                        isHit = False
                        for j in range(len(pages)):
                            if cache[k] == pages[j]:
                                lateIndex = max(lateIndex, j)
                                isHit = True
                                break
                        if not(isHit):
                            cache.remove(cache[k])
                            break

                    if isHit:
                        cache.remove(pages[lateIndex])

                    cache.append(pages[0])
                pages.pop(0)

    nameFile = "tests/testsFiles/Answer/PERFECT/" + f'{i :02}' + ".txt"
    file = open(nameFile, 'w')
    file.write(str(hits))
    file.close