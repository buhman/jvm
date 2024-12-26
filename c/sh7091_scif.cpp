#include "sh7091/sh7091.hpp"
#include "sh7091/sh7091_bits.hpp"

#include "sh7091_scif.h"

void scif_init_wait()
{
  sh7091.TMU.TSTR &= (~tmu::tstr::str1::counter_start) & 0xff; // stop TCNT1
  sh7091.TMU.TOCR = tmu::tocr::tcoe::tclk_is_external_clock_or_input_capture;
  sh7091.TMU.TCR1 = tmu::tcr1::tpsc::p_phi_1024; // 1024 / 50MHz = 20.48 μs
  sh7091.TMU.TCOR1 = 0xffff'ffff;
  sh7091.TMU.TCNT1 = 0xffff'ffff;
  sh7091.TMU.TSTR |= tmu::tstr::str1::counter_start;

  uint32_t start = sh7091.TMU.TCNT1;
  while ((start - sh7091.TMU.TCNT1) < 20);

  sh7091.TMU.TSTR &= (~tmu::tstr::str1::counter_start) & 0xff; // stop TCNT1
}

void scif_init(int bit_rate)
{
  using namespace scif;

  sh7091.SCIF.SCSCR2 = 0; // disable transmission / reception

  sh7091.SCIF.SCSPTR2 = 0; // clear output data pins

  sh7091.SCIF.SCFCR2 = scfcr2::tfrst::reset_operation_enabled
                     | scfcr2::rfrst::reset_operation_enabled;

  sh7091.SCIF.SCSMR2 = scsmr2::chr::_8_bit_data
		     | scsmr2::pe::parity_disabled
		     | scsmr2::stop::_1_stop_bit
		     | scsmr2::cks::p_phi_clock;

  sh7091.SCIF.SCBRR2 = bit_rate; // bps = 1562500 / (SCBRR2 + 1)

  sh7091.SCIF.SCFSR2 = (~scfsr2::er::bit_mask)
		     & (~scfsr2::tend::bit_mask)
		     & (~scfsr2::tdfe::bit_mask)
		     & (~scfsr2::brk::bit_mask)
		     & (~scfsr2::rdf::bit_mask)
		     & (~scfsr2::dr::bit_mask)
		     & 0xffff;


  // wait 1 bit interval
  scif_init_wait();

  sh7091.SCIF.SCFCR2 = scfcr2::rtrg::trigger_on_1_byte
		     | scfcr2::ttrg::trigger_on_8_bytes
		     //| scfcr2::mce::modem_signals_enabled
		     ;

  sh7091.SCIF.SCSCR2 = scscr2::te::transmission_enabled
                     | scscr2::re::reception_enabled;

  sh7091.SCIF.SCLSR2 = 0; // clear ORER
}

void scif_character(const char c)
{
  using namespace scif;
  // wait for transmit fifo to become partially empty
  while ((sh7091.SCIF.SCFSR2 & scfsr2::tdfe::bit_mask) == 0);

  sh7091.SCIF.SCFSR2 &= ~scfsr2::tdfe::bit_mask;

  sh7091.SCIF.SCFTDR2 = static_cast<uint8_t>(c);
}
