uint32_t decode_print_instruction(const uint8_t * code, uint32_t pc)
{
  switch (code[pc]) {
    case 0: // nop
    {
      printf("%4d: nop           \n", pc);
      return pc + 1;
    }
    case 1: // aconst_null
    {
      printf("%4d: aconst_null   \n", pc);
      return pc + 1;
    }
    case 2: // iconst_m1
    {
      printf("%4d: iconst_m1     \n", pc);
      return pc + 1;
    }
    case 3: // iconst_0
    {
      printf("%4d: iconst_0      \n", pc);
      return pc + 1;
    }
    case 4: // iconst_1
    {
      printf("%4d: iconst_1      \n", pc);
      return pc + 1;
    }
    case 5: // iconst_2
    {
      printf("%4d: iconst_2      \n", pc);
      return pc + 1;
    }
    case 6: // iconst_3
    {
      printf("%4d: iconst_3      \n", pc);
      return pc + 1;
    }
    case 7: // iconst_4
    {
      printf("%4d: iconst_4      \n", pc);
      return pc + 1;
    }
    case 8: // iconst_5
    {
      printf("%4d: iconst_5      \n", pc);
      return pc + 1;
    }
    case 9: // lconst_0
    {
      printf("%4d: lconst_0      \n", pc);
      return pc + 1;
    }
    case 10: // lconst_1
    {
      printf("%4d: lconst_1      \n", pc);
      return pc + 1;
    }
    case 11: // fconst_0
    {
      printf("%4d: fconst_0      \n", pc);
      return pc + 1;
    }
    case 12: // fconst_1
    {
      printf("%4d: fconst_1      \n", pc);
      return pc + 1;
    }
    case 13: // fconst_2
    {
      printf("%4d: fconst_2      \n", pc);
      return pc + 1;
    }
    case 14: // dconst_0
    {
      printf("%4d: dconst_0      \n", pc);
      return pc + 1;
    }
    case 15: // dconst_1
    {
      printf("%4d: dconst_1      \n", pc);
      return pc + 1;
    }
    case 16: // bipush
    {
      int32_t byte = _s1(&code[pc + 1]);
      printf("%4d: bipush        %d\n", pc, byte);
      return pc + 2;
    }
    case 17: // sipush
    {
      int32_t byte = _s2(&code[pc + 1]);
      printf("%4d: sipush        %d\n", pc, byte);
      return pc + 3;
    }
    case 18: // ldc
    {
      uint32_t index = _u1(&code[pc + 1]);
      printf("%4d: ldc           %u\n", pc, index);
      return pc + 2;
    }
    case 19: // ldc_w
    {
      uint32_t index = _u2(&code[pc + 1]);
      printf("%4d: ldc_w         %u\n", pc, index);
      return pc + 3;
    }
    case 20: // ldc2_w
    {
      uint32_t index = _u2(&code[pc + 1]);
      printf("%4d: ldc2_w        %u\n", pc, index);
      return pc + 3;
    }
    case 21: // iload
    {
      uint32_t index = _u1(&code[pc + 1]);
      printf("%4d: iload         %u\n", pc, index);
      return pc + 2;
    }
    case 22: // lload
    {
      uint32_t index = _u1(&code[pc + 1]);
      printf("%4d: lload         %u\n", pc, index);
      return pc + 2;
    }
    case 23: // fload
    {
      uint32_t index = _u1(&code[pc + 1]);
      printf("%4d: fload         %u\n", pc, index);
      return pc + 2;
    }
    case 24: // dload
    {
      uint32_t index = _u1(&code[pc + 1]);
      printf("%4d: dload         %u\n", pc, index);
      return pc + 2;
    }
    case 25: // aload
    {
      uint32_t index = _u1(&code[pc + 1]);
      printf("%4d: aload         %u\n", pc, index);
      return pc + 2;
    }
    case 26: // iload_0
    {
      printf("%4d: iload_0       \n", pc);
      return pc + 1;
    }
    case 27: // iload_1
    {
      printf("%4d: iload_1       \n", pc);
      return pc + 1;
    }
    case 28: // iload_2
    {
      printf("%4d: iload_2       \n", pc);
      return pc + 1;
    }
    case 29: // iload_3
    {
      printf("%4d: iload_3       \n", pc);
      return pc + 1;
    }
    case 30: // lload_0
    {
      printf("%4d: lload_0       \n", pc);
      return pc + 1;
    }
    case 31: // lload_1
    {
      printf("%4d: lload_1       \n", pc);
      return pc + 1;
    }
    case 32: // lload_2
    {
      printf("%4d: lload_2       \n", pc);
      return pc + 1;
    }
    case 33: // lload_3
    {
      printf("%4d: lload_3       \n", pc);
      return pc + 1;
    }
    case 34: // fload_0
    {
      printf("%4d: fload_0       \n", pc);
      return pc + 1;
    }
    case 35: // fload_1
    {
      printf("%4d: fload_1       \n", pc);
      return pc + 1;
    }
    case 36: // fload_2
    {
      printf("%4d: fload_2       \n", pc);
      return pc + 1;
    }
    case 37: // fload_3
    {
      printf("%4d: fload_3       \n", pc);
      return pc + 1;
    }
    case 38: // dload_0
    {
      printf("%4d: dload_0       \n", pc);
      return pc + 1;
    }
    case 39: // dload_1
    {
      printf("%4d: dload_1       \n", pc);
      return pc + 1;
    }
    case 40: // dload_2
    {
      printf("%4d: dload_2       \n", pc);
      return pc + 1;
    }
    case 41: // dload_3
    {
      printf("%4d: dload_3       \n", pc);
      return pc + 1;
    }
    case 42: // aload_0
    {
      printf("%4d: aload_0       \n", pc);
      return pc + 1;
    }
    case 43: // aload_1
    {
      printf("%4d: aload_1       \n", pc);
      return pc + 1;
    }
    case 44: // aload_2
    {
      printf("%4d: aload_2       \n", pc);
      return pc + 1;
    }
    case 45: // aload_3
    {
      printf("%4d: aload_3       \n", pc);
      return pc + 1;
    }
    case 46: // iaload
    {
      printf("%4d: iaload        \n", pc);
      return pc + 1;
    }
    case 47: // laload
    {
      printf("%4d: laload        \n", pc);
      return pc + 1;
    }
    case 48: // faload
    {
      printf("%4d: faload        \n", pc);
      return pc + 1;
    }
    case 49: // daload
    {
      printf("%4d: daload        \n", pc);
      return pc + 1;
    }
    case 50: // aaload
    {
      printf("%4d: aaload        \n", pc);
      return pc + 1;
    }
    case 51: // baload
    {
      printf("%4d: baload        \n", pc);
      return pc + 1;
    }
    case 52: // caload
    {
      printf("%4d: caload        \n", pc);
      return pc + 1;
    }
    case 53: // saload
    {
      printf("%4d: saload        \n", pc);
      return pc + 1;
    }
    case 54: // istore
    {
      uint32_t index = _u1(&code[pc + 1]);
      printf("%4d: istore        %u\n", pc, index);
      return pc + 2;
    }
    case 55: // lstore
    {
      uint32_t index = _u1(&code[pc + 1]);
      printf("%4d: lstore        %u\n", pc, index);
      return pc + 2;
    }
    case 56: // fstore
    {
      uint32_t index = _u1(&code[pc + 1]);
      printf("%4d: fstore        %u\n", pc, index);
      return pc + 2;
    }
    case 57: // dstore
    {
      uint32_t index = _u1(&code[pc + 1]);
      printf("%4d: dstore        %u\n", pc, index);
      return pc + 2;
    }
    case 58: // astore
    {
      uint32_t index = _u1(&code[pc + 1]);
      printf("%4d: astore        %u\n", pc, index);
      return pc + 2;
    }
    case 59: // istore_0
    {
      printf("%4d: istore_0      \n", pc);
      return pc + 1;
    }
    case 60: // istore_1
    {
      printf("%4d: istore_1      \n", pc);
      return pc + 1;
    }
    case 61: // istore_2
    {
      printf("%4d: istore_2      \n", pc);
      return pc + 1;
    }
    case 62: // istore_3
    {
      printf("%4d: istore_3      \n", pc);
      return pc + 1;
    }
    case 63: // lstore_0
    {
      printf("%4d: lstore_0      \n", pc);
      return pc + 1;
    }
    case 64: // lstore_1
    {
      printf("%4d: lstore_1      \n", pc);
      return pc + 1;
    }
    case 65: // lstore_2
    {
      printf("%4d: lstore_2      \n", pc);
      return pc + 1;
    }
    case 66: // lstore_3
    {
      printf("%4d: lstore_3      \n", pc);
      return pc + 1;
    }
    case 67: // fstore_0
    {
      printf("%4d: fstore_0      \n", pc);
      return pc + 1;
    }
    case 68: // fstore_1
    {
      printf("%4d: fstore_1      \n", pc);
      return pc + 1;
    }
    case 69: // fstore_2
    {
      printf("%4d: fstore_2      \n", pc);
      return pc + 1;
    }
    case 70: // fstore_3
    {
      printf("%4d: fstore_3      \n", pc);
      return pc + 1;
    }
    case 71: // dstore_0
    {
      printf("%4d: dstore_0      \n", pc);
      return pc + 1;
    }
    case 72: // dstore_1
    {
      printf("%4d: dstore_1      \n", pc);
      return pc + 1;
    }
    case 73: // dstore_2
    {
      printf("%4d: dstore_2      \n", pc);
      return pc + 1;
    }
    case 74: // dstore_3
    {
      printf("%4d: dstore_3      \n", pc);
      return pc + 1;
    }
    case 75: // astore_0
    {
      printf("%4d: astore_0      \n", pc);
      return pc + 1;
    }
    case 76: // astore_1
    {
      printf("%4d: astore_1      \n", pc);
      return pc + 1;
    }
    case 77: // astore_2
    {
      printf("%4d: astore_2      \n", pc);
      return pc + 1;
    }
    case 78: // astore_3
    {
      printf("%4d: astore_3      \n", pc);
      return pc + 1;
    }
    case 79: // iastore
    {
      printf("%4d: iastore       \n", pc);
      return pc + 1;
    }
    case 80: // lastore
    {
      printf("%4d: lastore       \n", pc);
      return pc + 1;
    }
    case 81: // fastore
    {
      printf("%4d: fastore       \n", pc);
      return pc + 1;
    }
    case 82: // dastore
    {
      printf("%4d: dastore       \n", pc);
      return pc + 1;
    }
    case 83: // aastore
    {
      printf("%4d: aastore       \n", pc);
      return pc + 1;
    }
    case 84: // bastore
    {
      printf("%4d: bastore       \n", pc);
      return pc + 1;
    }
    case 85: // castore
    {
      printf("%4d: castore       \n", pc);
      return pc + 1;
    }
    case 86: // sastore
    {
      printf("%4d: sastore       \n", pc);
      return pc + 1;
    }
    case 87: // pop
    {
      printf("%4d: pop           \n", pc);
      return pc + 1;
    }
    case 88: // pop2
    {
      printf("%4d: pop2          \n", pc);
      return pc + 1;
    }
    case 89: // dup
    {
      printf("%4d: dup           \n", pc);
      return pc + 1;
    }
    case 90: // dup_x1
    {
      printf("%4d: dup_x1        \n", pc);
      return pc + 1;
    }
    case 91: // dup_x2
    {
      printf("%4d: dup_x2        \n", pc);
      return pc + 1;
    }
    case 92: // dup2
    {
      printf("%4d: dup2          \n", pc);
      return pc + 1;
    }
    case 93: // dup2_x1
    {
      printf("%4d: dup2_x1       \n", pc);
      return pc + 1;
    }
    case 94: // dup2_x2
    {
      printf("%4d: dup2_x2       \n", pc);
      return pc + 1;
    }
    case 95: // swap
    {
      printf("%4d: swap          \n", pc);
      return pc + 1;
    }
    case 96: // iadd
    {
      printf("%4d: iadd          \n", pc);
      return pc + 1;
    }
    case 97: // ladd
    {
      printf("%4d: ladd          \n", pc);
      return pc + 1;
    }
    case 98: // fadd
    {
      printf("%4d: fadd          \n", pc);
      return pc + 1;
    }
    case 99: // dadd
    {
      printf("%4d: dadd          \n", pc);
      return pc + 1;
    }
    case 100: // isub
    {
      printf("%4d: isub          \n", pc);
      return pc + 1;
    }
    case 101: // lsub
    {
      printf("%4d: lsub          \n", pc);
      return pc + 1;
    }
    case 102: // fsub
    {
      printf("%4d: fsub          \n", pc);
      return pc + 1;
    }
    case 103: // dsub
    {
      printf("%4d: dsub          \n", pc);
      return pc + 1;
    }
    case 104: // imul
    {
      printf("%4d: imul          \n", pc);
      return pc + 1;
    }
    case 105: // lmul
    {
      printf("%4d: lmul          \n", pc);
      return pc + 1;
    }
    case 106: // fmul
    {
      printf("%4d: fmul          \n", pc);
      return pc + 1;
    }
    case 107: // dmul
    {
      printf("%4d: dmul          \n", pc);
      return pc + 1;
    }
    case 108: // idiv
    {
      printf("%4d: idiv          \n", pc);
      return pc + 1;
    }
    case 109: // ldiv
    {
      printf("%4d: ldiv          \n", pc);
      return pc + 1;
    }
    case 110: // fdiv
    {
      printf("%4d: fdiv          \n", pc);
      return pc + 1;
    }
    case 111: // ddiv
    {
      printf("%4d: ddiv          \n", pc);
      return pc + 1;
    }
    case 112: // irem
    {
      printf("%4d: irem          \n", pc);
      return pc + 1;
    }
    case 113: // lrem
    {
      printf("%4d: lrem          \n", pc);
      return pc + 1;
    }
    case 114: // frem
    {
      printf("%4d: frem          \n", pc);
      return pc + 1;
    }
    case 115: // drem
    {
      printf("%4d: drem          \n", pc);
      return pc + 1;
    }
    case 116: // ineg
    {
      printf("%4d: ineg          \n", pc);
      return pc + 1;
    }
    case 117: // lneg
    {
      printf("%4d: lneg          \n", pc);
      return pc + 1;
    }
    case 118: // fneg
    {
      printf("%4d: fneg          \n", pc);
      return pc + 1;
    }
    case 119: // dneg
    {
      printf("%4d: dneg          \n", pc);
      return pc + 1;
    }
    case 120: // ishl
    {
      printf("%4d: ishl          \n", pc);
      return pc + 1;
    }
    case 121: // lshl
    {
      printf("%4d: lshl          \n", pc);
      return pc + 1;
    }
    case 122: // ishr
    {
      printf("%4d: ishr          \n", pc);
      return pc + 1;
    }
    case 123: // lshr
    {
      printf("%4d: lshr          \n", pc);
      return pc + 1;
    }
    case 124: // iushr
    {
      printf("%4d: iushr         \n", pc);
      return pc + 1;
    }
    case 125: // lushr
    {
      printf("%4d: lushr         \n", pc);
      return pc + 1;
    }
    case 126: // iand
    {
      printf("%4d: iand          \n", pc);
      return pc + 1;
    }
    case 127: // land
    {
      printf("%4d: land          \n", pc);
      return pc + 1;
    }
    case 128: // ior
    {
      printf("%4d: ior           \n", pc);
      return pc + 1;
    }
    case 129: // lor
    {
      printf("%4d: lor           \n", pc);
      return pc + 1;
    }
    case 130: // ixor
    {
      printf("%4d: ixor          \n", pc);
      return pc + 1;
    }
    case 131: // lxor
    {
      printf("%4d: lxor          \n", pc);
      return pc + 1;
    }
    case 132: // iinc
    {
      uint32_t index = _u1(&code[pc + 1]);
      uint32_t _const = _u1(&code[pc + 2]);
      printf("%4d: iinc          %u, %u\n", pc, index, _const);
      return pc + 3;
    }
    case 133: // i2l
    {
      printf("%4d: i2l           \n", pc);
      return pc + 1;
    }
    case 134: // i2f
    {
      printf("%4d: i2f           \n", pc);
      return pc + 1;
    }
    case 135: // i2d
    {
      printf("%4d: i2d           \n", pc);
      return pc + 1;
    }
    case 136: // l2i
    {
      printf("%4d: l2i           \n", pc);
      return pc + 1;
    }
    case 137: // l2f
    {
      printf("%4d: l2f           \n", pc);
      return pc + 1;
    }
    case 138: // l2d
    {
      printf("%4d: l2d           \n", pc);
      return pc + 1;
    }
    case 139: // f2i
    {
      printf("%4d: f2i           \n", pc);
      return pc + 1;
    }
    case 140: // f2l
    {
      printf("%4d: f2l           \n", pc);
      return pc + 1;
    }
    case 141: // f2d
    {
      printf("%4d: f2d           \n", pc);
      return pc + 1;
    }
    case 142: // d2i
    {
      printf("%4d: d2i           \n", pc);
      return pc + 1;
    }
    case 143: // d2l
    {
      printf("%4d: d2l           \n", pc);
      return pc + 1;
    }
    case 144: // d2f
    {
      printf("%4d: d2f           \n", pc);
      return pc + 1;
    }
    case 145: // i2b
    {
      printf("%4d: i2b           \n", pc);
      return pc + 1;
    }
    case 146: // i2c
    {
      printf("%4d: i2c           \n", pc);
      return pc + 1;
    }
    case 147: // i2s
    {
      printf("%4d: i2s           \n", pc);
      return pc + 1;
    }
    case 148: // lcmp
    {
      printf("%4d: lcmp          \n", pc);
      return pc + 1;
    }
    case 149: // fcmpl
    {
      printf("%4d: fcmpl         \n", pc);
      return pc + 1;
    }
    case 150: // fcmpg
    {
      printf("%4d: fcmpg         \n", pc);
      return pc + 1;
    }
    case 151: // dcmpl
    {
      printf("%4d: dcmpl         \n", pc);
      return pc + 1;
    }
    case 152: // dcmpg
    {
      printf("%4d: dcmpg         \n", pc);
      return pc + 1;
    }
    case 153: // ifeq
    {
      int32_t branch = _s2(&code[pc + 1]);
      printf("%4d: ifeq          %d\n", pc, branch);
      return pc + 3;
    }
    case 154: // ifne
    {
      int32_t branch = _s2(&code[pc + 1]);
      printf("%4d: ifne          %d\n", pc, branch);
      return pc + 3;
    }
    case 155: // iflt
    {
      int32_t branch = _s2(&code[pc + 1]);
      printf("%4d: iflt          %d\n", pc, branch);
      return pc + 3;
    }
    case 156: // ifge
    {
      int32_t branch = _s2(&code[pc + 1]);
      printf("%4d: ifge          %d\n", pc, branch);
      return pc + 3;
    }
    case 157: // ifgt
    {
      int32_t branch = _s2(&code[pc + 1]);
      printf("%4d: ifgt          %d\n", pc, branch);
      return pc + 3;
    }
    case 158: // ifle
    {
      int32_t branch = _s2(&code[pc + 1]);
      printf("%4d: ifle          %d\n", pc, branch);
      return pc + 3;
    }
    case 159: // if_icmpeq
    {
      int32_t branch = _s2(&code[pc + 1]);
      printf("%4d: if_icmpeq     %d\n", pc, branch);
      return pc + 3;
    }
    case 160: // if_icmpne
    {
      int32_t branch = _s2(&code[pc + 1]);
      printf("%4d: if_icmpne     %d\n", pc, branch);
      return pc + 3;
    }
    case 161: // if_icmplt
    {
      int32_t branch = _s2(&code[pc + 1]);
      printf("%4d: if_icmplt     %d\n", pc, branch);
      return pc + 3;
    }
    case 162: // if_icmpge
    {
      int32_t branch = _s2(&code[pc + 1]);
      printf("%4d: if_icmpge     %d\n", pc, branch);
      return pc + 3;
    }
    case 163: // if_icmpgt
    {
      int32_t branch = _s2(&code[pc + 1]);
      printf("%4d: if_icmpgt     %d\n", pc, branch);
      return pc + 3;
    }
    case 164: // if_icmple
    {
      int32_t branch = _s2(&code[pc + 1]);
      printf("%4d: if_icmple     %d\n", pc, branch);
      return pc + 3;
    }
    case 165: // if_acmpeq
    {
      int32_t branch = _s2(&code[pc + 1]);
      printf("%4d: if_acmpeq     %d\n", pc, branch);
      return pc + 3;
    }
    case 166: // if_acmpne
    {
      int32_t branch = _s2(&code[pc + 1]);
      printf("%4d: if_acmpne     %d\n", pc, branch);
      return pc + 3;
    }
    case 167: // goto
    {
      int32_t branch = _s2(&code[pc + 1]);
      printf("%4d: goto          %d\n", pc, branch);
      return pc + 3;
    }
    case 168: // jsr
    {
      int32_t branch = _s2(&code[pc + 1]);
      printf("%4d: jsr           %d\n", pc, branch);
      return pc + 3;
    }
    case 169: // ret
    {
      uint32_t index = _u1(&code[pc + 1]);
      printf("%4d: ret           %u\n", pc, index);
      return pc + 2;
    }
    case 170: // tableswitch
    {
      TABLESWITCH_ARGS;
      printf("%4d: tableswitch   {\n", pc);
      TABLESWITCH_PRINT_ARGS();
      printf("}\n");
      return TABLESWITCH_NEXT_PC;
    }
    case 171: // lookupswitch
    {
      LOOKUPSWITCH_ARGS;
      printf("%4d: lookupswitch  {\n", pc);
      LOOKUPSWITCH_PRINT_ARGS();
      printf("}\n");
      return LOOKUPSWITCH_NEXT_PC;
    }
    case 172: // ireturn
    {
      printf("%4d: ireturn       \n", pc);
      return pc + 1;
    }
    case 173: // lreturn
    {
      printf("%4d: lreturn       \n", pc);
      return pc + 1;
    }
    case 174: // freturn
    {
      printf("%4d: freturn       \n", pc);
      return pc + 1;
    }
    case 175: // dreturn
    {
      printf("%4d: dreturn       \n", pc);
      return pc + 1;
    }
    case 176: // areturn
    {
      printf("%4d: areturn       \n", pc);
      return pc + 1;
    }
    case 177: // return
    {
      printf("%4d: return        \n", pc);
      return pc + 1;
    }
    case 178: // getstatic
    {
      uint32_t index = _u2(&code[pc + 1]);
      printf("%4d: getstatic     %u\n", pc, index);
      return pc + 3;
    }
    case 179: // putstatic
    {
      uint32_t index = _u2(&code[pc + 1]);
      printf("%4d: putstatic     %u\n", pc, index);
      return pc + 3;
    }
    case 180: // getfield
    {
      uint32_t index = _u2(&code[pc + 1]);
      printf("%4d: getfield      %u\n", pc, index);
      return pc + 3;
    }
    case 181: // putfield
    {
      uint32_t index = _u2(&code[pc + 1]);
      printf("%4d: putfield      %u\n", pc, index);
      return pc + 3;
    }
    case 182: // invokevirtual
    {
      uint32_t index = _u2(&code[pc + 1]);
      printf("%4d: invokevirtual %u\n", pc, index);
      return pc + 3;
    }
    case 183: // invokespecial
    {
      uint32_t index = _u2(&code[pc + 1]);
      printf("%4d: invokespecial %u\n", pc, index);
      return pc + 3;
    }
    case 184: // invokestatic
    {
      uint32_t index = _u2(&code[pc + 1]);
      printf("%4d: invokestatic  %u\n", pc, index);
      return pc + 3;
    }
    case 185: // invokeinterface
    {
      uint32_t index = _u2(&code[pc + 1]);
      uint32_t count = _u1(&code[pc + 3]);
      printf("%4d: invokeinterface %u, %u\n", pc, index, count);
      return pc + 5;
    }
    case 186: // invokedynamic
    {
      uint32_t index = _u2(&code[pc + 1]);
      printf("%4d: invokedynamic %u\n", pc, index);
      return pc + 5;
    }
    case 187: // new
    {
      uint32_t index = _u2(&code[pc + 1]);
      printf("%4d: new           %u\n", pc, index);
      return pc + 3;
    }
    case 188: // newarray
    {
      uint32_t atype = _u1(&code[pc + 1]);
      printf("%4d: newarray      %u\n", pc, atype);
      return pc + 2;
    }
    case 189: // anewarray
    {
      uint32_t index = _u2(&code[pc + 1]);
      printf("%4d: anewarray     %u\n", pc, index);
      return pc + 3;
    }
    case 190: // arraylength
    {
      printf("%4d: arraylength   \n", pc);
      return pc + 1;
    }
    case 191: // athrow
    {
      printf("%4d: athrow        \n", pc);
      return pc + 1;
    }
    case 192: // checkcast
    {
      uint32_t index = _u2(&code[pc + 1]);
      printf("%4d: checkcast     %u\n", pc, index);
      return pc + 3;
    }
    case 193: // instanceof
    {
      uint32_t index = _u2(&code[pc + 1]);
      printf("%4d: instanceof    %u\n", pc, index);
      return pc + 3;
    }
    case 194: // monitorenter
    {
      printf("%4d: monitorenter  \n", pc);
      return pc + 1;
    }
    case 195: // monitorexit
    {
      printf("%4d: monitorexit   \n", pc);
      return pc + 1;
    }
    case 196: // wide
    {
      WIDE_ARGS;
      printf("%4d: wide          {\n", pc);
      WIDE_PRINT_ARGS();
      printf("}\n");
      return WIDE_NEXT_PC;
    }
    case 197: // multianewarray
    {
      uint32_t index = _u2(&code[pc + 1]);
      uint32_t dimensions = _u1(&code[pc + 3]);
      printf("%4d: multianewarray %u, %u\n", pc, index, dimensions);
      return pc + 4;
    }
    case 198: // ifnull
    {
      int32_t branch = _s2(&code[pc + 1]);
      printf("%4d: ifnull        %d\n", pc, branch);
      return pc + 3;
    }
    case 199: // ifnonnull
    {
      int32_t branch = _s2(&code[pc + 1]);
      printf("%4d: ifnonnull     %d\n", pc, branch);
      return pc + 3;
    }
    case 200: // goto_w
    {
      int32_t branch = _s2(&code[pc + 1]);
      printf("%4d: goto_w        %d\n", pc, branch);
      return pc + 3;
    }
    case 201: // jsr_w
    {
      int32_t branch = _s4(&code[pc + 1]);
      printf("%4d: jsr_w         %d\n", pc, branch);
      return pc + 5;
    }
    case 202: // breakpoint
    {
      printf("%4d: breakpoint    \n", pc);
      return pc + 1;
    }
    case 254: // impdep1
    {
      printf("%4d: impdep1       \n", pc);
      return pc + 1;
    }
    case 255: // impdep2
    {
      printf("%4d: impdep2       \n", pc);
      return pc + 1;
    }
    default:
    {
      assert(false);
      return pc;
    }
  }
}
uint32_t decode_execute_instruction(struct vm * vm, const uint8_t * code, uint32_t pc)
{
  switch (code[pc]) {
    case 0: // nop
    {
      op_nop(vm);
      return pc + 1;
    }
    case 1: // aconst_null
    {
      op_aconst_null(vm);
      return pc + 1;
    }
    case 2: // iconst_m1
    {
      op_iconst_m1(vm);
      return pc + 1;
    }
    case 3: // iconst_0
    {
      op_iconst_0(vm);
      return pc + 1;
    }
    case 4: // iconst_1
    {
      op_iconst_1(vm);
      return pc + 1;
    }
    case 5: // iconst_2
    {
      op_iconst_2(vm);
      return pc + 1;
    }
    case 6: // iconst_3
    {
      op_iconst_3(vm);
      return pc + 1;
    }
    case 7: // iconst_4
    {
      op_iconst_4(vm);
      return pc + 1;
    }
    case 8: // iconst_5
    {
      op_iconst_5(vm);
      return pc + 1;
    }
    case 9: // lconst_0
    {
      op_lconst_0(vm);
      return pc + 1;
    }
    case 10: // lconst_1
    {
      op_lconst_1(vm);
      return pc + 1;
    }
    case 11: // fconst_0
    {
      op_fconst_0(vm);
      return pc + 1;
    }
    case 12: // fconst_1
    {
      op_fconst_1(vm);
      return pc + 1;
    }
    case 13: // fconst_2
    {
      op_fconst_2(vm);
      return pc + 1;
    }
    case 14: // dconst_0
    {
      op_dconst_0(vm);
      return pc + 1;
    }
    case 15: // dconst_1
    {
      op_dconst_1(vm);
      return pc + 1;
    }
    case 16: // bipush
    {
      int32_t byte = _s1(&code[pc + 1]);
      op_bipush(vm, byte);
      return pc + 2;
    }
    case 17: // sipush
    {
      int32_t byte = _s2(&code[pc + 1]);
      op_sipush(vm, byte);
      return pc + 3;
    }
    case 18: // ldc
    {
      uint32_t index = _u1(&code[pc + 1]);
      op_ldc(vm, index);
      return pc + 2;
    }
    case 19: // ldc_w
    {
      uint32_t index = _u2(&code[pc + 1]);
      op_ldc_w(vm, index);
      return pc + 3;
    }
    case 20: // ldc2_w
    {
      uint32_t index = _u2(&code[pc + 1]);
      op_ldc2_w(vm, index);
      return pc + 3;
    }
    case 21: // iload
    {
      uint32_t index = _u1(&code[pc + 1]);
      op_iload(vm, index);
      return pc + 2;
    }
    case 22: // lload
    {
      uint32_t index = _u1(&code[pc + 1]);
      op_lload(vm, index);
      return pc + 2;
    }
    case 23: // fload
    {
      uint32_t index = _u1(&code[pc + 1]);
      op_fload(vm, index);
      return pc + 2;
    }
    case 24: // dload
    {
      uint32_t index = _u1(&code[pc + 1]);
      op_dload(vm, index);
      return pc + 2;
    }
    case 25: // aload
    {
      uint32_t index = _u1(&code[pc + 1]);
      op_aload(vm, index);
      return pc + 2;
    }
    case 26: // iload_0
    {
      op_iload_0(vm);
      return pc + 1;
    }
    case 27: // iload_1
    {
      op_iload_1(vm);
      return pc + 1;
    }
    case 28: // iload_2
    {
      op_iload_2(vm);
      return pc + 1;
    }
    case 29: // iload_3
    {
      op_iload_3(vm);
      return pc + 1;
    }
    case 30: // lload_0
    {
      op_lload_0(vm);
      return pc + 1;
    }
    case 31: // lload_1
    {
      op_lload_1(vm);
      return pc + 1;
    }
    case 32: // lload_2
    {
      op_lload_2(vm);
      return pc + 1;
    }
    case 33: // lload_3
    {
      op_lload_3(vm);
      return pc + 1;
    }
    case 34: // fload_0
    {
      op_fload_0(vm);
      return pc + 1;
    }
    case 35: // fload_1
    {
      op_fload_1(vm);
      return pc + 1;
    }
    case 36: // fload_2
    {
      op_fload_2(vm);
      return pc + 1;
    }
    case 37: // fload_3
    {
      op_fload_3(vm);
      return pc + 1;
    }
    case 38: // dload_0
    {
      op_dload_0(vm);
      return pc + 1;
    }
    case 39: // dload_1
    {
      op_dload_1(vm);
      return pc + 1;
    }
    case 40: // dload_2
    {
      op_dload_2(vm);
      return pc + 1;
    }
    case 41: // dload_3
    {
      op_dload_3(vm);
      return pc + 1;
    }
    case 42: // aload_0
    {
      op_aload_0(vm);
      return pc + 1;
    }
    case 43: // aload_1
    {
      op_aload_1(vm);
      return pc + 1;
    }
    case 44: // aload_2
    {
      op_aload_2(vm);
      return pc + 1;
    }
    case 45: // aload_3
    {
      op_aload_3(vm);
      return pc + 1;
    }
    case 46: // iaload
    {
      op_iaload(vm);
      return pc + 1;
    }
    case 47: // laload
    {
      op_laload(vm);
      return pc + 1;
    }
    case 48: // faload
    {
      op_faload(vm);
      return pc + 1;
    }
    case 49: // daload
    {
      op_daload(vm);
      return pc + 1;
    }
    case 50: // aaload
    {
      op_aaload(vm);
      return pc + 1;
    }
    case 51: // baload
    {
      op_baload(vm);
      return pc + 1;
    }
    case 52: // caload
    {
      op_caload(vm);
      return pc + 1;
    }
    case 53: // saload
    {
      op_saload(vm);
      return pc + 1;
    }
    case 54: // istore
    {
      uint32_t index = _u1(&code[pc + 1]);
      op_istore(vm, index);
      return pc + 2;
    }
    case 55: // lstore
    {
      uint32_t index = _u1(&code[pc + 1]);
      op_lstore(vm, index);
      return pc + 2;
    }
    case 56: // fstore
    {
      uint32_t index = _u1(&code[pc + 1]);
      op_fstore(vm, index);
      return pc + 2;
    }
    case 57: // dstore
    {
      uint32_t index = _u1(&code[pc + 1]);
      op_dstore(vm, index);
      return pc + 2;
    }
    case 58: // astore
    {
      uint32_t index = _u1(&code[pc + 1]);
      op_astore(vm, index);
      return pc + 2;
    }
    case 59: // istore_0
    {
      op_istore_0(vm);
      return pc + 1;
    }
    case 60: // istore_1
    {
      op_istore_1(vm);
      return pc + 1;
    }
    case 61: // istore_2
    {
      op_istore_2(vm);
      return pc + 1;
    }
    case 62: // istore_3
    {
      op_istore_3(vm);
      return pc + 1;
    }
    case 63: // lstore_0
    {
      op_lstore_0(vm);
      return pc + 1;
    }
    case 64: // lstore_1
    {
      op_lstore_1(vm);
      return pc + 1;
    }
    case 65: // lstore_2
    {
      op_lstore_2(vm);
      return pc + 1;
    }
    case 66: // lstore_3
    {
      op_lstore_3(vm);
      return pc + 1;
    }
    case 67: // fstore_0
    {
      op_fstore_0(vm);
      return pc + 1;
    }
    case 68: // fstore_1
    {
      op_fstore_1(vm);
      return pc + 1;
    }
    case 69: // fstore_2
    {
      op_fstore_2(vm);
      return pc + 1;
    }
    case 70: // fstore_3
    {
      op_fstore_3(vm);
      return pc + 1;
    }
    case 71: // dstore_0
    {
      op_dstore_0(vm);
      return pc + 1;
    }
    case 72: // dstore_1
    {
      op_dstore_1(vm);
      return pc + 1;
    }
    case 73: // dstore_2
    {
      op_dstore_2(vm);
      return pc + 1;
    }
    case 74: // dstore_3
    {
      op_dstore_3(vm);
      return pc + 1;
    }
    case 75: // astore_0
    {
      op_astore_0(vm);
      return pc + 1;
    }
    case 76: // astore_1
    {
      op_astore_1(vm);
      return pc + 1;
    }
    case 77: // astore_2
    {
      op_astore_2(vm);
      return pc + 1;
    }
    case 78: // astore_3
    {
      op_astore_3(vm);
      return pc + 1;
    }
    case 79: // iastore
    {
      op_iastore(vm);
      return pc + 1;
    }
    case 80: // lastore
    {
      op_lastore(vm);
      return pc + 1;
    }
    case 81: // fastore
    {
      op_fastore(vm);
      return pc + 1;
    }
    case 82: // dastore
    {
      op_dastore(vm);
      return pc + 1;
    }
    case 83: // aastore
    {
      op_aastore(vm);
      return pc + 1;
    }
    case 84: // bastore
    {
      op_bastore(vm);
      return pc + 1;
    }
    case 85: // castore
    {
      op_castore(vm);
      return pc + 1;
    }
    case 86: // sastore
    {
      op_sastore(vm);
      return pc + 1;
    }
    case 87: // pop
    {
      op_pop(vm);
      return pc + 1;
    }
    case 88: // pop2
    {
      op_pop2(vm);
      return pc + 1;
    }
    case 89: // dup
    {
      op_dup(vm);
      return pc + 1;
    }
    case 90: // dup_x1
    {
      op_dup_x1(vm);
      return pc + 1;
    }
    case 91: // dup_x2
    {
      op_dup_x2(vm);
      return pc + 1;
    }
    case 92: // dup2
    {
      op_dup2(vm);
      return pc + 1;
    }
    case 93: // dup2_x1
    {
      op_dup2_x1(vm);
      return pc + 1;
    }
    case 94: // dup2_x2
    {
      op_dup2_x2(vm);
      return pc + 1;
    }
    case 95: // swap
    {
      op_swap(vm);
      return pc + 1;
    }
    case 96: // iadd
    {
      op_iadd(vm);
      return pc + 1;
    }
    case 97: // ladd
    {
      op_ladd(vm);
      return pc + 1;
    }
    case 98: // fadd
    {
      op_fadd(vm);
      return pc + 1;
    }
    case 99: // dadd
    {
      op_dadd(vm);
      return pc + 1;
    }
    case 100: // isub
    {
      op_isub(vm);
      return pc + 1;
    }
    case 101: // lsub
    {
      op_lsub(vm);
      return pc + 1;
    }
    case 102: // fsub
    {
      op_fsub(vm);
      return pc + 1;
    }
    case 103: // dsub
    {
      op_dsub(vm);
      return pc + 1;
    }
    case 104: // imul
    {
      op_imul(vm);
      return pc + 1;
    }
    case 105: // lmul
    {
      op_lmul(vm);
      return pc + 1;
    }
    case 106: // fmul
    {
      op_fmul(vm);
      return pc + 1;
    }
    case 107: // dmul
    {
      op_dmul(vm);
      return pc + 1;
    }
    case 108: // idiv
    {
      op_idiv(vm);
      return pc + 1;
    }
    case 109: // ldiv
    {
      op_ldiv(vm);
      return pc + 1;
    }
    case 110: // fdiv
    {
      op_fdiv(vm);
      return pc + 1;
    }
    case 111: // ddiv
    {
      op_ddiv(vm);
      return pc + 1;
    }
    case 112: // irem
    {
      op_irem(vm);
      return pc + 1;
    }
    case 113: // lrem
    {
      op_lrem(vm);
      return pc + 1;
    }
    case 114: // frem
    {
      op_frem(vm);
      return pc + 1;
    }
    case 115: // drem
    {
      op_drem(vm);
      return pc + 1;
    }
    case 116: // ineg
    {
      op_ineg(vm);
      return pc + 1;
    }
    case 117: // lneg
    {
      op_lneg(vm);
      return pc + 1;
    }
    case 118: // fneg
    {
      op_fneg(vm);
      return pc + 1;
    }
    case 119: // dneg
    {
      op_dneg(vm);
      return pc + 1;
    }
    case 120: // ishl
    {
      op_ishl(vm);
      return pc + 1;
    }
    case 121: // lshl
    {
      op_lshl(vm);
      return pc + 1;
    }
    case 122: // ishr
    {
      op_ishr(vm);
      return pc + 1;
    }
    case 123: // lshr
    {
      op_lshr(vm);
      return pc + 1;
    }
    case 124: // iushr
    {
      op_iushr(vm);
      return pc + 1;
    }
    case 125: // lushr
    {
      op_lushr(vm);
      return pc + 1;
    }
    case 126: // iand
    {
      op_iand(vm);
      return pc + 1;
    }
    case 127: // land
    {
      op_land(vm);
      return pc + 1;
    }
    case 128: // ior
    {
      op_ior(vm);
      return pc + 1;
    }
    case 129: // lor
    {
      op_lor(vm);
      return pc + 1;
    }
    case 130: // ixor
    {
      op_ixor(vm);
      return pc + 1;
    }
    case 131: // lxor
    {
      op_lxor(vm);
      return pc + 1;
    }
    case 132: // iinc
    {
      uint32_t index = _u1(&code[pc + 1]);
      uint32_t _const = _u1(&code[pc + 2]);
      op_iinc(vm, index, _const);
      return pc + 3;
    }
    case 133: // i2l
    {
      op_i2l(vm);
      return pc + 1;
    }
    case 134: // i2f
    {
      op_i2f(vm);
      return pc + 1;
    }
    case 135: // i2d
    {
      op_i2d(vm);
      return pc + 1;
    }
    case 136: // l2i
    {
      op_l2i(vm);
      return pc + 1;
    }
    case 137: // l2f
    {
      op_l2f(vm);
      return pc + 1;
    }
    case 138: // l2d
    {
      op_l2d(vm);
      return pc + 1;
    }
    case 139: // f2i
    {
      op_f2i(vm);
      return pc + 1;
    }
    case 140: // f2l
    {
      op_f2l(vm);
      return pc + 1;
    }
    case 141: // f2d
    {
      op_f2d(vm);
      return pc + 1;
    }
    case 142: // d2i
    {
      op_d2i(vm);
      return pc + 1;
    }
    case 143: // d2l
    {
      op_d2l(vm);
      return pc + 1;
    }
    case 144: // d2f
    {
      op_d2f(vm);
      return pc + 1;
    }
    case 145: // i2b
    {
      op_i2b(vm);
      return pc + 1;
    }
    case 146: // i2c
    {
      op_i2c(vm);
      return pc + 1;
    }
    case 147: // i2s
    {
      op_i2s(vm);
      return pc + 1;
    }
    case 148: // lcmp
    {
      op_lcmp(vm);
      return pc + 1;
    }
    case 149: // fcmpl
    {
      op_fcmpl(vm);
      return pc + 1;
    }
    case 150: // fcmpg
    {
      op_fcmpg(vm);
      return pc + 1;
    }
    case 151: // dcmpl
    {
      op_dcmpl(vm);
      return pc + 1;
    }
    case 152: // dcmpg
    {
      op_dcmpg(vm);
      return pc + 1;
    }
    case 153: // ifeq
    {
      int32_t branch = _s2(&code[pc + 1]);
      op_ifeq(vm, branch);
      return pc + 3;
    }
    case 154: // ifne
    {
      int32_t branch = _s2(&code[pc + 1]);
      op_ifne(vm, branch);
      return pc + 3;
    }
    case 155: // iflt
    {
      int32_t branch = _s2(&code[pc + 1]);
      op_iflt(vm, branch);
      return pc + 3;
    }
    case 156: // ifge
    {
      int32_t branch = _s2(&code[pc + 1]);
      op_ifge(vm, branch);
      return pc + 3;
    }
    case 157: // ifgt
    {
      int32_t branch = _s2(&code[pc + 1]);
      op_ifgt(vm, branch);
      return pc + 3;
    }
    case 158: // ifle
    {
      int32_t branch = _s2(&code[pc + 1]);
      op_ifle(vm, branch);
      return pc + 3;
    }
    case 159: // if_icmpeq
    {
      int32_t branch = _s2(&code[pc + 1]);
      op_if_icmpeq(vm, branch);
      return pc + 3;
    }
    case 160: // if_icmpne
    {
      int32_t branch = _s2(&code[pc + 1]);
      op_if_icmpne(vm, branch);
      return pc + 3;
    }
    case 161: // if_icmplt
    {
      int32_t branch = _s2(&code[pc + 1]);
      op_if_icmplt(vm, branch);
      return pc + 3;
    }
    case 162: // if_icmpge
    {
      int32_t branch = _s2(&code[pc + 1]);
      op_if_icmpge(vm, branch);
      return pc + 3;
    }
    case 163: // if_icmpgt
    {
      int32_t branch = _s2(&code[pc + 1]);
      op_if_icmpgt(vm, branch);
      return pc + 3;
    }
    case 164: // if_icmple
    {
      int32_t branch = _s2(&code[pc + 1]);
      op_if_icmple(vm, branch);
      return pc + 3;
    }
    case 165: // if_acmpeq
    {
      int32_t branch = _s2(&code[pc + 1]);
      op_if_acmpeq(vm, branch);
      return pc + 3;
    }
    case 166: // if_acmpne
    {
      int32_t branch = _s2(&code[pc + 1]);
      op_if_acmpne(vm, branch);
      return pc + 3;
    }
    case 167: // goto
    {
      int32_t branch = _s2(&code[pc + 1]);
      op_goto(vm, branch);
      return pc + 3;
    }
    case 168: // jsr
    {
      int32_t branch = _s2(&code[pc + 1]);
      op_jsr(vm, branch);
      return pc + 3;
    }
    case 169: // ret
    {
      uint32_t index = _u1(&code[pc + 1]);
      op_ret(vm, index);
      return pc + 2;
    }
    case 170: // tableswitch
    {
      TABLESWITCH_ARGS;
      op_tableswitch(vm, defaultbyte, lowbyte, highbyte, table);
      return TABLESWITCH_NEXT_PC;
    }
    case 171: // lookupswitch
    {
      LOOKUPSWITCH_ARGS;
      op_lookupswitch(vm);
      return LOOKUPSWITCH_NEXT_PC;
    }
    case 172: // ireturn
    {
      op_ireturn(vm);
      return pc + 1;
    }
    case 173: // lreturn
    {
      op_lreturn(vm);
      return pc + 1;
    }
    case 174: // freturn
    {
      op_freturn(vm);
      return pc + 1;
    }
    case 175: // dreturn
    {
      op_dreturn(vm);
      return pc + 1;
    }
    case 176: // areturn
    {
      op_areturn(vm);
      return pc + 1;
    }
    case 177: // return
    {
      op_return(vm);
      return pc + 1;
    }
    case 178: // getstatic
    {
      uint32_t index = _u2(&code[pc + 1]);
      op_getstatic(vm, index);
      return pc + 3;
    }
    case 179: // putstatic
    {
      uint32_t index = _u2(&code[pc + 1]);
      op_putstatic(vm, index);
      return pc + 3;
    }
    case 180: // getfield
    {
      uint32_t index = _u2(&code[pc + 1]);
      op_getfield(vm, index);
      return pc + 3;
    }
    case 181: // putfield
    {
      uint32_t index = _u2(&code[pc + 1]);
      op_putfield(vm, index);
      return pc + 3;
    }
    case 182: // invokevirtual
    {
      uint32_t index = _u2(&code[pc + 1]);
      op_invokevirtual(vm, index);
      return pc + 3;
    }
    case 183: // invokespecial
    {
      uint32_t index = _u2(&code[pc + 1]);
      op_invokespecial(vm, index);
      return pc + 3;
    }
    case 184: // invokestatic
    {
      uint32_t index = _u2(&code[pc + 1]);
      op_invokestatic(vm, index);
      return pc + 3;
    }
    case 185: // invokeinterface
    {
      uint32_t index = _u2(&code[pc + 1]);
      uint32_t count = _u1(&code[pc + 3]);
      op_invokeinterface(vm, index, count);
      return pc + 5;
    }
    case 186: // invokedynamic
    {
      uint32_t index = _u2(&code[pc + 1]);
      op_invokedynamic(vm, index);
      return pc + 5;
    }
    case 187: // new
    {
      uint32_t index = _u2(&code[pc + 1]);
      op_new(vm, index);
      return pc + 3;
    }
    case 188: // newarray
    {
      uint32_t atype = _u1(&code[pc + 1]);
      op_newarray(vm, atype);
      return pc + 2;
    }
    case 189: // anewarray
    {
      uint32_t index = _u2(&code[pc + 1]);
      op_anewarray(vm, index);
      return pc + 3;
    }
    case 190: // arraylength
    {
      op_arraylength(vm);
      return pc + 1;
    }
    case 191: // athrow
    {
      op_athrow(vm);
      return pc + 1;
    }
    case 192: // checkcast
    {
      uint32_t index = _u2(&code[pc + 1]);
      op_checkcast(vm, index);
      return pc + 3;
    }
    case 193: // instanceof
    {
      uint32_t index = _u2(&code[pc + 1]);
      op_instanceof(vm, index);
      return pc + 3;
    }
    case 194: // monitorenter
    {
      op_monitorenter(vm);
      return pc + 1;
    }
    case 195: // monitorexit
    {
      op_monitorexit(vm);
      return pc + 1;
    }
    case 196: // wide
    {
      WIDE_ARGS;
      op_wide(vm);
      return WIDE_NEXT_PC;
    }
    case 197: // multianewarray
    {
      uint32_t index = _u2(&code[pc + 1]);
      uint32_t dimensions = _u1(&code[pc + 3]);
      op_multianewarray(vm, index, dimensions);
      return pc + 4;
    }
    case 198: // ifnull
    {
      int32_t branch = _s2(&code[pc + 1]);
      op_ifnull(vm, branch);
      return pc + 3;
    }
    case 199: // ifnonnull
    {
      int32_t branch = _s2(&code[pc + 1]);
      op_ifnonnull(vm, branch);
      return pc + 3;
    }
    case 200: // goto_w
    {
      int32_t branch = _s2(&code[pc + 1]);
      op_goto_w(vm, branch);
      return pc + 3;
    }
    case 201: // jsr_w
    {
      int32_t branch = _s4(&code[pc + 1]);
      op_jsr_w(vm, branch);
      return pc + 5;
    }
    case 202: // breakpoint
    {
      op_breakpoint(vm);
      return pc + 1;
    }
    case 254: // impdep1
    {
      op_impdep1(vm);
      return pc + 1;
    }
    case 255: // impdep2
    {
      op_impdep2(vm);
      return pc + 1;
    }
    default:
    {
      assert(false);
      return pc;
    }
  }
}
