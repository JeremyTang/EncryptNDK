#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <android/log.h>
#include "des.h"

static  void Init_bit_tab(unsigned char *dest,unsigned char *source,unsigned char n);
static  unsigned char puissance(unsigned char puissance);
static  void Bin_to_Hex(char *vect,char *source);
static  void Vect_Permutation(unsigned char *vect,unsigned char n_vect,
										unsigned char *regle,unsigned char n_regle);
void Xor(unsigned char *vect1,unsigned char *vect2,unsigned char num_byte);
static  void S_Box_Calc(unsigned char *vect);
static  void Init_4bit_tab(unsigned char *dest,unsigned char *source);
static  void Left_shifts(unsigned char *vect,unsigned char n);
static  void Calcul_sous_cles(unsigned char *DESKEY);

unsigned char IP[64] =
		 {
			 58,50,42,34,26,18,10,2,
			 60,52,44,36,28,20,12,4,
			 62,54,46,38,30,22,14,6,
			 64,56,48,40,32,24,16,8,
			 57,49,41,33,25,17,9,1,
			 59,51,43,35,27,19,11,3,
			 61,53,45,37,29,21,13,5,
			 63,55,47,39,31,23,15,7
       };


unsigned char IPinv[64]=
      { 
			40,8,48,16,56,24,64,32,
			39,7,47,15,55,23,63,31,
	 38,6,46,14,54,22,62,30,
			37,5,45,13,53,21,61,29,
	 36,4,44,12,52,20,60,28,
			35,3,43,11,51,19,59,27,
			34,2,42,10,50,18,58,26,
			33,1,41,9,49,17,57,25
      };


unsigned char E[48]=
       {        
			32,1,2,3,4,5,
			4,5,6,7,8,9,
			8,9,10,11,12,13,
			12,13,14,15,16,17,
			16,17,18,19,20,21,
			20,21,22,23,24,25,
			24,25,26,27,28,29,
			28,29,30,31,32,1
       };


unsigned char S1[64]=
	{
	  14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
     0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
     4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
	  15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
	};

unsigned char S2[64]=
	{
	  15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
     3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
     0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
	  13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
	};

unsigned char S3[64]=
	{ 
	  10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
     13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
     13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
	  1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
	};

unsigned char S4[64]=
   { 
	  7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
     13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
     10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
	  3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
   };

unsigned char S5[64]=
   { 
	  2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
     14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
     4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
	  11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
   };

unsigned char S6[64]=
   { 
	  12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
     10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
     9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
	  4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
   };

unsigned char S7[64]=
   { 
	  4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
     13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
     1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
	  6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
   };

unsigned char S8[64]=
   {
	  13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
     1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
     7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
	  2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
   };


unsigned char P[32]=
     { 
       16,7,20,21,
		 29,12,28,17,
		 1,15,23,26,
		 5,18,31,10,
       2,8,24,14,
		 32,27,3,9,
		 19,13,30,6,
		 22,11,4,25
	  };


unsigned char PC1[56] =
       {        
			57,49,41,33,25,17,9,
			1,58,50,42,34,26,18,
			10,2,59,51,43,35,27,
			19,11,3,60,52,44,36,
			63,55,47,39,31,23,15,
			7,62,54,46,38,30,22,
			14,6,61,53,45,37,29,
			21,13,5,28,20,12,4
		 };


unsigned char PC2[48] =
       {        
			14,17,11,24,1,5,
			3,28,15,6,21,10,
			23,19,12,4,26,8,
			16,7,27,20,13,2,
			41,52,31,37,47,55,
			30,40,51,45,33,48,
			44,49,39,56,34,53,
			46,42,50,36,29,32
		 };


unsigned char LS[17] =
       {        0,1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};


unsigned char Ki[17][49];


void Init_bit_tab(unsigned char *dest,unsigned char *source,unsigned char n)
{
	unsigned char masque,i,j;

	for(i=0;i<n;i++) {
		masque=0x80;
		for(j=0;j<8;j++) {
			dest[8*i+j] = (source[i] & masque) >> (7-j);
			masque >>= 1;
		}
	}
}

/****************************************************************************
 Bin_to_Hex()   :
	range la valeur hexa sur 8 octets d'un nombre binaire de 64 bits
*****************************************************************************/
void Bin_to_Hex(char *vect,char *source)
{
unsigned char i,j,masque;

	memset(vect,0,8);
	for(i=0; i <8; i++) {
		masque=7;
		for(j=0; j<8; j++) {
			vect[i] += (puissance(masque)) * source[i*8+j];
			--masque;
		}
	}
}

unsigned char puissance(unsigned char puissance)
{
 unsigned char res = 1, i;

	for(i=1 ; i <= puissance; i++) 
	res *= 2;

	return(res);
}


void Vect_Permutation(unsigned char *vect,unsigned char n_vect,unsigned char *regle,unsigned char n_regle)
{
	unsigned char buff[65],i;

	memset(buff,0,65);
	memcpy(buff,vect,n_vect);

	for(i=0;i<n_regle;i++) 
		vect[i] = buff[regle[i]-1];

}


void S_Box_Calc(unsigned char *vect)
{
  unsigned char *S_Box[8];
  unsigned lig,col,i;

  S_Box[0]=S1;
  S_Box[1]=S2;
  S_Box[2]=S3;
  S_Box[3]=S4;
  S_Box[4]=S5;
  S_Box[5]=S6;
  S_Box[6]=S7;
  S_Box[7]=S8;

  for(i=0;i<8;i++) {
		col= 8*vect[1+6*i] + 4*vect[2+6*i] + 2*vect[3+6*i] + vect[4+6*i];
		lig= 2*vect[6*i] + vect[5+6*i];
		Init_4bit_tab(&vect[4*i],&S_Box[i][col+lig*16]);
  }
}


void Init_4bit_tab(unsigned char *dest,unsigned char *source)
{
	unsigned char masque,i;

	masque=0x08;
	for(i=0; i<4; i++) {
		dest[i] = (*source & masque)>>(3-i);
		masque >>= 1;
	}
}


void Xor(unsigned char *vect1,unsigned char * vect2,unsigned char num_byte)
{

unsigned char i;

	for(i=0; i<num_byte; i++) 
		vect1[i] ^= vect2[i];
}


void Left_shifts(unsigned char *vect,unsigned char n)
{
	unsigned char i,tmp_vect28,tmp_vect0;

	for(i=0; i<n; i++) {
		tmp_vect0 = vect[0];
		memcpy(vect,&vect[1],27);
		vect[27] = tmp_vect0;

		tmp_vect28 = vect[28];
		memcpy(&vect[28],&vect[29],27);
		vect[55] = tmp_vect28;
	}
}

void Calcul_sous_cles(unsigned char *DESKEY)
{
	unsigned char i;
	unsigned char Kb[65],inter_key[57];

	Init_bit_tab(&Kb[1],DESKEY,8);                           
	Vect_Permutation(&Kb[1],64,PC1,56);

	for(i=1; i<=16; i++) {
		Left_shifts(&Kb[1],LS[i]);
		memcpy(&inter_key[1],&Kb[1],56);
		Vect_Permutation(&inter_key[1],56,PC2,48);
		memcpy(&Ki[i][1],&inter_key[1],48);
	}
}


void function_des(char cryp_decrypt,unsigned char *DES_DATA,unsigned char *DESKEY,unsigned char *DES_RESULT)
{
	LOGE("function_des start DES_DATA=%s ,DESKEY=%s ",DES_DATA,DESKEY);
 unsigned char right32_bit[32],i;
 unsigned char Data_B[81];


 Init_bit_tab(&Data_B[1],DES_DATA,8);
 Vect_Permutation(&Data_B[1],64,IP,64);

 Calcul_sous_cles(DESKEY);

 /******************* boucle principale de 15 iterations */
 for(i=1; i<=15; i++) {

		memcpy(right32_bit,&Data_B[33],32);
		Vect_Permutation(&Data_B[33],32,E,48);

		switch(cryp_decrypt) {
			case ENCRYPT:
				Xor(&Data_B[33],&Ki[i][1],48);
				break;

			case DECRYPT:
				Xor(&Data_B[33],&Ki[17-i][1],48);
				break;
		}

		S_Box_Calc(&Data_B[33]);
		Vect_Permutation(&Data_B[33],32,P,32);
		Xor(&Data_B[33],&Data_B[1],32);
		memcpy(&Data_B[1],right32_bit,32);

 }

 /******************************** 16 iteration *****/

 memcpy(right32_bit,&Data_B[33],32);
 Vect_Permutation(&Data_B[33],32,E,48);

 if(cryp_decrypt==ENCRYPT)
	Xor(&Data_B[33],&Ki[16][1],48);
 else
	Xor(&Data_B[33],&Ki[1][1],48);

 S_Box_Calc(&Data_B[33]);
 Vect_Permutation(&Data_B[33],32,P,32);
 Xor(&Data_B[1],&Data_B[33],32);
 memcpy(&Data_B[33],right32_bit,32);
 Vect_Permutation(&Data_B[1],64,IPinv,64);

 Bin_to_Hex(( char * )DES_RESULT,( char * )&Data_B[1]);
 LOGE("function_des end %s ",DES_RESULT);
}

/*void vPbocMac(unsigned char ucDesMode, unsigned char *psKey, unsigned char *psMsg, unsigned char ucLength, unsigned char *psMac)
{
    unsigned char ucBlock;
    unsigned char sOutMAC[8], sBuf[8];

    memcpy(sOutMAC, (char *)psMac, 8);
    ucBlock=0;
    while(ucLength > ucBlock) {
        if((ucLength - ucBlock) <= 8) {
            if((ucLength - ucBlock) == 8) {
                Xor(sOutMAC, &psMsg[ucBlock], ucLength-ucBlock);
                function_des(ENCRYPT, sOutMAC, psKey, sOutMAC);
                memcpy(sBuf, "\x80\x0\x0\x0\x0\x0\x0\x0", 8);
                Xor(sOutMAC, sBuf, 8);
                function_des(ENCRYPT, sOutMAC, psKey, sOutMAC);
                if(ucDesMode == TRI_DES) {
                    function_des(DECRYPT, sOutMAC, &psKey[8], sOutMAC);
                    function_des(ENCRYPT, sOutMAC, psKey, sOutMAC);
                }
                memcpy((char *)psMac, sOutMAC, 8);
                return;
            } else {
                memset(sBuf, 0, sizeof(sBuf));
                memcpy(sBuf, &psMsg[ucBlock], (ucLength-ucBlock));
                sBuf[ucLength-ucBlock] = 0x80;
                Xor(sOutMAC, sBuf, 8);
                function_des(ENCRYPT, sOutMAC, psKey, sOutMAC);
                if(ucDesMode == TRI_DES) {
                    function_des(DECRYPT, sOutMAC, &psKey[8], sOutMAC);
                    function_des(ENCRYPT, sOutMAC, psKey, sOutMAC);
                }
                memcpy((char *)psMac, sOutMAC, 8);
                return;
            }
        }
        Xor(sOutMAC, &psMsg[ucBlock], 8);
        function_des(ENCRYPT, sOutMAC, psKey, sOutMAC);
        ucBlock += 8;
    }
}*/

/*
void MAC(unsigned char msg[], int length, unsigned char key[],
	 unsigned char result[])
{
 int block;

 block=0;
 memset(result,0,8);

 while ( length > block )
 {
  if ( (length-block) <= 8 )
	 {
	  Xor(result,&msg[block],(unsigned char)(length-block));
	  function_des(ENCRYPT, result, key, result);
	  return;
	 }
  Xor(result,&msg[block],8);
  function_des(ENCRYPT, result, key, result);
  block += 8;
 }

}

*/

/*************************************************************************
Function : two bytes change to one bytes
Param in :
   pusFrom : sourse strings
   uiFromLen : length of sourse strings
Param out :
    pusTo : object strings.
Return Code : none
*************************************************************************/
void vTwo2One( unsigned char *pusFrom, unsigned char *pusTo, unsigned int uiFromLen )
{
   unsigned char ucTmp;
   unsigned int i;

   for( i=0; i<uiFromLen; i+=2 )
   {
      ucTmp = pusFrom[i];
      if( ucTmp > '9' )
         ucTmp = toupper(ucTmp) - 'A' + 0x0A;
      else if( ucTmp == 0x00 )   ucTmp = 0x00;
      else
         ucTmp = ucTmp - '0';

      ucTmp <<= 4;
      pusTo[i/2] = ucTmp;

      ucTmp = pusFrom[i+1];
      if( ucTmp > '9' )
         ucTmp = toupper(ucTmp) - 'A' + 0x0A;
      else if( ucTmp == 0x00 )   ucTmp = 0x00;
      else
         ucTmp = ucTmp - '0';

      pusTo[i/2] = pusTo[i/2] + ucTmp;
   }

}
/*************************************************************************
Function     : one byte change to two bytes
Param in     :
   pusFrom   : source strings
   uiFromLen : bytes of source strings
Param out    :
   pusTo     : object strings.
Return Code  : none
*************************************************************************/
void vOne2Two(unsigned char* pusFrom, unsigned char* pusTo, unsigned int uiFromLen)
{
   static unsigned char usHexToChar[16] = "0123456789ABCDEF";
   unsigned int i;

   for (i = 0; i < uiFromLen; i++)
   {
       pusTo[2 * i] = usHexToChar[(pusFrom[i] >> 4)];
       pusTo[2 * i + 1] = usHexToChar[(pusFrom[i] & 0x0F)];
   }

   return;
}
