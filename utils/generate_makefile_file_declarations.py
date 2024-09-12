import os
import subprocess

# Define the path to the directory containing .c files
src_dir = "../src/"

# Get a list of all .c files in the directory
c_files = [f for f in os.listdir(src_dir) if f.endswith(".c")]

# Sort the files alphabetically
c_files.sort()

if "audio_dummy.c" in c_files:
    c_files.remove("audio_dummy.c")
    c_files.append("audio_dummy.c")

if "audio_bonus.c" in c_files:
    c_files.remove("audio_bonus.c")
    c_files.append("audio_bonus.c")

if "main_bonus.c" in c_files:
    c_files.remove("main_bonus.c")

if "main.c" in c_files:
    c_files.remove("main.c")

# Create the formatted text with backslashes
formatted_lines = []
for idx, file in enumerate(c_files):
    if file == "audio_bonus.c":
        # Comment out 'audio_bonus.c'
        formatted_lines.append(f"# {file} \\")
    else:
        formatted_lines.append(f"{file} \\")

# Join the lines, adding "SHARED_SRCS =" at the start
formatted_text = "SHARED_SRCS = \\\n" + "\n".join(formatted_lines)

# Copy the text to clipboard using xclip
process = subprocess.Popen(['xclip', '-selection', 'clipboard'], stdin=subprocess.PIPE)
process.communicate(formatted_text.encode('utf-8'))

print("The list of .c files has been copied to the clipboard.")
