python gen_decoder.py > c/decode.inc.c

#                                                            [block name]  [package name]  [class_name]  [base_address]
python regs/register_gen.py ../dreamcast/regs/holly.csv      holly         holly           Holly         0xa05f8000     > sega/dreamcast/holly/Holly.java
python regs/register_gen.py ../dreamcast/regs/systembus.csv  systembus     systembus       Systembus     0xa05f6800     > sega/dreamcast/systembus/Systembus.java
python regs/register_gen.py ../dreamcast/regs/systembus.csv  maple_if      maple           MapleIF       0xa05f6c00     > sega/dreamcast/maple/MapleIF.java
python regs/register_gen.py ../dreamcast/regs/systembus.csv  gdrom_if      gdrom           GdromIF       0xa05f7000     > sega/dreamcast/gdrom/GdromIF.java
python regs/register_gen.py ../dreamcast/regs/systembus.csv  g1_if         gdrom           G1IF          0xa05f7400     > sega/dreamcast/gdrom/G1IF.java
python regs/register_gen.py ../dreamcast/regs/systembus.csv  g2_if         g2_if           G2IF          0xa05f7800     > sega/dreamcast/g2_if/G2IF.java
python regs/register_gen.py ../dreamcast/regs/systembus.csv  pvr_if        pvr_if          PVRIF         0xa05f7c00     > sega/dreamcast/pvr_if/PVRIF.java
python regs/register_gen.py ../dreamcast/regs/gdrom.csv      gdrom         gdrom           Gdrom         0xa05f7000     > sega/dreamcast/gdrom/Gdrom.java

python regs/bits_gen.py ../dreamcast/regs/core_bits.csv      holly CoreBits    > sega/dreamcast/holly/CoreBits.java
python regs/bits_gen.py ../dreamcast/regs/ta_bits.csv        holly TABits      > sega/dreamcast/holly/TABits.java
python regs/bits_gen.py ../dreamcast/regs/isp_tsp.csv        holly ISPTSP      > sega/dreamcast/holly/ISPTSP.java
python regs/bits_gen.py ../dreamcast/regs/ta_parameter.csv   holly TAParameter > sega/dreamcast/holly/TAParameter.java
python regs/bits_gen.py ..//dreamcast/regs/gdrom_bits.csv    gdrom GdromBits   > sega/dreamcast/gdrom/GdromBits.java

python regs/bits_gen.py ../dreamcast/regs/systembus_bits.csv systembus SystembusBits > sega/dreamcast/systembus/SystembusBits.java

python regs/ta_parameters.py ../dreamcast/regs/vertex_parameter_format.csv holly TAVertexParameter > sega/dreamcast/holly/TAVertexParameter.java
python regs/ta_parameters.py ../dreamcast/regs/global_parameter_format.csv holly TAGlobalParameter > sega/dreamcast/holly/TAGlobalParameter.java

PYTHONPATH=./regs/ python ../model_generator/generate_java.py ../untitled.obj UntitledModel > ./model/UntitledModel.java

python images/color_convert.py images/java_cup.png argb4444 images/java_cup.data
python images/color_convert.py images/java_text.png argb4444 images/java_text.data
python images/color_convert.py images/java_powered.png argb4444 images/java_powered.data

python regs/gdrom_command_packet_format.py ../dreamcast/regs/gdrom_command_packet_format.csv gdrom GdromCommandPacketFormat > sega/dreamcast/gdrom/GdromCommandPacketFormat.java
