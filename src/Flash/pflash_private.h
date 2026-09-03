/*=============================================================================
 *
 * Copyright 2018-2020 NXP
 *
 * NXP Proprietary. This software is owned or controlled by NXP and may only be
 * used strictly in accordance with the applicable license terms. By expressly
 * accepting such terms or by downloading, installing, activating and/or otherwise
 * using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms. If you do not agree to be
 * bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software.
===============================================================================*/
/*
 * @file      pflash_private.h
 * @brief     Platform Flash Memory Controller (PFLASH) private definitions.
 ******************************************************************************/
#ifndef __PFLASH_PRIVATE_H
#define __PFLASH_PRIVATE_H

#include "S32K344_PFLASH.h"

/******************************************************************************
 * PFLASH registers for driver implementation
 ******************************************************************************/
#define PFLASH_PFCR0  PFLASH->PFCR[0]
#define PFLASH_PFCR1  PFLASH->PFCR[1]
#define PFLASH_PFCR2  PFLASH->PFCR[2]
#define PFLASH_PFCR3  PFLASH->PFCR[3]

#define PFLASH_PFCBLK0_SSPELOCK   PFLASH->PFCBLK_SSPELOCK[0]
#define PFLASH_PFCBLK1_SSPELOCK   PFLASH->PFCBLK_SSPELOCK[1]
#define PFLASH_PFCBLK2_SSPELOCK   PFLASH->PFCBLK_SSPELOCK[2]
#define PFLASH_PFCBLK3_SSPELOCK   PFLASH->PFCBLK_SSPELOCK[3]

#define PFLASH_PFCBLK0_SPELOCK    PFLASH->PFCBLK_SPELOCK[0]
#define PFLASH_PFCBLK1_SPELOCK    PFLASH->PFCBLK_SPELOCK[1]
#define PFLASH_PFCBLK2_SPELOCK    PFLASH->PFCBLK_SPELOCK[2]
#define PFLASH_PFCBLK3_SPELOCK    PFLASH->PFCBLK_SPELOCK[3]
#define PFLASH_PFCBLK4_SPELOCK    PFLASH->PFCBLK_SPELOCK[4]
#define PFLASH_PFCBLK5_SPELOCK    PFLASH->PFCBLKU_SPELOCK[0]

#define PFLASH_PFCBLK0_SSETSLOCK  PFLASH->PFCBLK_SSETSLOCK[0]
#define PFLASH_PFCBLK1_SSETSLOCK  PFLASH->PFCBLK_SSETSLOCK[1]
#define PFLASH_PFCBLK2_SSETSLOCK  PFLASH->PFCBLK_SSETSLOCK[2]
#define PFLASH_PFCBLK3_SSETSLOCK  PFLASH->PFCBLK_SSETSLOCK[3]

#define PFLASH_PFCBLK0_SETSLOCK   PFLASH->PFCBLK_SETSLOCK[0]
#define PFLASH_PFCBLK1_SETSLOCK   PFLASH->PFCBLK_SETSLOCK[1]
#define PFLASH_PFCBLK2_SETSLOCK   PFLASH->PFCBLK_SETSLOCK[2]
#define PFLASH_PFCBLK3_SETSLOCK   PFLASH->PFCBLK_SETSLOCK[3]
#define PFLASH_PFCBLK4_SETSLOCK   PFLASH->PFCBLK_SETSLOCK[4]

#endif /* __PFLASH_PRIVATE_H */
