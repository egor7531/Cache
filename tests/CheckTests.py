from subprocess import run, Popen, PIPE
from sys import executable, argv

numTests = int(open("./tests/NumberTests.txt", 'r').read())

ok = True

for i in range(1, numTests + 1):
	dataStr = "tests/testsFiles/"
	ansStr  = "tests/testsFiles/Answer/" + 	argv[1].upper() + "/"

	dataStr += f'{i :02}' + ".txt"
	ansStr  += f'{i :02}' + ".txt"

	outFile = open(ansStr, "r")
	ans = outFile.read()
	outFile.close()
		
	inputFile = open(dataStr, "r")

	result = run(["./build/src/cache" , argv[1]], capture_output = True, encoding = 'cp866', stdin = inputFile)
	print("Test: " + str(i).strip())

	result = ''.join(''.join(c if c.isdigit() else ' ' for c in result.stdout).split())
	
	ok &= (result == ans)
	
	if result == ans:
		print("OK")
	else:
		print("ERROR\n", "correct: " + str(ans).strip(), "\n", "result: ", result)
	print("-------------------------------------------------")
	
if ok:
	print("TESTS PASSED")
else:
	print("TESTS FAILED")