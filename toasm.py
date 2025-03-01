import re
import sys
import chardet

def process_files(input_file_path, output_file_path):
    # 探测原始文件的编码
    with open(input_file_path, 'rb') as f:
        result = chardet.detect(f.read())
        encoding = result['encoding']
    pattern = re.compile(r'^([0-9A-Fa-f]{8})\s+([0-9A-Fa-f ]+)\s+(.*)$')
    with open(input_file_path, 'r', encoding=encoding) as input_file, open(output_file_path, 'w',
                                                                       encoding='utf - 8') as output_file:
        for line in input_file:
            line = line.rstrip()
            if match := pattern.match(line):
                addr_str, _, instr = match.groups()
                addr = int(addr_str, 16)
                output_file.write(f"0x{addr:x}:\n")
                output_file.write(f"{instr}\n")
            else:
                output_file.write(line + "\n")


if __name__ == "__main__":
    if len(sys.argv)!= 3:
        print("Usage: python script_name.py input_file output_file")
        sys.exit(1)
    input_file_path = sys.argv[1]
    output_file_path = sys.argv[2]
    process_files(input_file_path, output_file_path)
