import os
import subprocess
import time

TEST_DIR = "tests/"
TEST_FILE = "test"

RESULT_DIR = "results/"
RESULT_FILE = "file"

BUILD_DIR = "build/"
BRUTEFORCE_EXE = "bruteforce.exe"
DYNAMICFORWEIGHTS_EXE = "dynamicforweights.exe"
DYNAMICFORPROFITS_EXE = "dynamicforprofits.exe"
FPTAS_EXE = "fptas.exe"

subprocess.run("python generator.py")

for test_num in range(1, 21):
	test_file = os.path.join(TEST_DIR, f"{TEST_FILE}_{test_num}.in")
	result_file = os.path.join(RESULT_DIR, f"{RESULT_FILE}_{test_num}.out")
	
	print(f"Test: {test_num}")
	# Brute Force
	command = [f"{BUILD_DIR}{BRUTEFORCE_EXE} ", test_file]
	start_time = time.time()
	subprocess.run(command, stdout=open(result_file, "w"))
	bruteforce_time = time.time() - start_time
	print(f"Brute force ran in {bruteforce_time * 1000}ms.")

	# Dynamic for weights
	command = [f"{BUILD_DIR}{DYNAMICFORWEIGHTS_EXE} ", test_file]
	start_time = time.time()
	subprocess.run(command, stdout=open(result_file, "w"))
	dynamicforweights_time = time.time() - start_time
	print(f"Dynamic for weights ran in {dynamicforweights_time * 1000}ms.")
	
	# Dynamic for profits
	command = [f"{BUILD_DIR}{DYNAMICFORPROFITS_EXE} ", test_file]
	start_time = time.time()
	subprocess.run(command, stdout=open(result_file, "w"))
	dynamicforprofits_time = time.time() - start_time
	print(f"Dynamic for profits ran in {dynamicforprofits_time * 1000}ms.")

	# Fully polynomial time approximation schem
	command = [f"{BUILD_DIR}{FPTAS_EXE} ", test_file]
	start_time = time.time()
	subprocess.run(command, stdout=open(result_file, "w"))
	fptas_time = time.time() - start_time
	print(f"FPTAS ran in {fptas_time * 1000}ms.")

	print()
