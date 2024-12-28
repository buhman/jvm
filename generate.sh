python gen_decoder.py > c/decode.inc.c

python regs/register_gen.py ../dreamcast/regs/holly.csv holly 0xa05f8000 > sega/dreamcast/holly/Holly.java
python regs/register_gen.py ../dreamcast/regs/systembus.csv systembus 0xa05f6800 > sega/dreamcast/systembus/Systembus.java

python regs/bits_gen.py ../dreamcast/regs/core_bits.csv holly CoreBits > sega/dreamcast/holly/CoreBits.java
python regs/bits_gen.py ../dreamcast/regs/ta_bits.csv   holly TABits   > sega/dreamcast/holly/TABits.java
python regs/bits_gen.py ../dreamcast/regs/isp_tsp.csv   holly ISPTSP   > sega/dreamcast/holly/ISPTSP.java
python regs/bits_gen.py ../dreamcast/regs/ta_parameter.csv   holly TAParameter   > sega/dreamcast/holly/TAParameter.java

python regs/bits_gen.py ../dreamcast/regs/systembus_bits.csv systembus SystembusBits > sega/dreamcast/systembus/SystembusBits.java

python regs/ta_parameters.py ../dreamcast/regs/vertex_parameter_format.csv holly TAVertexParameter > sega/dreamcast/holly/TAVertexParameter.java
python regs/ta_parameters.py ../dreamcast/regs/global_parameter_format.csv holly TAGlobalParameter > sega/dreamcast/holly/TAGlobalParameter.java

PYTHONPATH=./regs/ python ../model_generator/generate_java.py ../untitled.obj UntitledModel > ./models/UntitledModel.java
