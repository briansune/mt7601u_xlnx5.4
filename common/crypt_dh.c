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
    DH

    Abstract:
    RFC 2631: Diffie-Hellman Key Agreement Method
    
    Revision History:
    Who         When            What
    --------    ----------      ------------------------------------------
    Eddy        2009/01/21      Create Diffie-Hellman
***************************************************************************/


#include "crypt_dh.h"
#include "crypt_biginteger.h"


/*
========================================================================
Routine Description:
    Diffie-Hellman public key generation

Arguments:
    GValue           Array in unsigned char
    GValueLength     The length of G in bytes
    PValue           Array in unsigned char
    PValueLength     The length of P in bytes
    PrivateKey       Private key
    PrivateKeyLength The length of Private key in bytes

Return Value:
    PublicKey       Public key
    PublicKeyLength The length of public key in bytes

Note:
    Reference to RFC2631
    PublicKey = G^PrivateKey (mod P)
========================================================================
*/
void DH_PublicKey_Generate (
    IN unsigned char GValue[],
    IN unsigned int GValueLength,
    IN unsigned char PValue[],
    IN unsigned int PValueLength,
    IN unsigned char PrivateKey[],
    IN unsigned int PrivateKeyLength,
    OUT unsigned char PublicKey[],
    INOUT unsigned int *PublicKeyLength)
{
    PBIG_INTEGER pBI_G = NULL;
    PBIG_INTEGER pBI_P = NULL;
    PBIG_INTEGER pBI_PrivateKey = NULL;
    PBIG_INTEGER pBI_PublicKey = NULL;

    /*   
     * 1. Check the input parameters
     *    - GValueLength, PValueLength and PrivateLength must be large than zero
     *    - PublicKeyLength must be large or equal than PValueLength
     *    - PValue must be odd
     *
     *    - PValue must be prime number (no implement)
     *    - GValue must be greater than 0 but less than the PValue (no implement)
     */
    if (GValueLength == 0) {
    	DBGPRINT(RT_DEBUG_ERROR, ("DH_PublicKey_Generate: G length is (%d)\n", GValueLength));
        return;
    } /* End of if */
    if (PValueLength == 0) {
    	DBGPRINT(RT_DEBUG_ERROR, ("DH_PublicKey_Generate: P length is (%d)\n", PValueLength));
        return;
    } /* End of if */
    if (PrivateKeyLength == 0) {
    	DBGPRINT(RT_DEBUG_ERROR, ("DH_PublicKey_Generate: private key length is (%d)\n", PrivateKeyLength));
        return;
    } /* End of if */
    if (*PublicKeyLength < PValueLength) {
    	DBGPRINT(RT_DEBUG_ERROR, ("DH_PublicKey_Generate: public key length(%d) must be large or equal than P length(%d)\n", 
            *PublicKeyLength, PValueLength));
        return;
    } /* End of if */
    if (!(PValue[PValueLength - 1] & 0x1)) {
    	DBGPRINT(RT_DEBUG_ERROR, ("DH_PublicKey_Generate: P value must be odd\n"));
        return;
    } /* End of if */

    /*   
     * 2. Transfer parameters to BigInteger structure
     */
    BigInteger_Init(&pBI_G);
    BigInteger_Init(&pBI_P);
    BigInteger_Init(&pBI_PrivateKey);
    BigInteger_Init(&pBI_PublicKey);
    BigInteger_Bin2BI(GValue, GValueLength, &pBI_G);
    BigInteger_Bin2BI(PValue, PValueLength, &pBI_P);
    BigInteger_Bin2BI(PrivateKey, PrivateKeyLength, &pBI_PrivateKey);

    /*   
     * 3. Calculate PublicKey = G^PrivateKey (mod P)
     *    - BigInteger Operation
     *    - Montgomery reduction
     */     
    BigInteger_Montgomery_ExpMod(pBI_G, pBI_PrivateKey, pBI_P, &pBI_PublicKey);

    /*   
     * 4. Transfer BigInteger structure to char array
     */
    BigInteger_BI2Bin(pBI_PublicKey, PublicKey, PublicKeyLength);

    BigInteger_Free(&pBI_G);
    BigInteger_Free(&pBI_P);
    BigInteger_Free(&pBI_PrivateKey);
    BigInteger_Free(&pBI_PublicKey);    
} /* End of DH_PublicKey_Generate */


/*
========================================================================
Routine Description:
    Diffie-Hellman secret key generation

Arguments:
    PublicKey        Public key
    PublicKeyLength  The length of Public key in bytes
    PValue           Array in unsigned char
    PValueLength     The length of P in bytes
    PrivateKey       Private key
    PrivateKeyLength The length of Private key in bytes

Return Value:
    SecretKey        Secret key
    SecretKeyLength  The length of secret key in bytes

Note:
    Reference to RFC2631
    SecretKey = PublicKey^PrivateKey (mod P)
========================================================================
*/
void DH_SecretKey_Generate (
    IN unsigned char PublicKey[],
    IN unsigned int PublicKeyLength,
    IN unsigned char PValue[],
    IN unsigned int PValueLength,
    IN unsigned char PrivateKey[],
    IN unsigned int PrivateKeyLength,
    OUT unsigned char SecretKey[],
    INOUT unsigned int *SecretKeyLength)
{
    PBIG_INTEGER pBI_P = NULL;
    PBIG_INTEGER pBI_SecretKey = NULL;
    PBIG_INTEGER pBI_PrivateKey = NULL;
    PBIG_INTEGER pBI_PublicKey = NULL;

    /*   
     * 1. Check the input parameters
     *    - PublicKeyLength, PValueLength and PrivateLength must be large than zero
     *    - SecretKeyLength must be large or equal than PValueLength
     *    - PValue must be odd
     *
     *    - PValue must be prime number (no implement)
     */
    if (PublicKeyLength == 0) {
    	DBGPRINT(RT_DEBUG_ERROR, ("DH_SecretKey_Generate: public key length is (%d)\n", PublicKeyLength));
        return;
    } /* End of if */
    if (PValueLength == 0) {
    	DBGPRINT(RT_DEBUG_ERROR, ("DH_SecretKey_Generate: P length is (%d)\n", PValueLength));
        return;
    } /* End of if */
    if (PrivateKeyLength == 0) {
    	DBGPRINT(RT_DEBUG_ERROR, ("DH_SecretKey_Generate: private key length is (%d)\n", PrivateKeyLength));
        return;
    } /* End of if */
    if (*SecretKeyLength < PValueLength) {
    	DBGPRINT(RT_DEBUG_ERROR, ("DH_SecretKey_Generate: secret key length(%d) must be large or equal than P length(%d)\n", 
            *SecretKeyLength, PValueLength));
        return;
    } /* End of if */
    if (!(PValue[PValueLength - 1] & 0x1)) {
    	DBGPRINT(RT_DEBUG_ERROR, ("DH_SecretKey_Generate: P value must be odd\n"));
        return;
    } /* End of if */

    /*   
     * 2. Transfer parameters to BigInteger structure
     */
    BigInteger_Init(&pBI_P);
    BigInteger_Init(&pBI_PrivateKey);
    BigInteger_Init(&pBI_PublicKey);
    BigInteger_Init(&pBI_SecretKey);

    BigInteger_Bin2BI(PublicKey, PublicKeyLength, &pBI_PublicKey);
    BigInteger_Bin2BI(PValue, PValueLength, &pBI_P);
    BigInteger_Bin2BI(PrivateKey, PrivateKeyLength, &pBI_PrivateKey);

    /*   
     * 3. Calculate SecretKey = PublicKey^PrivateKey (mod P)
     *    - BigInteger Operation
     *    - Montgomery reduction
     */
    BigInteger_Montgomery_ExpMod(pBI_PublicKey, pBI_PrivateKey, pBI_P, &pBI_SecretKey);

    /*   
     * 4. Transfer BigInteger structure to char array
     */
    BigInteger_BI2Bin(pBI_SecretKey, SecretKey, SecretKeyLength);

    BigInteger_Free(&pBI_P);
    BigInteger_Free(&pBI_PrivateKey);
    BigInteger_Free(&pBI_PublicKey);    
    BigInteger_Free(&pBI_SecretKey);
} /* End of DH_SecretKey_Generate */

