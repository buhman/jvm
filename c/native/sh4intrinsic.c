#include "sh4intrinsic.h"

void native_jvm_internal_sh4intrinsic_pref1_1(struct vm * vm, uint32_t * args)
{
  uint32_t address = (uint32_t)args[0];

  // start 32-byte transfer from store queue 0 (SQ0) to QACR0
  asm volatile ("pref @%0"
		:                       // output
		: "r" (address) // input
		: "memory");
}

void native_jvm_internal_sh4intrinsic_pref2_1(struct vm * vm, uint32_t * args)
{
  uint32_t address = (uint32_t)args[0];

  // start 32-byte transfer from store queue 0 (SQ0) to QACR0
  asm volatile ("pref @%0"
		:                       // output
		: "r" (address) // input
		: "memory");

  // start 32-byte transfer from store queue 1 (SQ1) to QACR1
  asm volatile ("pref @%0"
		:                       // output
		: "r" (address + 32)    // input
		: "memory");
}
