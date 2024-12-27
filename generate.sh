python gen_decoder.py > c/decode.inc.c

python regs/holly.py ../dreamcast/regs/holly.csv > sega/dreamcast/holly/Holly.java

python regs/bits_gen.py ../dreamcast/regs/core_bits.csv holly CoreBits > sega/dreamcast/holly/CoreBits.java
python regs/bits_gen.py ../dreamcast/regs/ta_bits.csv   holly TABits   > sega/dreamcast/holly/TABits.java
python regs/bits_gen.py ../dreamcast/regs/isp_tsp.csv   holly ISPTSP   > sega/dreamcast/holly/ISPTSP.java
