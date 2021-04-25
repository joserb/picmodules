/**
* \file microtips-lcd.c
* \brief Main functions to configure and control Microtips Graphic Color LCD
*
* Copyright (C) 2020 INGEN10 Ingenieria S.L.
* http://www.ingen10.com
*
* LEGAL NOTICE:
* All information contained herein is, and remains property of INGEN10 INGENIERIA SL.
* Dissemination of this information or reproduction of this material is strictly
* forbidden unless prior written permission is obtained from its owner.
* ANY REPRODUCTION, MODIFICATION, DISTRIBUTION, PUBLIC PERFORMANCE, OR PUBLIC DISPLAY
* OF, OR THROUGH USE OF THIS SOURCE CODE IS STRICTLY PROHIBITED, AND IT IS A VIOLATION
* OF INTERNATIONAL TRADE TREATIES AND LAWS.
* THE RECEIPT OR POSSESSION OF THIS DOCUMENT DOES NOT CONVEY OR IMPLY ANY RIGHTS.
*
* \author   JRB
* \date     10/04/2020
*
*/

#include "microtips-lcd.h"


/**
 * Defines a 5x7 font
 */
const char kFont[][5] = {{0x00, 0x00, 0x00, 0x00, 0x00}, // SPACE
    {0x00, 0x00, 0x5F, 0x00, 0x00}, // !
    {0x00, 0x03, 0x00, 0x03, 0x00}, // "
    {0x14, 0x3E, 0x14, 0x3E, 0x14}, // #
    {0x24, 0x2A, 0x7F, 0x2A, 0x12}, // $
    {0x43, 0x33, 0x08, 0x66, 0x61}, // %
    {0x36, 0x49, 0x55, 0x22, 0x50}, // &
    {0x00, 0x05, 0x03, 0x00, 0x00}, // '
    {0x00, 0x1C, 0x22, 0x41, 0x00}, // (
    {0x00, 0x41, 0x22, 0x1C, 0x00}, // )
    {0x14, 0x08, 0x3E, 0x08, 0x14}, // *
    {0x08, 0x08, 0x3E, 0x08, 0x08}, // +
    {0x00, 0x50, 0x30, 0x00, 0x00}, // ,
    {0x08, 0x08, 0x08, 0x08, 0x08}, // -
    {0x00, 0x60, 0x60, 0x00, 0x00}, // .
    {0x20, 0x10, 0x08, 0x04, 0x02}, // /
    {0x3E, 0x51, 0x49, 0x45, 0x3E}, // 0
    {0x00, 0x04, 0x02, 0x7F, 0x00}, // 1
    {0x42, 0x61, 0x51, 0x49, 0x46}, // 2
    {0x22, 0x41, 0x49, 0x49, 0x36}, // 3
    {0x18, 0x14, 0x12, 0x7F, 0x10}, // 4
    {0x27, 0x45, 0x45, 0x45, 0x39}, // 5
    {0x3E, 0x49, 0x49, 0x49, 0x32}, // 6
    {0x01, 0x01, 0x71, 0x09, 0x07}, // 7
    {0x36, 0x49, 0x49, 0x49, 0x36}, // 8
    {0x26, 0x49, 0x49, 0x49, 0x3E}, // 9
    {0x00, 0x36, 0x36, 0x00, 0x00}, // :
    {0x00, 0x56, 0x36, 0x00, 0x00}, // ;
    {0x08, 0x14, 0x22, 0x41, 0x00}, // <
    {0x14, 0x14, 0x14, 0x14, 0x14}, // =
    {0x00, 0x41, 0x22, 0x14, 0x08}, // >
    {0x02, 0x01, 0x51, 0x09, 0x06}, // ?
    {0x3E, 0x41, 0x59, 0x55, 0x5E}, // @
    {0x7E, 0x09, 0x09, 0x09, 0x7E}, // A
    {0x7F, 0x49, 0x49, 0x49, 0x36}, // B
    {0x3E, 0x41, 0x41, 0x41, 0x22}, // C
    {0x7F, 0x41, 0x41, 0x41, 0x3E}, // D
    {0x7F, 0x49, 0x49, 0x49, 0x41}, // E
    {0x7F, 0x09, 0x09, 0x09, 0x01}, // F
    {0x3E, 0x41, 0x41, 0x49, 0x3A}, // G
    {0x7F, 0x08, 0x08, 0x08, 0x7F}, // H
    {0x00, 0x41, 0x7F, 0x41, 0x00}, // I
    {0x30, 0x40, 0x40, 0x40, 0x3F}, // J
    {0x7F, 0x08, 0x14, 0x22, 0x41}, // K
    {0x7F, 0x40, 0x40, 0x40, 0x40}, // L
    {0x7F, 0x02, 0x0C, 0x02, 0x7F}, // M
    {0x7F, 0x02, 0x04, 0x08, 0x7F}, // N
    {0x3E, 0x41, 0x41, 0x41, 0x3E}, // O
    {0x7F, 0x09, 0x09, 0x09, 0x06}, // P
    {0x1E, 0x21, 0x21, 0x21, 0x5E}, // Q
    {0x7F, 0x09, 0x09, 0x09, 0x76}, // R
    {0x26, 0x49, 0x49, 0x49, 0x32}, // S
    {0x01, 0x01, 0x7F, 0x01, 0x01}, // T
    {0x3F, 0x40, 0x40, 0x40, 0x3F}, // U
    {0x1F, 0x20, 0x40, 0x20, 0x1F}, // V
    {0x7F, 0x20, 0x10, 0x20, 0x7F}, // W
    {0x41, 0x22, 0x1C, 0x22, 0x41}, // X
    {0x07, 0x08, 0x70, 0x08, 0x07}, // Y
    {0x61, 0x51, 0x49, 0x45, 0x43}, // Z
    {0x00, 0x7F, 0x41, 0x00, 0x00}, // [
    {0x02, 0x04, 0x08, 0x10, 0x20}, // "\"
    {0x00, 0x00, 0x41, 0x7F, 0x00}, // ]
    {0x04, 0x02, 0x01, 0x02, 0x04}, // ^
    {0x40, 0x40, 0x40, 0x40, 0x40}, // _
    {0x00, 0x01, 0x02, 0x04, 0x00}, // `
    {0x20, 0x54, 0x54, 0x54, 0x78}, // a
    {0x7F, 0x44, 0x44, 0x44, 0x38}, // b
    {0x38, 0x44, 0x44, 0x44, 0x44}, // c
    {0x38, 0x44, 0x44, 0x44, 0x7F}, // d
    {0x38, 0x54, 0x54, 0x54, 0x18}, // e
    {0x04, 0x04, 0x7E, 0x05, 0x05}, // f
    {0x08, 0x54, 0x54, 0x54, 0x3C}, // g
    {0x7F, 0x08, 0x04, 0x04, 0x78}, // h
    {0x00, 0x44, 0x7D, 0x40, 0x00}, // i
    {0x20, 0x40, 0x44, 0x3D, 0x00}, // j
    {0x7F, 0x10, 0x28, 0x44, 0x00}, // k
    {0x00, 0x41, 0x7F, 0x40, 0x00}, // l
    {0x7C, 0x04, 0x78, 0x04, 0x78}, // m
    {0x7C, 0x08, 0x04, 0x04, 0x78}, // n
    {0x38, 0x44, 0x44, 0x44, 0x38}, // o
    {0x7C, 0x14, 0x14, 0x14, 0x08}, // p
    {0x08, 0x14, 0x14, 0x14, 0x7C}, // q
    {0x00, 0x7C, 0x08, 0x04, 0x04}, // r
    {0x48, 0x54, 0x54, 0x54, 0x20}, // s
    {0x04, 0x04, 0x3F, 0x44, 0x44}, // t
    {0x3C, 0x40, 0x40, 0x20, 0x7C}, // u
    {0x1C, 0x20, 0x40, 0x20, 0x1C}, // v
    {0x3C, 0x40, 0x30, 0x40, 0x3C}, // w
    {0x44, 0x28, 0x10, 0x28, 0x44}, // x
    {0x0C, 0x50, 0x50, 0x50, 0x3C}, // y
    {0x44, 0x64, 0x54, 0x4C, 0x44}, // z
    {0x00, 0x08, 0x36, 0x41, 0x41}, // {
    {0x00, 0x00, 0x7F, 0x00, 0x00}, // |
    {0x41, 0x41, 0x36, 0x08, 0x00}, // }
    {0x7C, 0x09, 0x11, 0x21, 0x7C}
};// ~ as ñ

void ConfigureScreen() {
    /////////////////////////////////////////////////////////
    PMPSetReg(&GLCDBus, SW_Reset_Reg, 1);     //Do software reset to SSD192X
    PMPSetReg(&GLCDBus, SW_Reset_Reg, 0);    //Release software reset from SSD192X
    /////////////////////////////////////////////////////////////////////
    // PLL SETUP
    // Crystal frequency x M / N = 80 MHz
    // for 4 MHz crystal:
    /////////////////////////////////////////////////////////////////////
    PMPSetReg(&GLCDBus, PLL_Clock_Setting_Reg0, 0x0A);     //0x126
    PMPSetReg(&GLCDBus, PLL_Clock_Setting_Reg1, 0xC8);     //0x127
    PMPSetReg(&GLCDBus, PLL_Clock_Setting_Reg2, 0xAE);     //0x12B
    PMPSetReg(&GLCDBus, PLL_Clock_Setting_Reg0, 0x8A);     //0x126
    /////////////////////////////////////////////////////////////////////
    // VIDEO BUFFER MEMORY CLOCK SETUP
    // Memory frequency = PLL frequency / (MCLK + 1)
    ////////////////////////////////////////////////////////////////////
    PMPSetReg(&GLCDBus, Mem_Clock_Config_Reg, 0x01);     //0x004
    /////////////////////////////////////////////////////////////////////
    // PIXEL OUTPUT CLOCK SETUP (LCD_SHIFT SIGNAL)
    // Pixel clock = Memory frequency * (PCLK + 1) / 0x100000
    /////////////////////////////////////////////////////////////////////
    PMPSetReg(&GLCDBus, PCLK_Freq_Ratio_Reg0, 0x5C);     //0x158
    PMPSetReg(&GLCDBus, PCLK_Freq_Ratio_Reg1, 0x8F);     //0x159
    PMPSetReg(&GLCDBus, PCLK_Freq_Ratio_Reg2, 0x02);     //0x15A
    /////////////////////////////////////////////////////////////////////
    // Panel Configuration (reg 10h)
    // TFT display with 18 bit or 24-bit RGB parallel interface.
    /////////////////////////////////////////////////////////////////////
    PMPSetReg(&GLCDBus, Panel_Type_Reg, 0xE1);           //0x010
    PMPSetReg(&GLCDBus, MOD_Rate_Reg, 0x00);           //0x011
    /////////////////////////////////////////////////////////////////////
    // Horizontal total HT (reg 12h)
    /////////////////////////////////////////////////////////////////////
    PMPSetReg(&GLCDBus, Horiz_Total_Reg1, 0x32);           //0x012
    PMPSetReg(&GLCDBus, Horiz_Total_Reg0, 0x07);           //0x013
    /////////////////////////////////////////////////////////////////////
    // Horizontal display period HDP (reg 14h)
    /////////////////////////////////////////////////////////////////////
    PMPSetReg(&GLCDBus, Horiz_Display_Period_Reg, 0x27);  //0x014
    /////////////////////////////////////////////////////////////////////
    // Horizontal display period start HDPS (regs 16h, 17h)
    /////////////////////////////////////////////////////////////////////
    PMPSetReg(&GLCDBus, HDispPeriod_StartPos_Reg0, 0x44);  //0x016
    PMPSetReg(&GLCDBus, HDispPeriod_StartPos_Reg1, 0x00);  //0x017
    /////////////////////////////////////////////////////////////////////
    // Horizontal syncronization pulse width HPW (reg 20h)
    /////////////////////////////////////////////////////////////////////
    PMPSetReg(&GLCDBus, LLINE_Pulse_Width_Reg, 0x25);     //0x020
    /////////////////////////////////////////////////////////////////////
    // Vertical total VT (regs 18h, 19h)
    /////////////////////////////////////////////////////////////////////
    PMPSetReg(&GLCDBus, Vertical_Total_Reg0, 0x06);        //0x018
    PMPSetReg(&GLCDBus, Vertical_Total_Reg1, 0x01);        //0x019
    /////////////////////////////////////////////////////////////////////
    // Vertical display period VDP (regs 1ch, 1dh)
    /////////////////////////////////////////////////////////////////////
    PMPSetReg(&GLCDBus, Vert_Display_Period_Reg0, 0xEF);  //0x01C
    PMPSetReg(&GLCDBus, Vert_Display_Period_Reg1, 0x00);  //0x01D
    /////////////////////////////////////////////////////////////////////
    // Vertical display period start VDPS (regs 1eh, 1fh)
    /////////////////////////////////////////////////////////////////////
    PMPSetReg(&GLCDBus, V_Disp_Per_StartPos_Reg0, 0x12);  //0x01E
    PMPSetReg(&GLCDBus, V_Disp_Per_StartPos_Reg1, 0x00);  //0x01F
    PMPSetReg(&GLCDBus, LLINE_PStart_Spix_Pos_Reg, 0x00);  //0x021
    PMPSetReg(&GLCDBus, LLINE_PStart_Position_Reg0, 0x00);  //0x022
    PMPSetReg(&GLCDBus, LLINE_PStart_Position_Reg1, 0x00);  //0x023
    /////////////////////////////////////////////////////////////////////
    // Vertical syncronization pulse width VPW (reg 24h)
    /////////////////////////////////////////////////////////////////////
    PMPSetReg(&GLCDBus, LFRAME_Pulse_Width_Reg, 0x07);  //0x024
    /////////////////////////////////////////////////////////////////////
    PMPSetReg(&GLCDBus, LFRAME_PStart_Posit_Reg0, 0x00);  //0x026
    PMPSetReg(&GLCDBus, LFRAME_PStart_Posit_Reg1, 0x00);  //0x027
    PMPSetReg(&GLCDBus, DispP_Saturat_Control_Reg, 0x40);  //0x02C
    PMPSetReg(&GLCDBus, DispP_Brightn_Control_Reg, 0x80);  //0x02D
    PMPSetReg(&GLCDBus, DispP_Contrast_Control_Reg, 0x40);  //0x02E
    PMPSetReg(&GLCDBus, DispP_Control_Reg, 0x00);        //0x02F
    PMPSetReg(&GLCDBus, LFRAME_PStart_Offs_Reg0, 0x00);  //0x030
    PMPSetReg(&GLCDBus, LFRAME_PStart_Offs_Reg1, 0x00);  //0x031
    PMPSetReg(&GLCDBus, LFRAME_PStop_Offs_Reg0, 0x00);  //0x034
    PMPSetReg(&GLCDBus, LFRAME_PStop_Offs_Reg1, 0x00);  //0x035
    PMPSetReg(&GLCDBus, LSHIFT_sig_StartPos_Reg0, 0x00);  //0x350
    PMPSetReg(&GLCDBus, LSHIFT_sig_StartPos_Reg1, 0x00);  //0x351
    PMPSetReg(&GLCDBus, LSHIFT_sig_EndPos_Reg0, 0x00);  //0x354
    PMPSetReg(&GLCDBus, LSHIFT_sig_EndPos_Reg1, 0x00);  //0x355
    PMPSetReg(&GLCDBus, Power_Saving_Config_Reg, 0x00);  //0x0A0
    PMPSetReg(&GLCDBus, Display_Mode_Reg, 0x14);        //0x070
    PMPSetReg(&GLCDBus, GPIO_Pins_Config_Reg0, 0x1F);     //0x0A
    /////////////////////////////////////////////////////////////////////
    // Special Effects Register (reg 71h)
    /////////////////////////////////////////////////////////////////////
    PMPSetReg(&GLCDBus, Special_Effects_Reg, 0x40);        //0x071
    /////////////////////////////////////////////////////////////////////
    // Main Window Display Start Address (regs 74h, 75h, 76h)
    /////////////////////////////////////////////////////////////////////
    PMPSetReg(&GLCDBus, MWindowDisp_StAddr_Reg0, 0x00);  //0x074
    PMPSetReg(&GLCDBus, MWindowDisp_StAddr_Reg1, 0x00);  //0x075
    PMPSetReg(&GLCDBus, MWindowDisp_StAddr_Reg2, 0x00);  //0x076
    /////////////////////////////////////////////////////////////////////
    // Main Window Display Offset (regs 78h, 79h)
    /////////////////////////////////////////////////////////////////////
    PMPSetReg(&GLCDBus, MWindLine_AddrOffs_Reg0, 0xA0);  //0x078
    PMPSetReg(&GLCDBus, MWindLine_AddrOffs_Reg1, 0x00);  //0x079
    /////////////////////////////////////////////////////////////////////
    // RGB Settings Register (reg 1a4h)
    /////////////////////////////////////////////////////////////////////
    PMPSetReg(&GLCDBus, RGB_Setting_Register, 0xFF);       //0x1A4
    /////////////////////////////////////////////////////////////////////
    // LSHIFT Polarity Register (reg 38h)
    /////////////////////////////////////////////////////////////////////
    PMPSetReg(&GLCDBus, LSHIFT_Polarity_Reg, 0x00);        //0x038
    PMPTCONInit(&GLCDBus);
}

/**
 * @brief Clears screen
 */
void ClearDevice(glcd_device* dev) {
    DWORD counter;
    digitalWrite(LCD_CS1, 0);
    PMPSetAddress(&GLCDBus, 0);

    for (counter = 0; counter < (DWORD)(GetMaxX() + 1) * (GetMaxY() + 1);
            counter++) {
        PMPWriteData(&GLCDBus, dev->bg_color);
    }

    digitalWrite(LCD_CS1, 1);
}



/**
 * RGB565Convert
 * @brief Convert a combination of 3 colors to a WORD value
 * @param Red value (BYTE)
 * @param Green value (BYTE)
 * @param Blue value (BYTE)
 * @return WORD value
 */
int RGBColor(int r, int g, int b) {
    int color, cr, cg, cb;
    cr = r;
    cr = (cr >> 3);
    cr = cr << 11;
    cg = g;
    cg = (cg >> 2);
    cg = cg << 5;
    cb = b;
    cb = (cb >> 3);
    color = (cr | cg | cb);
    return color;
}

/**
 * @brief Turn on/off LCD backlight
 * @param on Enable/disable lcd backlight
 */
void LCDBacklight(char on) {
    digitalWrite(LCD_BL, on);
}


/**
 * @brief Sets main color
 * @param color (WORD)
 */
void SetColor(glcd_device* dev, WORD color) {
    dev->_color = color;
}

/**
 * ClcdSetColor
 * @bief Set backgroung color
 * @param Color in word format.
 */
void SetBgColor(glcd_device* dev, WORD color) {
    dev->bg_color = color;
}


/**
 * ClcdGoToXY
 * @bief  Set text position
 * @param left
 * @param top
 */
void ClcdGoToXY(glcd_device* dev, int x, int y) {
    // Set start address
    dev->my_x = x;
    dev->my_y = y;
    dev->my_address = glcd_address(x, y);
}

/**
 * @brief Puts pixel
 * @param x pixel coordinate
 * @param y pixel coordinate
 */
void PutPixel(glcd_device* dev, int x, int y) {
    DWORD address;
    address = glcd_address(x, y);
    digitalWrite(LCD_CS1, 0);
    PMPSetAddress(&GLCDBus, address);
    PMPWriteData(&GLCDBus, dev->_color);
    digitalWrite(LCD_CS1, 1);
}



/**
 * @brief Returns pixel color at x,y position
 * @param x pixel coordinate
 * @param y pixel coordinate
 * @return color (WORD)
 */
WORD GetPixel(glcd_device* dev, int x, int y) {
    DWORD address;
    WORD_VAL value;
    address = glcd_address(x, y);
    digitalWrite(LCD_CS1, 0);
    PMPSetAddress(&GLCDBus, address);
    value.Val = PMPReadData(&GLCDBus);
    digitalWrite(LCD_CS1, 1);
    //PMCONbits.PMPEN = 0;  // suspend PMP
    //value.v[0] = PMDIN1;
    //PMCONbits.PMPEN  = 1;  // resume PMP
    return value.Val;
}



/**
 * ClcdPrint
 * @bief Prints a string on the LCD
 * @param *str
 */
void ClcdPrint(glcd_device* dev, const char* str, ...) {
    char* charsel;
    char pixel_data[5];                     // Stores character data
    register DWORD address;
    WORD size_x, size_y;
    register WORD x, y;
    int i;
    char str_format[255];
    register WORD stretch_x, stretch_y;
    va_list args;
    va_start(args, str);
    vsprintf(str_format, str, args);
    va_end(args);
    charsel = str_format;

    while (*charsel != '\0') {
        memcpy(pixel_data, kFont[*charsel - ' '], 5);

        if (*charsel == '\n') {
            dev->my_y += 8 * dev->text_size;
            ClcdGoToXY(dev, dev->my_x, dev->my_y);
            charsel++;
            continue;
        } else if (*charsel == '\r') {
            dev->my_x = 0;
            ClcdGoToXY(dev, dev->my_x, dev->my_y);
            charsel++;
            continue;
        }

        // Read image size
        size_y = 7 * dev->text_size;
        size_x = 5 * dev->text_size;
        address = dev->my_address;
        digitalWrite(LCD_CS1, 0);

        for (y = 0; y < size_y; y++) {
            for (stretch_y = 0; stretch_y < 1; stretch_y++) {
                PMPSetAddress(&GLCDBus, address);

                for (x = 0; x < size_x; x++) {
                    if ((pixel_data[x / dev->text_size] >> (y / dev->text_size)) & 0x1) {
                        for (stretch_x = 0; stretch_x < 1; stretch_x++)
                            PMPWriteData(&GLCDBus, dev->_color);
                    } else {
                        for (stretch_x = 0; stretch_x < 1; stretch_x++)
                            PMPWriteData(&GLCDBus, dev->bg_color);
                    }
                }

                for (i = 0; i < dev->text_size; i++)
                    PMPWriteData(&GLCDBus, dev->bg_color);

                address += (GetMaxX() + 1) << 1;
            }
        }

        ClcdGoToXY(dev, dev->my_x + 6 * dev->text_size, dev->my_y);
        digitalWrite(LCD_CS1, 1);
        charsel++;
    }
}

/**
 * ClcdPrint
 * @bief Prints a string on the LCD
 * @param *str
 */
void ClcdPuts(glcd_device* dev, const char* str) {
    char* charsel;
    char pixel_data[5];                     // Stores character data
    register DWORD address;
    WORD size_x, size_y;
    register WORD x, y;
    int i;
    register WORD stretch_y;
    charsel = str;
    size_y = 7 * dev->text_size;
    size_x = 5 * dev->text_size;

    while (*charsel != '\0') {
        memcpy(pixel_data, kFont[*charsel - ' '], 5);

        if (*charsel == '\n') {
            dev->my_y += 8 * dev->text_size;
            ClcdGoToXY(dev, dev->my_x, dev->my_y);
            charsel++;
            continue;
        } else if (*charsel == '\r') {
            dev->my_x = 0;
            ClcdGoToXY(dev, dev->my_x, dev->my_y);
            charsel++;
            continue;
        }

        address = dev->my_address;
        digitalWrite(LCD_CS1, 0);

        for (y = 0; y < size_y; y++) {
            for (stretch_y = 0; stretch_y < 1; stretch_y++) {
                PMPSetAddress(&GLCDBus, address);

                for (x = 0; x < size_x; x++) {
                    if ((pixel_data[x / dev->text_size] >> (y / dev->text_size)) & 0x1) {
                        PMPWriteData(&GLCDBus, dev->_color);
                    } else {
                        PMPWriteData(&GLCDBus, dev->bg_color);
                    }
                }

                for (i = 0; i < dev->text_size; i++)
                    PMPWriteData(&GLCDBus, dev->bg_color);

                address += (GetMaxX() + 1) << 1;    //go to next Y pixel
            }
        }

        ClcdGoToXY(dev, dev->my_x + 6 * dev->text_size, dev->my_y);
        digitalWrite(LCD_CS1, 1);
        charsel++;
    }
}

/**
 * ClcdPrint
 * @bief Prints a string on the LCD
 * @param *str
 */
void ClcdXYPuts(glcd_device* dev, int xpos, int ypos, const char* str) {
    char* charsel;
    char pixel_data[5];                     // Stores character data
    register DWORD address;
    WORD size_x, size_y;
    register WORD x, y;
    int i;
    register WORD stretch_y;
    charsel = str;
    size_y = 7 * dev->text_size;
    size_x = 5 * dev->text_size;

    while (*charsel != '\0') {
        memcpy(pixel_data, kFont[*charsel - ' '], 5);

        if (*charsel == '\n') {
            ypos += 8 * dev->text_size;
            charsel++;
            continue;
        } else if (*charsel == '\r') {
            xpos = 0;
            charsel++;
            continue;
        }

        address = glcd_address(xpos, ypos);
        digitalWrite(LCD_CS1, 0);

        for (y = 0; y < size_y; y++) {
            for (stretch_y = 0; stretch_y < 1; stretch_y++) {
                PMPSetAddress(&GLCDBus, address);

                for (x = 0; x < size_x; x++) {
                    if ((pixel_data[x / dev->text_size] >> (y / dev->text_size)) & 0x1) {
                        PMPWriteData(&GLCDBus, dev->_color);
                    } else {
                        PMPWriteData(&GLCDBus, dev->bg_color);
                    }
                }

                for (i = 0; i < dev->text_size; i++)
                    PMPWriteData(&GLCDBus, dev->bg_color);

                address += (GetMaxX() + 1) << 1;    //go to next Y pixel
            }
        }

        xpos += 6 * dev->text_size;
        digitalWrite(LCD_CS1, 1);
        charsel++;
    }
}


/**
 * ClcdTextSize
 * @bief Set text size
 * @param size
 */
void ClcdTextSize(glcd_device* dev, WORD size) {
    dev->text_size = size;
}


/**
 * @brief Outputs rectangle starting from left,top coordinates
 * @param left corner coordinates
 * @param top corner coordinates
 * @param rectangle height
 * @param rectangle width
 */
void PutRectangle(glcd_device* dev, int height, int width) {
    register DWORD address;
    register WORD x, y;
    address = glcd_address(dev->my_x, dev->my_y);
    digitalWrite(LCD_CS1, 0);

    for (y = 0; y < height; y++) {
        PMPSetAddress(&GLCDBus, address);

        for (x = 0; x < width; x++) {
            PMPWriteData(&GLCDBus, dev->_color);
        }

        address += (GetMaxX() + 1) << 1;    //jump to next line
    }

    digitalWrite(LCD_CS1, 1);
}

/**
 * @brief Puts horizontal line
 * @param length
 */
void PutHLine(glcd_device* dev, int length) {
    DWORD address;
    int x;
    address = glcd_address(dev->my_x, dev->my_y);
    digitalWrite(LCD_CS1, 0);
    PMPSetAddress(&GLCDBus, address);

    for (x = 0; x < length; x++) {
        PMPWriteData(&GLCDBus, dev->_color);
    }

    digitalWrite(LCD_CS1, 1);
}

/**
 * @brief Puts vertical line
 * @param length
 */
void PutVLine(glcd_device* dev, int length) {
    DWORD address;
    int x;
    address = glcd_address(dev->my_x, dev->my_y);
    digitalWrite(LCD_CS1, 0);

    for (x = 0; x < length; x++) {
        PMPSetAddress(&GLCDBus, address);
        PMPWriteData(&GLCDBus, dev->_color);
        address += (GetMaxX() + 1) << 1;
    }

    digitalWrite(LCD_CS1, 1);
}

/**
 * @brief Setup input output pins for use LCD
 */
void MicrotipsLCDInit(glcd_device* dev) {
    pinMode(LCD_RST, 0);
    pinMode(LCD_RS, 0);
    pinMode(LCD_WR, 0);
    pinMode(LCD_RD, 0);
    pinMode(LCD_CS1, 0);
    pinMode(LCD_BL, 0);
    LCDBacklight(0);
    PMPInit(&GLCDBus);
    delay(40);
    digitalWrite(LCD_RST, 1); // Release from reset
    delay(200);
    ConfigureScreen();
    ClearDevice(dev);
    LCDBacklight(1);
}


void NewMicrotipsLCD(glcd_driver* drv) {
    drv->dev.text_size = 2;
    drv->dev._color = BLACK;
    drv->dev.bg_color = WHITE;
    drv->ops.glcdinit = MicrotipsLCDInit;
    drv->ops.cleardevice = ClearDevice;
    drv->ops.glcdsetcolor = SetColor;
    drv->ops.glcdtextsize = ClcdTextSize;
    drv->ops.glcdgotoxy = ClcdGoToXY;
    drv->ops.glcdputpixel = PutPixel;
    drv->ops.glcdgetpixel = GetPixel;
    drv->ops.glcdputs = ClcdPuts;
    drv->ops.glcdxyputs = ClcdXYPuts;
    drv->ops.glcdrectangle = PutRectangle;
    drv->ops.glcdhline = PutHLine;
    drv->ops.glcdvline = PutVLine;
}
