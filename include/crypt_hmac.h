/****************************************************************************
 * Ralink Tech Inc.
 * Taiwan, R.O.C.
 *
 * (c) Copyright 2002, Ralink Technology, Inc.
 *
 * All rights reserved. Ralink's source code is an unpublished work and the
 * use of a copyright notice does not imply otherwise. This source code
 * contains confidential trade secret material of Ralink Tech. Any attemp
 * or participation in deciphering, decoding, reverse engineering or in any
 * way altering the source code is stricitly prohibited, unless the prior
 * written consent of Ralink Technology, Inc. is obtained.
 ***************************************************************************/

/****************************************************************************
    Module Name:
    HMAC

    Abstract:
    FIPS 198: The Keyed-Hash Message Authentication Code (HMAC)
    
    Revision History:
    Who         When            What
    --------    ----------      ------------------------------------------
    Eddy        2008/11/24      Create HMAC-SHA1, HMAC-SHA256
***************************************************************************/

#ifndef __CRYPT_HMAC_H__
#define __CRYPT_HMAC_H__

#include "rt_config.h"


#ifdef SHA1_SUPPORT
#define HMAC_SHA1_SUPPORT
VOID RT_HMAC_SHA1(
	IN const unsigned char Key[],
	IN unsigned int KeyLen,
	IN const unsigned char Message[],
	IN unsigned int MessageLen,
	OUT unsigned char MAC[],
	IN unsigned int MACLen);
#endif /* SHA1_SUPPORT */

#ifdef SHA256_SUPPORT
#define HMAC_SHA256_SUPPORT
VOID RT_HMAC_SHA256(
	IN const unsigned char Key[],
	IN unsigned int KeyLen,
	IN const unsigned char Message[],
	IN unsigned int MessageLen,
	OUT unsigned char MAC[],
	IN unsigned int MACLen);
#endif /* SHA256_SUPPORT */

#ifdef MD5_SUPPORT
#define HMAC_MD5_SUPPORT
VOID RT_HMAC_MD5(
	IN const unsigned char Key[],
	IN unsigned int KeyLen,
	IN const unsigned char Message[],
	IN unsigned int MessageLen,
	OUT unsigned char MAC[],
	IN unsigned int MACLen);
#endif /* MD5_SUPPORT */


#endif /* __CRYPT_HMAC_H__ */