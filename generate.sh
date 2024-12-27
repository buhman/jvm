python gen_decoder.py > c/decode.inc.c

python regs/holly.py ../dreamcast/regs/holly.csv > sega/dreamcast/holly/Holly.java
python regs/core_bits.py ../dreamcast/regs/core_bits.csv > sega/dreamcast/holly/HollyBits.java
python regs/ta_bits.py ../dreamcast/regs/ta_bits.csv > sega/dreamcast/holly/TABits.java
