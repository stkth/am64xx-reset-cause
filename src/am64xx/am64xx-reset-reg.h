/*
 * SPDX-License-Identifier: GPLv2
 * Copyright (c) 2025 Steffen Kothe <steffen.kothe@skothe.net>
 */

// Determine page for given register
#define OFFSET_PAGE_FOR_REGISTER(r) (r & ~(getpagesize() - 1))

// Determine address for register in page
#define ADDR_OF_REGISTER_IN_PAGE(p, r) (p + (r & (getpagesize() - 1)))

#ifndef AM64XX_RESET_REG_H
#define AM64XX_RESET_REG_H

/* Reset control register */
#define CTRLMMR_RST_SRC_PROXY_0 0x43018178
#define CTRLMMR_RST_SRC_PROXY_1 0x4301A178

/* Two proxy registers are available hence use proxy 0 */
#define CTRLMMR_RST_SRC CTRLMMR_RST_SRC_PROXY_0

/* CTRLMMR_RST_SRC register definition
 * LSB of register comes first
 */
typedef struct {
  unsigned int MCU_RESET_PIN : 1; /* MAIN Domain Reset Pin Initiated Reset */
  unsigned int RESERVED_1 : 1;
  unsigned int MAIN_RESET_REQ : 1; /* MAIN Domain Reset Pin Initiated Reset */
  unsigned int RESERVED_3 : 1;
  unsigned int THERMAL_RST : 1; /* MAIN Domain Reset Pin Initiated Reset */
  unsigned int RESERVED_7_5 : 3;
  unsigned int DEBUG_RST : 1; /* Debug Subsystem Initiated Reset */
  unsigned int RESERVED_11_9 : 3;
  unsigned int COLD_OUT_RST : 1; /* DMSC Cold Reset */
  unsigned int WARM_OUT_RST : 1; /* DMSC Warm Reset */
  unsigned int RESERVED_15_14 : 2;
  unsigned int SW_MCU_WARMRST : 1; /* Software Warm Reset */
  unsigned int RESERVED_19_17 : 3;
  unsigned int
      SW_MAIN_WARMRST_FROM_MCU : 1; /* Software Main Warm Reset from MCU */
  unsigned int
      SW_MAIN_WARMRST_FROM_MAIN : 1; /* Software Main Warm Reset from MAIN */
  unsigned int RESERVED_23_22 : 2;
  unsigned int
      SW_MAIN_POR_FROM_MCU : 1; /* SW Main Power On Reset from MCU CTRL MMR */
  unsigned int SW_MAIN_POR_FROM_MAIN : 1; /* SW Main Power On Reset from MAIN
                                             CTRL MMR */
  unsigned int RESERVED_29_26 : 4;
  unsigned int MAIN_ESM_ERROR : 1; /* Reset Caused by Main ESM ERROR */
  unsigned int SAFETY_ERROR : 1;   /* Reset Caused by MCU ESM ERROR */
} AM64XX_RESET_CAUSE;

int GetAM64ResetRegister(AM64XX_RESET_CAUSE *reg);

void PrettyPrintAM64ResetCause(const AM64XX_RESET_CAUSE *reg);

void BinaryPrintAM64ResetCause(const AM64XX_RESET_CAUSE *reg);

#endif /*AM64XX_RESET_REG_H*/
