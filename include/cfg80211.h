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

	All MAC80211/CFG80211 Related Structure & Definition.

***************************************************************************/

#ifdef RT_CFG80211_SUPPORT

#include <linux/ieee80211.h>

typedef struct __CFG80211_CB {

	/* we can change channel/rate information on the fly so we backup them */
	struct ieee80211_supported_band Cfg80211_bands[IEEE80211_NUM_BANDS];
	struct ieee80211_channel *pCfg80211_Channels;
	struct ieee80211_rate *pCfg80211_Rates;

	/* used in wiphy_unregister */
	struct wireless_dev *pCfg80211_Wdev;

	/* used in scan end */
	struct cfg80211_scan_request *pCfg80211_ScanReq;

	/* monitor filter */
	unsigned int MonFilterFlag;

	/* channel information */
	struct ieee80211_channel ChanInfo[MAX_NUM_OF_CHANNELS];
} CFG80211_CB;




/*
========================================================================
Routine Description:
	Register MAC80211 Module.

Arguments:
	pAd				- WLAN control block pointer
	pDev			- Generic device interface
	pNetDev			- Network device

Return Value:
	NONE

Note:
	pDev != pNetDev
	#define SET_NETDEV_DEV(net, pdev)	((net)->dev.parent = (pdev))

	Can not use pNetDev to replace pDev; Or kernel panic.
========================================================================
*/
bool CFG80211_Register(
	VOID						*pAd,
	struct device				*pDev,
	struct net_device			*pNetDev);


#endif /* RT_CFG80211_SUPPORT */

/* End of cfg80211.h */
