CLASS_DIRECTORY=./classes
LIB=./dreamcast

python gen_decoder.py > "${CLASS_DIRECTORY}"/c/decode.inc.c

#                                                            [block name]  [package name]  [class_name]  [base_address]
python regs/register_gen.py "${LIB}"/regs/holly.csv      holly         holly           Holly         0xa05f8000     > "${CLASS_DIRECTORY}"/sega/dreamcast/holly/Holly.java
python regs/register_gen.py "${LIB}"/regs/systembus.csv  systembus     systembus       Systembus     0xa05f6800     > "${CLASS_DIRECTORY}"/sega/dreamcast/systembus/Systembus.java
python regs/register_gen.py "${LIB}"/regs/systembus.csv  maple_if      maple           MapleIF       0xa05f6c00     > "${CLASS_DIRECTORY}"/sega/dreamcast/maple/MapleIF.java
python regs/register_gen.py "${LIB}"/regs/gdrom.csv      gdrom         gdrom           Gdrom         0xa05f7000     > "${CLASS_DIRECTORY}"/sega/dreamcast/gdrom/Gdrom.java
python regs/register_gen.py "${LIB}"/regs/systembus.csv  g1_if         gdrom           G1IF          0xa05f7400     > "${CLASS_DIRECTORY}"/sega/dreamcast/gdrom/G1IF.java
python regs/register_gen.py "${LIB}"/regs/systembus.csv  g2_if         g2_if           G2IF          0xa05f7800     > "${CLASS_DIRECTORY}"/sega/dreamcast/g2_if/G2IF.java
python regs/register_gen.py "${LIB}"/regs/systembus.csv  pvr_if        pvr_if          PVRIF         0xa05f7c00     > "${CLASS_DIRECTORY}"/sega/dreamcast/pvr_if/PVRIF.java

python regs/bits_gen.py "${LIB}"/regs/core_bits.csv      holly CoreBits    > "${CLASS_DIRECTORY}"/sega/dreamcast/holly/CoreBits.java
python regs/bits_gen.py "${LIB}"/regs/ta_bits.csv        holly TABits      > "${CLASS_DIRECTORY}"/sega/dreamcast/holly/TABits.java
python regs/bits_gen.py "${LIB}"/regs/isp_tsp.csv        holly ISPTSP      > "${CLASS_DIRECTORY}"/sega/dreamcast/holly/ISPTSP.java
python regs/bits_gen.py "${LIB}"/regs/ta_parameter.csv   holly TAParameter > "${CLASS_DIRECTORY}"/sega/dreamcast/holly/TAParameter.java
python regs/bits_gen.py "${LIB}"/regs/gdrom_bits.csv    gdrom GdromBits   > "${CLASS_DIRECTORY}"/sega/dreamcast/gdrom/GdromBits.java

python regs/bits_gen.py "${LIB}"/regs/systembus_bits.csv systembus SystembusBits > "${CLASS_DIRECTORY}"/sega/dreamcast/systembus/SystembusBits.java

python regs/ta_parameters.py "${LIB}"/regs/vertex_parameter_format.csv holly TAVertexParameter > "${CLASS_DIRECTORY}"/sega/dreamcast/holly/TAVertexParameter.java
python regs/ta_parameters.py "${LIB}"/regs/global_parameter_format.csv holly TAGlobalParameter > "${CLASS_DIRECTORY}"/sega/dreamcast/holly/TAGlobalParameter.java

PYTHONPATH=./regs/ python ../model_generator/generate_java.py cube.obj CubeModel > "${CLASS_DIRECTORY}"/./model/CubeModel.java

python images/color_convert.py images/java_cup.png argb4444 images/java_cup.data
python images/color_convert.py images/java_text.png argb4444 images/java_text.data
python images/color_convert.py images/java_powered.png argb4444 images/java_powered.data

python regs/gdrom_command_packet_format.py "${LIB}"/regs/gdrom_command_packet_format.csv gdrom GdromCommandPacketFormat > "${CLASS_DIRECTORY}"/sega/dreamcast/gdrom/GdromCommandPacketFormat.java
