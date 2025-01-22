#include "sh7091_scif.h"

void scif_init_wait()
{
  sh7091_TMU.TSTR &= (~tmu__tstr__str1__counter_start) & 0xff; // stop TCNT1
  sh7091_TMU.TOCR = tmu__tocr__tcoe__tclk_is_external_clock_or_input_capture;
  sh7091_TMU.TCR1 = tmu__tcr1__tpsc__p_phi_1024; // 1024 / 50MHz = 20.48 μs
  sh7091_TMU.TCOR1 = 0xffffffff;
  sh7091_TMU.TCNT1 = 0xffffffff;
  sh7091_TMU.TSTR |= tmu__tstr__str1__counter_start;

  uint32_t start = sh7091_TMU.TCNT1;
  while ((start - sh7091_TMU.TCNT1) < 20);

  sh7091_TMU.TSTR &= (~tmu__tstr__str1__counter_start) & 0xff; // stop TCNT1
}

void scif_init(int bit_rate)
{
  sh7091_SCIF.SCSCR2 = 0; // disable transmission / reception

  sh7091_SCIF.SCSPTR2 = 0; // clear output data pins

  sh7091_SCIF.SCFCR2 = scfcr2__tfrst__reset_operation_enabled
                     | scfcr2__rfrst__reset_operation_enabled;

  sh7091_SCIF.SCSMR2 = scsmr2__chr__8_bit_data
		     | scsmr2__pe__parity_disabled
		     | scsmr2__stop__1_stop_bit
		     | scsmr2__cks__p_phi_clock;

  sh7091_SCIF.SCBRR2 = bit_rate; // bps = 1562500 / (SCBRR2 + 1)

  sh7091_SCIF.SCFSR2 = (~scfsr2__er__bit_mask)
		     & (~scfsr2__tend__bit_mask)
		     & (~scfsr2__tdfe__bit_mask)
		     & (~scfsr2__brk__bit_mask)
		     & (~scfsr2__rdf__bit_mask)
		     & (~scfsr2__dr__bit_mask)
		     & 0xffff;


  // wait 1 bit interval
  scif_init_wait();

  sh7091_SCIF.SCFCR2 = scfcr2__rtrg__trigger_on_1_byte
		     | scfcr2__ttrg__trigger_on_8_bytes
		     //| scfcr2__mce__modem_signals_enabled
		     ;

  sh7091_SCIF.SCSCR2 = scscr2__te__transmission_enabled
                     | scscr2__re__reception_enabled;

  sh7091_SCIF.SCLSR2 = 0; // clear ORER
}

void scif_character(const char c)
{
  // wait for transmit fifo to become partially empty
  while ((sh7091_SCIF.SCFSR2 & scfsr2__tdfe__bit_mask) == 0);

  sh7091_SCIF.SCFSR2 &= ~scfsr2__tdfe__bit_mask;

  sh7091_SCIF.SCFTDR2 = (uint8_t)(c);
}
