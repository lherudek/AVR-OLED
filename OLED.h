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
 
 
#ifndef		OLED_H
#define		OLED_H

#include <avr/pgmspace.h>

#define F_CPU	1000000UL

//pouze jedno mùže být odkomentováno - vybírá obrázek
#define LOGO_TIPA
//#define LOGO_SPSEI


#define FONT_NORMAL			0
#define FONT_NORMAL_BOLD	1
#define FONT_BIG			2
#define FONT_BIG_BOLD		3
#define FONT_MEGA			4
#define FONT_MEGA_BOLD		5
#define FONT_MICRO			6

#define FONT_NORMAL_NEG			7
#define FONT_NORMAL_BOLD_NEG	8
#define FONT_BIG_NEG			9
#define FONT_BIG_BOLD_NEG		10
#define FONT_MEGA_NEG			11
#define FONT_MEGA_BOLD_NEG		12
#define FONT_MICRO_NEG			13


//pixel size of space between chars
#define MICRO_FONT_SPACE_SIZE		1 
#define NORMAL_FONT_SPACE_SIZE		2 
#define NORMAL_FONT_BOLD_SPACE_SIZE	2
#define BIG_FONT_SPACE_SIZE			6
#define BIG_FONT_BOLD_SPACE_SIZE	1
#define MEGA_FONT_SPACE_SIZE		6
#define MEGA_FONT_BOLD_SPACE_SIZE	1
//pixel width size of chars
#define MICRO_FONT_SIZE			3
#define NORMAL_FONT_SIZE		8
#define NORMAL_FONT_BOLD_SIZE	16
#define BIG_FONT_SIZE			16
#define BIG_FONT_BOLD_SIZE		24
#define MEGA_FONT_SIZE			16
#define MEGA_FONT_BOLD_SIZE		24
//manually counted myself...
#define MICRO_FONT_CHARS_PER_LINE		32
#define NORMAL_FONT_CHARS_PER_LINE		13
#define NORMAL_FONT_BOLD_CHARS_PER_LINE	7
#define BIG_FONT_CHARS_PER_LINE			6
#define BIG_FONT_BOLD_CHARS_PER_LINE	5
#define MEGA_FONT_CHARS_PER_LINE		6
#define MEGA_FONT_BOLD_CHARS_PER_LINE	5


#define X_RESOLUTION	128
#define Y_RESOLUTION	64
#define RESOLUTION		(X_RESOLUTION*Y_RESOLUTION)

#define X_BYTE_RESOLUTION	128	//128 sloupcù
#define Y_BYTE_RESOLUTION	8	//8 øádkù
#define BYTE_RESOLUTION		(X_BYTE_RESOLUTION*Y_BYTE_RESOLUTION)//1024 bajtù na celý displej

#define START		0
#define X_START		0
#define Y_START		0
#define X_END		X_BYTE_RESOLUTION
#define Y_END		Y_BYTE_RESOLUTION

#define LINE0	0
#define LINE1	1
#define LINE2	2
#define LINE3	3
#define LINE4	4
#define LINE5	5
#define LINE6	6
#define LINE7	7
#define LINE_1	0
#define LINE_2	1
#define LINE_3	2
#define LINE_4	3
#define LINE_5	4
#define LINE_6	5
#define LINE_7	6
#define LINE_8	7
#define SMALL_LINE_1	0
#define SMALL_LINE_2	1
#define SMALL_LINE_3	2
#define SMALL_LINE_4	3
#define SMALL_LINE_5	4
#define SMALL_LINE_6	5
#define SMALL_LINE_7	6
#define SMALL_LINE_8	7
#define BIG_LINE_1		0
#define BIG_LINE_2		2
#define BIG_LINE_3		4
#define BIG_LINE_4		6

#define OLED_SET_COL_HI		0x10
#define OLED_SET_COL_LO		0x00
#define OLED_SET_LINE		0x40
#define OLED_SET_CONTRAST	0x81
#define OLED_SET_SEG_REMAP0 0xA0
#define OLED_SET_SEG_REMAP1	0xA1
#define OLED_EON_OFF		0xA4
#define OLED_EON_ON			0xA5
#define OLED_DISP_NOR		0xA6
#define OLED_DISP_REV		0xA7
#define OLED_MULTIPLEX      0xA8
#define OLED_CHARGE_PUMP    0x8D
#define OLED_PUMP_OFF    	0x10
#define OLED_PUMP_ON     	0x14
#define OLED_DISP_OFF 		0xAE
#define OLED_DISP_ON		0xAF
#define OLED_SET_PAGE		0xB0
#define OLED_SET_SCAN_FLIP	0xC0
#define OLED_SET_SCAN_NOR	0xC8
#define OLED_SET_OFFSET		0xD3
#define OLED_SET_RATIO_OSC	0xD5
#define OLED_SET_CHARGE  	0xD9
#define OLED_SET_PADS    	0xDA
#define OLED_SET_VCOM    	0xDB
#define OLED_NOP     		0xE3
#define OLED_SCROLL_RIGHT	0x26
#define OLED_SCROLL_LEFT	0x27
#define OLED_SCROLL_VR	    0x29
#define OLED_SCROLL_VL		0x2A
#define OLED_SCROLL_OFF		0x2E
#define OLED_SCROLL_ON   	0x2F
#define OLED_VERT_SCROLL_A  0xA3
#define OLED_MEM_ADDRESSING 0x20
#define OLED_SET_COL_ADDR	0x21
#define OLED_SET_PAGE_ADDR	0x22

#define OLED_DISPLAYALLON_RESUME	0xA4
#define OLED_DISPLAYALLON 			0xA5
#define OLED_NORMALDISPLAY			0xA6
#define OLED_INVERTDISPLAY 			0xA7
#define OLED_DISPLAYOFF				0xAE
#define OLED_DISPLAYON 				0xAF
#define OLED_SETDISPLAYOFFSET 		0xD3
#define OLED_SETCOMPINS 			0xDA
#define OLED_SETVCOMDETECT 			0xDB
#define OLED_SETDISPLAYCLOCKDIV 	0xD5
#define OLED_SETPRECHARGE 			0xD9
#define OLED_SETMULTIPLEX 			0xA8
#define OLED_SETLOWCOLUMN 			0x00
#define OLED_SETHIGHCOLUMN 			0x10
#define OLED_SETSTARTLINE 			0x40
#define OLED_MEMORYMODE 			0x20
#define OLED_COMSCANINC 			0xC0
#define OLED_COMSCANDEC 			0xC8
#define OLED_SEGREMAP 				0xA0
#define OLED_CHARGEPUMP 			0x8D
#define OLED_EXTERNALVCC 			0x01
#define OLED_SWITCHCAPVCC 			0x02


#define DC_data()		(PORTB|=(1<<PINB0))
#define DC_command()	(PORTB&=~(1<<PINB0))
#define setResetPin()	(PORTB|=(1<<PINB1))
#define clearResetPin()	(PORTB&=~(1<<PINB1))
#define CS_off()		(PORTD|=(1<<PIND7))
#define CS_active()		(PORTD&=~(1<<PIND7));_delay_us(10)


void OLEDdata(unsigned char data);
void OLED2data(unsigned char data);//one byte twice
void OLED3data(unsigned char data);//one byte triple times
void OLED4data(unsigned char data);//one byte four times
void OLEDdataNEG(unsigned char data);
void OLED2dataNEG(unsigned char data);//one byte twice
void OLED3dataNEG(unsigned char data);//one byte triple times
void OLED4dataNEG(unsigned char data);//one byte four times
void OLEDcommand(unsigned char command);
void OLEDreset();//resetování displeje
void OLEDon();//zapnutí displeje
void OLEDoff();//vypnutí displeje
void OLEDsetContrast(unsigned char contrast);//0xFF max, 0x00 min (not dark!)
void OLEDsetY(unsigned char y);//nastavení souøadnice
void OLEDsetX(unsigned char x);//nastavení souøadnice
void OLEDsetXY(unsigned char x, unsigned char y);//nastavení obou souøadnic zároveò
void OLEDinvert();//invertování displeje (zhasnuté pixely se rozsvítí a rozsvícené zhasnou)
void OLEDdeinvert();//deinvertování displeje (zhasnuté pixely se rozsvítí a rozsvícené zhasnou)
void OLEDclear();//vymazání displeje
void OLEDfill();//vyplnìní displeje
void OLEDclearLine(unsigned char line);//vymazání jednoho øádku displeje
void OLEDfillLine(unsigned char line);//vyplnìní jednoho øádku displeje
//////////////////////////////////////////////////////////////////////////
void OLEDinit();//inicializace displeje
void OLEDdrawImage();//vykreslí obrázek
void OLEDdrawImageInvert();//vykreslí obrázek
//////////////////////////////////////////////////////////////////////////
unsigned char OLEDconvertChar(unsigned char ch);
unsigned char OLEDconvertCharMicroFont(unsigned char ch);
//////////////////////////////////////////////////////////////////////////
void OLEDwriteChar1line(unsigned char x, unsigned char y, unsigned char ch);
void OLEDwriteChar2lines(unsigned char x, unsigned char y, unsigned char ch);
void OLEDwriteChar2linesBOLD(unsigned char x, unsigned char y, unsigned char ch);//tuèné
void OLEDwriteChar4lines(unsigned char x, unsigned char y, unsigned char ch);
void OLEDwriteChar4linesBOLD(unsigned char x, unsigned char y, unsigned char ch);
void OLEDwriteChar8lines(unsigned char x, unsigned char y, unsigned char ch);
void OLEDwriteChar8linesBOLD(unsigned char x, unsigned char y, unsigned char ch);
//////////////////////////////////////////////////////////////////////////
void OLEDwriteString1line(unsigned char x, unsigned char y, char* string);
void OLEDwriteString2lines(unsigned char x, unsigned char y, char* string);
void OLEDwriteString2linesBOLD(unsigned char x, unsigned char y, char* string);
void OLEDwriteString4lines(unsigned char x, unsigned char y, char* string);
void OLEDwriteString4linesBOLD(unsigned char x, unsigned char y, char* string);
void OLEDwriteString8lines(unsigned char x, unsigned char y, char* string);
void OLEDwriteString8linesBOLD(unsigned char x, unsigned char y, char* string);
//////////////////////////////////////////////////////////////////////////
void OLEDwriteString1linePGM(unsigned char x, unsigned char y, const char* string);
void OLEDwriteString2linesPGM(unsigned char x, unsigned char y, const char* string);
void OLEDwriteString2linesBOLDPGM(unsigned char x, unsigned char y, const char* string);
void OLEDwriteString4linesPGM(unsigned char x, unsigned char y, const char* string);
void OLEDwriteString4linesBOLDPGM(unsigned char x, unsigned char y, const char* string);
void OLEDwriteString8linesPGM(unsigned char x, unsigned char y, const char* string);
void OLEDwriteString8linesBOLDPGM(unsigned char x, unsigned char y, const char* string);
//////////////////////////////////////////////////////////////////////////
void OLEDwriteChar1lineNEG(unsigned char x, unsigned char y, unsigned char ch);
void OLEDwriteChar2linesNEG(unsigned char x, unsigned char y, unsigned char ch);
void OLEDwriteChar4linesNEG(unsigned char x, unsigned char y, unsigned char ch);
void OLEDwriteChar4linesBOLDNEG(unsigned char x, unsigned char y, unsigned char ch);
void OLEDwriteChar8linesNEG(unsigned char x, unsigned char y, unsigned char ch);
void OLEDwriteChar8linesBOLDNEG(unsigned char x, unsigned char y, unsigned char ch);
//////////////////////////////////////////////////////////////////////////
void OLEDwriteSpace1lineNEG(unsigned char x, unsigned char y);
void OLEDwriteSpace2linesNEG(unsigned char x, unsigned char y);
void OLEDwriteSpace2linesBOLDNEG(unsigned char x, unsigned char y);//tuèné
void OLEDwriteSpace4linesNEG(unsigned char x, unsigned char y);
void OLEDwriteSpace4linesBOLDNEG(unsigned char x, unsigned char y);
void OLEDwriteSpace8linesNEG(unsigned char x, unsigned char y);
void OLEDwriteSpace8linesBOLDNEG(unsigned char x, unsigned char y);
//////////////////////////////////////////////////////////////////////////
void OLEDwriteString1lineNEG(unsigned char x, unsigned char y, char* string);
void OLEDwriteString2linesNEG(unsigned char x, unsigned char y, char* string);
void OLEDwriteString2linesBOLDNEG(unsigned char x, unsigned char y, char* string);
void OLEDwriteString4linesNEG(unsigned char x, unsigned char y, char* string);
void OLEDwriteString4linesBOLDNEG(unsigned char x, unsigned char y, char* string);
void OLEDwriteString8linesNEG(unsigned char x, unsigned char y, char* string);
void OLEDwriteString8linesBOLDNEG(unsigned char x, unsigned char y, char* string);
//////////////////////////////////////////////////////////////////////////
void OLEDwriteString1linePGMNEG(unsigned char x, unsigned char y, const char* string);
void OLEDwriteString2linesPGMNEG(unsigned char x, unsigned char y, const char* string);
void OLEDwriteString2linesBOLDPGMNEG(unsigned char x, unsigned char y, const char* string);
void OLEDwriteString4linesPGMNEG(unsigned char x, unsigned char y, const char* string);
void OLEDwriteString4linesBOLDPGMNEG(unsigned char x, unsigned char y, const char* string);
void OLEDwriteString8linesPGMNEG(unsigned char x, unsigned char y, const char* string);
void OLEDwriteString8linesBOLDPGMNEG(unsigned char x, unsigned char y, const char* string);
// -Wl,-u,vfprintf -lprintf_flt -lm --- Toolchain > Linker > Misc..
void OLEDprint(unsigned char x, unsigned char y, unsigned char font, char *retezec, ...);
void OLEDprintText(unsigned char x, unsigned char y, unsigned char font, const char *string);


extern const unsigned char font[82][16] PROGMEM;
extern const unsigned char microFont[67][3] PROGMEM;
extern unsigned char const picture[8][128] PROGMEM;

#endif