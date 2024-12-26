uint32_t decode_print_instruction(const uint8_t * code, uint32_t pc)
{
  switch (code[pc]) {
    case 0: // nop
    {
      debugf("%4d: nop           \n", pc);
      return pc + 1;
    }
    case 1: // aconst_null
    {
      debugf("%4d: aconst_null   \n", pc);
      return pc + 1;
    }
    case 2: // iconst_m1
    {
      debugf("%4d: iconst_m1     \n", pc);
      return pc + 1;
    }
    case 3: // iconst_0
    {
      debugf("%4d: iconst_0      \n", pc);
      return pc + 1;
    }
    case 4: // iconst_1
    {
      debugf("%4d: iconst_1      \n", pc);
      return pc + 1;
    }
    case 5: // iconst_2
    {
      debugf("%4d: iconst_2      \n", pc);
      return pc + 1;
    }
    case 6: // iconst_3
    {
      debugf("%4d: iconst_3      \n", pc);
      return pc + 1;
    }
    case 7: // iconst_4
    {
      debugf("%4d: iconst_4      \n", pc);
      return pc + 1;
    }
    case 8: // iconst_5
    {
      debugf("%4d: iconst_5      \n", pc);
      return pc + 1;
    }
    case 9: // lconst_0
    {
      debugf("%4d: lconst_0      \n", pc);
      return pc + 1;
    }
    case 10: // lconst_1
    {
      debugf("%4d: lconst_1      \n", pc);
      return pc + 1;
    }
    case 11: // fconst_0
    {
      debugf("%4d: fconst_0      \n", pc);
      return pc + 1;
    }
    case 12: // fconst_1
    {
      debugf("%4d: fconst_1      \n", pc);
      return pc + 1;
    }
    case 13: // fconst_2
    {
      debugf("%4d: fconst_2      \n", pc);
      return pc + 1;
    }
    case 14: // dconst_0
    {
      debugf("%4d: dconst_0      \n", pc);
      return pc + 1;
    }
    case 15: // dconst_1
    {
      debugf("%4d: dconst_1      \n", pc);
      return pc + 1;
    }
    case 16: // bipush
    {
      int32_t byte = _s1(&code[pc + 1]);
      debugf("%4d: bipush        %d\n", pc, byte);
      return pc + 2;
    }
    case 17: // sipush
    {
      int32_t byte = _s2(&code[pc + 1]);
      debugf("%4d: sipush        %d\n", pc, byte);
      return pc + 3;
    }
    case 18: // ldc
    {
      uint32_t index = _u1(&code[pc + 1]);
      debugf("%4d: ldc           %u\n", pc, index);
      return pc + 2;
    }
    case 19: // ldc_w
    {
      uint32_t index = _u2(&code[pc + 1]);
      debugf("%4d: ldc_w         %u\n", pc, index);
      return pc + 3;
    }
    case 20: // ldc2_w
    {
      uint32_t index = _u2(&code[pc + 1]);
      debugf("%4d: ldc2_w        %u\n", pc, index);
      return pc + 3;
    }
    case 21: // iload
    {
      uint32_t index = _u1(&code[pc + 1]);
      debugf("%4d: iload         %u\n", pc, index);
      return pc + 2;
    }
    case 22: // lload
    {
      uint32_t index = _u1(&code[pc + 1]);
      debugf("%4d: lload         %u\n", pc, index);
      return pc + 2;
    }
    case 23: // fload
    {
      uint32_t index = _u1(&code[pc + 1]);
      debugf("%4d: fload         %u\n", pc, index);
      return pc + 2;
    }
    case 24: // dload
    {
      uint32_t index = _u1(&code[pc + 1]);
      debugf("%4d: dload         %u\n", pc, index);
      return pc + 2;
    }
    case 25: // aload
    {
      uint32_t index = _u1(&code[pc + 1]);
      debugf("%4d: aload         %u\n", pc, index);
      return pc + 2;
    }
    case 26: // iload_0
    {
      debugf("%4d: iload_0       \n", pc);
      return pc + 1;
    }
    case 27: // iload_1
    {
      debugf("%4d: iload_1       \n", pc);
      return pc + 1;
    }
    case 28: // iload_2
    {
      debugf("%4d: iload_2       \n", pc);
      return pc + 1;
    }
    case 29: // iload_3
    {
      debugf("%4d: iload_3       \n", pc);
      return pc + 1;
    }
    case 30: // lload_0
    {
      debugf("%4d: lload_0       \n", pc);
      return pc + 1;
    }
    case 31: // lload_1
    {
      debugf("%4d: lload_1       \n", pc);
      return pc + 1;
    }
    case 32: // lload_2
    {
      debugf("%4d: lload_2       \n", pc);
      return pc + 1;
    }
    case 33: // lload_3
    {
      debugf("%4d: lload_3       \n", pc);
      return pc + 1;
    }
    case 34: // fload_0
    {
      debugf("%4d: fload_0       \n", pc);
      return pc + 1;
    }
    case 35: // fload_1
    {
      debugf("%4d: fload_1       \n", pc);
      return pc + 1;
    }
    case 36: // fload_2
    {
      debugf("%4d: fload_2       \n", pc);
      return pc + 1;
    }
    case 37: // fload_3
    {
      debugf("%4d: fload_3       \n", pc);
      return pc + 1;
    }
    case 38: // dload_0
    {
      debugf("%4d: dload_0       \n", pc);
      return pc + 1;
    }
    case 39: // dload_1
    {
      debugf("%4d: dload_1       \n", pc);
      return pc + 1;
    }
    case 40: // dload_2
    {
      debugf("%4d: dload_2       \n", pc);
      return pc + 1;
    }
    case 41: // dload_3
    {
      debugf("%4d: dload_3       \n", pc);
      return pc + 1;
    }
    case 42: // aload_0
    {
      debugf("%4d: aload_0       \n", pc);
      return pc + 1;
    }
    case 43: // aload_1
    {
      debugf("%4d: aload_1       \n", pc);
      return pc + 1;
    }
    case 44: // aload_2
    {
      debugf("%4d: aload_2       \n", pc);
      return pc + 1;
    }
    case 45: // aload_3
    {
      debugf("%4d: aload_3       \n", pc);
      return pc + 1;
    }
    case 46: // iaload
    {
      debugf("%4d: iaload        \n", pc);
      return pc + 1;
    }
    case 47: // laload
    {
      debugf("%4d: laload        \n", pc);
      return pc + 1;
    }
    case 48: // faload
    {
      debugf("%4d: faload        \n", pc);
      return pc + 1;
    }
    case 49: // daload
    {
      debugf("%4d: daload        \n", pc);
      return pc + 1;
    }
    case 50: // aaload
    {
      debugf("%4d: aaload        \n", pc);
      return pc + 1;
    }
    case 51: // baload
    {
      debugf("%4d: baload        \n", pc);
      return pc + 1;
    }
    case 52: // caload
    {
      debugf("%4d: caload        \n", pc);
      return pc + 1;
    }
    case 53: // saload
    {
      debugf("%4d: saload        \n", pc);
      return pc + 1;
    }
    case 54: // istore
    {
      uint32_t index = _u1(&code[pc + 1]);
      debugf("%4d: istore        %u\n", pc, index);
      return pc + 2;
    }
    case 55: // lstore
    {
      uint32_t index = _u1(&code[pc + 1]);
      debugf("%4d: lstore        %u\n", pc, index);
      return pc + 2;
    }
    case 56: // fstore
    {
      uint32_t index = _u1(&code[pc + 1]);
      debugf("%4d: fstore        %u\n", pc, index);
      return pc + 2;
    }
    case 57: // dstore
    {
      uint32_t index = _u1(&code[pc + 1]);
      debugf("%4d: dstore        %u\n", pc, index);
      return pc + 2;
    }
    case 58: // astore
    {
      uint32_t index = _u1(&code[pc + 1]);
      debugf("%4d: astore        %u\n", pc, index);
      return pc + 2;
    }
    case 59: // istore_0
    {
      debugf("%4d: istore_0      \n", pc);
      return pc + 1;
    }
    case 60: // istore_1
    {
      debugf("%4d: istore_1      \n", pc);
      return pc + 1;
    }
    case 61: // istore_2
    {
      debugf("%4d: istore_2      \n", pc);
      return pc + 1;
    }
    case 62: // istore_3
    {
      debugf("%4d: istore_3      \n", pc);
      return pc + 1;
    }
    case 63: // lstore_0
    {
      debugf("%4d: lstore_0      \n", pc);
      return pc + 1;
    }
    case 64: // lstore_1
    {
      debugf("%4d: lstore_1      \n", pc);
      return pc + 1;
    }
    case 65: // lstore_2
    {
      debugf("%4d: lstore_2      \n", pc);
      return pc + 1;
    }
    case 66: // lstore_3
    {
      debugf("%4d: lstore_3      \n", pc);
      return pc + 1;
    }
    case 67: // fstore_0
    {
      debugf("%4d: fstore_0      \n", pc);
      return pc + 1;
    }
    case 68: // fstore_1
    {
      debugf("%4d: fstore_1      \n", pc);
      return pc + 1;
    }
    case 69: // fstore_2
    {
      debugf("%4d: fstore_2      \n", pc);
      return pc + 1;
    }
    case 70: // fstore_3
    {
      debugf("%4d: fstore_3      \n", pc);
      return pc + 1;
    }
    case 71: // dstore_0
    {
      debugf("%4d: dstore_0      \n", pc);
      return pc + 1;
    }
    case 72: // dstore_1
    {
      debugf("%4d: dstore_1      \n", pc);
      return pc + 1;
    }
    case 73: // dstore_2
    {
      debugf("%4d: dstore_2      \n", pc);
      return pc + 1;
    }
    case 74: // dstore_3
    {
      debugf("%4d: dstore_3      \n", pc);
      return pc + 1;
    }
    case 75: // astore_0
    {
      debugf("%4d: astore_0      \n", pc);
      return pc + 1;
    }
    case 76: // astore_1
    {
      debugf("%4d: astore_1      \n", pc);
      return pc + 1;
    }
    case 77: // astore_2
    {
      debugf("%4d: astore_2      \n", pc);
      return pc + 1;
    }
    case 78: // astore_3
    {
      debugf("%4d: astore_3      \n", pc);
      return pc + 1;
    }
    case 79: // iastore
    {
      debugf("%4d: iastore       \n", pc);
      return pc + 1;
    }
    case 80: // lastore
    {
      debugf("%4d: lastore       \n", pc);
      return pc + 1;
    }
    case 81: // fastore
    {
      debugf("%4d: fastore       \n", pc);
      return pc + 1;
    }
    case 82: // dastore
    {
      debugf("%4d: dastore       \n", pc);
      return pc + 1;
    }
    case 83: // aastore
    {
      debugf("%4d: aastore       \n", pc);
      return pc + 1;
    }
    case 84: // bastore
    {
      debugf("%4d: bastore       \n", pc);
      return pc + 1;
    }
    case 85: // castore
    {
      debugf("%4d: castore       \n", pc);
      return pc + 1;
    }
    case 86: // sastore
    {
      debugf("%4d: sastore       \n", pc);
      return pc + 1;
    }
    case 87: // pop
    {
      debugf("%4d: pop           \n", pc);
      return pc + 1;
    }
    case 88: // pop2
    {
      debugf("%4d: pop2          \n", pc);
      return pc + 1;
    }
    case 89: // dup
    {
      debugf("%4d: dup           \n", pc);
      return pc + 1;
    }
    case 90: // dup_x1
    {
      debugf("%4d: dup_x1        \n", pc);
      return pc + 1;
    }
    case 91: // dup_x2
    {
      debugf("%4d: dup_x2        \n", pc);
      return pc + 1;
    }
    case 92: // dup2
    {
      debugf("%4d: dup2          \n", pc);
      return pc + 1;
    }
    case 93: // dup2_x1
    {
      debugf("%4d: dup2_x1       \n", pc);
      return pc + 1;
    }
    case 94: // dup2_x2
    {
      debugf("%4d: dup2_x2       \n", pc);
      return pc + 1;
    }
    case 95: // swap
    {
      debugf("%4d: swap          \n", pc);
      return pc + 1;
    }
    case 96: // iadd
    {
      debugf("%4d: iadd          \n", pc);
      return pc + 1;
    }
    case 97: // ladd
    {
      debugf("%4d: ladd          \n", pc);
      return pc + 1;
    }
    case 98: // fadd
    {
      debugf("%4d: fadd          \n", pc);
      return pc + 1;
    }
    case 99: // dadd
    {
      debugf("%4d: dadd          \n", pc);
      return pc + 1;
    }
    case 100: // isub
    {
      debugf("%4d: isub          \n", pc);
      return pc + 1;
    }
    case 101: // lsub
    {
      debugf("%4d: lsub          \n", pc);
      return pc + 1;
    }
    case 102: // fsub
    {
      debugf("%4d: fsub          \n", pc);
      return pc + 1;
    }
    case 103: // dsub
    {
      debugf("%4d: dsub          \n", pc);
      return pc + 1;
    }
    case 104: // imul
    {
      debugf("%4d: imul          \n", pc);
      return pc + 1;
    }
    case 105: // lmul
    {
      debugf("%4d: lmul          \n", pc);
      return pc + 1;
    }
    case 106: // fmul
    {
      debugf("%4d: fmul          \n", pc);
      return pc + 1;
    }
    case 107: // dmul
    {
      debugf("%4d: dmul          \n", pc);
      return pc + 1;
    }
    case 108: // idiv
    {
      debugf("%4d: idiv          \n", pc);
      return pc + 1;
    }
    case 109: // ldiv
    {
      debugf("%4d: ldiv          \n", pc);
      return pc + 1;
    }
    case 110: // fdiv
    {
      debugf("%4d: fdiv          \n", pc);
      return pc + 1;
    }
    case 111: // ddiv
    {
      debugf("%4d: ddiv          \n", pc);
      return pc + 1;
    }
    case 112: // irem
    {
      debugf("%4d: irem          \n", pc);
      return pc + 1;
    }
    case 113: // lrem
    {
      debugf("%4d: lrem          \n", pc);
      return pc + 1;
    }
    case 114: // frem
    {
      debugf("%4d: frem          \n", pc);
      return pc + 1;
    }
    case 115: // drem
    {
      debugf("%4d: drem          \n", pc);
      return pc + 1;
    }
    case 116: // ineg
    {
      debugf("%4d: ineg          \n", pc);
      return pc + 1;
    }
    case 117: // lneg
    {
      debugf("%4d: lneg          \n", pc);
      return pc + 1;
    }
    case 118: // fneg
    {
      debugf("%4d: fneg          \n", pc);
      return pc + 1;
    }
    case 119: // dneg
    {
      debugf("%4d: dneg          \n", pc);
      return pc + 1;
    }
    case 120: // ishl
    {
      debugf("%4d: ishl          \n", pc);
      return pc + 1;
    }
    case 121: // lshl
    {
      debugf("%4d: lshl          \n", pc);
      return pc + 1;
    }
    case 122: // ishr
    {
      debugf("%4d: ishr          \n", pc);
      return pc + 1;
    }
    case 123: // lshr
    {
      debugf("%4d: lshr          \n", pc);
      return pc + 1;
    }
    case 124: // iushr
    {
      debugf("%4d: iushr         \n", pc);
      return pc + 1;
    }
    case 125: // lushr
    {
      debugf("%4d: lushr         \n", pc);
      return pc + 1;
    }
    case 126: // iand
    {
      debugf("%4d: iand          \n", pc);
      return pc + 1;
    }
    case 127: // land
    {
      debugf("%4d: land          \n", pc);
      return pc + 1;
    }
    case 128: // ior
    {
      debugf("%4d: ior           \n", pc);
      return pc + 1;
    }
    case 129: // lor
    {
      debugf("%4d: lor           \n", pc);
      return pc + 1;
    }
    case 130: // ixor
    {
      debugf("%4d: ixor          \n", pc);
      return pc + 1;
    }
    case 131: // lxor
    {
      debugf("%4d: lxor          \n", pc);
      return pc + 1;
    }
    case 132: // iinc
    {
      uint32_t index = _u1(&code[pc + 1]);
      uint32_t _const = _u1(&code[pc + 2]);
      debugf("%4d: iinc          %u, %u\n", pc, index, _const);
      return pc + 3;
    }
    case 133: // i2l
    {
      debugf("%4d: i2l           \n", pc);
      return pc + 1;
    }
    case 134: // i2f
    {
      debugf("%4d: i2f           \n", pc);
      return pc + 1;
    }
    case 135: // i2d
    {
      debugf("%4d: i2d           \n", pc);
      return pc + 1;
    }
    case 136: // l2i
    {
      debugf("%4d: l2i           \n", pc);
      return pc + 1;
    }
    case 137: // l2f
    {
      debugf("%4d: l2f           \n", pc);
      return pc + 1;
    }
    case 138: // l2d
    {
      debugf("%4d: l2d           \n", pc);
      return pc + 1;
    }
    case 139: // f2i
    {
      debugf("%4d: f2i           \n", pc);
      return pc + 1;
    }
    case 140: // f2l
    {
      debugf("%4d: f2l           \n", pc);
      return pc + 1;
    }
    case 141: // f2d
    {
      debugf("%4d: f2d           \n", pc);
      return pc + 1;
    }
    case 142: // d2i
    {
      debugf("%4d: d2i           \n", pc);
      return pc + 1;
    }
    case 143: // d2l
    {
      debugf("%4d: d2l           \n", pc);
      return pc + 1;
    }
    case 144: // d2f
    {
      debugf("%4d: d2f           \n", pc);
      return pc + 1;
    }
    case 145: // i2b
    {
      debugf("%4d: i2b           \n", pc);
      return pc + 1;
    }
    case 146: // i2c
    {
      debugf("%4d: i2c           \n", pc);
      return pc + 1;
    }
    case 147: // i2s
    {
      debugf("%4d: i2s           \n", pc);
      return pc + 1;
    }
    case 148: // lcmp
    {
      debugf("%4d: lcmp          \n", pc);
      return pc + 1;
    }
    case 149: // fcmpl
    {
      debugf("%4d: fcmpl         \n", pc);
      return pc + 1;
    }
    case 150: // fcmpg
    {
      debugf("%4d: fcmpg         \n", pc);
      return pc + 1;
    }
    case 151: // dcmpl
    {
      debugf("%4d: dcmpl         \n", pc);
      return pc + 1;
    }
    case 152: // dcmpg
    {
      debugf("%4d: dcmpg         \n", pc);
      return pc + 1;
    }
    case 153: // ifeq
    {
      int32_t branch = _s2(&code[pc + 1]);
      debugf("%4d: ifeq          %d\n", pc, branch);
      return pc + 3;
    }
    case 154: // ifne
    {
      int32_t branch = _s2(&code[pc + 1]);
      debugf("%4d: ifne          %d\n", pc, branch);
      return pc + 3;
    }
    case 155: // iflt
    {
      int32_t branch = _s2(&code[pc + 1]);
      debugf("%4d: iflt          %d\n", pc, branch);
      return pc + 3;
    }
    case 156: // ifge
    {
      int32_t branch = _s2(&code[pc + 1]);
      debugf("%4d: ifge          %d\n", pc, branch);
      return pc + 3;
    }
    case 157: // ifgt
    {
      int32_t branch = _s2(&code[pc + 1]);
      debugf("%4d: ifgt          %d\n", pc, branch);
      return pc + 3;
    }
    case 158: // ifle
    {
      int32_t branch = _s2(&code[pc + 1]);
      debugf("%4d: ifle          %d\n", pc, branch);
      return pc + 3;
    }
    case 159: // if_icmpeq
    {
      int32_t branch = _s2(&code[pc + 1]);
      debugf("%4d: if_icmpeq     %d\n", pc, branch);
      return pc + 3;
    }
    case 160: // if_icmpne
    {
      int32_t branch = _s2(&code[pc + 1]);
      debugf("%4d: if_icmpne     %d\n", pc, branch);
      return pc + 3;
    }
    case 161: // if_icmplt
    {
      int32_t branch = _s2(&code[pc + 1]);
      debugf("%4d: if_icmplt     %d\n", pc, branch);
      return pc + 3;
    }
    case 162: // if_icmpge
    {
      int32_t branch = _s2(&code[pc + 1]);
      debugf("%4d: if_icmpge     %d\n", pc, branch);
      return pc + 3;
    }
    case 163: // if_icmpgt
    {
      int32_t branch = _s2(&code[pc + 1]);
      debugf("%4d: if_icmpgt     %d\n", pc, branch);
      return pc + 3;
    }
    case 164: // if_icmple
    {
      int32_t branch = _s2(&code[pc + 1]);
      debugf("%4d: if_icmple     %d\n", pc, branch);
      return pc + 3;
    }
    case 165: // if_acmpeq
    {
      int32_t branch = _s2(&code[pc + 1]);
      debugf("%4d: if_acmpeq     %d\n", pc, branch);
      return pc + 3;
    }
    case 166: // if_acmpne
    {
      int32_t branch = _s2(&code[pc + 1]);
      debugf("%4d: if_acmpne     %d\n", pc, branch);
      return pc + 3;
    }
    case 167: // goto
    {
      int32_t branch = _s2(&code[pc + 1]);
      debugf("%4d: goto          %d\n", pc, branch);
      return pc + 3;
    }
    case 168: // jsr
    {
      int32_t branch = _s2(&code[pc + 1]);
      debugf("%4d: jsr           %d\n", pc, branch);
      return pc + 3;
    }
    case 169: // ret
    {
      uint32_t index = _u1(&code[pc + 1]);
      debugf("%4d: ret           %u\n", pc, index);
      return pc + 2;
    }
    case 170: // tableswitch
    {
      TABLESWITCH_ARGS;
      debugf("%4d: tableswitch   {\n", pc);
      TABLESWITCH_PRINT_ARGS();
      debugf("}\n");
      return TABLESWITCH_NEXT_PC;
    }
    case 171: // lookupswitch
    {
      LOOKUPSWITCH_ARGS;
      debugf("%4d: lookupswitch  {\n", pc);
      LOOKUPSWITCH_PRINT_ARGS();
      debugf("}\n");
      return LOOKUPSWITCH_NEXT_PC;
    }
    case 172: // ireturn
    {
      debugf("%4d: ireturn       \n", pc);
      return pc + 1;
    }
    case 173: // lreturn
    {
      debugf("%4d: lreturn       \n", pc);
      return pc + 1;
    }
    case 174: // freturn
    {
      debugf("%4d: freturn       \n", pc);
      return pc + 1;
    }
    case 175: // dreturn
    {
      debugf("%4d: dreturn       \n", pc);
      return pc + 1;
    }
    case 176: // areturn
    {
      debugf("%4d: areturn       \n", pc);
      return pc + 1;
    }
    case 177: // return
    {
      debugf("%4d: return        \n", pc);
      return pc + 1;
    }
    case 178: // getstatic
    {
      uint32_t index = _u2(&code[pc + 1]);
      debugf("%4d: getstatic     %u\n", pc, index);
      return pc + 3;
    }
    case 179: // putstatic
    {
      uint32_t index = _u2(&code[pc + 1]);
      debugf("%4d: putstatic     %u\n", pc, index);
      return pc + 3;
    }
    case 180: // getfield
    {
      uint32_t index = _u2(&code[pc + 1]);
      debugf("%4d: getfield      %u\n", pc, index);
      return pc + 3;
    }
    case 181: // putfield
    {
      uint32_t index = _u2(&code[pc + 1]);
      debugf("%4d: putfield      %u\n", pc, index);
      return pc + 3;
    }
    case 182: // invokevirtual
    {
      uint32_t index = _u2(&code[pc + 1]);
      debugf("%4d: invokevirtual %u\n", pc, index);
      return pc + 3;
    }
    case 183: // invokespecial
    {
      uint32_t index = _u2(&code[pc + 1]);
      debugf("%4d: invokespecial %u\n", pc, index);
      return pc + 3;
    }
    case 184: // invokestatic
    {
      uint32_t index = _u2(&code[pc + 1]);
      debugf("%4d: invokestatic  %u\n", pc, index);
      return pc + 3;
    }
    case 185: // invokeinterface
    {
      uint32_t index = _u2(&code[pc + 1]);
      uint32_t count = _u1(&code[pc + 3]);
      debugf("%4d: invokeinterface %u, %u\n", pc, index, count);
      return pc + 5;
    }
    case 186: // invokedynamic
    {
      uint32_t index = _u2(&code[pc + 1]);
      debugf("%4d: invokedynamic %u\n", pc, index);
      return pc + 5;
    }
    case 187: // new
    {
      uint32_t index = _u2(&code[pc + 1]);
      debugf("%4d: new           %u\n", pc, index);
      return pc + 3;
    }
    case 188: // newarray
    {
      uint32_t atype = _u1(&code[pc + 1]);
      debugf("%4d: newarray      %u\n", pc, atype);
      return pc + 2;
    }
    case 189: // anewarray
    {
      uint32_t index = _u2(&code[pc + 1]);
      debugf("%4d: anewarray     %u\n", pc, index);
      return pc + 3;
    }
    case 190: // arraylength
    {
      debugf("%4d: arraylength   \n", pc);
      return pc + 1;
    }
    case 191: // athrow
    {
      debugf("%4d: athrow        \n", pc);
      return pc + 1;
    }
    case 192: // checkcast
    {
      uint32_t index = _u2(&code[pc + 1]);
      debugf("%4d: checkcast     %u\n", pc, index);
      return pc + 3;
    }
    case 193: // instanceof
    {
      uint32_t index = _u2(&code[pc + 1]);
      debugf("%4d: instanceof    %u\n", pc, index);
      return pc + 3;
    }
    case 194: // monitorenter
    {
      debugf("%4d: monitorenter  \n", pc);
      return pc + 1;
    }
    case 195: // monitorexit
    {
      debugf("%4d: monitorexit   \n", pc);
      return pc + 1;
    }
    case 196: // wide
    {
      WIDE_ARGS;
      debugf("%4d: wide          {\n", pc);
      WIDE_PRINT_ARGS();
      debugf("}\n");
      return WIDE_NEXT_PC;
    }
    case 197: // multianewarray
    {
      uint32_t index = _u2(&code[pc + 1]);
      uint32_t dimensions = _u1(&code[pc + 3]);
      debugf("%4d: multianewarray %u, %u\n", pc, index, dimensions);
      return pc + 4;
    }
    case 198: // ifnull
    {
      int32_t branch = _s2(&code[pc + 1]);
      debugf("%4d: ifnull        %d\n", pc, branch);
      return pc + 3;
    }
    case 199: // ifnonnull
    {
      int32_t branch = _s2(&code[pc + 1]);
      debugf("%4d: ifnonnull     %d\n", pc, branch);
      return pc + 3;
    }
    case 200: // goto_w
    {
      int32_t branch = _s2(&code[pc + 1]);
      debugf("%4d: goto_w        %d\n", pc, branch);
      return pc + 3;
    }
    case 201: // jsr_w
    {
      int32_t branch = _s4(&code[pc + 1]);
      debugf("%4d: jsr_w         %d\n", pc, branch);
      return pc + 5;
    }
    case 202: // breakpoint
    {
      debugf("%4d: breakpoint    \n", pc);
      return pc + 1;
    }
    case 254: // impdep1
    {
      debugf("%4d: impdep1       \n", pc);
      return pc + 1;
    }
    case 255: // impdep2
    {
      debugf("%4d: impdep2       \n", pc);
      return pc + 1;
    }
    default:
    {
      assert(false);
      return pc;
    }
  }
}
void decode_execute_instruction(struct vm * vm, const uint8_t * code, uint32_t pc)
{
  switch (code[pc]) {
    case 0: // nop
    {
      vm->current_frame->next_pc = pc + 1;
      op_nop(vm);
      break;
    }
    case 1: // aconst_null
    {
      vm->current_frame->next_pc = pc + 1;
      op_aconst_null(vm);
      break;
    }
    case 2: // iconst_m1
    {
      vm->current_frame->next_pc = pc + 1;
      op_iconst_m1(vm);
      break;
    }
    case 3: // iconst_0
    {
      vm->current_frame->next_pc = pc + 1;
      op_iconst_0(vm);
      break;
    }
    case 4: // iconst_1
    {
      vm->current_frame->next_pc = pc + 1;
      op_iconst_1(vm);
      break;
    }
    case 5: // iconst_2
    {
      vm->current_frame->next_pc = pc + 1;
      op_iconst_2(vm);
      break;
    }
    case 6: // iconst_3
    {
      vm->current_frame->next_pc = pc + 1;
      op_iconst_3(vm);
      break;
    }
    case 7: // iconst_4
    {
      vm->current_frame->next_pc = pc + 1;
      op_iconst_4(vm);
      break;
    }
    case 8: // iconst_5
    {
      vm->current_frame->next_pc = pc + 1;
      op_iconst_5(vm);
      break;
    }
    case 9: // lconst_0
    {
      vm->current_frame->next_pc = pc + 1;
      op_lconst_0(vm);
      break;
    }
    case 10: // lconst_1
    {
      vm->current_frame->next_pc = pc + 1;
      op_lconst_1(vm);
      break;
    }
    case 11: // fconst_0
    {
      vm->current_frame->next_pc = pc + 1;
      op_fconst_0(vm);
      break;
    }
    case 12: // fconst_1
    {
      vm->current_frame->next_pc = pc + 1;
      op_fconst_1(vm);
      break;
    }
    case 13: // fconst_2
    {
      vm->current_frame->next_pc = pc + 1;
      op_fconst_2(vm);
      break;
    }
    case 14: // dconst_0
    {
      vm->current_frame->next_pc = pc + 1;
      op_dconst_0(vm);
      break;
    }
    case 15: // dconst_1
    {
      vm->current_frame->next_pc = pc + 1;
      op_dconst_1(vm);
      break;
    }
    case 16: // bipush
    {
      int32_t byte = _s1(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 2;
      op_bipush(vm, byte);
      break;
    }
    case 17: // sipush
    {
      int32_t byte = _s2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_sipush(vm, byte);
      break;
    }
    case 18: // ldc
    {
      uint32_t index = _u1(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 2;
      op_ldc(vm, index);
      break;
    }
    case 19: // ldc_w
    {
      uint32_t index = _u2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_ldc_w(vm, index);
      break;
    }
    case 20: // ldc2_w
    {
      uint32_t index = _u2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_ldc2_w(vm, index);
      break;
    }
    case 21: // iload
    {
      uint32_t index = _u1(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 2;
      op_iload(vm, index);
      break;
    }
    case 22: // lload
    {
      uint32_t index = _u1(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 2;
      op_lload(vm, index);
      break;
    }
    case 23: // fload
    {
      uint32_t index = _u1(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 2;
      op_fload(vm, index);
      break;
    }
    case 24: // dload
    {
      uint32_t index = _u1(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 2;
      op_dload(vm, index);
      break;
    }
    case 25: // aload
    {
      uint32_t index = _u1(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 2;
      op_aload(vm, index);
      break;
    }
    case 26: // iload_0
    {
      vm->current_frame->next_pc = pc + 1;
      op_iload_0(vm);
      break;
    }
    case 27: // iload_1
    {
      vm->current_frame->next_pc = pc + 1;
      op_iload_1(vm);
      break;
    }
    case 28: // iload_2
    {
      vm->current_frame->next_pc = pc + 1;
      op_iload_2(vm);
      break;
    }
    case 29: // iload_3
    {
      vm->current_frame->next_pc = pc + 1;
      op_iload_3(vm);
      break;
    }
    case 30: // lload_0
    {
      vm->current_frame->next_pc = pc + 1;
      op_lload_0(vm);
      break;
    }
    case 31: // lload_1
    {
      vm->current_frame->next_pc = pc + 1;
      op_lload_1(vm);
      break;
    }
    case 32: // lload_2
    {
      vm->current_frame->next_pc = pc + 1;
      op_lload_2(vm);
      break;
    }
    case 33: // lload_3
    {
      vm->current_frame->next_pc = pc + 1;
      op_lload_3(vm);
      break;
    }
    case 34: // fload_0
    {
      vm->current_frame->next_pc = pc + 1;
      op_fload_0(vm);
      break;
    }
    case 35: // fload_1
    {
      vm->current_frame->next_pc = pc + 1;
      op_fload_1(vm);
      break;
    }
    case 36: // fload_2
    {
      vm->current_frame->next_pc = pc + 1;
      op_fload_2(vm);
      break;
    }
    case 37: // fload_3
    {
      vm->current_frame->next_pc = pc + 1;
      op_fload_3(vm);
      break;
    }
    case 38: // dload_0
    {
      vm->current_frame->next_pc = pc + 1;
      op_dload_0(vm);
      break;
    }
    case 39: // dload_1
    {
      vm->current_frame->next_pc = pc + 1;
      op_dload_1(vm);
      break;
    }
    case 40: // dload_2
    {
      vm->current_frame->next_pc = pc + 1;
      op_dload_2(vm);
      break;
    }
    case 41: // dload_3
    {
      vm->current_frame->next_pc = pc + 1;
      op_dload_3(vm);
      break;
    }
    case 42: // aload_0
    {
      vm->current_frame->next_pc = pc + 1;
      op_aload_0(vm);
      break;
    }
    case 43: // aload_1
    {
      vm->current_frame->next_pc = pc + 1;
      op_aload_1(vm);
      break;
    }
    case 44: // aload_2
    {
      vm->current_frame->next_pc = pc + 1;
      op_aload_2(vm);
      break;
    }
    case 45: // aload_3
    {
      vm->current_frame->next_pc = pc + 1;
      op_aload_3(vm);
      break;
    }
    case 46: // iaload
    {
      vm->current_frame->next_pc = pc + 1;
      op_iaload(vm);
      break;
    }
    case 47: // laload
    {
      vm->current_frame->next_pc = pc + 1;
      op_laload(vm);
      break;
    }
    case 48: // faload
    {
      vm->current_frame->next_pc = pc + 1;
      op_faload(vm);
      break;
    }
    case 49: // daload
    {
      vm->current_frame->next_pc = pc + 1;
      op_daload(vm);
      break;
    }
    case 50: // aaload
    {
      vm->current_frame->next_pc = pc + 1;
      op_aaload(vm);
      break;
    }
    case 51: // baload
    {
      vm->current_frame->next_pc = pc + 1;
      op_baload(vm);
      break;
    }
    case 52: // caload
    {
      vm->current_frame->next_pc = pc + 1;
      op_caload(vm);
      break;
    }
    case 53: // saload
    {
      vm->current_frame->next_pc = pc + 1;
      op_saload(vm);
      break;
    }
    case 54: // istore
    {
      uint32_t index = _u1(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 2;
      op_istore(vm, index);
      break;
    }
    case 55: // lstore
    {
      uint32_t index = _u1(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 2;
      op_lstore(vm, index);
      break;
    }
    case 56: // fstore
    {
      uint32_t index = _u1(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 2;
      op_fstore(vm, index);
      break;
    }
    case 57: // dstore
    {
      uint32_t index = _u1(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 2;
      op_dstore(vm, index);
      break;
    }
    case 58: // astore
    {
      uint32_t index = _u1(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 2;
      op_astore(vm, index);
      break;
    }
    case 59: // istore_0
    {
      vm->current_frame->next_pc = pc + 1;
      op_istore_0(vm);
      break;
    }
    case 60: // istore_1
    {
      vm->current_frame->next_pc = pc + 1;
      op_istore_1(vm);
      break;
    }
    case 61: // istore_2
    {
      vm->current_frame->next_pc = pc + 1;
      op_istore_2(vm);
      break;
    }
    case 62: // istore_3
    {
      vm->current_frame->next_pc = pc + 1;
      op_istore_3(vm);
      break;
    }
    case 63: // lstore_0
    {
      vm->current_frame->next_pc = pc + 1;
      op_lstore_0(vm);
      break;
    }
    case 64: // lstore_1
    {
      vm->current_frame->next_pc = pc + 1;
      op_lstore_1(vm);
      break;
    }
    case 65: // lstore_2
    {
      vm->current_frame->next_pc = pc + 1;
      op_lstore_2(vm);
      break;
    }
    case 66: // lstore_3
    {
      vm->current_frame->next_pc = pc + 1;
      op_lstore_3(vm);
      break;
    }
    case 67: // fstore_0
    {
      vm->current_frame->next_pc = pc + 1;
      op_fstore_0(vm);
      break;
    }
    case 68: // fstore_1
    {
      vm->current_frame->next_pc = pc + 1;
      op_fstore_1(vm);
      break;
    }
    case 69: // fstore_2
    {
      vm->current_frame->next_pc = pc + 1;
      op_fstore_2(vm);
      break;
    }
    case 70: // fstore_3
    {
      vm->current_frame->next_pc = pc + 1;
      op_fstore_3(vm);
      break;
    }
    case 71: // dstore_0
    {
      vm->current_frame->next_pc = pc + 1;
      op_dstore_0(vm);
      break;
    }
    case 72: // dstore_1
    {
      vm->current_frame->next_pc = pc + 1;
      op_dstore_1(vm);
      break;
    }
    case 73: // dstore_2
    {
      vm->current_frame->next_pc = pc + 1;
      op_dstore_2(vm);
      break;
    }
    case 74: // dstore_3
    {
      vm->current_frame->next_pc = pc + 1;
      op_dstore_3(vm);
      break;
    }
    case 75: // astore_0
    {
      vm->current_frame->next_pc = pc + 1;
      op_astore_0(vm);
      break;
    }
    case 76: // astore_1
    {
      vm->current_frame->next_pc = pc + 1;
      op_astore_1(vm);
      break;
    }
    case 77: // astore_2
    {
      vm->current_frame->next_pc = pc + 1;
      op_astore_2(vm);
      break;
    }
    case 78: // astore_3
    {
      vm->current_frame->next_pc = pc + 1;
      op_astore_3(vm);
      break;
    }
    case 79: // iastore
    {
      vm->current_frame->next_pc = pc + 1;
      op_iastore(vm);
      break;
    }
    case 80: // lastore
    {
      vm->current_frame->next_pc = pc + 1;
      op_lastore(vm);
      break;
    }
    case 81: // fastore
    {
      vm->current_frame->next_pc = pc + 1;
      op_fastore(vm);
      break;
    }
    case 82: // dastore
    {
      vm->current_frame->next_pc = pc + 1;
      op_dastore(vm);
      break;
    }
    case 83: // aastore
    {
      vm->current_frame->next_pc = pc + 1;
      op_aastore(vm);
      break;
    }
    case 84: // bastore
    {
      vm->current_frame->next_pc = pc + 1;
      op_bastore(vm);
      break;
    }
    case 85: // castore
    {
      vm->current_frame->next_pc = pc + 1;
      op_castore(vm);
      break;
    }
    case 86: // sastore
    {
      vm->current_frame->next_pc = pc + 1;
      op_sastore(vm);
      break;
    }
    case 87: // pop
    {
      vm->current_frame->next_pc = pc + 1;
      op_pop(vm);
      break;
    }
    case 88: // pop2
    {
      vm->current_frame->next_pc = pc + 1;
      op_pop2(vm);
      break;
    }
    case 89: // dup
    {
      vm->current_frame->next_pc = pc + 1;
      op_dup(vm);
      break;
    }
    case 90: // dup_x1
    {
      vm->current_frame->next_pc = pc + 1;
      op_dup_x1(vm);
      break;
    }
    case 91: // dup_x2
    {
      vm->current_frame->next_pc = pc + 1;
      op_dup_x2(vm);
      break;
    }
    case 92: // dup2
    {
      vm->current_frame->next_pc = pc + 1;
      op_dup2(vm);
      break;
    }
    case 93: // dup2_x1
    {
      vm->current_frame->next_pc = pc + 1;
      op_dup2_x1(vm);
      break;
    }
    case 94: // dup2_x2
    {
      vm->current_frame->next_pc = pc + 1;
      op_dup2_x2(vm);
      break;
    }
    case 95: // swap
    {
      vm->current_frame->next_pc = pc + 1;
      op_swap(vm);
      break;
    }
    case 96: // iadd
    {
      vm->current_frame->next_pc = pc + 1;
      op_iadd(vm);
      break;
    }
    case 97: // ladd
    {
      vm->current_frame->next_pc = pc + 1;
      op_ladd(vm);
      break;
    }
    case 98: // fadd
    {
      vm->current_frame->next_pc = pc + 1;
      op_fadd(vm);
      break;
    }
    case 99: // dadd
    {
      vm->current_frame->next_pc = pc + 1;
      op_dadd(vm);
      break;
    }
    case 100: // isub
    {
      vm->current_frame->next_pc = pc + 1;
      op_isub(vm);
      break;
    }
    case 101: // lsub
    {
      vm->current_frame->next_pc = pc + 1;
      op_lsub(vm);
      break;
    }
    case 102: // fsub
    {
      vm->current_frame->next_pc = pc + 1;
      op_fsub(vm);
      break;
    }
    case 103: // dsub
    {
      vm->current_frame->next_pc = pc + 1;
      op_dsub(vm);
      break;
    }
    case 104: // imul
    {
      vm->current_frame->next_pc = pc + 1;
      op_imul(vm);
      break;
    }
    case 105: // lmul
    {
      vm->current_frame->next_pc = pc + 1;
      op_lmul(vm);
      break;
    }
    case 106: // fmul
    {
      vm->current_frame->next_pc = pc + 1;
      op_fmul(vm);
      break;
    }
    case 107: // dmul
    {
      vm->current_frame->next_pc = pc + 1;
      op_dmul(vm);
      break;
    }
    case 108: // idiv
    {
      vm->current_frame->next_pc = pc + 1;
      op_idiv(vm);
      break;
    }
    case 109: // ldiv
    {
      vm->current_frame->next_pc = pc + 1;
      op_ldiv(vm);
      break;
    }
    case 110: // fdiv
    {
      vm->current_frame->next_pc = pc + 1;
      op_fdiv(vm);
      break;
    }
    case 111: // ddiv
    {
      vm->current_frame->next_pc = pc + 1;
      op_ddiv(vm);
      break;
    }
    case 112: // irem
    {
      vm->current_frame->next_pc = pc + 1;
      op_irem(vm);
      break;
    }
    case 113: // lrem
    {
      vm->current_frame->next_pc = pc + 1;
      op_lrem(vm);
      break;
    }
    case 114: // frem
    {
      vm->current_frame->next_pc = pc + 1;
      op_frem(vm);
      break;
    }
    case 115: // drem
    {
      vm->current_frame->next_pc = pc + 1;
      op_drem(vm);
      break;
    }
    case 116: // ineg
    {
      vm->current_frame->next_pc = pc + 1;
      op_ineg(vm);
      break;
    }
    case 117: // lneg
    {
      vm->current_frame->next_pc = pc + 1;
      op_lneg(vm);
      break;
    }
    case 118: // fneg
    {
      vm->current_frame->next_pc = pc + 1;
      op_fneg(vm);
      break;
    }
    case 119: // dneg
    {
      vm->current_frame->next_pc = pc + 1;
      op_dneg(vm);
      break;
    }
    case 120: // ishl
    {
      vm->current_frame->next_pc = pc + 1;
      op_ishl(vm);
      break;
    }
    case 121: // lshl
    {
      vm->current_frame->next_pc = pc + 1;
      op_lshl(vm);
      break;
    }
    case 122: // ishr
    {
      vm->current_frame->next_pc = pc + 1;
      op_ishr(vm);
      break;
    }
    case 123: // lshr
    {
      vm->current_frame->next_pc = pc + 1;
      op_lshr(vm);
      break;
    }
    case 124: // iushr
    {
      vm->current_frame->next_pc = pc + 1;
      op_iushr(vm);
      break;
    }
    case 125: // lushr
    {
      vm->current_frame->next_pc = pc + 1;
      op_lushr(vm);
      break;
    }
    case 126: // iand
    {
      vm->current_frame->next_pc = pc + 1;
      op_iand(vm);
      break;
    }
    case 127: // land
    {
      vm->current_frame->next_pc = pc + 1;
      op_land(vm);
      break;
    }
    case 128: // ior
    {
      vm->current_frame->next_pc = pc + 1;
      op_ior(vm);
      break;
    }
    case 129: // lor
    {
      vm->current_frame->next_pc = pc + 1;
      op_lor(vm);
      break;
    }
    case 130: // ixor
    {
      vm->current_frame->next_pc = pc + 1;
      op_ixor(vm);
      break;
    }
    case 131: // lxor
    {
      vm->current_frame->next_pc = pc + 1;
      op_lxor(vm);
      break;
    }
    case 132: // iinc
    {
      uint32_t index = _u1(&code[pc + 1]);
      uint32_t _const = _u1(&code[pc + 2]);
      vm->current_frame->next_pc = pc + 3;
      op_iinc(vm, index, _const);
      break;
    }
    case 133: // i2l
    {
      vm->current_frame->next_pc = pc + 1;
      op_i2l(vm);
      break;
    }
    case 134: // i2f
    {
      vm->current_frame->next_pc = pc + 1;
      op_i2f(vm);
      break;
    }
    case 135: // i2d
    {
      vm->current_frame->next_pc = pc + 1;
      op_i2d(vm);
      break;
    }
    case 136: // l2i
    {
      vm->current_frame->next_pc = pc + 1;
      op_l2i(vm);
      break;
    }
    case 137: // l2f
    {
      vm->current_frame->next_pc = pc + 1;
      op_l2f(vm);
      break;
    }
    case 138: // l2d
    {
      vm->current_frame->next_pc = pc + 1;
      op_l2d(vm);
      break;
    }
    case 139: // f2i
    {
      vm->current_frame->next_pc = pc + 1;
      op_f2i(vm);
      break;
    }
    case 140: // f2l
    {
      vm->current_frame->next_pc = pc + 1;
      op_f2l(vm);
      break;
    }
    case 141: // f2d
    {
      vm->current_frame->next_pc = pc + 1;
      op_f2d(vm);
      break;
    }
    case 142: // d2i
    {
      vm->current_frame->next_pc = pc + 1;
      op_d2i(vm);
      break;
    }
    case 143: // d2l
    {
      vm->current_frame->next_pc = pc + 1;
      op_d2l(vm);
      break;
    }
    case 144: // d2f
    {
      vm->current_frame->next_pc = pc + 1;
      op_d2f(vm);
      break;
    }
    case 145: // i2b
    {
      vm->current_frame->next_pc = pc + 1;
      op_i2b(vm);
      break;
    }
    case 146: // i2c
    {
      vm->current_frame->next_pc = pc + 1;
      op_i2c(vm);
      break;
    }
    case 147: // i2s
    {
      vm->current_frame->next_pc = pc + 1;
      op_i2s(vm);
      break;
    }
    case 148: // lcmp
    {
      vm->current_frame->next_pc = pc + 1;
      op_lcmp(vm);
      break;
    }
    case 149: // fcmpl
    {
      vm->current_frame->next_pc = pc + 1;
      op_fcmpl(vm);
      break;
    }
    case 150: // fcmpg
    {
      vm->current_frame->next_pc = pc + 1;
      op_fcmpg(vm);
      break;
    }
    case 151: // dcmpl
    {
      vm->current_frame->next_pc = pc + 1;
      op_dcmpl(vm);
      break;
    }
    case 152: // dcmpg
    {
      vm->current_frame->next_pc = pc + 1;
      op_dcmpg(vm);
      break;
    }
    case 153: // ifeq
    {
      int32_t branch = _s2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_ifeq(vm, branch);
      break;
    }
    case 154: // ifne
    {
      int32_t branch = _s2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_ifne(vm, branch);
      break;
    }
    case 155: // iflt
    {
      int32_t branch = _s2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_iflt(vm, branch);
      break;
    }
    case 156: // ifge
    {
      int32_t branch = _s2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_ifge(vm, branch);
      break;
    }
    case 157: // ifgt
    {
      int32_t branch = _s2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_ifgt(vm, branch);
      break;
    }
    case 158: // ifle
    {
      int32_t branch = _s2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_ifle(vm, branch);
      break;
    }
    case 159: // if_icmpeq
    {
      int32_t branch = _s2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_if_icmpeq(vm, branch);
      break;
    }
    case 160: // if_icmpne
    {
      int32_t branch = _s2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_if_icmpne(vm, branch);
      break;
    }
    case 161: // if_icmplt
    {
      int32_t branch = _s2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_if_icmplt(vm, branch);
      break;
    }
    case 162: // if_icmpge
    {
      int32_t branch = _s2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_if_icmpge(vm, branch);
      break;
    }
    case 163: // if_icmpgt
    {
      int32_t branch = _s2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_if_icmpgt(vm, branch);
      break;
    }
    case 164: // if_icmple
    {
      int32_t branch = _s2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_if_icmple(vm, branch);
      break;
    }
    case 165: // if_acmpeq
    {
      int32_t branch = _s2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_if_acmpeq(vm, branch);
      break;
    }
    case 166: // if_acmpne
    {
      int32_t branch = _s2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_if_acmpne(vm, branch);
      break;
    }
    case 167: // goto
    {
      int32_t branch = _s2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_goto(vm, branch);
      break;
    }
    case 168: // jsr
    {
      int32_t branch = _s2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_jsr(vm, branch);
      break;
    }
    case 169: // ret
    {
      uint32_t index = _u1(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 2;
      op_ret(vm, index);
      break;
    }
    case 170: // tableswitch
    {
      TABLESWITCH_ARGS;
      vm->current_frame->next_pc = TABLESWITCH_NEXT_PC;
      op_tableswitch(vm, defaultbyte, lowbyte, highbyte, table);
      break;
    }
    case 171: // lookupswitch
    {
      LOOKUPSWITCH_ARGS;
      vm->current_frame->next_pc = LOOKUPSWITCH_NEXT_PC;
      op_lookupswitch(vm);
      break;
    }
    case 172: // ireturn
    {
      vm->current_frame->next_pc = pc + 1;
      op_ireturn(vm);
      break;
    }
    case 173: // lreturn
    {
      vm->current_frame->next_pc = pc + 1;
      op_lreturn(vm);
      break;
    }
    case 174: // freturn
    {
      vm->current_frame->next_pc = pc + 1;
      op_freturn(vm);
      break;
    }
    case 175: // dreturn
    {
      vm->current_frame->next_pc = pc + 1;
      op_dreturn(vm);
      break;
    }
    case 176: // areturn
    {
      vm->current_frame->next_pc = pc + 1;
      op_areturn(vm);
      break;
    }
    case 177: // return
    {
      vm->current_frame->next_pc = pc + 1;
      op_return(vm);
      break;
    }
    case 178: // getstatic
    {
      uint32_t index = _u2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_getstatic(vm, index);
      break;
    }
    case 179: // putstatic
    {
      uint32_t index = _u2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_putstatic(vm, index);
      break;
    }
    case 180: // getfield
    {
      uint32_t index = _u2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_getfield(vm, index);
      break;
    }
    case 181: // putfield
    {
      uint32_t index = _u2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_putfield(vm, index);
      break;
    }
    case 182: // invokevirtual
    {
      uint32_t index = _u2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_invokevirtual(vm, index);
      break;
    }
    case 183: // invokespecial
    {
      uint32_t index = _u2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_invokespecial(vm, index);
      break;
    }
    case 184: // invokestatic
    {
      uint32_t index = _u2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_invokestatic(vm, index);
      break;
    }
    case 185: // invokeinterface
    {
      uint32_t index = _u2(&code[pc + 1]);
      uint32_t count = _u1(&code[pc + 3]);
      vm->current_frame->next_pc = pc + 5;
      op_invokeinterface(vm, index, count);
      break;
    }
    case 186: // invokedynamic
    {
      uint32_t index = _u2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 5;
      op_invokedynamic(vm, index);
      break;
    }
    case 187: // new
    {
      uint32_t index = _u2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_new(vm, index);
      break;
    }
    case 188: // newarray
    {
      uint32_t atype = _u1(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 2;
      op_newarray(vm, atype);
      break;
    }
    case 189: // anewarray
    {
      uint32_t index = _u2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_anewarray(vm, index);
      break;
    }
    case 190: // arraylength
    {
      vm->current_frame->next_pc = pc + 1;
      op_arraylength(vm);
      break;
    }
    case 191: // athrow
    {
      vm->current_frame->next_pc = pc + 1;
      op_athrow(vm);
      break;
    }
    case 192: // checkcast
    {
      uint32_t index = _u2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_checkcast(vm, index);
      break;
    }
    case 193: // instanceof
    {
      uint32_t index = _u2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_instanceof(vm, index);
      break;
    }
    case 194: // monitorenter
    {
      vm->current_frame->next_pc = pc + 1;
      op_monitorenter(vm);
      break;
    }
    case 195: // monitorexit
    {
      vm->current_frame->next_pc = pc + 1;
      op_monitorexit(vm);
      break;
    }
    case 196: // wide
    {
      WIDE_ARGS;
      vm->current_frame->next_pc = WIDE_NEXT_PC;
      op_wide(vm);
      break;
    }
    case 197: // multianewarray
    {
      uint32_t index = _u2(&code[pc + 1]);
      uint32_t dimensions = _u1(&code[pc + 3]);
      vm->current_frame->next_pc = pc + 4;
      op_multianewarray(vm, index, dimensions);
      break;
    }
    case 198: // ifnull
    {
      int32_t branch = _s2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_ifnull(vm, branch);
      break;
    }
    case 199: // ifnonnull
    {
      int32_t branch = _s2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_ifnonnull(vm, branch);
      break;
    }
    case 200: // goto_w
    {
      int32_t branch = _s2(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 3;
      op_goto_w(vm, branch);
      break;
    }
    case 201: // jsr_w
    {
      int32_t branch = _s4(&code[pc + 1]);
      vm->current_frame->next_pc = pc + 5;
      op_jsr_w(vm, branch);
      break;
    }
    case 202: // breakpoint
    {
      vm->current_frame->next_pc = pc + 1;
      op_breakpoint(vm);
      break;
    }
    case 254: // impdep1
    {
      vm->current_frame->next_pc = pc + 1;
      op_impdep1(vm);
      break;
    }
    case 255: // impdep2
    {
      vm->current_frame->next_pc = pc + 1;
      op_impdep2(vm);
      break;
    }
    default:
    {
      assert(false);
      break;
    }
  }
}
