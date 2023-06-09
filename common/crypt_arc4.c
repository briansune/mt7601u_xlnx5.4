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
    RC4

    Abstract:
    
    Revision History:
    Who         When            What
    --------    ----------      ------------------------------------------
    Eddy        2009/05/13      ARC4
***************************************************************************/

#include "crypt_arc4.h"


/*
========================================================================
Routine Description:
    ARC4 initialize the key block

Arguments:
    pARC4_CTX        Pointer to ARC4 CONTEXT
    Key              Cipher key, it may be 16, 24, or 32 bytes (128, 192, or 256 bits)
    KeyLength        The length of cipher key in bytes

========================================================================
*/
VOID ARC4_INIT (
    IN ARC4_CTX_STRUC *pARC4_CTX,
    IN unsigned char * pKey,
	IN unsigned int KeyLength)
{
    unsigned int BlockIndex = 0, SWAPIndex = 0, KeyIndex = 0;
    unsigned char TempValue = 0;

    /*Initialize the block value*/
    pARC4_CTX->BlockIndex1 = 0;
    pARC4_CTX->BlockIndex2 = 0;
    for (BlockIndex = 0; BlockIndex < ARC4_KEY_BLOCK_SIZE; BlockIndex++)
        pARC4_CTX->KeyBlock[BlockIndex] = (unsigned char) BlockIndex;

    /*Key schedule*/
    for (BlockIndex = 0; BlockIndex < ARC4_KEY_BLOCK_SIZE; BlockIndex++)
    {
        TempValue = pARC4_CTX->KeyBlock[BlockIndex];
        KeyIndex = BlockIndex % KeyLength;
        SWAPIndex = (SWAPIndex + TempValue + pKey[KeyIndex]) & 0xff;
        pARC4_CTX->KeyBlock[BlockIndex] = pARC4_CTX->KeyBlock[SWAPIndex];
        pARC4_CTX->KeyBlock[SWAPIndex] = TempValue;                
    } /* End of for */

} /* End of ARC4_INIT */


/*
========================================================================
Routine Description:
    ARC4 encryption/decryption

Arguments:
    pARC4_CTX       Pointer to ARC4 CONTEXT
    InputText       Input text
    InputTextLength The length of input text in bytes

Return Value:
    OutputBlock       Return output text
 ========================================================================
*/
VOID ARC4_Compute (
    IN ARC4_CTX_STRUC *pARC4_CTX,
    IN unsigned char InputBlock[],
    IN unsigned int InputBlockSize,
    OUT unsigned char OutputBlock[])
{
    unsigned int InputIndex = 0;
    unsigned char TempValue = 0;

    for (InputIndex = 0; InputIndex < InputBlockSize; InputIndex++)
    {
        pARC4_CTX->BlockIndex1 = (pARC4_CTX->BlockIndex1 + 1) & 0xff;
        TempValue = pARC4_CTX->KeyBlock[pARC4_CTX->BlockIndex1];
        pARC4_CTX->BlockIndex2 = (pARC4_CTX->BlockIndex2 + TempValue) & 0xff;
        
        pARC4_CTX->KeyBlock[pARC4_CTX->BlockIndex1] = pARC4_CTX->KeyBlock[pARC4_CTX->BlockIndex2];
        pARC4_CTX->KeyBlock[pARC4_CTX->BlockIndex2] = TempValue;
        
        TempValue = (TempValue + pARC4_CTX->KeyBlock[pARC4_CTX->BlockIndex1]) & 0xff;
        OutputBlock[InputIndex] = InputBlock[InputIndex]^pARC4_CTX->KeyBlock[TempValue];

    } /* End of for */
} /* End of ARC4_Compute */


/*
========================================================================
Routine Description:
    Discard the key length

Arguments:
    pARC4_CTX   Pointer to ARC4 CONTEXT
    Length      Discard the key length

========================================================================
*/
VOID ARC4_Discard_KeyLength (
    IN ARC4_CTX_STRUC *pARC4_CTX,
    IN unsigned int Length)    
{
    unsigned int Index = 0;
    unsigned char TempValue = 0;
    
    for (Index = 0; Index < Length; Index++)
    {
        pARC4_CTX->BlockIndex1 = (pARC4_CTX->BlockIndex1 + 1) & 0xff;
        TempValue = pARC4_CTX->KeyBlock[pARC4_CTX->BlockIndex1];
        pARC4_CTX->BlockIndex2 = (pARC4_CTX->BlockIndex2 + TempValue) & 0xff;
        
        pARC4_CTX->KeyBlock[pARC4_CTX->BlockIndex1] = pARC4_CTX->KeyBlock[pARC4_CTX->BlockIndex2];
        pARC4_CTX->KeyBlock[pARC4_CTX->BlockIndex2] = TempValue;
    } /* End of for */

} /* End of ARC4_Discard_KeyLength */


