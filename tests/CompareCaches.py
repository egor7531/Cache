
numTests = int(open("./tests/NumberTests.txt", 'r').read())

file = open("tests/testsFiles/RatioCaches.txt", 'w')
file.write("Perfect/LRU" + "\t" + "Perfect/LFU" + "\t" + "LFU/LRU" + "\n")

for i in range(1, numTests + 1):

    ansLRU      = int(open("tests/testsFiles/LRU/"      + f'{i :02}' + "Ans.txt", 'r').read())
    ansLFU      = int(open("tests/testsFiles/LFU/"      + f'{i :02}' + "Ans.txt", 'r').read())
    ansPerfect  = int(open("tests/testsFiles/PERFECT/"  + f'{i :02}' + "Ans.txt", 'r').read())

    ratio31 = round((float)(ansPerfect) / (float)(ansLRU), 2)
    ratio32 = round((float)(ansPerfect) / (float)(ansLFU), 2)
    ratio21 = round((float)(ansLFU)     / (float)(ansLRU), 2)

    file.write(f'{ratio31:<10}' + "\t" + f'{ratio32:<10}' + "\t" + f'{ratio21:<10}' + "\n")

file.close()