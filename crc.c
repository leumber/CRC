#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crc.h"

/****************************Info********************************************** 
 * Name:    InvertUint8 
 * Note: 	0x12 to 0x48
			0x12: 0001 0010
			0x48: 0100 1000
 *****************************************************************************/
void InvertUint8(unsigned char *dBuf,unsigned char *srcBuf)
{
	int i;
	unsigned char tmp[4]={0};

	for(i=0;i< 8;i++)
	{
		if(srcBuf[0]& (1 << i))
		tmp[0]|=1<<(7-i);
	}
	dBuf[0] = tmp[0];
	
}
void InvertUint16(unsigned short *dBuf,unsigned short *srcBuf)
{
	int i;
	unsigned short tmp[4]={0};

	for(i=0;i< 16;i++)
	{
		if(srcBuf[0]& (1 << i))
		tmp[0]|=1<<(15 - i);
	}
	dBuf[0] = tmp[0];
}
void InvertUint32(unsigned int *dBuf,unsigned int *srcBuf)
{
	int i;
	unsigned int tmp[4]={0};
	
	for(i=0;i< 32;i++)
	{
		if(srcBuf[0]& (1 << i))
		tmp[0]|=1<<(31 - i);
	}
	dBuf[0] = tmp[0];
}

/****************************Info********************************************** 
 * Name:    CRC-4/ITU	x4+x+1 
 * Width:	4
 * Poly:    0x03 
 * Init:    0x00 
 * Refin:   True 
 * Refout:  True 
 * Xorout:  0x00 
 * Note: 
 *****************************************************************************/
#if 0
unsigned char CRC4_ITU(unsigned char *data, unsigned int datalen)
{
	unsigned char wCRCin = 0x00;
	unsigned char wCPoly = 0x03;
	unsigned char wChar = 0;
	
	while (datalen--) 	
	{
		wChar = *(data++);
		InvertUint8(&wChar,&wChar);
		wCRCin ^= (wChar);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x80)
				wCRCin = (wCRCin << 1) ^ (wCPoly << 4);
			else
				wCRCin = wCRCin << 1;
		}
	}
	InvertUint8(&wCRCin,&wCRCin);
	return (wCRCin);
}
#else
unsigned char CRC4_ITU(unsigned char *data, unsigned int datalen)
{
	unsigned char wCRCin = 0x00;
	unsigned char wCPoly = 0x03;
	
	InvertUint8(&wCPoly,&wCPoly);
	while (datalen--) 	
	{
		wCRCin ^= *(data++);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x01)
				wCRCin = (wCRCin >> 1) ^ (wCPoly >>4);
			else
				wCRCin = wCRCin >> 1;
		}
	}
	return (wCRCin);
}
#endif
/****************************Info********************************************** 
 * Name:    CRC-5/EPC	x5+x3+1 
 * Width:	5
 * Poly:    0x09 
 * Init:    0x09 
 * Refin:   False 
 * Refout:  False 
 * Xorout:  0x00 
 * Note: 
 *****************************************************************************/
unsigned char CRC5_EPC(unsigned char *data, unsigned int datalen)
{
	unsigned char wCRCin = 0x09<<3;
	unsigned char wCPoly = 0x09<<3;
	
	while (datalen--) 	
	{
		wCRCin ^= *(data++);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x80)
				wCRCin = (wCRCin << 1) ^ (wCPoly);
			else
				wCRCin = wCRCin << 1;
		}
	}
	return (wCRCin >> 3);
}
/****************************Info********************************************** 
 * Name:    CRC-5/USB	x5+x2+1 
 * Width:	5
 * Poly:    0x05 
 * Init:    0x1F 
 * Refin:   True 
 * Refout:  True 
 * Xorout:  0x1F 
 * Note: 
 *****************************************************************************/
#if 0
unsigned char CRC5_USB(unsigned char *data, unsigned int datalen)
{
	unsigned char wCRCin = 0x1F<<3;
	unsigned char wCPoly = 0x05;
	unsigned char wChar = 0;
	
	while (datalen--) 	
	{
		wChar = *(data++);
		InvertUint8(&wChar,&wChar);
		wCRCin ^= (wChar);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x80)
				wCRCin = (wCRCin << 1) ^ (wCPoly << 3);
			else
				wCRCin = wCRCin << 1;
		}
	}
	InvertUint8(&wCRCin,&wCRCin);
	return (wCRCin^0x1F);
}
#else
unsigned char CRC5_USB(unsigned char *data, unsigned int datalen)  
{  
	unsigned char wCRCin = 0x1F;
	unsigned char wCPoly = 0x05;
	
	InvertUint8(&wCPoly,&wCPoly);
	while (datalen--) 	
	{
		wCRCin ^= *(data++);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x01)
				wCRCin = (wCRCin >> 1) ^ (wCPoly >> 3);
			else
				wCRCin = wCRCin >> 1;
		}
	}
	return (wCRCin^0x1F); 
} 
#endif
/****************************Info********************************************** 
 * Name:    CRC-5/ITU	x5+x4+x2+1  
 * Width:	5
 * Poly:    0x15 
 * Init:    0x00 
 * Refin:   True 
 * Refout:  True 
 * Xorout:  0x00 
 * Note: 
 *****************************************************************************/
 #if 0
unsigned char CRC5_ITU(unsigned char *data, unsigned int datalen)
{
	unsigned char wCRCin = 0x00;
	unsigned char wCPoly = 0x15;
	unsigned char wChar = 0;
	
	while (datalen--) 	
	{
		wChar = *(data++);
		InvertUint8(&wChar,&wChar);
		wCRCin ^= (wChar);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x80)
				wCRCin = (wCRCin << 1) ^ (wCPoly << 3);
			else
				wCRCin = wCRCin << 1;
		}
	}
	InvertUint8(&wCRCin,&wCRCin);
	return (wCRCin);
}
#else
unsigned char CRC5_ITU(unsigned char *data, unsigned int datalen)  
{  
	unsigned char wCRCin = 0x00;
	unsigned char wCPoly = 0x15;
	
	InvertUint8(&wCPoly,&wCPoly);
	while (datalen--) 	
	{
		wCRCin ^= *(data++);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x01)
				wCRCin = (wCRCin >> 1) ^ (wCPoly >> 3);
			else
				wCRCin = wCRCin >> 1;
		}
	}
	return (wCRCin); 
} 
#endif
/****************************Info********************************************** 
 * Name:    CRC-6/ITU	x6+x+1 
 * Width:	6
 * Poly:    0x03 
 * Init:    0x00 
 * Refin:   True 
 * Refout:  True 
 * Xorout:  0x00 
 * Note: 
 *****************************************************************************/
unsigned char CRC6_ITU(unsigned char *data, unsigned int datalen)
{
	unsigned char wCRCin = 0x00;
	unsigned char wCPoly = 0x03;
	unsigned char wChar = 0;
	
	while (datalen--) 	
	{
		wChar = *(data++);
		InvertUint8(&wChar,&wChar);
		wCRCin ^= (wChar);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x80)
				wCRCin = (wCRCin << 1) ^ (wCPoly << 2);
			else
				wCRCin = wCRCin << 1;
		}
	}
	InvertUint8(&wCRCin,&wCRCin);
	return (wCRCin);
}
/****************************Info********************************************** 
 * Name:    CRC-7/MMC           x7+x3+1  
 * Width:	7
 * Poly:    0x09 
 * Init:    0x00 
 * Refin:   False 
 * Refout:  False 
 * Xorout:  0x00 
 * Use:     MultiMediaCard,SD,ect. 
 *****************************************************************************/
unsigned char CRC7_MMC(unsigned char *data, unsigned int datalen)
{
	unsigned char wCRCin = 0x00;
	unsigned char wCPoly = 0x09;
	
	while (datalen--) 	
	{
		wCRCin ^= *(data++);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x80)
				wCRCin = (wCRCin << 1) ^ (wCPoly<<1);
			else
				wCRCin = wCRCin << 1;
		}
	}
	return (wCRCin>>1);
}
/****************************Info********************************************** 
 * Name:    CRC-8               x8+x2+x+1 
 * Width:	8 
 * Poly:    0x07 
 * Init:    0x00 
 * Refin:   False 
 * Refout:  False 
 * Xorout:  0x00 
 * Note: 
 *****************************************************************************/
unsigned char CRC8(unsigned char *data, unsigned int datalen)
{
	unsigned char wCRCin = 0x00;
	unsigned char wCPoly = 0x07;
	
	while (datalen--) 	
	{
		wCRCin ^= *(data++);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x80)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	return (wCRCin);
}
/****************************Info********************************************** 
 * Name:    CRC-8/ITU           x8+x2+x+1 
 * Width:	8 
 * Poly:    0x07 
 * Init:    0x00 
 * Refin:   False 
 * Refout:  False 
 * Xorout:  0x55 
 * Alias:   CRC-8/ATM 
 *****************************************************************************/
unsigned char CRC8_ITU(unsigned char *data, unsigned int datalen)
{
	unsigned char wCRCin = 0x00;
	unsigned char wCPoly = 0x07;
	
	while (datalen--) 	
	{
		wCRCin ^= *(data++);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x80)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	return (wCRCin^0x55);
}
/****************************Info********************************************** 
 * Name:    CRC-8/ROHC          x8+x2+x+1 
 * Width:	8 
 * Poly:    0x07 
 * Init:    0xFF 
 * Refin:   True 
 * Refout:  True 
 * Xorout:  0x00 
 * Note: 
 *****************************************************************************/
#if 0
unsigned char CRC8_ROHC(unsigned char *data, unsigned int datalen)
{
	unsigned char wCRCin = 0xFF;
	unsigned char wCPoly = 0x07;
	unsigned char wChar = 0;
	
	while (datalen--) 	
	{
		wChar = *(data++);
		InvertUint8(&wChar,&wChar);
		wCRCin ^= (wChar << 0);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x80)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	InvertUint8(&wCRCin,&wCRCin);
	return (wCRCin);
}
#else 
unsigned char CRC8_ROHC(unsigned char *data, unsigned int datalen)
{
	unsigned char wCRCin = 0xFF;
	unsigned char wCPoly = 0x07;
	
	InvertUint8(&wCPoly,&wCPoly);
	while (datalen--) 	
	{
		wCRCin ^= *(data++);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x01)
				wCRCin = (wCRCin >> 1) ^ wCPoly;
			else
				wCRCin = wCRCin >> 1;
		}
	}
	return (wCRCin);
}
#endif
/****************************Info********************************************** 
 * Name:    CRC-8/MAXIM         x8+x5+x4+1 
 * Width:	8 
 * Poly:    0x31 
 * Init:    0x00 
 * Refin:   True 
 * Refout:  True 
 * Xorout:  0x00 
 * Alias:   DOW-CRC,CRC-8/IBUTTON 
 * Use:     Maxim(Dallas)'s some devices,e.g. DS18B20 
 *****************************************************************************/ 
#if 0
unsigned char CRC8_MAXIM(unsigned char *data, unsigned int datalen)
{
	unsigned char wCRCin = 0x00;
	unsigned char wCPoly = 0x31;
	unsigned char wChar = 0;
	
	while (datalen--) 	
	{
		wChar = *(data++);
		InvertUint8(&wChar,&wChar);
		wCRCin ^= (wChar << 0);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x80)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	InvertUint8(&wCRCin,&wCRCin);
	return (wCRCin);
}
#else 
unsigned char CRC8_MAXIM(unsigned char *data, unsigned int datalen)
{
	unsigned char wCRCin = 0x00;
	unsigned char wCPoly = 0x31;
	
	InvertUint8(&wCPoly,&wCPoly);
	while (datalen--) 	
	{
		wCRCin ^= *(data++);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x01)
				wCRCin = (wCRCin >> 1) ^ wCPoly;
			else
				wCRCin = wCRCin >> 1;
		}
	}
	return (wCRCin);
}
#endif
/****************************Info********************************************** 
 * Name:    CRC-16/CCITT        x16+x12+x5+1
 * Width:	16 
 * Poly:    0x1021 
 * Init:    0x0000 
 * Refin:   True 
 * Refout:  True 
 * Xorout:  0x0000 
 * Alias:   CRC-CCITT,CRC-16/CCITT-TRUE,CRC-16/KERMIT 
 *****************************************************************************/ 
#if 0
unsigned short CRC16_CCITT(unsigned char *data, unsigned int datalen)
{
	unsigned short wCRCin = 0x0000;
	unsigned short wCPoly = 0x1021;
	unsigned char wChar = 0;
	
	while (datalen--) 	
	{
		wChar = *(data++);
		InvertUint8(&wChar,&wChar);
		wCRCin ^= (wChar << 8);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x8000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	InvertUint16(&wCRCin,&wCRCin);
	return (wCRCin);
}
#else 
//这里为了效率，我们不需要将所有Refin和refout为true的输入输出数据移位转换
//只需要将poly二项式转换后，运算时将左移变为右移
unsigned short CRC16_CCITT(unsigned char *data, unsigned int datalen)
{
	unsigned short wCRCin = 0x0000;
	unsigned short wCPoly = 0x1021;
	unsigned char wChar = 0;
	
	InvertUint16(&wCPoly,&wCPoly);
	while (datalen--) 	
	{
		wCRCin ^= *(data++);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x01)
				wCRCin = (wCRCin >> 1) ^ wCPoly;
			else
				wCRCin = wCRCin >> 1;
		}
	}
	return (wCRCin);
}
#endif
/****************************Info********************************************** 
 * Name:    CRC-16/CCITT-FALSE   x16+x12+x5+1 
 * Width:	16 
 * Poly:    0x1021 
 * Init:    0xFFFF 
 * Refin:   False 
 * Refout:  False 
 * Xorout:  0x0000 
 * Note: 
 *****************************************************************************/ 
unsigned short CRC16_CCITT_FALSE(unsigned char *data, unsigned int datalen)
{
	unsigned short wCRCin = 0xFFFF;
	unsigned short wCPoly = 0x1021;
	
	while (datalen--) 	
	{
		wCRCin ^= *(data++) << 8;
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x8000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	return (wCRCin);
}
/****************************Info********************************************** 
 * Name:    CRC-16/XMODEM       x16+x12+x5+1 
 * Width:	16 
 * Poly:    0x1021 
 * Init:    0x0000 
 * Refin:   False 
 * Refout:  False 
 * Xorout:  0x0000 
 * Alias:   CRC-16/ZMODEM,CRC-16/ACORN 
 *****************************************************************************/ 
unsigned short CRC16_XMODEM(unsigned char *data, unsigned int datalen)
{
	unsigned short wCRCin = 0x0000;
	unsigned short wCPoly = 0x1021;
	
	while (datalen--) 	
	{
		wCRCin ^= (*(data++) << 8);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x8000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	return (wCRCin);
}
/****************************Info********************************************** 
 * Name:    CRC-16/X25          x16+x12+x5+1 
 * Width:	16 
 * Poly:    0x1021 
 * Init:    0xFFFF 
 * Refin:   True 
 * Refout:  True 
 * Xorout:  0XFFFF 
 * Note: 
 *****************************************************************************/
#if 0 
unsigned short CRC16_X25(unsigned char *data, unsigned int datalen)
{
	unsigned short wCRCin = 0xFFFF;
	unsigned short wCPoly = 0x1021;
	unsigned char wChar = 0;

	while (datalen--) 	
	{
		wChar = *(data++);
		InvertUint8(&wChar,&wChar);
		wCRCin ^= (wChar << 8);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x8000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	InvertUint16(&wCRCin,&wCRCin);
	return (wCRCin^0xFFFF);
}
#else 
unsigned short CRC16_X25(unsigned char *data, unsigned int datalen)
{
	unsigned short wCRCin = 0xFFFF;
	unsigned short wCPoly = 0x1021;
	
	InvertUint16(&wCPoly,&wCPoly);
	while (datalen--) 	
	{
		wCRCin ^= *(data++);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x01)
				wCRCin = (wCRCin >> 1) ^ wCPoly;
			else
				wCRCin = wCRCin >> 1;
		}
	}
	return (wCRCin^0xFFFF);
}
#endif
/****************************Info********************************************** 
 * Name:    CRC-16/MODBUS       x16+x15+x2+1 
 * Width:	16 
 * Poly:    0x8005 
 * Init:    0xFFFF 
 * Refin:   True 
 * Refout:  True 
 * Xorout:  0x0000 
 * Note: 
 *****************************************************************************/
#if 0 
unsigned short CRC16_MODBUS(unsigned char *data, unsigned int datalen)
{
	unsigned short wCRCin = 0xFFFF;
	unsigned short wCPoly = 0x8005;
	unsigned char wChar = 0;
	
	while (datalen--) 	
	{
		wChar = *(data++);
		InvertUint8(&wChar,&wChar);
		wCRCin ^= (wChar << 8);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x8000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	InvertUint16(&wCRCin,&wCRCin);
	return (wCRCin);
}
#else 
unsigned short CRC16_MODBUS(unsigned char *data, unsigned int datalen)
{
	unsigned short wCRCin = 0xFFFF;
	unsigned short wCPoly = 0x8005;
	
	InvertUint16(&wCPoly,&wCPoly);
	while (datalen--) 	
	{
		wCRCin ^= *(data++);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x01)
				wCRCin = (wCRCin >> 1) ^ wCPoly;
			else
				wCRCin = wCRCin >> 1;
		}
	}
	return (wCRCin);
}
#endif
/****************************Info********************************************** 
 * Name:    CRC-16/IBM          x16+x15+x2+1 
 * Width:	16 
 * Poly:    0x8005 
 * Init:    0x0000 
 * Refin:   True 
 * Refout:  True 
 * Xorout:  0x0000 
 * Alias:   CRC-16,CRC-16/ARC,CRC-16/LHA 
 *****************************************************************************/ 
#if 0
unsigned short CRC16_IBM(unsigned char *data, unsigned int datalen)
{
	unsigned short wCRCin = 0x0000;
	unsigned short wCPoly = 0x8005;
	unsigned char wChar = 0;
	
	while (datalen--) 	
	{
		wChar = *(data++);
		InvertUint8(&wChar,&wChar);
		wCRCin ^= (wChar << 8);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x8000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	InvertUint16(&wCRCin,&wCRCin);
	return (wCRCin);
}
#else 
unsigned short CRC16_IBM(unsigned char *data, unsigned int datalen)
{
	unsigned short wCRCin = 0x0000;
	unsigned short wCPoly = 0x8005;
	
	InvertUint16(&wCPoly,&wCPoly);
	while (datalen--) 	
	{
		wCRCin ^= *(data++);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x01)
				wCRCin = (wCRCin >> 1) ^ wCPoly;
			else
				wCRCin = wCRCin >> 1;
		}
	}
	return (wCRCin);
}
#endif
/****************************Info********************************************** 
 * Name:    CRC-16/MAXIM        x16+x15+x2+1 
 * Width:	16 
 * Poly:    0x8005 
 * Init:    0x0000 
 * Refin:   True 
 * Refout:  True 
 * Xorout:  0xFFFF 
 * Note: 
 *****************************************************************************/
#if 0
unsigned short CRC16_MAXIM(unsigned char *data, unsigned int datalen)
{
	unsigned short wCRCin = 0x0000;
	unsigned short wCPoly = 0x8005;
	unsigned char wChar = 0;
	
	while (datalen--) 	
	{
		wChar = *(data++);
		InvertUint8(&wChar,&wChar);
		wCRCin ^= (wChar << 8);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x8000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	InvertUint16(&wCRCin,&wCRCin);
	return (wCRCin^0xFFFF);
}
#else 
unsigned short CRC16_MAXIM(unsigned char *data, unsigned int datalen)
{
	unsigned short wCRCin = 0x0000;
	unsigned short wCPoly = 0x8005;
	
	InvertUint16(&wCPoly,&wCPoly);
	while (datalen--) 	
	{
		wCRCin ^= *(data++);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x01)
				wCRCin = (wCRCin >> 1) ^ wCPoly;
			else
				wCRCin = wCRCin >> 1;
		}
	}
	return (wCRCin^0xFFFF);
}
#endif
/****************************Info********************************************** 
 * Name:    CRC-16/USB          x16+x15+x2+1 
 * Width:	16 
 * Poly:    0x8005 
 * Init:    0xFFFF 
 * Refin:   True 
 * Refout:  True 
 * Xorout:  0xFFFF 
 * Note: 
 *****************************************************************************/ 
#if 0
unsigned short CRC16_USB(unsigned char *data, unsigned int datalen)
{
	unsigned short wCRCin = 0xFFFF;
	unsigned short wCPoly = 0x8005;
	unsigned char wChar = 0;
	
	while (datalen--) 	
	{
		wChar = *(data++);
		InvertUint8(&wChar,&wChar);
		wCRCin ^= (wChar << 8);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x8000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	InvertUint16(&wCRCin,&wCRCin);
	return (wCRCin^0xFFFF);
}
#else 
unsigned short CRC16_USB(unsigned char *data, unsigned int datalen)
{
	unsigned short wCRCin = 0xFFFF;
	unsigned short wCPoly = 0x8005;
	
	InvertUint16(&wCPoly,&wCPoly);
	while (datalen--) 	
	{
		wCRCin ^= *(data++);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x01)
				wCRCin = (wCRCin >> 1) ^ wCPoly;
			else
				wCRCin = wCRCin >> 1;
		}
	}
	return (wCRCin^0xFFFF);
}
#endif
/****************************Info********************************************** 
 * Name:    CRC-16/DNP          x16+x13+x12+x11+x10+x8+x6+x5+x2+1 
 * Width:	16 
 * Poly:    0x3D65 
 * Init:    0x0000 
 * Refin:   True 
 * Refout:  True 
 * Xorout:  0xFFFF 
 * Use:     M-Bus,ect. 
 *****************************************************************************/  
#if 0
unsigned short CRC16_DNP(unsigned char *data, unsigned int datalen)
{
	unsigned short wCRCin = 0x0000;
	unsigned short wCPoly = 0x3D65;
	unsigned char wChar = 0;
	
	while (datalen--) 	
	{
		wChar = *(data++);
		InvertUint8(&wChar,&wChar);
		wCRCin ^= (wChar << 8);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x8000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	InvertUint16(&wCRCin,&wCRCin);
	return (wCRCin^0xFFFF) ;
}
#else
unsigned short CRC16_DNP(unsigned char *data, unsigned int datalen)
{
	unsigned short wCRCin = 0x0000;
	unsigned short wCPoly = 0x3D65;
	
	InvertUint16(&wCPoly,&wCPoly);
	while (datalen--) 	
	{
		wCRCin ^= *(data++);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x01)
				wCRCin = (wCRCin >> 1) ^ wCPoly;
			else
				wCRCin = (wCRCin >> 1);
		}
	}
	return (wCRCin^0xFFFF);
}
#endif
/****************************Info********************************************** 
 * Name:    CRC-32  x32+x26+x23+x22+x16+x12+x11+x10+x8+x7+x5+x4+x2+x+1 
 * Width:	32 
 * Poly:    0x4C11DB7 
 * Init:    0xFFFFFFF 
 * Refin:   True 
 * Refout:  True 
 * Xorout:  0xFFFFFFF 
 * Alias:   CRC_32/ADCCP 
 * Use:     WinRAR,ect. 
 *****************************************************************************/  
#if 0
unsigned int CRC32(unsigned char *data, unsigned int datalen)
{
	unsigned int wCRCin = 0xFFFFFFFF;
	unsigned int wCPoly = 0x04C11DB7;
	unsigned int wChar = 0;
	while (datalen--) 	
	{
		wChar = *(data++);
		InvertUint8((unsigned char *)&wChar,(unsigned char *)&wChar);
		wCRCin ^= (wChar << 24);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x80000000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	InvertUint32(&wCRCin,&wCRCin);
	return (wCRCin ^ 0xFFFFFFFF) ;
}
#else
unsigned int CRC32(unsigned char *data, unsigned int datalen)
{

	unsigned int wCRCin = 0xFFFFFFFF;
	unsigned int wCPoly = 0x04C11DB7;

	InvertUint32(&wCPoly,&wCPoly);
	while (datalen--) 	
	{
		wCRCin ^= *(data++);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x01)
				wCRCin = (wCRCin >> 1) ^ wCPoly;
			else
				wCRCin = wCRCin >> 1;
		}
	}
	return (wCRCin ^ 0xFFFFFFFF) ;
}
#endif
/****************************Info********************************************** 
 * Name:    CRC-32/MPEG-2  x32+x26+x23+x22+x16+x12+x11+x10+x8+x7+x5+x4+x2+x+1 
 * Width:	32 
 * Poly:    0x4C11DB7 
 * Init:    0xFFFFFFF 
 * Refin:   False 
 * Refout:  False 
 * Xorout:  0x0000000 
 * Note: 
 *****************************************************************************/ 
unsigned int CRC32_MPEG(unsigned char *data, unsigned int datalen)
{

	unsigned int wCRCin = 0xFFFFFFFF;
	unsigned int wCPoly = 0x04C11DB7;
	unsigned int wChar = 0;
	while (datalen--) 	
	{
		wChar = *(data++);
		wCRCin ^= (wChar << 24);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x80000000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	return (wCRCin) ;
}
#define myStrToHex(c) ((c==0)?0:(((c>='A')&&(c<='F'))?(c-0x37):(((c>='a')&&(c<='f'))?(c-0x57):(c-0x30))))
void MyStrToHex(unsigned char *pstr, unsigned char *phex)
{
	int i;
	for (i = 0; i < strlen(pstr)/2; i++)
	{
		phex[i] = myStrToHex(pstr[2*i]) << 4 | myStrToHex(pstr[2*i+1]);
	}
}



int main()
{
	char data[128] = {0};
	
	MyStrToHex("AB3F45AE9D023FA1",data);
	
	printf("CRC4_ITU:\t%#X\n",CRC4_ITU(data, strlen(data)));
	printf("CRC5_EPC:\t%#X\n",CRC5_EPC(data, strlen(data)));
	printf("CRC5_USB:\t%#X\n",CRC5_USB(data, strlen(data)));
	printf("CRC5_ITU:\t%#X\n",CRC5_ITU(data, strlen(data)));
	printf("CRC6_ITU:\t%#X\n",CRC6_ITU(data, strlen(data)));
	printf("CRC7_MMC:\t%#X\n",CRC7_MMC(data, strlen(data)));
	printf("CRC8:\t\t%#X\n",CRC8(data, strlen(data)));
	printf("CRC8_ITU:\t%#X\n",CRC8_ITU(data, strlen(data)));
	printf("CRC8_ROHC:\t%#X\n",CRC8_ROHC(data, strlen(data)));
	printf("CRC8_MAXIM:\t%#X\n",CRC8_MAXIM(data, strlen(data)));
	printf("CRC16_CCITT:\t%#X\n",CRC16_CCITT(data, strlen(data)));
	printf("CRC16_CCITT_F:\t%#X\n",CRC16_CCITT_FALSE(data, strlen(data)));
	printf("CRC16_XMODEM:\t%#X\n",CRC16_XMODEM(data, strlen(data)));
	printf("CRC16_X25:\t%#X\n",CRC16_X25(data, strlen(data)));
	printf("CRC16_MODBUS:\t%#X\n",CRC16_MODBUS(data, strlen(data)));
	printf("CRC16_IBM:\t%#X\n",CRC16_IBM(data, strlen(data)));
	printf("CRC16_MAXIM:\t%#X\n",CRC16_MAXIM(data, strlen(data)));
	printf("CRC16_USB:\t%#X\n",CRC16_USB(data, strlen(data)));
	printf("CRC16_DNP:\t%#X\n",CRC16_DNP(data, strlen(data)));
	
	printf("CRC32:\t\t%#X\n",CRC32(data, strlen(data)));
	printf("CRC32_MPEG:\t%#X\n",CRC32_MPEG(data, strlen(data)));
	
	return 0;

}
