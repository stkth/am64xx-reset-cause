/*
 * SPDX-License-Identifier: GPLv2
 * Copyright (c) 2025 Steffen Kothe <steffen.kothe@skothe.net>
 */

#define _GNU_SOURCE
#include "am64xx/am64xx-reset-reg.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef CVS_GIT_VERSION
#define CVS_GTT_VERSION "unset"
#endif

/* Expand macro first before stringification
 * https://gcc.gnu.org/onlinedocs/gcc-3.4.3/cpp/Stringification.html
 */
#define EXPAND_VERSION(v) VERSION(v)
#define VERSION(v) #v

void PrintUsage() {
  fprintf(stderr,
          "Usage: am64xx-reset-cause -p (pretty) -b (binary) -v (version)\n");
}

int main(int argc, char *argv[]) {

  int opt;
  int pretty = 0, binary = 0;
  AM64XX_RESET_CAUSE am64xx_rst_register;

  while ((opt = getopt(argc, argv, "vpb")) != -1) {
    switch (opt) {
    case 'v':
      printf("Version: %s\n", EXPAND_VERSION(CVS_GIT_VERSION));
      exit(EXIT_SUCCESS);
      break;
    case 'p':
      pretty = 1;
      break;
    case 'b':
      binary = 1;
      break;
    default:
      PrintUsage();
      exit(EXIT_FAILURE);
    }
  }

  if (!pretty && !binary) {
    PrintUsage();
    exit(EXIT_SUCCESS);
  }

  if (GetAM64ResetRegister(&am64xx_rst_register))
    fprintf(stderr, "Reading AM64XX reset register failed!\n");
  exit(EXIT_FAILURE);

  if (pretty)
    PrettyPrintAM64ResetCause(&am64xx_rst_register);

  if (binary)
    BinaryPrintAM64ResetCause(&am64xx_rst_register);

  return EXIT_SUCCESS;
}
