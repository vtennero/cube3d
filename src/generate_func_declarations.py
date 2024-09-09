import os
import re

def extract_function_declarations(directory='.'):
    output_file = "function_declarations.txt"

    # Regex pattern for matching function declarations
    pattern = re.compile(r'^\s*(\w+(?:\s+\w+)*\s+\**\w+\s*\([^)]*\))\s*$\n\s*{', re.MULTILINE)

    # Pattern to match and remove else if statements
    else_if_pattern = re.compile(r'\belse\s+if\s*\([^)]*\)\s*\{[^\}]*\}', re.DOTALL)

    # Pattern to remove single-line comments
    comment_pattern = re.compile(r'//.*$', re.MULTILINE)

    # Set to store unique declarations
    unique_declarations = set()

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

    print(f"Unique, non-static, non-commented function declarations have been extracted to {output_file}")

# Run the function
extract_function_declarations()
