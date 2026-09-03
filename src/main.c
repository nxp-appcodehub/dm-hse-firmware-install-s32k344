/*============================================================================
 *
 *   Copyright 2020 - 2026 NXP
 *
 * 	 NXP Proprietary. This software is owned or controlled by NXP and may only be
 *   used strictly in accordance with the applicable license terms. By expressly
 *   accepting such terms or by downloading, installing, activating and/or otherwise
 *   using the software, you are agreeing that you have read, and that you agree to
 *   comply with and are bound by, such license terms. If you do not agree to be
 *   bound by the applicable license terms, then you may not retain, install,
 *   activate or otherwise use the software.
 =============================================================================*/
/**
    @file        main.c
    @version     1.0.0

    @brief       HSE - FW Install project.
    @details     Sample project demonstrating how to install HSE Firmware to S32K3 device
*/
/*=============================================================================
                                         INCLUDE FILES
=============================================================================*/

#include "S32K344.h"
#include <typedefs.h>
#include <string.h>
#include "hse_mu.h"
#include "hse_host_attrs.h"
#include "pflash.h"
#include "flash.h"
#include "hse_host.h"



/*=============================================================================
                   LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
=============================================================================*/

typedef enum
{
    FW_NOT_INSTALLED = 0,
    FW_INSTALLED
}fwteststatus_t;


/*=============================================================================
*                         LOCAL MACROS
=============================================================================*/

//#define ERASE

#define ASSERT(condition)   \
    do {                    \
        if(!(condition))    \
            while(1);       \
    } while(0)


#define UTEST_BASE_ADDRESS		        0x1B000000UL

#define MuInstance_0 (0)

#define HSE_SRV_ID_ERASE_FW                 ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000057UL))  /**< @brief Erase Sys-Img, Backup FW as well Current running HSE FW from code flash. Data Structure used: #hseEraseFwSrv_t */

hseSrvResponse_t Erase_HSE_FW(uint8_t MuInstance);

/*=============================================================================
*                         LOCAL VARIABLES
=============================================================================*/
/* HSE FW feature usage flag to be loaded in UTEST */
static uint8_t hseFwFeatureFlagEnabledValue[8] = {0xAA, 0xBB, 0xCC, 0xDD,
										   0xDD, 0xCC, 0xBB, 0xAA};

/*=============================================================================
*                         GLOBAL CONSTANTS
=============================================================================*/

/*=============================================================================
*                         GLOBAL VARIABLES
=============================================================================*/

/* Variable to store HSE FW version details */
hseAttrFwVersion_t gHseFwVersion = {0U};

volatile fwteststatus_t gInstallHSEFwTest = FW_NOT_INSTALLED;

/*=============================================================================
 *                        GLOBAL FUNCTIONS
 * ==========================================================================*/
boolean checkHseFwFeatureFlagEnabled(void);
hseSrvResponse_t HSE_GetVersion_Example( hseAttrFwVersion_t *pHseFwVersion );


int main(void)
{
#ifdef ERASE
	hseSrvResponse_t SrvResponse = HSE_SRV_RSP_GENERAL_ERROR;

	while((HSE_STATUS_INIT_OK & HSE_MU_GetHseStatus(MuInstance_0)) == 0)
	{
		//Wait for the HSE_STATUS_INIT_OK flag to set
	}

	Erase_HSE_FW(MuInstance_0);
	ASSERT(HSE_SRV_RSP_OK == SrvResponse);

#else

	/* Status variable for flash interface */
	tFLASH_STATUS status;

    /* Check if HSE FW usage flag is already enabled. Otherwise program the flag */
    if(FALSE == checkHseFwFeatureFlagEnabled())
    {
    	  /* unlock UTEST data flash sector */
    	  PFLASH_Unlock (PFLASH_BL5, PFLASH_SS0, PFLASH_S0);

    	  /* Write in UtestSector using main interface */
    	  status = FLASH_Write ((uint32_t*)UTEST_BASE_ADDRESS,
    			  	  	  	  	  	  	   hseFwFeatureFlagEnabledValue,
    	                                   sizeof(hseFwFeatureFlagEnabledValue));

    	  (void)status;	// Dummy read to remove warning
    }

    /* Wait for HSE to initialize(read status bits) after installation */
    while((HSE_STATUS_INIT_OK & HSE_MU_GetHseStatus(0)) == 0)
    {
        gInstallHSEFwTest = FW_NOT_INSTALLED;
        /* Please generate a reset to allow installation */
    }

    (void)HSE_GetVersion_Example(&gHseFwVersion);

#endif

    while(1);
    return 0;
}


/******************************************************************************
 * Function:    checkHseFwFeatureFlagEnabled
 * Description: Verifies whether hse fw feature flag is already enabled or not
 *****************************************************************************/
boolean checkHseFwFeatureFlagEnabled(void)
{
    boolean fw_enabled = FALSE;
    uint64_t default_val = 0xFFFFFFFFFFFFFFFFUL;
    uint64_t hsefwfeatureflag = *(uint64_t*)(UTEST_BASE_ADDRESS);

    //check the default value
    if(FALSE != memcmp((void *)&hsefwfeatureflag, (void *)&default_val, 0x8U))
    {
        fw_enabled = TRUE;
    }
    return fw_enabled;
}

/******************************************************************************
 * Function:    HSE_GetVersion_Example
 * Description: Example of HSE service - get FW version
******************************************************************************/
hseSrvResponse_t HSE_GetVersion_Example( hseAttrFwVersion_t *pHseFwVersion )
{
    hseSrvResponse_t srvResponse;
    srvResponse = GetAttr(
            HSE_FW_VERSION_ATTR_ID,
            sizeof(hseAttrFwVersion_t),
            pHseFwVersion );
    ASSERT(HSE_SRV_RSP_OK == srvResponse);
    return srvResponse;
}

/******************************************************************************
 * Function:    Erase_HSE_FW
 * Description: Request the HSE_SRV_FW_ERASE service to erase the SYS-IMG and backup from FLASH.
******************************************************************************/
hseSrvResponse_t Erase_HSE_FW(uint8_t MuInstance)
{
    hseSrvResponse_t hseSrvResponse = HSE_SRV_RSP_GENERAL_ERROR;

    uint8_t MuChannel = 0;

    MuChannel = HSE_MU_GetFreeChannel(MuInstance);

	hseSrvDescriptor_t* pHseSrvDesc = &gHseSrvDesc[MuInstance][MuChannel];

	memset(pHseSrvDesc, 0, sizeof(hseSrvDescriptor_t));

	pHseSrvDesc->srvId = HSE_SRV_ID_ERASE_FW;

	hseSrvResponse = HSE_Send(MuInstance, MuChannel, gSyncTxOption, pHseSrvDesc);

    return hseSrvResponse;
}
