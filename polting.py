import math
import os
import subprocess
import time
from scipy.interpolate import interp1d
import numpy as np
import matplotlib.pyplot as plt

PLOTS_DIR = "plots/"
TEST_DIR = "tests/"
TEST_FILE = "test"

BUILD_DIR = "build/"
BRUTEFORCE_EXE = "bruteforce.exe"
DYNAMICFORWEIGHTS_EXE = "dynamicforweights.exe"
DYNAMICFORPROFITS_EXE = "dynamicforprofits.exe"
FPTAS_EXE = "fptas.exe"

def generate(num_tests, input_range, weight_range, value_range):
		input_start, input_step = input_range
		weight_start, weight_step = weight_range
		value_start, value_step = value_range
		for i in range(1, num_tests + 1):
			with open(f"{TEST_DIR}{TEST_FILE}_{i}.in", "w") as f:
				num_items = input_start
				capacity = int(weight_start * math.log2(input_start))

				# Write the number of items and knapsack capacity
				f.write(f"{num_items} {capacity}\n")

				# Generate items
				for _ in range(num_items):
						weight = weight_start
						value = value_start
						f.write(f"{weight} {value}\n")

				input_start += input_step
				weight_start += weight_step
				value_start += value_step

def test(num_tests):
	brute_times = []
	weight_times = []
	value_times = []
	fptas_times = []
	for test_num in range(1, num_tests + 1):
		test_file = os.path.join(TEST_DIR, f"{TEST_FILE}_{test_num}.in")
		
		print(f"Test: {test_num}")
		# Brute Force
		command = [f"{BUILD_DIR}{BRUTEFORCE_EXE} ", test_file]
		start_time = time.time()
		brute_ans = subprocess.run(command).returncode
		print(brute_ans)
		bruteforce_time = time.time() - start_time
		brute_times.append(bruteforce_time)
		print(f"Brute force ran in {bruteforce_time * 1000}ms.")

		# Dynamic for weights
		command = [f"{BUILD_DIR}{DYNAMICFORWEIGHTS_EXE} ", test_file]
		start_time = time.time()
		weights_ans = subprocess.run(command).returncode
		dynamicforweights_time = time.time() - start_time
		weight_times.append(dynamicforweights_time)
		print(f"Dynamic for weights ran in {dynamicforweights_time * 1000}ms.")
		
		# Dynamic for profits
		command = [f"{BUILD_DIR}{DYNAMICFORPROFITS_EXE} ", test_file]
		start_time = time.time()
		profits_ans = subprocess.run(command).returncode
		dynamicforprofits_time = time.time() - start_time
		value_times.append(dynamicforprofits_time)
		print(f"Dynamic for profits ran in {dynamicforprofits_time * 1000}ms.")

		# Fully polynomial time approximation schem
		command = [f"{BUILD_DIR}{FPTAS_EXE} ", test_file]
		start_time = time.time()
		fptas_ans = subprocess.run(command).returncode
		fptas_time = time.time() - start_time
		fptas_times.append(fptas_time)
		print(f"FPTAS ran in {fptas_time * 1000}ms.")

		print()
	return brute_times, weight_times, value_times, fptas_times

def plot(x, y, name):
	x = np.array(x)
	n = np.arange(x.shape[0]) 
	y = np.array(y)
	x_spline = interp1d(n, x,kind='cubic')
	n_ = np.linspace(n.min(), n.max(), 500)
	y_spline = interp1d(n, y,kind='cubic')
	x_ = x_spline(n_)
	y_ = y_spline(n_)
	plt.plot(x_, y_, label=name)


# Small tests. All variables increase.
num = 20
generate(num, (5, 5), (5, 5), (5, 5))
brute_times, weight_times, value_times, fptas_times = test(num)
plot(list(range(5, 5 * (num + 1), 5)), brute_times, "Brute")
plot(list(range(5, 5 * (num + 1), 5)), weight_times, "Weights dynamic")
plot(list(range(5, 5 * (num + 1), 5)), value_times, "Values dynamic")
plot(list(range(5, 5 * (num + 1), 5)), fptas_times, "FPTAS")
plt.legend(loc="upper left")
plt.title("Small General Tests")
plt.xlabel("Data size")
plt.ylabel("Time")
plt.savefig(f'{PLOTS_DIR}Small General Tests.png')
plt.clf()

# Increasing Weight
num = 100
generate(num, (50, 0), (100, 1000), (100, 0))
brute_times, weight_times, value_times, fptas_times = test(num)
plot(list(range(100, 100 + 1000 * num, 1000)), brute_times, "Brute")
plot(list(range(100, 100 + 1000 * num, 1000)), weight_times, "Weights dynamic")
plot(list(range(100, 100 + 1000 * num, 1000)), value_times, "Values dynamic")
plot(list(range(100, 100 + 1000 * num, 1000)), fptas_times, "FPTAS")
plt.legend(loc="upper left")
plt.title("Incresing Weigh")
plt.xlabel("Weight")
plt.ylabel("Time")
plt.savefig(f'{PLOTS_DIR}Increasing Weight.png')
plt.clf()

# Increasing Value
num = 100
generate(num, (50, 0), (100, 0), (100, 1000))
brute_times, weight_times, value_times, fptas_times = test(num)
plot(list(range(100, 100 + 1000 * num, 1000)), brute_times, "Brute")
plot(list(range(100, 100 + 1000 * num, 1000)), weight_times, "Weights dynamic")
plot(list(range(100, 100 + 1000 * num, 1000)), value_times, "Values dynamic")
plot(list(range(100, 100 + 1000 * num, 1000)), fptas_times, "FPTAS")
plt.legend(loc="upper left")
plt.title("Incresing Value")
plt.xlabel("Value")
plt.ylabel("Time")
plt.savefig(f'{PLOTS_DIR}Increasing Value.png')
plt.clf()

# Increasing Value and Weight
num = 100
generate(num, (50, 0), (100, 1000), (100, 1000))
brute_times, weight_times, value_times, fptas_times = test(num)
plot(list(range(100, 100 + 1000 * num, 1000)), brute_times, "Brute")
plot(list(range(100, 100 + 1000 * num, 1000)), weight_times, "Weights dynamic")
plot(list(range(100, 100 + 1000 * num, 1000)), value_times, "Values dynamic")
plot(list(range(100, 100 + 1000 * num, 1000)), fptas_times, "FPTAS")
plt.legend(loc="upper left")
plt.title("Incresing Value and Weight")
plt.xlabel("Value and Weight")
plt.ylabel("Time")
plt.savefig(f'{PLOTS_DIR}Increasing Value and Weight.png')
plt.clf()
