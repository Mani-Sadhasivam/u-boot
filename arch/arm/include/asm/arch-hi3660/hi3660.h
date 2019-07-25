/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2015 Linaro
 * Peter Griffin <peter.griffin@linaro.org>
 */

#ifndef __HI3660_H__
#define __HI3660_H__

#define HI3660_UART6_BASE			0xfff32000

#define PMU_REG_BASE                            0xFFF34000
#define SCTRL_REG_BASE                          0xFFF0A000

#define SCTRL_SCFPLLCTRL0                       (SCTRL_REG_BASE + 0x120)
#define SCTRL_SCFPLLCTRL0_FPLL0_EN              (1 << 0)

#define CRG_REG_BASE                            0xFFF35000

#define CRG_PEREN2                              (CRG_REG_BASE + 0x020)
#define CRG_PERDIS2                             (CRG_REG_BASE + 0x024)
#define CRG_PERCLKEN2                           (CRG_REG_BASE + 0x028)
#define CRG_PERSTAT2                            (CRG_REG_BASE + 0x02C)
#define CRG_PEREN4                              (CRG_REG_BASE + 0x040)
#define CRG_PERDIS4                             (CRG_REG_BASE + 0x044)
#define CRG_PERCLKEN4                           (CRG_REG_BASE + 0x048)
#define CRG_PERSTAT4                            (CRG_REG_BASE + 0x04C)
#define CRG_PERRSTEN2                           (CRG_REG_BASE + 0x078)
#define CRG_PERRSTDIS2                          (CRG_REG_BASE + 0x07C)
#define CRG_PERRSTSTAT2                         (CRG_REG_BASE + 0x080)
#define CRG_PERRSTEN3                           (CRG_REG_BASE + 0x084)
#define CRG_PERRSTDIS3                          (CRG_REG_BASE + 0x088)
#define CRG_PERRSTSTAT3                         (CRG_REG_BASE + 0x08C)
#define CRG_PERRSTEN4                           (CRG_REG_BASE + 0x090)
#define CRG_PERRSTDIS4                          (CRG_REG_BASE + 0x094)
#define CRG_PERRSTSTAT4                         (CRG_REG_BASE + 0x098)
#define CRG_ISOEN                               (CRG_REG_BASE + 0x144)
#define CRG_ISODIS                              (CRG_REG_BASE + 0x148)
#define CRG_ISOSTAT                             (CRG_REG_BASE + 0x14C)

#endif /*__HI3660_H__*/
