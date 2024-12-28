import sys
from itertools import chain

buf = sys.stdin.read()

def removesuffix(filename):
    if filename.endswith('.java'):
        filename = filename.removesuffix('.java')
    if filename.endswith('.class'):
        filename = filename.removesuffix('.class')
    return filename


java_files = buf.strip().split('\n')
nosuffix_files = [removesuffix(f) for f in java_files]
class_files = [f + '.class' for f in nosuffix_files]
class_h_files = [f + '.class.h' for f in nosuffix_files]
class_o_files = [f + '.class.o' for f in nosuffix_files]

with open('class_headers.sh', 'w') as f:
    filenames = ' '.join(class_files)
    f.write(' '.join(["make", filenames, '\n']))
    filenames = ' '.join(chain(class_h_files, class_o_files))
    f.write(' '.join(["make", "-f", "Makefile.dreamcast.mk", filenames, '\n']))

with open('c/main_classpath.inc.c', 'w') as f:
    for filename in class_files:
        name = filename.replace('/', '_').replace('.', '_')
        f.write(f"    (const uint8_t *)&_binary_{name}_start,\n")

with open('c/main_classpath.h', 'w') as f:
    for filename in class_h_files:
        f.write(f'#include "{filename}"\n')

with open('classpath.mk', 'w') as f:
    f.write("CLASS_PATH = \\\n")
    for filename in class_o_files[:-2]:
        f.write(f"\t{filename} \\\n")
    filename = class_o_files[-1]
    f.write(f"\t{filename}\n")
