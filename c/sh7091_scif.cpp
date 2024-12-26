#include "sh7091/sh7091.hpp"
#include "sh7091/sh7091_bits.hpp"

#include "sh7091_scif.h"

void scif_character(const char c)
{
  using namespace scif;
  // wait for transmit fifo to become partially empty
  while ((sh7091.SCIF.SCFSR2 & scfsr2::tdfe::bit_mask) == 0);

  sh7091.SCIF.SCFSR2 &= ~scfsr2::tdfe::bit_mask;

  sh7091.SCIF.SCFTDR2 = static_cast<uint8_t>(c);
}