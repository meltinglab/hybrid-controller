/*
 * File: Controller_ca.c
 *
 * Abstract: Tests assumptions in the generated code.
 */

#include "Controller_ca.h"

CA_HWImpl_TestResults CA_Controller_HWRes;
CA_PWS_TestResults CA_Controller_PWSRes;
const CA_HWImpl CA_Controller_ExpHW = {

#ifdef PORTABLE_WORDSIZES

  8,                                   /* BitPerChar */
  16,                                  /* BitPerShort */
  32,                                  /* BitPerInt */
  32,                                  /* BitPerLong */
  64,                                  /* BitPerLongLong */
  32,                                  /* BitPerFloat */
  64,                                  /* BitPerDouble */
  64,                                  /* BitPerPointer */
  64,                                  /* BitPerSizeT */
  64,                                  /* BitPerPtrDiffT */
  CA_LITTLE_ENDIAN,                    /* Endianess */
  CA_ZERO,                             /* IntDivRoundTo */
  1,                                   /* ShiftRightIntArith */

#else

  8,                                   /* BitPerChar */
  16,                                  /* BitPerShort */
  32,                                  /* BitPerInt */
  32,                                  /* BitPerLong */
  64,                                  /* BitPerLongLong */
  32,                                  /* BitPerFloat */
  64,                                  /* BitPerDouble */
  64,                                  /* BitPerPointer */
  64,                                  /* BitPerSizeT */
  64,                                  /* BitPerPtrDiffT */
  CA_LITTLE_ENDIAN,                    /* Endianess */
  CA_ZERO,                             /* IntDivRoundTo */
  1,                                   /* ShiftRightIntArith */

#endif

  0,                                   /* LongLongMode */
  1,                                   /* PortableWordSizes */
  "Intel->x86-64 (Windows64)",         /* HWDeviceType */
  0,                                   /* MemoryAtStartup */
  0,                                   /* DynamicMemoryAtStartup */
  0,                                   /* DenormalFlushToZero */
  0                                    /* DenormalAsZero */
};

CA_HWImpl CA_Controller_ActHW;
void Controller_caRunTests(void)
{
  /* verify hardware implementation */
  caVerifyPortableWordSizes(&CA_Controller_ActHW, &CA_Controller_ExpHW,
    &CA_Controller_PWSRes);
  caVerifyHWImpl(&CA_Controller_ActHW, &CA_Controller_ExpHW,
                 &CA_Controller_HWRes);
}
