/**
 * @author  Lukas Herudek
 * @email   lukas.herudek@gmail.com
 * @version v1.0
 * @ide     Atmel Studio 6.2
 * @license GNU GPL v3
 * @brief   OLED library using SSD1306 for AVR
 * @verbatim
   ----------------------------------------------------------------------
    Copyright (C) Lukas Herudek, 2018
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
     
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
	See the GNU General Public License for more details.
	
	<http://www.gnu.org/licenses/>
@endverbatim
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>
#include "OLED.h"


void OLEDdata(unsigned char data)
{
	SPDR = data;// Start transmission
	while(!(SPSR & (1<<SPIF)));// Wait for transmission complete
}

void OLED2data(unsigned char data)//one byte twice
{
	SPDR = data;// Start transmission
	while(!(SPSR & (1<<SPIF)));// Wait for transmission complete
	SPDR = data;// Start transmission
	while(!(SPSR & (1<<SPIF)));// Wait for transmission complete
}

void OLED3data(unsigned char data)//one byte triple times
{
	SPDR = data;// Start transmission
	while(!(SPSR & (1<<SPIF)));// Wait for transmission complete
	SPDR = data;// Start transmission
	while(!(SPSR & (1<<SPIF)));// Wait for transmission complete
	SPDR = data;// Start transmission
	while(!(SPSR & (1<<SPIF)));// Wait for transmission complete
}

void OLED4data(unsigned char data)//one byte four times
{
	SPDR = data;// Start transmission
	while(!(SPSR & (1<<SPIF)));// Wait for transmission complete
	SPDR = data;// Start transmission
	while(!(SPSR & (1<<SPIF)));// Wait for transmission complete
	SPDR = data;// Start transmission
	while(!(SPSR & (1<<SPIF)));// Wait for transmission complete
	SPDR = data;// Start transmission
	while(!(SPSR & (1<<SPIF)));// Wait for transmission complete
}

void OLEDdataNEG(unsigned char data)
{
	SPDR = (~data);// Start transmission
	while(!(SPSR & (1<<SPIF)));// Wait for transmission complete
}

void OLED2dataNEG(unsigned char data)//one byte twice
{
	data = (~data);
	SPDR = data;// Start transmission
	while(!(SPSR & (1<<SPIF)));// Wait for transmission complete
	SPDR = data;// Start transmission
	while(!(SPSR & (1<<SPIF)));// Wait for transmission complete
}

void OLED3dataNEG(unsigned char data)//one byte triple times
{
	data = (~data);
	SPDR = data;// Start transmission
	while(!(SPSR & (1<<SPIF)));// Wait for transmission complete
	SPDR = data;// Start transmission
	while(!(SPSR & (1<<SPIF)));// Wait for transmission complete
	SPDR = data;// Start transmission
	while(!(SPSR & (1<<SPIF)));// Wait for transmission complete
}

void OLED4dataNEG(unsigned char data)//one byte four times
{
	data = (~data);
	SPDR = data;// Start transmission
	while(!(SPSR & (1<<SPIF)));// Wait for transmission complete
	SPDR = data;// Start transmission
	while(!(SPSR & (1<<SPIF)));// Wait for transmission complete
	SPDR = data;// Start transmission
	while(!(SPSR & (1<<SPIF)));// Wait for transmission complete
	SPDR = data;// Start transmission
	while(!(SPSR & (1<<SPIF)));// Wait for transmission complete
}

void OLEDcommand(unsigned char command)
{
	DC_command();
	SPDR = command;// Start transmission
	while(!(SPSR & (1<<SPIF)));// Wait for transmission complete
	DC_data();
}

void OLEDreset()//resetov·nÌ displeje
{
	clearResetPin();
	_delay_ms(1);
	setResetPin();
	_delay_ms(1);
}

void OLEDon()//zapnutÌ displeje
{
	CS_active();
	OLEDcommand(OLED_DISP_ON);
	CS_off();
}

void OLEDoff()//vypnutÌ displeje
{
	CS_active();
	OLEDcommand(OLED_DISP_OFF);
	CS_off();
}

void OLEDsetContrast(unsigned char contrast)//0xFF max, 0x00 min (not dark!)
{
	CS_active();
	OLEDcommand(OLED_SET_CONTRAST);
	OLEDcommand(contrast);
	CS_off();
}

void OLEDsetY(unsigned char y) //nastavenÌ sou¯adnice
{
//	CS_active();
	OLEDcommand(176 + y);
//	CS_off();
}

void OLEDsetX(unsigned char x) //nastavenÌ sou¯adnice
{
//	CS_active();
	OLEDcommand(OLED_SET_COL_HI | (x>>4));
	OLEDcommand(OLED_SET_COL_LO | (x & 0x0F));
//	CS_off();
}

void OLEDsetXY(unsigned char x, unsigned char y) //nastavenÌ obou sou¯adnic z·roveÚ
{
//	CS_active();
	OLEDsetY(y);
	OLEDsetX(x);
//	CS_off();
}

void OLEDinvert()//invertov·nÌ displeje (zhasnutÈ pixely se rozsvÌtÌ a rozsvÌcenÈ zhasnou)
{
	CS_active();
	OLEDcommand(OLED_DISP_REV);
	CS_off();
}

void OLEDdeinvert()//deinvertov·nÌ displeje (zhasnutÈ pixely se rozsvÌtÌ a rozsvÌcenÈ zhasnou)
{
	CS_active();
	OLEDcommand(OLED_DISP_NOR);
	CS_off();
}

void OLEDclear()//vymaz·nÌ displeje
{
	CS_active();
	int i;
	OLEDsetXY(0,0);
	for(i=0; i<=BYTE_RESOLUTION; i++)
		OLEDdata(0x00);
	CS_off();
}

void OLEDfill()//vyplnÏnÌ displeje
{
	CS_active();
	int i;
	OLEDsetXY(0,0);
	for(i=0; i<=BYTE_RESOLUTION; i++)
		OLEDdata(0xFF);
	CS_off();
}

void OLEDclearLine(unsigned char line)//vymaz·nÌ jednoho ¯·dku displeje
{
	CS_active();
	int i;
	OLEDsetY(line);
	OLEDsetX(X_START);
	
	for(i=0; i<X_RESOLUTION; i++)
		OLEDdata(0x00);
	CS_off();
}

void OLEDfillLine(unsigned char line)//vyplnÏnÌ jednoho ¯·dku displeje
{
	CS_active();
	int i;
	OLEDsetY(line);
	OLEDsetX(X_START);
	
	for(i=0; i<X_RESOLUTION; i++)
		OLEDdata(0xFF);
	CS_off();
}

//////////////////////////////////////////////////////////////////////////

void OLEDinit()//inicializace displeje
{
	CS_active();
	//SPI inicializace
	SPSR = (1<<SPI2X);
	SPCR = (1<<SPE)|(1<<MSTR)/*|(SPR0)*/;//Enable SPI, Master, set clock rate fck/2
	
	OLEDreset();
	// Recommended intialization sequence
	OLEDcommand(OLED_DISP_OFF);
	OLEDcommand(OLED_SET_RATIO_OSC);
	OLEDcommand(0x80);
	OLEDcommand(OLED_MULTIPLEX);
	OLEDcommand(0x3F);
	OLEDcommand(OLED_SET_OFFSET);
	OLEDcommand(0x00);
	OLEDcommand(OLED_SET_LINE);
	OLEDcommand(OLED_CHARGE_PUMP);
	OLEDcommand(OLED_PUMP_ON);
	OLEDcommand(OLED_SET_SEG_REMAP1);
	OLEDcommand(OLED_SET_SCAN_NOR);
	OLEDcommand(OLED_SET_PADS);
	OLEDcommand(0x12);
	OLEDcommand(OLED_SET_CONTRAST);
	OLEDcommand(0xFF);//0xFF
	OLEDcommand(OLED_SET_CHARGE);
	OLEDcommand(0xF1);
	OLEDcommand(OLED_SET_VCOM);
	OLEDcommand(0x40);
	OLEDcommand(OLED_EON_OFF);
	OLEDcommand(OLED_DISP_NOR);
	OLEDcommand(OLED_MEM_ADDRESSING);
	OLEDcommand(0x00);//Horizont·lnÌ adresovacÌ mÛd
	OLEDcommand(OLED_DISP_ON);
	_delay_ms(100);//doporuËeno v˝robcem ¯adiËe
	OLEDclear();
	CS_off();
}

void OLEDdrawImage()//vykreslÌ obr·zek
{
	CS_active();
	unsigned char i, j;
	
	for(i=Y_START; i<Y_BYTE_RESOLUTION; i++)
	{
		OLEDsetXY(X_START, i);
		for(j=X_START; j<(X_BYTE_RESOLUTION); j++)
		{
			OLEDdata(pgm_read_byte(&(picture[i][j])));
		}
	}
	CS_off();
}

void OLEDdrawImageInvert()//vykreslÌ obr·zek
{
	CS_active();
	unsigned char i, j;
	
	for(i=Y_START; i<Y_BYTE_RESOLUTION; i++)
	{
		OLEDsetXY(X_START, i);
		for(j=X_START; j<(X_BYTE_RESOLUTION); j++)
		{
			OLEDdataNEG(pgm_read_byte(&(picture[i][j])));
		}
	}
	CS_off();
}
//////////////////////////////////////////////////////////////////////////


unsigned char OLEDconvertChar(unsigned char ch)
{
	switch(ch)
	{
		case '¡': ch='[';break;
		case '»': ch='\\';break;
		case 'œ': ch=']';break;
		case '…': ch='^';break;
		case 'Ã': ch='_';break;
		case 'Õ': ch='`';break;
		case '“': ch='a';break;
		case '”': ch='b';break;
		case 'ÿ': ch='c';break;
		case 'ä': ch='d';break;
		case 'ç': ch='e';break;
		case '⁄': ch='f';break;
		case 'Ÿ': ch='g';break;
		case '›': ch='h';break;
		case 'é': ch='i';break;
		case '∞': ch='j';break;
		case 0x0d: ch='k';break;//CR
		case 0x0a: ch='l';break;//LF
		case '|': ch='m';break;
		//case 'n': character='n';break;//baterie pln·
		//case 'o': character='o';break;//baterie p˘lka
		//case 'p': character='p';break;//baterie pr·zdn·
		//case '': character='';break;
	}
	return (ch - ' ');
}

unsigned char OLEDconvertCharMicroFont(unsigned char ch)
{
	switch(ch)
	{
		case '∞': ch='a';break;
		case '|': ch='b';break;
		//case '': character='';break;
	}
	return (ch - ' ');
}

//////////////////////////////////////////////////////////////////////////
void OLEDwriteChar1line(unsigned char x, unsigned char y, unsigned char ch)
{
	CS_active();
	unsigned char j=0;
	
	OLEDsetXY(x,y);	
	for(j=0;j<3;j++)
	{
		OLEDdata(pgm_read_byte(&(microFont[OLEDconvertCharMicroFont(ch)][j])));
	}
	CS_off();
}

void OLEDwriteChar2lines(unsigned char x, unsigned char y, unsigned char ch)
{
	CS_active();
	unsigned char i=0, j=0;
	ch = OLEDconvertChar(ch);
	
	for(i=0;i<2;i++)
	{
		OLEDsetXY(x,y+i);
		
		for(j=0;j<8;j++)
		{
			OLEDdata(pgm_read_byte(&(font[ch][j+8*i])));
		}
	}
	CS_off();
}

void OLEDwriteChar2linesBOLD(unsigned char x, unsigned char y, unsigned char ch)//tuËnÈ
{
	CS_active();
	unsigned char i=0, j=0, data;
	ch = OLEDconvertChar(ch);
	
	for(i=0;i<2;i++)
	{
		OLEDsetXY(x,y+i);
		
		for(j=0;j<8;j++)
		{
			data=pgm_read_byte(&(font[ch][j+8*i]));
			OLED2data(data);
		}
	}
	CS_off();
}

void OLEDwriteChar4lines(unsigned char x, unsigned char y, unsigned char ch)
{
	CS_active();
	unsigned char i=0, j=0, k=0;
	unsigned char bigData[4][8];
	ch = OLEDconvertChar(ch);

	for(i=0;i<4;i++)
	{
		for(j=0;j<8;j++)
		{
			bigData[i][j]=0;
		}
	}
	
	//z bajtu 0b  0  1  1  0      1  0  0  1 udÏl· 2 bajty
	//        0b 00 11 11 00 |0b 11 00 00 11
	for(i=0;i<2;i++)
	{
		for(j=0;j<8;j++)
		{
			for(k=0;k<8;k++)
			{
				if(pgm_read_byte(&(font[ch][j+8*i]))&(1<<k))
				{
					bigData[(k/4)+(i*2)][j]+=(0b11<<((k*2)%8));
				}
				else
				{
					bigData[(k/4)+(i*2)][j]+=(0b00<<((k*2)%8));
				}
			}
		}
	}

	for(i=0;i<4;i++)
	{
		OLEDsetXY(x,y+i);
		
		for(j=0;j<8;j++)
		{
			OLED2data(bigData[i][j]);
		}
	}
	CS_off();
}

void OLEDwriteChar4linesBOLD(unsigned char x, unsigned char y, unsigned char ch)
{
	CS_active();
	unsigned char i=0, j=0, k=0;
	unsigned char bigData[4][8];
	ch = OLEDconvertChar(ch);

	for(i=0;i<4;i++)
	{
		for(j=0;j<8;j++)
		{
			bigData[i][j]=0;
		}
	}
	
	//z bajtu 0b  0  1  1  0      1  0  0  1 udÏl· 2 bajty
	//        0b 00 11 11 00 |0b 11 00 00 11
	for(i=0;i<2;i++)
	{
		for(j=0;j<8;j++)
		{
			for(k=0;k<8;k++)
			{
				if(pgm_read_byte(&(font[ch][j+8*i]))&(1<<k))
				{
					bigData[(k/4)+(i*2)][j]+=(0b11<<((k*2)%8));
				}
				else
				{
					bigData[(k/4)+(i*2)][j]+=(0b00<<((k*2)%8));
				}
			}
		}
	}

	for(i=0;i<4;i++)
	{
		OLEDsetXY(x,y+i);
		
		for(j=0;j<8;j++)
		{
			OLED3data(bigData[i][j]);
		}
	}
	CS_off();
}

void OLEDwriteChar8lines(unsigned char x, unsigned char y, unsigned char ch)
{
	CS_active();
	unsigned char i=0, j=0, k=0;
	unsigned char bigData[8][8];
	ch = OLEDconvertChar(ch);

	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			bigData[i][j]=0;
		}
	}
	
	//z bajtu 0b   0    1      1    0        1    0      0    1    udÏl· 4 bajty
	//        0b 0000 1111 | 1111 0000 |0b 1111 0000 | 0000 1111
	for(i=0;i<2;i++)
	{
		for(j=0;j<8;j++)
		{
			for(k=0;k<8;k++)
			{
				if(pgm_read_byte(&(font[ch][j+8*i]))&(1<<k))
				{
					bigData[(k/2)+(i*4)][j]+=(0b1111<<((k*4)%8));
				}
				else
				{
					bigData[(k/2)+(i*4)][j]+=(0b0000<<((k*4)%8));
				}
			}
		}
	}

	for(i=0;i<8;i++)
	{
		OLEDsetXY(x,y+i);
		
		for(j=0;j<8;j++)
		{
			OLED2data(bigData[i][j]);
		}
	}
	CS_off();
}

void OLEDwriteChar8linesBOLD(unsigned char x, unsigned char y, unsigned char ch)
{
	CS_active();
	unsigned char i=0, j=0, k=0;
	unsigned char bigData[8][8];
	ch = OLEDconvertChar(ch);

	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			bigData[i][j]=0;
		}
	}
	
	//z bajtu 0b   0    1      1    0        1    0      0    1    udÏl· 4 bajty
	//        0b 0000 1111 | 1111 0000 |0b 1111 0000 | 0000 1111
	for(i=0;i<2;i++)
	{
		for(j=0;j<8;j++)
		{
			for(k=0;k<8;k++)
			{
				if(pgm_read_byte(&(font[ch][j+8*i]))&(1<<k))
				{
					bigData[(k/2)+(i*4)][j]+=(0b1111<<((k*4)%8));
				}
				else
				{
					bigData[(k/2)+(i*4)][j]+=(0b0000<<((k*4)%8));
				}
			}
		}
	}

	for(i=0;i<8;i++)
	{
		OLEDsetXY(x,y+i);
		
		for(j=0;j<8;j++)
		{
			OLED3data(bigData[i][j]);
		}
	}
	CS_off();
}

//////////////////////////////////////////////////////////////////////////
void OLEDwriteString1line(unsigned char x, unsigned char y, char* string)
{
	while(*string)
	{
		OLEDwriteChar1line(x, y, *string++);
		x+=MICRO_FONT_SIZE+MICRO_FONT_SPACE_SIZE;
	}
}

void OLEDwriteString2lines(unsigned char x, unsigned char y, char* string)
{
	while(*string)
	{
		OLEDwriteChar2lines(x, y, *string++);
		x+=NORMAL_FONT_SIZE+NORMAL_FONT_SPACE_SIZE;
	}
}

void OLEDwriteString2linesBOLD(unsigned char x, unsigned char y, char* string)
{
	while(*string)
	{
		OLEDwriteChar2linesBOLD(x, y, *string++);
		x+=NORMAL_FONT_BOLD_SIZE+NORMAL_FONT_BOLD_SPACE_SIZE;
	}
}

void OLEDwriteString4lines(unsigned char x, unsigned char y, char* string)
{
	while(*string)
	{
		OLEDwriteChar4lines(x, y, *string++);
		x+=BIG_FONT_SIZE+BIG_FONT_SPACE_SIZE;
	}
}

void OLEDwriteString4linesBOLD(unsigned char x, unsigned char y, char* string)
{
	while(*string)
	{
		OLEDwriteChar4linesBOLD(x, y, *string++);
		x+=BIG_FONT_BOLD_SIZE+BIG_FONT_BOLD_SPACE_SIZE;
	}
}

void OLEDwriteString8lines(unsigned char x, unsigned char y, char* string)
{
	while(*string)
	{
		OLEDwriteChar8lines(x, y, *string++);
		x+=MEGA_FONT_SIZE+MEGA_FONT_SPACE_SIZE;
	}
}

void OLEDwriteString8linesBOLD(unsigned char x, unsigned char y, char* string)
{
	while(*string)
	{
		OLEDwriteChar8linesBOLD(x, y, *string++);
		x+=MEGA_FONT_BOLD_SIZE+MEGA_FONT_BOLD_SPACE_SIZE;
	}
}

//////////////////////////////////////////////////////////////////////////
void OLEDwriteString1linePGM(unsigned char x, unsigned char y, const char* string)
{
	while(pgm_read_byte(string))
	{
		OLEDwriteChar1line(x, y, pgm_read_byte(string++));
		x+=MICRO_FONT_SIZE+MICRO_FONT_SPACE_SIZE;
	}
}

void OLEDwriteString2linesPGM(unsigned char x, unsigned char y, const char* string)
{
	while(pgm_read_byte(string))
	{
		OLEDwriteChar2lines(x, y, pgm_read_byte(string++));
		x+=NORMAL_FONT_SIZE+NORMAL_FONT_SPACE_SIZE;
	}
}

void OLEDwriteString2linesBOLDPGM(unsigned char x, unsigned char y, const char* string)
{
	while(pgm_read_byte(string))
	{
		OLEDwriteChar2linesBOLD(x, y, pgm_read_byte(string++));
		x+=NORMAL_FONT_BOLD_SIZE+NORMAL_FONT_BOLD_SPACE_SIZE;
	}
}

void OLEDwriteString4linesPGM(unsigned char x, unsigned char y, const char* string)
{
	while(pgm_read_byte(string))
	{
		OLEDwriteChar4lines(x, y, pgm_read_byte(string++));
		x+=BIG_FONT_SIZE+BIG_FONT_SPACE_SIZE;
	}
}

void OLEDwriteString4linesBOLDPGM(unsigned char x, unsigned char y, const char* string)
{
	while(pgm_read_byte(string))
	{
		OLEDwriteChar4linesBOLD(x, y, pgm_read_byte(string++));
		x+=BIG_FONT_BOLD_SIZE+BIG_FONT_BOLD_SPACE_SIZE;
	}
}

void OLEDwriteString8linesPGM(unsigned char x, unsigned char y, const char* string)
{
	while(pgm_read_byte(string))
	{
		OLEDwriteChar8lines(x, y, pgm_read_byte(string++));
		x+=MEGA_FONT_SIZE+MEGA_FONT_SPACE_SIZE;
	}
}

void OLEDwriteString8linesBOLDPGM(unsigned char x, unsigned char y, const char* string)
{
	while(pgm_read_byte(string))
	{
		OLEDwriteChar8linesBOLD(x, y, pgm_read_byte(string++));
		x+=MEGA_FONT_BOLD_SIZE+MEGA_FONT_BOLD_SPACE_SIZE;
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void OLEDwriteChar1lineNEG(unsigned char x, unsigned char y, unsigned char ch)
{
	CS_active();
	unsigned char j=0;
	
	OLEDsetXY(x,y);
	for(j=0;j<3;j++)
	{
		OLEDdataNEG(pgm_read_byte(&(microFont[OLEDconvertCharMicroFont(ch)][j])));
	}
	CS_off();
}

void OLEDwriteChar2linesNEG(unsigned char x, unsigned char y, unsigned char ch)
{
	CS_active();
	unsigned char i=0, j=0;
	ch = OLEDconvertChar(ch);
	
	for(i=0;i<2;i++)
	{
		OLEDsetXY(x,y+i);
		
		for(j=0;j<8;j++)
		{
			OLEDdataNEG(pgm_read_byte(&(font[ch][j+8*i])));
		}
	}
	CS_off();
}

void OLEDwriteChar2linesBOLDNEG(unsigned char x, unsigned char y, unsigned char ch)//tuËnÈ
{
	CS_active();
	unsigned char i=0, j=0, data;
	ch = OLEDconvertChar(ch);
	
	for(i=0;i<2;i++)
	{
		OLEDsetXY(x,y+i);
		
		for(j=0;j<8;j++)
		{
			data=pgm_read_byte(&(font[ch][j+8*i]));
			OLED2dataNEG(data);
		}
	}
	CS_off();
}

void OLEDwriteChar4linesNEG(unsigned char x, unsigned char y, unsigned char ch)
{
	CS_active();
	unsigned char i=0, j=0, k=0;
	unsigned char bigData[4][8];
	ch = OLEDconvertChar(ch);

	for(i=0;i<4;i++)
	{
		for(j=0;j<8;j++)
		{
			bigData[i][j]=0;
		}
	}
	
	//z bajtu 0b  0  1  1  0      1  0  0  1 udÏl· 2 bajty
	//        0b 00 11 11 00 |0b 11 00 00 11
	for(i=0;i<2;i++)
	{
		for(j=0;j<8;j++)
		{
			for(k=0;k<8;k++)
			{
				if(pgm_read_byte(&(font[ch][j+8*i]))&(1<<k))
				{
					bigData[(k/4)+(i*2)][j]+=(0b11<<((k*2)%8));
				}
				else
				{
					bigData[(k/4)+(i*2)][j]+=(0b00<<((k*2)%8));
				}
			}
		}
	}

	for(i=0;i<4;i++)
	{
		OLEDsetXY(x,y+i);
		
		for(j=0;j<8;j++)
		{
			OLED2dataNEG(bigData[i][j]);
		}
	}
	CS_off();
}

void OLEDwriteChar4linesBOLDNEG(unsigned char x, unsigned char y, unsigned char ch)
{
	CS_active();
	unsigned char i=0, j=0, k=0;
	unsigned char bigData[4][8];
	ch = OLEDconvertChar(ch);

	for(i=0;i<4;i++)
	{
		for(j=0;j<8;j++)
		{
			bigData[i][j]=0;
		}
	}
	
	//z bajtu 0b  0  1  1  0      1  0  0  1 udÏl· 2 bajty
	//        0b 00 11 11 00 |0b 11 00 00 11
	for(i=0;i<2;i++)
	{
		for(j=0;j<8;j++)
		{
			for(k=0;k<8;k++)
			{
				if(pgm_read_byte(&(font[ch][j+8*i]))&(1<<k))
				{
					bigData[(k/4)+(i*2)][j]+=(0b11<<((k*2)%8));
				}
				else
				{
					bigData[(k/4)+(i*2)][j]+=(0b00<<((k*2)%8));
				}
			}
		}
	}

	for(i=0;i<4;i++)
	{
		OLEDsetXY(x,y+i);
		
		for(j=0;j<8;j++)
		{
			OLED3dataNEG(bigData[i][j]);
		}
	}
	CS_off();
}

void OLEDwriteChar8linesNEG(unsigned char x, unsigned char y, unsigned char ch)
{
	CS_active();
	unsigned char i=0, j=0, k=0;
	unsigned char bigData[8][8];
	ch = OLEDconvertChar(ch);

	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			bigData[i][j]=0;
		}
	}
	
	//z bajtu 0b   0    1      1    0        1    0      0    1    udÏl· 4 bajty
	//        0b 0000 1111 | 1111 0000 |0b 1111 0000 | 0000 1111
	for(i=0;i<2;i++)
	{
		for(j=0;j<8;j++)
		{
			for(k=0;k<8;k++)
			{
				if(pgm_read_byte(&(font[ch][j+8*i]))&(1<<k))
				{
					bigData[(k/2)+(i*4)][j]+=(0b1111<<((k*4)%8));
				}
				else
				{
					bigData[(k/2)+(i*4)][j]+=(0b0000<<((k*4)%8));
				}
			}
		}
	}

	for(i=0;i<8;i++)
	{
		OLEDsetXY(x,y+i);
		
		for(j=0;j<8;j++)
		{
			OLED2dataNEG(bigData[i][j]);
		}
	}
	CS_off();
}

void OLEDwriteChar8linesBOLDNEG(unsigned char x, unsigned char y, unsigned char ch)
{
	CS_active();
	unsigned char i=0, j=0, k=0;
	unsigned char bigData[8][8];
	ch = OLEDconvertChar(ch);

	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			bigData[i][j]=0;
		}
	}
	
	//z bajtu 0b   0    1      1    0        1    0      0    1    udÏl· 4 bajty
	//        0b 0000 1111 | 1111 0000 |0b 1111 0000 | 0000 1111
	for(i=0;i<2;i++)
	{
		for(j=0;j<8;j++)
		{
			for(k=0;k<8;k++)
			{
				if(pgm_read_byte(&(font[ch][j+8*i]))&(1<<k))
				{
					bigData[(k/2)+(i*4)][j]+=(0b1111<<((k*4)%8));
				}
				else
				{
					bigData[(k/2)+(i*4)][j]+=(0b0000<<((k*4)%8));
				}
			}
		}
	}

	for(i=0;i<8;i++)
	{
		OLEDsetXY(x,y+i);
		
		for(j=0;j<8;j++)
		{
			OLED3dataNEG(bigData[i][j]);
		}
	}
	CS_off();
}

//////////////////////////////////////////////////////////////////////////

void OLEDwriteSpace1lineNEG(unsigned char x, unsigned char y)
{
	CS_active();
	unsigned char j=0;
	
	OLEDsetXY(x,y);
	for(j=0;j<MICRO_FONT_SPACE_SIZE;j++)
	{
		OLEDdataNEG(0);
	}
	CS_off();
}

void OLEDwriteSpace2linesNEG(unsigned char x, unsigned char y)
{
	CS_active();
	unsigned char i=0, j=0;
	
	for(i=0;i<2;i++)
	{
		OLEDsetXY(x,y+i);
		
		for(j=0;j<NORMAL_FONT_SPACE_SIZE;j++)
		{
			OLEDdataNEG(0);
		}
	}
	CS_off();
}

void OLEDwriteSpace2linesBOLDNEG(unsigned char x, unsigned char y)//tuËnÈ
{
	CS_active();
	unsigned char i=0, j=0;
	
	for(i=0;i<2;i++)
	{
		OLEDsetXY(x,y+i);
		
		for(j=0;j<NORMAL_FONT_BOLD_SPACE_SIZE;j++)
		{
			OLED2dataNEG(0);
		}
	}
	CS_off();
}

void OLEDwriteSpace4linesNEG(unsigned char x, unsigned char y)
{
	CS_active();
	unsigned char i=0, j=0;

	for(i=0;i<4;i++)
	{
		OLEDsetXY(x,y+i);
		
		for(j=0;j<BIG_FONT_SPACE_SIZE;j++)
		{
			OLED2dataNEG(0);
		}
	}
	CS_off();
}

void OLEDwriteSpace4linesBOLDNEG(unsigned char x, unsigned char y)
{
	CS_active();
	unsigned char i=0, j=0;

	for(i=0;i<4;i++)
	{
		OLEDsetXY(x,y+i);
		
		for(j=0;j<BIG_FONT_BOLD_SPACE_SIZE;j++)
		{
			OLED3dataNEG(0);
		}
	}
	CS_off();
}

void OLEDwriteSpace8linesNEG(unsigned char x, unsigned char y)
{
	CS_active();
	unsigned char i=0, j=0;

	for(i=0;i<8;i++)
	{
		OLEDsetXY(x,y+i);
		
		for(j=0;j<MEGA_FONT_SPACE_SIZE;j++)
		{
			OLED2dataNEG(0);
		}
	}
	CS_off();
}

void OLEDwriteSpace8linesBOLDNEG(unsigned char x, unsigned char y)
{
	CS_active();
	unsigned char i=0, j=0;

	for(i=0;i<8;i++)
	{
		OLEDsetXY(x,y+i);
		
		for(j=0;j<MEGA_FONT_BOLD_SPACE_SIZE;j++)
		{
			OLED3dataNEG(0);
		}
	}
	CS_off();
}

//////////////////////////////////////////////////////////////////////////

void OLEDwriteString1lineNEG(unsigned char x, unsigned char y, char* string)
{
	while(*string)
	{
		OLEDwriteChar1lineNEG(x, y, *string++);
		x+=MICRO_FONT_SIZE;
		OLEDwriteSpace1lineNEG(x, y);
		x+=MICRO_FONT_SPACE_SIZE;
	}
}

void OLEDwriteString2linesNEG(unsigned char x, unsigned char y, char* string)
{
	while(*string)
	{
		OLEDwriteChar2linesNEG(x, y, *string++);
		x+=NORMAL_FONT_SIZE;
		OLEDwriteSpace2linesNEG(x, y);
		x+=NORMAL_FONT_SPACE_SIZE;
	}
}

void OLEDwriteString2linesBOLDNEG(unsigned char x, unsigned char y, char* string)
{
	while(*string)
	{
		OLEDwriteChar2linesBOLDNEG(x, y, *string++);
		x+=NORMAL_FONT_BOLD_SIZE;
		OLEDwriteSpace2linesBOLDNEG(x, y);
		x+=NORMAL_FONT_BOLD_SPACE_SIZE;
	}
}

void OLEDwriteString4linesNEG(unsigned char x, unsigned char y, char* string)
{
	while(*string)
	{
		OLEDwriteChar4linesNEG(x, y, *string++);
		x+=BIG_FONT_SIZE;
		OLEDwriteSpace4linesNEG(x, y);
		x+=BIG_FONT_SPACE_SIZE;
	}
}

void OLEDwriteString4linesBOLDNEG(unsigned char x, unsigned char y, char* string)
{
	while(*string)
	{
		OLEDwriteChar4linesBOLDNEG(x, y, *string++);
		x+=BIG_FONT_BOLD_SIZE;
		OLEDwriteSpace4linesBOLDNEG(x, y);
		x+=BIG_FONT_BOLD_SPACE_SIZE;
	}
}

void OLEDwriteString8linesNEG(unsigned char x, unsigned char y, char* string)
{
	while(*string)
	{
		OLEDwriteChar8linesNEG(x, y, *string++);
		x+=MEGA_FONT_SIZE;
		OLEDwriteSpace8linesNEG(x, y);
		x+=MEGA_FONT_SPACE_SIZE;
	}
}

void OLEDwriteString8linesBOLDNEG(unsigned char x, unsigned char y, char* string)
{
	while(*string)
	{
		OLEDwriteChar8linesBOLDNEG(x, y, *string++);
		x+=MEGA_FONT_BOLD_SIZE;
		OLEDwriteSpace8linesBOLDNEG(x, y);
		x+=MEGA_FONT_BOLD_SPACE_SIZE;
	}
}

//////////////////////////////////////////////////////////////////////////
void OLEDwriteString1linePGMNEG(unsigned char x, unsigned char y, const char* string)
{
	while(pgm_read_byte(string))
	{
		OLEDwriteChar1lineNEG(x, y, pgm_read_byte(string++));
		x+=MICRO_FONT_SIZE;
		OLEDwriteSpace1lineNEG(x, y);
		x+=MICRO_FONT_SPACE_SIZE;
	}
}

void OLEDwriteString2linesPGMNEG(unsigned char x, unsigned char y, const char* string)
{
	while(pgm_read_byte(string))
	{
		OLEDwriteChar2linesNEG(x, y, pgm_read_byte(string++));
		x+=NORMAL_FONT_SIZE;
		OLEDwriteSpace2linesNEG(x, y);
		x+=NORMAL_FONT_SPACE_SIZE;
	}
}

void OLEDwriteString2linesBOLDPGMNEG(unsigned char x, unsigned char y, const char* string)
{
	while(pgm_read_byte(string))
	{
		OLEDwriteChar2linesBOLDNEG(x, y, pgm_read_byte(string++));
		x+=NORMAL_FONT_BOLD_SIZE;
		OLEDwriteSpace2linesBOLDNEG(x, y);
		x+=NORMAL_FONT_BOLD_SPACE_SIZE;
	}
}

void OLEDwriteString4linesPGMNEG(unsigned char x, unsigned char y, const char* string)
{
	while(pgm_read_byte(string))
	{
		OLEDwriteChar4linesNEG(x, y, pgm_read_byte(string++));
		x+=BIG_FONT_SIZE;
		OLEDwriteSpace4linesNEG(x, y);
		x+=BIG_FONT_SPACE_SIZE;
	}
}

void OLEDwriteString4linesBOLDPGMNEG(unsigned char x, unsigned char y, const char* string)
{
	while(pgm_read_byte(string))
	{
		OLEDwriteChar4linesBOLDNEG(x, y, pgm_read_byte(string++));
		x+=BIG_FONT_BOLD_SIZE;
		OLEDwriteSpace4linesBOLDNEG(x, y);
		x+=BIG_FONT_BOLD_SPACE_SIZE;
	}
}

void OLEDwriteString8linesPGMNEG(unsigned char x, unsigned char y, const char* string)
{
	while(pgm_read_byte(string))
	{
		OLEDwriteChar8linesNEG(x, y, pgm_read_byte(string++));
		x+=MEGA_FONT_SIZE;
		OLEDwriteSpace8linesNEG(x, y);
		x+=MEGA_FONT_SPACE_SIZE;
	}
}

void OLEDwriteString8linesBOLDPGMNEG(unsigned char x, unsigned char y, const char* string)
{
	while(pgm_read_byte(string))
	{
		OLEDwriteChar8linesBOLDNEG(x, y, pgm_read_byte(string++));
		x+=MEGA_FONT_BOLD_SIZE;
		OLEDwriteSpace8linesBOLDNEG(x, y);
		x+=MEGA_FONT_BOLD_SPACE_SIZE;
	}
}
//////////////////////////////////////////////////////////////////////////




// -Wl,-u,vfprintf -lprintf_flt -lm --- Toolchain > Linker > Misc..
void OLEDprint(unsigned char x, unsigned char y, unsigned char font, char *retezec, ...)
{
	char buffer[40];
	int pocet_znaku=sizeof(buffer)/sizeof(buffer[0]);
	va_list pArgs;
	va_start(pArgs, retezec);
	vsnprintf(buffer, pocet_znaku - 1, retezec, pArgs);
	va_end(pArgs);
	
	switch(font)
	{
		case FONT_MICRO: OLEDwriteString1line(x, y, buffer);break;
		case FONT_NORMAL: OLEDwriteString2lines(x, y, buffer);break;
		/*case FONT_NORMAL_BOLD: OLEDwriteString2linesBOLD(x, y, buffer);break;
		case FONT_BIG: OLEDwriteString4lines(x, y, buffer);break;
		case FONT_BIG_BOLD: OLEDwriteString4linesBOLD(x, y, buffer);break;
		case FONT_MEGA: OLEDwriteString8lines(x, y, buffer);break;
		case FONT_MEGA_BOLD: OLEDwriteString8linesBOLD(x, y, buffer);break;
		
		case FONT_MICRO_NEG: OLEDwriteString1lineNEG(x, y, buffer);break;
		case FONT_NORMAL_NEG: OLEDwriteString2linesNEG(x, y, buffer);break;
		case FONT_NORMAL_BOLD_NEG: OLEDwriteString2linesBOLDNEG(x, y, buffer);break;
		case FONT_BIG_NEG: OLEDwriteString4linesNEG(x, y, buffer);break;
		case FONT_BIG_BOLD_NEG: OLEDwriteString4linesBOLDNEG(x, y, buffer);break;
		case FONT_MEGA_NEG: OLEDwriteString8linesNEG(x, y, buffer);break;
		case FONT_MEGA_BOLD_NEG: OLEDwriteString8linesBOLDNEG(x, y, buffer);break;*/
	}
}

void OLEDprintText(unsigned char x, unsigned char y, unsigned char font, const char *string)
{
	switch(font)
	{
		case FONT_MICRO: OLEDwriteString1linePGM(x, y, string);break;
		case FONT_NORMAL: OLEDwriteString2linesPGM(x, y, string);break;
		/*case FONT_NORMAL_BOLD: OLEDwriteString2linesBOLDPGM(x, y, string);break;
		case FONT_BIG: OLEDwriteString4linesPGM(x, y, string);break;
		case FONT_BIG_BOLD: OLEDwriteString4linesBOLDPGM(x, y, string);break;
		case FONT_MEGA: OLEDwriteString8linesPGM(x, y, string);break;
		case FONT_MEGA_BOLD: OLEDwriteString8linesBOLDPGM(x, y, string);break;
		
		case FONT_MICRO_NEG: OLEDwriteString1linePGMNEG(x, y, string);break;
		case FONT_NORMAL_NEG: OLEDwriteString2linesPGMNEG(x, y, string);break;
		case FONT_NORMAL_BOLD_NEG: OLEDwriteString2linesBOLDPGMNEG(x, y, string);break;
		case FONT_BIG_NEG: OLEDwriteString4linesPGMNEG(x, y, string);break;
		case FONT_BIG_BOLD_NEG: OLEDwriteString4linesBOLDPGMNEG(x, y, string);break;
		case FONT_MEGA_NEG: OLEDwriteString8linesPGMNEG(x, y, string);break;
		case FONT_MEGA_BOLD_NEG: OLEDwriteString8linesBOLDPGMNEG(x, y, string);break;*/
	}
}
//////////////////////////////////////////////////////////////////////////



const unsigned char font[82][16] PROGMEM = 
{
//' '//+32
{0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},

//'!'
{0b00000000, 0b00000000, 0b11111111, 0b11111111, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01100111, 0b01100111, 0b00000000, 0b00000000, 0b00000000, 0b00000000},

//' " ' -˙zkÈ
{0b00000000, 0b00001111, 0b00001111, 0b00000000, 0b00001111, 0b00001111, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},

//'#'
{0b00110000, 0b11111110, 0b11111110, 0b00110000, 0b00110000, 0b11111110, 0b11111110, 0b00110000, 0b00001100, 0b01111111, 0b01111111, 0b00001100, 0b00001100, 0b01111111, 0b01111111, 0b00001100},

//'$'
{0b00111000, 0b01000100, 0b11111110, 0b10000100, 0b11111110, 0b00000100, 0b00001000, 0b00000000, 0b00010000, 0b00100000, 0b01111111, 0b00100000, 0b01111111, 0b00100001, 0b00011110, 0b00000000},

//'%'
{0b00001100, 0b00010010, 0b00010010, 0b10001100, 0b11100000, 0b01111000, 0b00011110, 0b00000110, 0b01100000, 0b01111000, 0b00011110, 0b00000111, 0b00110001, 0b01001000, 0b01001000, 0b00110000},

//'&'
{0b00111110, 0b11100011, 0b11000001, 0b11000001, 0b11100011, 0b00111110, 0b00000000, 0b00000000, 0b00111111, 0b01100001, 0b01000000, 0b01000000, 0b01100001, 0b00111111, 0b00101000, 0b01000100},

//''' apostrof
{0b00000000, 0b00000000, 0b00000000, 0b00001111, 0b00001111, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},

//'('
{0b11100000, 0b11111000, 0b00011100, 0b00000110, 0b00000011, 0b00000001, 0b00000000, 0b00000000, 0b00000011, 0b00001111, 0b00011100, 0b00110000, 0b01100000, 0b01000000, 0b00000000, 0b00000000},

//')'
{0b00000001, 0b00000011, 0b00000110, 0b00011100, 0b11111000, 0b11100000, 0b00000000, 0b00000000, 0b01000000, 0b01100000, 0b00110000, 0b00011100, 0b00001111, 0b00000011, 0b00000000, 0b00000000},

//'*'
{0b10000110, 0b11001100, 0b01111000, 0b11111111, 0b11111111, 0b01111000, 0b11001100, 0b10000110, 0b00000001, 0b00000000, 0b00000000, 0b00000011, 0b00000011, 0b00000000, 0b00000000, 0b00000001},

//'+'
{0b00000000, 0b10000000, 0b10000000, 0b11100000, 0b11100000, 0b10000000, 0b10000000, 0b00000000, 0b00000000, 0b00000001, 0b00000001, 0b00000111, 0b00000111, 0b00000001, 0b00000001, 0000000000},

//','
{0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01011000, 0b00111000, 0b00000000, 0b00000000, 0b00000000},

//'-'
{0b00000000, 0b10000000, 0b10000000, 0b10000000, 0b10000000, 0b10000000, 0b10000000, 0b00000000, 0b00000000, 0b00000001, 0b00000001, 0b00000001, 0b00000001, 0b00000001, 0b00000001, 0b00000000},

//'.'
{0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01100000, 0b01100000, 0b00000000, 0b00000000, 0b00000000},

//'/'
{0b00000000, 0b00000000, 0b00000000, 0b10000000, 0b11100000, 0b01111000, 0b00011110, 0b00000110, 0b01100000, 0b01111000, 0b00011110, 0b00000111, 0b00000001, 0b00000000, 0b00000000, 0b00000000},

//'0'
{0b11111100, 0b11111110, 0b00000111, 0b10000011, 0b11000011, 0b01100111, 0b11111110, 0b11111100, 0b00011111, 0b00111111, 0b01110011, 0b01100001, 0b01100000, 0b01110000, 0b00111111, 0b00011111},

//'1'
{0b00000000, 0b00110000, 0b00111000, 0b00011100, 0b00001110, 0b11111111, 0b11111111, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01111111, 0b01111111, 0b00000000},

//'2'
{0b00001100, 0b00001110, 0b00000111, 0b00000011, 0b10000011, 0b11000111, 0b11111110, 0b01111100, 0b01111000, 0b01111100, 0b01101110, 0b01100111, 0b01100011, 0b01100001, 0b01100000, 0b01100000},

//'3'
{0b00001100, 0b00001110, 0b00000111, 0b11000011, 0b11000011, 0b11100111, 0b01111110, 0b00111100, 0b00011000, 0b00111000, 0b01110000, 0b01100001, 0b01100001, 0b01110011, 0b00111111, 0b00011100},

//'4'
{0b11111111, 0b11111111, 0b00000000, 0b00000000, 0b11100000, 0b11100000, 0b00000000, 0b00000000, 0b00001111, 0b00001111, 0b00001100, 0b00001100, 0b01111111, 0b01111111, 0b00001100, 0b00001100},

//'5'
{0b11111111, 0b11111111, 0b01100011, 0b01100011, 0b01100011, 0b01100011, 0b11100011, 0b11000011, 0b00110000, 0b01110000, 0b01100000, 0b01100000, 0b01100000, 0b01100000, 0b01111111, 0b00111111},

//'6'
{0b11110000, 0b11111000, 0b00011100, 0b10001110, 0b10000111, 0b10000011, 0b00000000, 0b00000000, 0b00011111, 0b00111111, 0b01110011, 0b01100001, 0b01100001, 0b01110011, 0b00111111, 0b00011110},

//'7'
{0b00001111, 0b00001111, 0b00000011, 0b00000011, 0b00000011, 0b11100011, 0b11111111, 0b00011111, 0b00000000, 0b00000000, 0b00000000, 0b01111000, 0b01111111, 0b00000111, 0b00000000, 0b00000000},

//'8'
{0b00111100, 0b01111110, 0b11100111, 0b11000011, 0b11000011, 0b11100111, 0b01111110, 0b00111100, 0b00011110, 0b00111111, 0b01110011, 0b01100001, 0b01100001, 0b01110011, 0b00111111, 0b00011110},

//'9'
{0b00111100, 0b01111110, 0b11100111, 0b11000011, 0b11000011, 0b01100111, 0b11111110, 0b11111100, 0b00000000, 0b00000000, 0b01100000, 0b01110000, 0b00111000, 0b00011100, 0b00001111, 0b00000111},

//':'
{0b00000000, 0b00000000, 0b00000000, 0b01100000, 0b01100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000110, 0b00000110, 0b00000000, 0b00000000, 0b00000000},

//';'
{0b00000000, 0b00000000, 0b00000000, 0b10000000, 0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01011001, 0b00111001, 0b00000000, 0b00000000, 0b00000000},

//'<'
{0b10000000, 0b11000000, 0b01100000, 0b00110000, 0b00011000, 0b00001000, 0b00000000, 0b00000000, 0b00000001, 0b00000011, 0b00000110, 0b00001100, 0b00011000, 0b00010000, 0b00000000, 0b00000000},

//'='
{0b11000000, 0b11000000, 0b11000000, 0b11000000, 0b11000000, 0b11000000, 0b11000000, 0b11000000, 0b00000110, 0b00000110, 0b00000110, 0b00000110, 0b00000110, 0b00000110, 0b00000110, 0b00000110},

//'>'
{0b00001000, 0b00011000, 0b00110000, 0b01100000, 0b11000000, 0b10000000, 0b00000000, 0b00000000, 0b00010000, 0b00011000, 0b00001100, 0b00000110, 0b00000011, 0b00000001, 0b00000000, 0b00000000},

//'?'
{0b00011100, 0b00011110, 0b00000111, 0b00000011, 0b10000011, 0b11000111, 0b11111110, 0b01111100, 0b00000000, 0b00000000, 0b00000000, 0b01100111, 0b01100111, 0b00000001, 0b00000000, 0b00000000},

//'@'
{0b11111000, 0b00001100, 0b11000100, 0b00100100, 0b00100100, 0b11100100, 0b00001100, 0b11111000, 0b00001111, 0b00011000, 0b00010011, 0b00010010, 0b00010010, 0b00010001, 0b00011010, 0b00001011},

//**************************************************
//**************************************************

//'A'
{0b11110000, 0b11111100, 0b00011110, 0b00000111, 0b00000111, 0b00011110, 0b11111100, 0b11110000, 0b01111111, 0b01111111, 0b00000011, 0b00000011, 0b00000011, 0b00000011, 0b01111111, 0b01111111},

//'B'
{0b11111111, 0b11111111, 0b11000011, 0b11000011, 0b11000011, 0b11100111, 0b01111110, 0b00111100, 0b01111111, 0b01111111, 0b01100000, 0b01100000, 0b01100000, 0b01110001, 0b00111111, 0b00011110},

//'C'
{0b11111100, 0b11111110, 0b00000111, 0b00000011, 0b00000011, 0b00000011, 0b00000111, 0b00000110, 0b00011111, 0b00111111, 0b01110000, 0b01100000, 0b01100000, 0b01100000, 0b01110000, 0b00110000},

//'D'
{0b11111111, 0b11111111, 0b00000011, 0b00000011, 0b00000011, 0b00000110, 0b11111110, 0b11111000, 0b01111111, 0b01111111, 0b01100000, 0b01100000, 0b01100000, 0b00110000, 0b00111111, 0b00001111},

//'E'
{0b11111111, 0b11111111, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b01111111, 0b01111111, 0b01100000, 0b01100000, 0b01100000, 0b01100000, 0b01100000, 0b01100000},

//'F'
{0b11111111, 0b11111111, 0b11000011, 0b11000011, 0b11000011, 0b11000011, 0b00000011, 0b00000011, 0b01111111, 0b01111111, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},

//'G'
{0b11111100, 0b11111110, 0b00000111, 0b10000011, 0b10000011, 0b10000111, 0b10001110, 0b10001100, 0b00011111, 0b00111111, 0b01110000, 0b01100001, 0b01100001, 0b01110001, 0b00111111, 0b00011111},

//'H'
{0b11111111, 0b11111111, 0b11000000, 0b11000000, 0b11000000, 0b11000000, 0b11111111, 0b11111111, 0b01111111, 0b01111111, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01111111, 0b01111111},

//'I'
{0b00000011, 0b00000011, 0b00000011, 0b11111111, 0b11111111, 0b00000011, 0b00000011, 0b00000011, 0b01100000, 0b01100000, 0b01100000, 0b01111111, 0b01111111, 0b01100000, 0b01100000, 0b01100000},

//'J'
{0b00000011, 0b00000011, 0b00000011, 0b00000011, 0b00000011, 0b00000011, 0b11111111, 0b11111111, 0b00011100, 0b00111100, 0b01110000, 0b01100000, 0b01100000, 0b01110000, 0b00111111, 0b00011111},

//'K'
{0b11111111, 0b11111111, 0b11100000, 0b01110000, 0b00111000, 0b00011100, 0b00001110, 0b00000111, 0b01111111, 0b01111111, 0b00000011, 0b00000111, 0b00001110, 0b00011100, 0b00111000, 0b01110000},

//'L'
{0b11111111, 0b11111111, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01111111, 0b01111111, 0b01100000, 0b01100000, 0b01100000, 0b01100000, 0b01100000, 0b01100000},

//'M'
{0b11111111, 0b11111111, 0b00001110, 0b00111100, 0b00111100, 0b00001110, 0b11111111, 0b11111111, 0b01111111, 0b01111111, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01111111, 0b01111111},

//'N'
{0b11111111, 0b11111111, 0b00111100, 0b11111000, 0b11100000, 0b00000000, 0b11111111, 0b11111111, 0b01111111, 0b01111111, 0b00000000, 0b00000111, 0b00011111, 0b01111100, 0b01111111, 0b01111111},

//'O'
{0b11111110, 0b11111111, 0b00000111, 0b00000011, 0b00000011, 0b00000111, 0b11111111, 0b11111110, 0b00111111, 0b01111111, 0b01110000, 0b01100000, 0b01100000, 0b01110000, 0b01111111, 0b00111111},

//'P'
{0b11111111, 0b11111111, 0b11000011, 0b11000011, 0b11000011, 0b11100111, 0b01111110, 0b00111100, 0b01111111, 0b01111111, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},

//'Q'
{0b11111100, 0b11111110, 0b00000111, 0b00000011, 0b00000011, 0b00000111, 0b11111110, 0b11111100, 0b00011111, 0b00111111, 0b01110000, 0b01100110, 0b01111110, 0b01111000, 0b00111111, 0b01011111},

//'R'
{0b11111111, 0b11111111, 0b11000011, 0b11000011, 0b11000011, 0b11100111, 0b01111110, 0b00111100, 0b01111111, 0b01111111, 0b00000000, 0b00000011, 0b00001111, 0b00111110, 0b01111000, 0b01100000},

//'S'
{0b00111100, 0b01111110, 0b11100111, 0b11000011, 0b11000011, 0b10000111, 0b00001110, 0b00001100, 0b00011000, 0b00111000, 0b01110000, 0b01100000, 0b01100001, 0b01110011, 0b00111111, 0b00011110},

//'T'
{0b00000011, 0b00000011, 0b00000011, 0b11111111, 0b11111111, 0b00000011, 0b00000011, 0b00000011, 0b00000000, 0b00000000, 0b00000000, 0b01111111, 0b01111111, 0b00000000, 0b00000000, 0b00000000},

//'U'
{0b11111111, 0b11111111, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b11111111, 0b11111111, 0b00111111, 0b01111111, 0b01110000, 0b01100000, 0b01100000, 0b01110000, 0b01111111, 0b00111111},

//'V'
{0b11111111, 0b11111111, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b11111111, 0b11111111, 0b00000001, 0b00001111, 0b00011111, 0b01111000, 0b01111000, 0b00011111, 0b00001111, 0b00000001},

//'W'
{0b11111111, 0b11111111, 0b00000000, 0b11111111, 0b11111111, 0b00000000, 0b11111111, 0b11111111, 0b00011111, 0b01111111, 0b00111000, 0b00011111, 0b00011111, 0b00111000, 0b01111111, 0b00011111},

//'X'
{0b00000111, 0b00011111, 0b01111100, 0b11100000, 0b11100000, 0b01111100, 0b00011111, 0b00000111, 0b01110000, 0b01111100, 0b00011111, 0b00000011, 0b00000011, 0b00011111, 0b01111100, 0b01110000},

//'Y'
{0b00000111, 0b00011111, 0b01111100, 0b11110000, 0b11110000, 0b01111100, 0b00011111, 0b00000111, 0b00000000, 0b00000000, 0b00000000, 0b01111111, 0b01111111, 0b00000000, 0b00000000, 0b00000000},

//'Z'
{0b00000011, 0b00000011, 0b00000011, 0b11000011, 0b11100011, 0b01111011, 0b00011111, 0b00000111, 0b01110000, 0b01111100, 0b01101111, 0b01100011, 0b01100000, 0b01100000, 0b01100000, 0b01100000},
//90 hodnota 'Z' v ASCII
//////////////////////////////////////////////////////////////////////////
//'¡' odpovÌd· '[' v ASCII
{0b11000000, 0b11100000, 0b01110000, 0b00110000, 0b00110100, 0b01110010, 0b11100001, 0b11000000, 0b01111111, 0b01111111, 0b00001100, 0b00001100, 0b00001100, 0b00001100, 0b01111111, 0b01111111}, 

//'»' odpovÌd· '\' v ASCII
{0b00000000, 0b11000001, 0b11100010, 0b01110100, 0b00110100, 0b00110010, 0b00110001, 0b00000000, 0b00000000, 0b00011111, 0b00111111, 0b01110000, 0b01100000, 0b01100000, 0b01100000, 0b00000000}, 

//'œ' odpovÌd· ']' v ASCII
{0b00000000, 0b11110001, 0b11110010, 0b00110100, 0b00110100, 0b01100010, 0b11100001, 0b10000000, 0b00000000, 0b01111111, 0b01111111, 0b01100000, 0b01100000, 0b00110000, 0b00111111, 0b00001111}, 

//'…' odpovÌd· '^' v ASCII
{0b00000000, 0b11110000, 0b11110000, 0b00110000, 0b00110100, 0b00110010, 0b00110001, 0b00110000, 0b00000000, 0b01111111, 0b01111111, 0b01100011, 0b01100011, 0b01100011, 0b01100011, 0b01100011}, 

//'Ã' odpovÌd· '_' v ASCII
{0b00000000, 0b11110001, 0b11110010, 0b00110100, 0b00110100, 0b00110010, 0b00110001, 0b00110000, 0b00000000, 0b01111111, 0b01111111, 0b01100011, 0b01100011, 0b01100011, 0b01100011, 0b01100011}, 

//'Õ' odpovÌd· '`' v ASCII
{0b00000000, 0b00110000, 0b00110000, 0b11110000, 0b11110100, 0b00110010, 0b00110001, 0b00000000, 0b00000000, 0b01100000, 0b01100000, 0b01111111, 0b01111111, 0b01100000, 0b01100000, 0b00000000}, 

//'“' odpovÌd· 'a' v ASCII
{0b11110000, 0b11110001, 0b01100010, 0b11100100, 0b00000100, 0b00000010, 0b11110001, 0b11110000, 0b01111111, 0b01111111, 0b00000000, 0b00000011, 0b00111110, 0b00110000, 0b01111111, 0b01111111}, 

//'”' odpovÌd· 'b' v ASCII
{0b11000000, 0b11100000, 0b01110000, 0b00110000, 0b00110100, 0b01110010, 0b11100001, 0b11000000, 0b00011111, 0b00111111, 0b01110000, 0b01100000, 0b01100000, 0b01110000, 0b00111111, 0b00011111}, 

//'ÿ' odpovÌd· 'c' v ASCII
{0b00000000, 0b11110001, 0b11110010, 0b00110100, 0b00110100, 0b00110010, 0b11110001, 0b11000000, 0b00000000, 0b01111111, 0b01111111, 0b00000110, 0b00001110, 0b00011110, 0b01110111, 0b01100001},

//'ä' odpovÌd· 'd' v ASCII
{0b11000000, 0b11100001, 0b11110010, 0b00110100, 0b00110100, 0b00110010, 0b01110001, 0b01100000, 0b00110000, 0b01110001, 0b01100011, 0b01100111, 0b01100111, 0b01111110, 0b00111100, 0b00011000},

//'ç' odpovÌd· 'e' v ASCII
{0b00110000, 0b00110001, 0b00110010, 0b11110100, 0b11110100, 0b00110010, 0b00110001, 0b00110000, 0b00000000, 0b00000000, 0b00000000, 0b01111111, 0b01111111, 0b00000000, 0b00000000, 0b00000000},

//'⁄' odpovÌd· 'f' v ASCII
{0b11110000, 0b11110000, 0b00000000, 0b00000000, 0b00000100, 0b00000010, 0b11110001, 0b11110000, 0b00111111, 0b00111111, 0b01110000, 0b01100000, 0b01100000, 0b01110000, 0b00111111, 0b00111111},

//'Ÿ' odpovÌd· 'g' v ASCII
{0b11110000, 0b11110000, 0b00000111, 0b00000101, 0b00000101, 0b00000111, 0b11110000, 0b11110000, 0b00111111, 0b00111111, 0b01110000, 0b01100000, 0b01100000, 0b01110000, 0b00111111, 0b00111111},

//'›' odpovÌd· 'h' v ASCII
{0b00110000, 0b11110000, 0b11000000, 0b00000000, 0b00000100, 0b11000010, 0b11110001, 0b00110000, 0b00000000, 0b00000000, 0b00000011, 0b01111111, 0b01111111, 0b00000011, 0b00000000, 0b00000000},

//'é' odpovÌd· 'i' v ASCII
{0b00110000, 0b00110001, 0b00110010, 0b00110100, 0b00110100, 0b10110010, 0b11110001, 0b01110000, 0b01110000, 0b01111000, 0b01101100, 0b01100110, 0b01100011, 0b01100001, 0b01100000, 0b01100000},

//////////////////////////////////////////////////////////////////////////

//'∞' odpovÌd· 'j' v ASCII
{0b00000000, 0b00011110, 0b00111111, 0b00110011, 0b00110011, 0b00111111, 0b00011110, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},

//0x0d <CR> odpovÌd· 'k' v ASCII
{0b01111100, 0b01000100, 0b01001100, 0b01111000, 0b01111000, 0b01001100, 0b01000100, 0b01000100, 0b00111100, 0b01100000, 0b01000000, 0b01000000, 0b01000000, 0b01000000, 0b01100000, 0b00111100},

//0x0a <LF> odpovÌd· 'l' v ASCII
{0b01111100, 0b01000000, 0b01000000, 0b01111000, 0b01000000, 0b01000000, 0b01000000, 0b01000000, 0b01000000, 0b01000000, 0b01000000, 0b01000000, 0b01000000, 0b01000000, 0b01000000, 0b01111100},

//'|' odpovÌd· 'm' v ASCII
{0b00000000, 0b00000000, 0b00000000, 0b11111111, 0b11111111, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01111111, 0b01111111, 0b00000000, 0b00000000, 0b00000000},

//baterie pln· odpovÌd· 'n' v ASCII
{0b11111100, 0b11111100, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111100, 0b11111100, 0b01111111, 0b01111111, 0b01111111, 0b01111111, 0b01111111, 0b01111111, 0b01111111, 0b01111111},

//baterie p˘lka odpovÌd· 'o' v ASCII
{0b11111100, 0b11111100, 0b00001111, 0b00000011, 0b00000011, 0b10001111, 0b11111100, 0b11111100, 0b01111111, 0b01111111, 0b01111100, 0b01111110, 0b01111111, 0b01111111, 0b01111111, 0b01111111},

//baterie pr·zdn· odpovÌd· 'p' v ASCII
{0b11111100, 0b11111100, 0b00001111, 0b00000011, 0b00000011, 0b00001111, 0b11111100, 0b11111100, 0b01111111, 0b01111111, 0b01100000, 0b01100000, 0b01100000, 0b01100000, 0b01111111, 0b01111111}
};



const unsigned char microFont[67][3] PROGMEM =
{
	{0x00,0x00,0x00}, // Space
	{0x00,0x5C,0x00}, // !
	{0x0C,0x00,0x0C}, // "
	{0x7C,0x28,0x7C}, // #
	{0x5C,0xD6,0x74}, // $
	{0x24,0x10,0x48}, // %
	{0x28,0x54,0x08}, // &
	{0x00,0x0C,0x00}, // '
	{0x38,0x44,0x00}, // (
	{0x44,0x38,0x00}, // )
	{0x28,0x1C,0x28}, // *
	{0x10,0x38,0x10}, // +
	{0x80,0x40,0x00}, // ,
	{0x10,0x10,0x10}, // -
	{0x00,0x40,0x00}, // .
	{0x60,0x18,0x04}, // /
	{0x38,0x44,0x38}, // 0
	{0x48,0x7C,0x40}, // 1
	{0x64,0x54,0x48}, // 2
	{0x44,0x54,0x28}, // 3
	{0x1C,0x10,0x7C}, // 4
	{0x5C,0x54,0x24}, // 5
	{0x7C,0x54,0x74}, // 6
	{0x04,0x74,0x0C}, // 7
	{0x7C,0x54,0x7C}, // 8
	{0x5C,0x54,0x7C}, // 9
	{0x00,0x28,0x00}, // :
	{0x40,0x28,0x00}, // ;
	{0x10,0x28,0x44}, // <
	{0x28,0x28,0x28}, // =
	{0x44,0x28,0x10}, // >
	{0x04,0x54,0x08}, // ?
	{0x38,0x4C,0x5C}, // @
	{0x78,0x14,0x78}, // A
	{0x7C,0x54,0x28}, // B
	{0x38,0x44,0x44}, // C
	{0x7C,0x44,0x38}, // D
	{0x7C,0x54,0x44}, // E
	{0x7C,0x14,0x04}, // F
	{0x38,0x44,0x34}, // G
	{0x7C,0x10,0x7C}, // H
	{0x44,0x7C,0x44}, // I
	{0x20,0x40,0x3C}, // J
	{0x7C,0x10,0x6C}, // K
	{0x7C,0x40,0x40}, // L
	{0x7C,0x08,0x7C}, // M
	{0x7C,0x04,0x7C}, // N
	{0x7C,0x44,0x7C}, // O
	{0x7C,0x14,0x08}, // P
	{0x38,0x44,0x78}, // Q
	{0x7C,0x14,0x68}, // R
	{0x48,0x54,0x24}, // S
	{0x04,0x7C,0x04}, // T
	{0x7C,0x40,0x7C}, // U
	{0x3C,0x40,0x3C}, // V
	{0x7C,0x20,0x7C}, // W
	{0x6C,0x10,0x6C}, // X
	{0x1C,0x70,0x1C}, // Y
	{0x64,0x54,0x4C}, // Z
	{0x7C,0x44,0x00}, // [
	{0x06,0x18,0x60}, //*\*
	{0x00,0x44,0x7C}, // ]
	{0x08,0x04,0x08}, // ^
	{0x80,0x80,0x80}, // _
	{0x04,0x08,0x00}, // `
	{0x04,0x0A,0x04}, // ∞
	{0x00,0xFF,0x00}  // |
};






//////////////////////////////////////////////////////////////////////////


unsigned char const picture[8][128] PROGMEM = {

#ifdef LOGO_TIPA
//Obr·zek na celou obrazovku 64x128 px
//logo TIPA
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x80,0xC0,0x60,0x30,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
	0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0xF8,0xFC,0xFE,0x1F,0x0F,0x07,
	0x07,0x07,0x07,0x07,0x07,0x0F,0x1F,0xFE,0xFC,0xF8,0x10,0x10,0x10,0x10,0x10,0x10,
	0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
	0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
	0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
	0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
	0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x30,0x60,0xC0,0x80,0x00,0x00,
	0xFF,0x01,0x00,0x00,0x00,0x00,0xF0,0xF8,0xFC,0x9E,0x0E,0x07,0x07,0x07,0x07,0x07,
	0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x07,0x07,0x67,0xF7,0xFF,0x9F,0x0F,0x0F,
	0x9F,0xFF,0xF7,0x67,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,
	0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,
	0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,
	0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,
	0x0E,0x9E,0xFC,0xF8,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xFF,0x00,
	0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x07,0x0E,0x0E,0x0E,0x0E,0x0E,
	0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0xFE,0xFE,0xFE,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0xFE,0xFE,0x7E,0x3E,0x1F,0x0F,0x0F,0x0F,
	0x0F,0x1F,0x3E,0x7E,0xFE,0xEE,0xCE,0xEE,0xFE,0xFE,0x7E,0x3E,0x1E,0x1E,0x1E,0x0E,
	0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x1E,0x1E,0x1E,0x3E,
	0x7E,0xFE,0xEE,0x8E,0x8E,0xCE,0xEE,0xEE,0x7E,0x3E,0x1E,0x1E,0x1E,0x0E,0x0E,0x0E,
	0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x0E,0x1E,0x3E,0x7E,
	0xF7,0xE7,0xC3,0x81,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,
	0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0xF8,0x7C,0xFE,0xFE,0xFE,0xFE,0xFE,0x7C,0x38,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x83,0xFF,0xFF,0xFF,0x83,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,
	0x7C,0xFE,0xFE,0xFE,0xFE,0xFE,0x7C,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x03,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,
	0x7F,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x3F,0x7F,0xF8,0xF0,0xE0,
	0xE0,0xE0,0xE0,0xE0,0xE0,0xF0,0xF8,0x7F,0x3F,0x3F,0x78,0xF0,0xE0,0xE0,0xE0,0xE0,
	0xE0,0xE0,0x70,0x78,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0xFF,0xF0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0x70,0x70,0x70,0x38,0x38,0x38,0x3C,
	0x1E,0x1F,0x0F,0x07,0x07,0x07,0x0F,0x0F,0x1E,0x3C,0x78,0x70,0xF0,0xE0,0xE0,0xE0,
	0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xF0,0xFF,0x38,0x70,0xE0,0xE0,0xE0,0xE0,0xE0,0xF0,
	0xF8,0x7C,0x3F,0x1F,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0x7F,0x00,
	0x00,0x00,0x01,0x03,0x06,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
	0x04,0x04,0x04,0x04,0x1F,0x3F,0x7F,0xF8,0xF0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,
	0xF0,0x7F,0x3F,0x1F,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x06,0x03,0x01,0x00,0x00,0x00
#endif
	
	
#ifdef LOGO_SPSEI
//Obr·zek na celou obrazovku 64x128 px
//logo SPäei Ostrava
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xF8,0x1C,0x0E,0x07,0x03,
	0x03,0x03,0x03,0x07,0x0E,0x1C,0xF8,0xF0,0x00,0x00,0xE0,0xF0,0x30,0x30,0x30,0x30,
	0x70,0x60,0x00,0x00,0x30,0x30,0xFF,0xFF,0x30,0x30,0x00,0xF0,0xF0,0xE0,0x70,0x30,
	0x30,0x00,0x60,0x60,0x70,0x30,0x30,0x30,0x30,0xF0,0xF0,0xE0,0x00,0x30,0xF0,0xF0,
	0xC0,0x00,0x00,0x00,0xC0,0xF0,0xF0,0x30,0x00,0x60,0x60,0x70,0x30,0x30,0x30,0x30,
	0xF0,0xF0,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x0F,0x1C,0x38,0x70,0x60,
	0x60,0x60,0x60,0x70,0x38,0x1C,0x0F,0x07,0x00,0x00,0x31,0x73,0x63,0x63,0x67,0x67,
	0x7E,0x3C,0x00,0x00,0x00,0x00,0x7F,0x7F,0x60,0x60,0x00,0x7F,0x7F,0x00,0x00,0x00,
	0x00,0x00,0x3C,0x7E,0x6E,0x66,0x66,0x63,0x73,0x3F,0x7F,0x7F,0x00,0x00,0x00,0x03,
	0x1F,0x7E,0x78,0x7E,0x1F,0x03,0x00,0x00,0x00,0x3C,0x7E,0x6E,0x66,0x66,0x63,0x73,
	0x3F,0x7F,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x08,0x18,0x38,0x78,0xF0,0xE0,0xE0,0x70,0x78,0x38,0x18,0x08,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0xC0,0xC0,0xE0,0xF0,
	0xF0,0xF8,0xF8,0xF8,0xFC,0x7C,0x7E,0x3E,0x3E,0x1F,0x0F,0x0F,0x0F,0x0F,0x07,0x07,
	0x07,0x03,0x03,0x03,0x03,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE7,0xCF,
	0x9F,0x3F,0x7F,0xFE,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0xC0,0xF0,0xF8,0xF8,0xFC,0x3C,0x1C,0x1C,0x1C,0x1C,0x3C,0x3C,
	0xF8,0xF8,0xF0,0xE0,0x00,0x00,0x00,0x00,0xC0,0xFC,0xFC,0xFC,0xFC,0xF0,0x78,0x38,
	0x1C,0x1C,0x1C,0x3C,0x7C,0xFC,0xF8,0xF0,0xE0,0x80,0x00,0x00,0x00,0x00,0xC0,0xF0,
	0xF8,0xF8,0xFC,0x3C,0x1C,0x1C,0x1C,0x1C,0x3C,0x3C,0xF8,0xF8,0xF0,0xE0,0x00,0x00,
	0x00,0x00,0x00,0x00,0xC0,0xF0,0xF8,0xFC,0xFE,0xFF,0xFF,0xFF,0x7F,0x1F,0x0F,0x0F,
	0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFE,0xFC,0xF9,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x80,0x80,0x81,0x07,0x07,0x0F,0x0F,0x1F,0x1E,0x3E,0x3C,0x7C,0xF8,0xF8,
	0xF0,0xE0,0xC0,0x00,0x00,0x00,0x80,0xF8,0xFF,0xFF,0xFF,0x07,0x03,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x80,0xC0,0xFF,0xFF,0xFF,0x3F,0x00,0x00,0x80,0x80,0x81,0x07,
	0x07,0x0F,0x0F,0x1F,0x1E,0x3E,0x3C,0x7C,0xF8,0xF8,0xF0,0xE0,0xC0,0x00,0x00,0x00,
	0x00,0x00,0xF8,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x1F,0xC1,0xF0,0xF0,0xF0,0xF0,
	0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xE0,0xE0,0xE0,0xE0,0xE0,0x60,0x40,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0xFF,
	0xFF,0x3F,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x03,0x0F,0x1F,0x3E,0x7C,0x78,0x70,0x70,0x70,0x70,0x70,0x78,0x3C,0x3F,
	0x1F,0x0F,0x07,0x00,0x00,0xF0,0xFF,0xFF,0xFF,0x3F,0x1F,0x3C,0x38,0x70,0x70,0x70,
	0x70,0x78,0x3C,0x3E,0x1F,0x0F,0x07,0x03,0x00,0x00,0x00,0x00,0x03,0x0F,0x1F,0x3E,
	0x3C,0x78,0x70,0x70,0x70,0x70,0x70,0x78,0x3C,0x3F,0x1F,0x0F,0x07,0x00,0x00,0x00,
	0x00,0x00,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,0x00,0x01,0x01,0x01,0x01,0x01,
	0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xF0,0xFC,0xFF,0xFF,0xFF,0x7F,0x1F,0x07,
	0x00,0x00,0x03,0x0F,0x7F,0xFF,0xFC,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x7C,0x7F,0x7F,0x7F,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x0F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xF8,0xE0,0xC0,0x80,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xC0,
	0xE0,0xE0,0xF0,0xF8,0xFC,0xFE,0x7F,0x3F,0x1F,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x03,0x0F,0x3F,0x7F,0xFC,0xF0,0xE0,0xC0,0x80,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x03,0x07,0x0F,0x1F,0x1E,
	0x1C,0x18,0x00,0x00,0x18,0x18,0x1C,0x1C,0x1C,0x1E,0x1E,0x1F,0x0F,0x0F,0x0F,0x07,
	0x07,0x03,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x03,0x00,0x00
#endif
	
};