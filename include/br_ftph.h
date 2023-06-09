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

	Abstract:

	All Bridge Fast Path Related Structure & Definition.

***************************************************************************/

#ifndef __BR_FTPH_H__
#define __BR_FTPH_H__

/* Public function prototype */
/*
========================================================================
Routine Description:
	Init bridge fast path module.

Arguments:
	None

Return Value:
	None

Note:
	Used in module init.
========================================================================
*/
VOID BG_FTPH_Init(VOID);

/*
========================================================================
Routine Description:
	Remove bridge fast path module.

Arguments:
	None

Return Value:
	None

Note:
	Used in module remove.
========================================================================
*/
VOID BG_FTPH_Remove(VOID);

/*
========================================================================
Routine Description:
	Forward the received packet.

Arguments:
	pPacket			- the received packet

Return Value:
	None

Note:
========================================================================
*/
unsigned int BG_FTPH_PacketFromApHandle(
	IN		PNDIS_PACKET	pPacket);

#endif /* __BR_FTPH_H__ */

/* End of br_ftph.h */

