import subprocess
import re
from collections import defaultdict
import os
import sys
import glob

def run_norminette(src_dir, files):
	try:
		command = ['norminette', '-R', 'CheckForbiddenSourceHeader'] + files
		result = subprocess.run(command, capture_output=True, text=True, cwd=src_dir)
		return result.stdout + result.stderr
	except Exception as e:
		print(f"Error running norminette: {e}", file=sys.stderr)
		return ""

def count_errors(output):
	error_counts = defaultdict(int)
	current_file = None

	for line in output.split('\n'):
		if ': Error!' in line:
			current_file = line.split(':')[0]
		elif line.startswith('Error:'):
			if current_file:
				error_counts[current_file] += 1

	return error_counts

def save_and_display_results(error_counts):
	sorted_files = sorted(error_counts.items(), key=lambda x: x[1], reverse=True)

	# Find the longest filename for proper alignment
	max_filename_length = max(len(file) for file, _ in sorted_files)

	# Prepare the formatted strings
	formatted_results = []
	for file, count in sorted_files:
		formatted_line = f"{file:<{max_filename_length}} : {count:>4} error(s)"
		formatted_results.append(formatted_line)

	# Save to file and display
	with open('norminette_error_summary.txt', 'w') as f:
		f.write("Error summary:\n")
		for line in formatted_results:
			f.write(line + '\n')
			print(line)

def main():
	src_dir = os.path.abspath('../src')
	if not os.path.isdir(src_dir):
		print(f"Error: {src_dir} directory not found.", file=sys.stderr)
		return

	# Get all .c and .h files in the ../src directory
	c_files = glob.glob(os.path.join(src_dir, '*.c'))
	h_files = glob.glob(os.path.join(src_dir, '*.h'))
	files = [os.path.basename(f) for f in c_files + h_files]

	if not files:
		print(f"No .c or .h files found in {src_dir}", file=sys.stderr)
		return

	print(f"Found {len(files)} file(s) to check in {src_dir}")
	print("Running norminette...")
	output = run_norminette(src_dir, files)

	if not output:
		print("No output received from norminette.", file=sys.stderr)
		return

	print("Norminette output received.")
	print("\nCounting errors...")

	error_counts = count_errors(output)

	if not error_counts:
		print("No errors found in the norminette output.", file=sys.stderr)
		return

	print("\nError summary:")
	save_and_display_results(error_counts)
	print(f"\nResults saved to {os.path.abspath('norminette_error_summary.txt')}")

if __name__ == "__main__":
	main()
