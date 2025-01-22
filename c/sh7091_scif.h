#pragma once

#include <stdint.h>
#include "compat.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef volatile uint8_t reg8;
typedef volatile uint16_t reg16;
typedef volatile uint32_t reg32;

static_assert((sizeof (reg8)) == 1);
static_assert((sizeof (reg16)) == 2);
static_assert((sizeof (reg32)) == 4);

struct scif_reg {
  reg16 SCSMR2;              /* Serial mode register 2 */
  reg8  _pad0[2];
  reg8  SCBRR2;              /* Bit rate register 2 */
  reg8  _pad1[3];
  reg16 SCSCR2;              /* Serial control register 2 */
  reg8  _pad2[2];
  reg8  SCFTDR2;             /* Transmit FIFO data register 2 */
  reg8  _pad3[3];
  reg16 SCFSR2;              /* Serial status register 2 */
  reg8  _pad4[2];
  reg8  SCFRDR2;             /* Receive FIFO data register 2 */
  reg8  _pad5[3];
  reg16 SCFCR2;              /* FIFO control register */
  reg8  _pad6[2];
  reg16 SCFDR2;              /* FIFO data count register */
  reg8  _pad7[2];
  reg16 SCSPTR2;             /* Serial port register 2 */
  reg8  _pad8[2];
  reg16 SCLSR2;              /* Line status register 2 */
};

static_assert((offsetof (struct scif_reg, SCSMR2)) == 0x0);
static_assert((offsetof (struct scif_reg, SCBRR2)) == 0x4);
static_assert((offsetof (struct scif_reg, SCSCR2)) == 0x8);
static_assert((offsetof (struct scif_reg, SCFTDR2)) == 0xc);
static_assert((offsetof (struct scif_reg, SCFSR2)) == 0x10);
static_assert((offsetof (struct scif_reg, SCFRDR2)) == 0x14);
static_assert((offsetof (struct scif_reg, SCFCR2)) == 0x18);
static_assert((offsetof (struct scif_reg, SCFDR2)) == 0x1c);
static_assert((offsetof (struct scif_reg, SCSPTR2)) == 0x20);
static_assert((offsetof (struct scif_reg, SCLSR2)) == 0x24);

struct tmu_reg {
  reg8  TOCR;                /* Timer output control register */
  reg8  _pad0[3];
  reg8  TSTR;                /* Timer start register */
  reg8  _pad1[3];
  reg32 TCOR0;               /* Timer constant register 0 */
  reg32 TCNT0;               /* Timer counter 0 */
  reg16 TCR0;                /* Timer control register 0 */
  reg8  _pad2[2];
  reg32 TCOR1;               /* Timer constant register 1 */
  reg32 TCNT1;               /* Timer counter 1 */
  reg16 TCR1;                /* Timer control register 1 */
  reg8  _pad3[2];
  reg32 TCOR2;               /* Timer constant register 2 */
  reg32 TCNT2;               /* Timer counter 2 */
  reg16 TCR2;                /* Timer control register 2 */
  reg8  _pad4[2];
  reg32 TCPR2;               /* Timer input capture register 2 */
};

static_assert((offsetof (struct tmu_reg, TOCR)) == 0x0);
static_assert((offsetof (struct tmu_reg, TSTR)) == 0x4);
static_assert((offsetof (struct tmu_reg, TCOR0)) == 0x8);
static_assert((offsetof (struct tmu_reg, TCNT0)) == 0xc);
static_assert((offsetof (struct tmu_reg, TCR0)) == 0x10);
static_assert((offsetof (struct tmu_reg, TCOR1)) == 0x14);
static_assert((offsetof (struct tmu_reg, TCNT1)) == 0x18);
static_assert((offsetof (struct tmu_reg, TCR1)) == 0x1c);
static_assert((offsetof (struct tmu_reg, TCOR2)) == 0x20);
static_assert((offsetof (struct tmu_reg, TCNT2)) == 0x24);
static_assert((offsetof (struct tmu_reg, TCR2)) == 0x28);
static_assert((offsetof (struct tmu_reg, TCPR2)) == 0x2c);

#define tmu__tstr__str1__counter_start (1 << 2)
#define tmu__tocr__tcoe__tclk_is_external_clock_or_input_capture (0 << 0)
#define tmu__tcr1__tpsc__p_phi_1024 (0b100 << 0)
#define scfcr2__tfrst__reset_operation_enabled (1 << 2)
#define scfcr2__rfrst__reset_operation_enabled (1 << 1)
#define scsmr2__chr__8_bit_data (0 << 6)
#define scsmr2__pe__parity_disabled (0 << 5)
#define scsmr2__stop__1_stop_bit (0 << 3)
#define scsmr2__cks__p_phi_clock (0b00 << 0)
#define scfsr2__er__bit_mask (0x1 << 7)
#define scfsr2__tend__bit_mask (0x1 << 6)
#define scfsr2__tdfe__bit_mask (0x1 << 5)
#define scfsr2__brk__bit_mask (0x1 << 4)
#define scfsr2__rdf__bit_mask (0x1 << 1)
#define scfsr2__dr__bit_mask (0x1 << 0)
#define scfcr2__rtrg__trigger_on_1_byte (0b00 << 6)
#define scfcr2__ttrg__trigger_on_8_bytes (0b00 << 4)
#define scscr2__te__transmission_enabled (1 << 5)
#define scscr2__re__reception_enabled (1 << 4)

void scif_init_wait();
void scif_init(int bit_rate);
void scif_character(const char c);

extern struct tmu_reg sh7091_TMU __asm("sh7091_TMU");
extern struct scif_reg sh7091_SCIF __asm("sh7091_SCIF");

#ifdef __cplusplus
}
#endif
