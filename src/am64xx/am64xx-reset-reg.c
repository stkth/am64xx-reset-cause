/*
 * SPDX-License-Identifier: GPLv2
 * Copyright (c) 2025 Steffen Kothe <steffen.kothe@skothe.net>
 */

#include "am64xx-reset-reg.h"

#define _GNU_SOURCE
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int GetAM64ResetRegister(AM64XX_RESET_CAUSE *reg) {
  int fd;
  void *page;

  assert(reg != NULL);

  fd = open("/dev/mem", O_RDONLY);
  if (fd < 0) {
    fprintf(stderr, "Opening /dev/mem failed: %s\n", strerror(errno));
    return -1;
  }

  page = mmap(NULL, getpagesize(), PROT_READ, MAP_SHARED, fd,
              OFFSET_PAGE_FOR_REGISTER(CTRLMMR_RST_SRC));
  if (page == MAP_FAILED) {
    fprintf(stderr, "Mapping of register to page failed!\n");
    close(fd);
    return -1;
  }

  memset(reg, 0, sizeof(AM64XX_RESET_CAUSE));
  memcpy(reg, ADDR_OF_REGISTER_IN_PAGE(page, CTRLMMR_RST_SRC),
         sizeof(AM64XX_RESET_CAUSE));

  munmap(page, getpagesize());
  close(fd);

  return 0;
}

void PrettyPrintAM64ResetCause(const AM64XX_RESET_CAUSE *reg) {
  printf("AM64XX CTRLMMR_RST_SRC REGISTER\n"
         " SAFETY_ERROR: %i\n"
         " MAIN_ESM_ERROR: %i\n"
         " SW_MAIN_POR_FROM_MAIN: %i\n"
         " SW_MAIN_POR_FROM_MCU: %i\n"
         " SW_MAIN_WARMRST_FROM_MAIN: %i\n"
         " SW_MAIN_WARMRST_FROM_MCU: %i\n"
         " SW_MCU_WARMRST: %i\n"
         " WARM_OUT_RST: %i\n"
         " COLD_OUT_RST: %i\n"
         " DEBUG_RST: %i\n"
         " THERMAL_RST: %i\n"
         " MAIN_RESET_REQ_RST: %i\n"
         " MCU_RESET_PIN: %i\n"
         "\n",
         reg->SAFETY_ERROR, reg->MAIN_ESM_ERROR, reg->SW_MAIN_POR_FROM_MAIN,
         reg->SW_MAIN_POR_FROM_MCU, reg->SW_MAIN_WARMRST_FROM_MAIN,
         reg->SW_MAIN_WARMRST_FROM_MCU, reg->SW_MCU_WARMRST, reg->WARM_OUT_RST,
         reg->COLD_OUT_RST, reg->DEBUG_RST, reg->THERMAL_RST,
         reg->MAIN_RESET_REQ, reg->MCU_RESET_PIN);
}

void BinaryPrintAM64ResetCause(const AM64XX_RESET_CAUSE *reg) {
  printf("%x/n", *(unsigned int *)reg);
}
