import random

DIR = "tests/"

def generate_knapsack_tests(output_file, num_tests):
	# Generate small tests
	for i in range(1, num_tests + 1):
		with open(f"{DIR}{output_file}_{i}.in", "w") as f:
			# Randomize the number of items and knapsack capacity
			num_items = random.randint(1, 50)
			capacity = random.randint(1, 100)

			# Write the number of items and knapsack capacity
			f.write(f"{num_items} {capacity}\n")

			# Generate items with random weights and values
			for _ in range(num_items):
					weight = random.randint(1, 50)
					value = random.randint(1, 100)
					f.write(f"{weight} {value}\n")

	#Generate big weight tests
	for i in range(num_tests + 1, 2 * num_tests + 1):
		with open(f"{DIR}{output_file}_{i}.in", "w") as f:
			# Randomize the number of items and knapsack capacity
			num_items = random.randint(1, 10)
			capacity = random.randint(1e6, 1e6 * 5)

			# Write the number of items and knapsack capacity
			f.write(f"{num_items} {capacity}\n")

			# Generate items with random weights and values
			for _ in range(num_items):
					weight = random.randint(1e5, 1e6)
					value = random.randint(1, 1e3)
					f.write(f"{weight} {value}\n")

	#Generate big value tests
	for i in range(2 * num_tests + 1, 3 * num_tests + 1):
		with open(f"{DIR}{output_file}_{i}.in", "w") as f:
			# Randomize the number of items and knapsack capacity
			num_items = random.randint(1, 100)
			capacity = random.randint(1, 100)

			# Write the number of items and knapsack capacity
			f.write(f"{num_items} {capacity}\n")

			# Generate items with random weights and values
			for _ in range(num_items):
					weight = random.randint(1, 100)
					value = random.randint(1e3, 1e5)
					f.write(f"{weight} {value}\n")

	#Generate lots of objects
	for i in range(3 * num_tests + 1, 4 * num_tests + 1):
		with open(f"{DIR}{output_file}_{i}.in", "w") as f:
			# Randomize the number of items and knapsack capacity
			num_items = random.randint(1e2, 1e2 * 5)
			capacity = random.randint(30, 40) # Brute force killer

			# Write the number of items and knapsack capacity
			f.write(f"{num_items} {capacity}\n")

			# Generate items with random weights and values
			for _ in range(num_items):
					weight = random.randint(1, 100)
					value = random.randint(1, 100)
					f.write(f"{weight} {value}\n")


	print(f"Generated {num_tests * 4} test cases and saved to {output_file}.")

if __name__ == "__main__":
  generate_knapsack_tests(output_file="test", num_tests=5)
