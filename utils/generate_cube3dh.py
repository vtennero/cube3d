import os
import re
import subprocess

def extract_function_declarations(directory='../src'):
    output_file = "function_declarations.txt"
    cube3d_audio_bonus_file = "cube3d_audio_bonus_declarations.txt"

    # Regex pattern for matching function declarations
    pattern = re.compile(r'^\s*(\w+(?:\s+\w+)*\s+\**\w+\s*\([^)]*\))\s*$\n\s*{', re.MULTILINE)

    # Pattern to match and remove else if statements
    else_if_pattern = re.compile(r'\belse\s+if\s*\([^)]*\)\s*\{[^\}]*\}', re.DOTALL)

    # Pattern to remove single-line comments
    comment_pattern = re.compile(r'//.*$', re.MULTILINE)

    # Set to store unique declarations
    unique_declarations = set()
    audio_bonus_declarations = set()

    for filename in os.listdir(directory):
        if filename.endswith('.c'):
            with open(os.path.join(directory, filename), 'r') as file:
                content = file.read()

                # Remove single-line comments
                content = comment_pattern.sub('', content)

                # Remove else if statements
                content = else_if_pattern.sub('', content)

                matches = pattern.finditer(content)

                for match in matches:
                    declaration = match.group(1).strip()
                    # Check if declaration starts with 'static', 'if', or 'else'
                    if not any(declaration.startswith(word) for word in ['static', 'if', 'else']):
                        if filename in ['audio_bonus00.c', 'audio_bonus01.c', 'audio_bonus02.c', 'audio_bonus03.c']:
                            audio_bonus_declarations.add(declaration)
                        elif filename == 'audio_dummy00.c':
                            unique_declarations.add(declaration)
                        else:
                            unique_declarations.add(declaration)

    # Write unique declarations to file
    with open(output_file, 'w') as out_file:
        for declaration in sorted(unique_declarations):
            # Split the declaration into return type and the rest
            parts = declaration.split(maxsplit=1)
            if len(parts) == 2:
                return_type, rest = parts
                out_file.write(f"{return_type}\t{rest};\n")
            else:
                # If we can't split properly, write the original declaration
                out_file.write(f"{declaration};\n")

    # Write audio bonus declarations to a separate file
    with open(cube3d_audio_bonus_file, 'w') as out_file:
        for declaration in sorted(audio_bonus_declarations):
            parts = declaration.split(maxsplit=1)
            if len(parts) == 2:
                return_type, rest = parts
                out_file.write(f"{return_type}\t{rest};\n")
            else:
                out_file.write(f"{declaration};\n")

    print(f"Unique, non-static, non-commented function declarations have been extracted to {output_file}")
    print(f"Audio bonus function declarations have been extracted to {cube3d_audio_bonus_file}")

    # Copy the contents of the output file to clipboard using xclip
    try:
        with open(output_file, 'r') as file:
            subprocess.run(['xclip', '-selection', 'clipboard'], input=file.read().encode('utf-8'), check=True)
        print(f"Contents of {output_file} have been copied to clipboard")
    except subprocess.CalledProcessError:
        print("Failed to copy to clipboard. Make sure xclip is installed.")
    except FileNotFoundError:
        print("xclip is not installed. Please install it using: sudo apt-get install xclip")

    # Update cube3d.h and cube3d_audio_bonus.h
    update_header(output_file, "../src/cube3d.h")
    update_header(cube3d_audio_bonus_file, "../src/cube3d_audio_bonus.h")

def update_header(declarations_file, header_file):
    # Read the current content of the header file
    with open(header_file, 'r') as file:
        content = file.read()

    # Read the function declarations
    with open(declarations_file, 'r') as file:
        declarations = file.read()

    # Find the start and end markers
    start_marker = "// FUNCTION DECLARATIONS START"
    end_marker = "// FUNCTION DECLARATIONS END"

    # Replace the content between the markers
    pattern = re.compile(f"{start_marker}.*?{end_marker}", re.DOTALL)
    new_content = pattern.sub(f"{start_marker}\n{declarations}\n{end_marker}", content)

    # Write the new content to the header file
    with open(header_file, 'w') as file:
        file.write(new_content)

    print(f"Updated {header_file} with the new function declarations")

# Run the function
extract_function_declarations()
