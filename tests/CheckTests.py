from subprocess import run, Popen, PIPE
from sys import executable, argv

numTests = 10
ok = True

for i in range(1, numTests + 1):
	dataStr = "tests/testsFiles/test"
	ansStr  = "tests/testsFiles/testAns"
	if i % 10 != 0:
		dataStr += "0"
		ansStr += "0"	
	dataStr += str(i) + ".txt"
	ansStr  += str(i) + ".txt"

	outFile = open(ansStr, "r")
	ans = outFile.read()
	outFile.close()
		
	inputFile = open(dataStr, "r")

	result = run(["./src/cache" , argv[1]], capture_output = True, encoding = 'cp866', stdin = inputFile)
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