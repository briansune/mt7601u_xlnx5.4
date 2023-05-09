/*

*/

#ifndef __FCE_H__
#define __FCE_H__

#include "rt_config.h"

#define FCE_PSE_CTRL	0x0800
#define FCE_CSO			0x0808
#define FCE_L2_STUFF	0x080c
#define TX_CPU_PORT_FROM_FCE_BASE_PTR		0x09A0
#define TX_CPU_PORT_FROM_FCE_MAX_COUNT		0x09A4
#define FCE_PDMA_GLOBAL_CONF				0x09C4
#define TX_CPU_PORT_FROM_FCE_CPU_DESC_INDEX 0x09A8
#define FCE_SKIP_FS							0x0A6C
#define PER_PORT_PAUSE_ENABLE_CONTROL1		0x0A38

#ifdef BIG_ENDIAN
typedef	union _L2_STUFFING_STRUC
{
	struct	{
	    unsigned int  RSV:6;
	    unsigned int  OTHER_PORT:2;
		unsigned int  TS_LENGTH_EN:8;
		unsigned int  TS_CMD_QSEL_EN:8;
		unsigned int  RSV2:2;
		unsigned int  MVINF_BYTE_SWP:1;
		unsigned int  FS_WR_MPDU_LEN_EN:1;
		unsigned int  TX_L2_DE_STUFFING_EN:1;
		unsigned int  RX_L2_STUFFING_EN:1;
		unsigned int  QoS_L2_EN:1;
		unsigned int  HT_L2_EN:1;
	}	field;
	
	unsigned int word;
} L2_STUFFING_STRUC, *PL2_STUFFING_STRUC;
#else
typedef	union _L2_STUFFING_STRUC
{
	struct	{
		unsigned int  HT_L2_EN:1;
		unsigned int  QoS_L2_EN:1;
		unsigned int  RX_L2_STUFFING_EN:1;
		unsigned int  TX_L2_DE_STUFFING_EN:1;
		unsigned int  FS_WR_MPDU_LEN_EN:1;
		unsigned int  MVINF_BYTE_SWP:1;
		unsigned int  RSV2:2;
		unsigned int  TS_CMD_QSEL_EN:8;
		unsigned int  TS_LENGTH_EN:8;
		unsigned int  OTHER_PORT:2;
		unsigned int  RSV:6;
	}	field;
	
	unsigned int word;
} L2_STUFFING_STRUC, *PL2_STUFFING_STRUC;
#endif

#define NORMAL_PKT				0x0
#define CMD_PKT					0x1

#define FCE_WLAN_PORT			0x0
#define FCE_CPU_RX_PORT			0x1
#define FCE_CPU_TX_PORT			0x2
#define FCE_HOST_PORT			0x3
#define FCE_VIRTUAL_CPU_RX_PORT	0x4
#define FCE_VIRTUAL_CPU_TX_PORT	0x5
#define FCE_DISCARD				0x6
#endif /*__FCE_H__ */