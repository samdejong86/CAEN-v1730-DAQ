#include <iostream>
#include <unistd.h>
#include <stdint.h>   /* C99 compliant compilers: uint64_t */
#include <ctype.h>    /* toupper() */
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/io.h>
#include <sys/perm.h>
#include <string.h>
#include <math.h>
#include <CAENDigitizerType.h>

#include "keyb.h"
#include "fft.h"

/*
#ifndef OUTFILEFLAGS_e
#define OUTFILEFLAGS_e

typedef enum {
	OFF_BINARY= 0x00000001,  // Bit 0: 1 = BINARY, 0 =ASCII
	OFF_HEADER= 0x00000002,  // Bit 1: 1 = include header, 0 = just samples data
} OUTFILE_FLAGS;

#endif
*/


#define MAXNB   1
#define MaxNChannels 8  
#define MAXNBITS 14


#define GNUPLOT_DEFAULT_PATH ""

#define OUTFILENAME "wave"  /* The actual file name is wave_n.txt, where n is the channel */
#define MAX_CH  64          /* max. number of channels */
#define MAX_SET 16           /* max. number of independent settings */

#define MAX_GW  1000        /* max. number of generic write commads */

#define PLOT_REFRESH_TIME 1000

#define VME_INTERRUPT_LEVEL      1
#define VME_INTERRUPT_STATUS_ID  0xAAAA
#define INTERRUPT_TIMEOUT        200  // ms
        
#define PLOT_WAVEFORMS   0
#define PLOT_FFT         1
#define PLOT_HISTOGRAM   2

#define CFGRELOAD_CORRTABLES_BIT (0)
#define CFGRELOAD_DESMODE_BIT (1)

#define NPOINTS 2

#define NACQS   50
