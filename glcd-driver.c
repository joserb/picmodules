/**
* \file glcd_bus_driver.c
* \brief bus controller for use DSPIC peripheral PMP
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

#include "glcd-driver.h"

pmp_driver GLCDBus = {
    .dev = {
        .name = "PMP BUS"
    },
    .ops = {
        .pmpinit = InitPMP,
        .tconinit = TCON_Init,
        .pmpsetreg = SetReg,
        .pmpgetreg = GetReg,
        .writedata = WriteData,
        .readdata = ReadData,
        .setaddress = SetAddress
    }
};

void InitPMP(pmp_device* dev) {
    TRISE = 0; // PMP as output
    digitalWrite(LCD_RST, 0);// hold in reset by default
    digitalWrite(LCD_CS1, 1);// SSD1926 is not selected by default
    PMCON = 0; // all active low
    PMCONbits.ADRMUX = 0; //   Address and data appear on separate pins
    PMCONbits.CSF = 0b11; // Chip select functions bits reserved
    PMCONbits.PTRDEN = 1; // PMR port enabled
    PMCONbits.PTWREN = 1; // PMW port enabled
    PMMODE = 0;
    PMMODEbits.MODE =
        0b10; // Master Mode 2 (PMCSx, PMRD, PMWR, PMBE, PMA<x:0>, and PMD<7:0>)
    PMMODEbits.WAITB = 0b11;
    PMMODEbits.WAITE = 0b11;
    PMMODEbits.WAITM = 0b111;
    PMAEN = 0;
    PMCONbits.PMPEN = 1; // PMP module enabled
}
/**
 * WritePMD
 * @brief Send data by PMD
 * @param data (int)
 */
void WritePMD(pmp_device* dev, uint8_t data) {
    PMDIN1 = data;
}
/**
 * ReadPMD
 * @brief Read data by PMD
 * @return data (int)
 */
uint8_t ReadPMD(pmp_device* dev) {
    uint8_t value;
    value = PMDIN1;
    PMPWaitBusy();
    return value;
}
/**
 * @brief Writes data into controller's RAM
 *
 * SetAdress(...) must be called before. Chip select should be enabled.
 * @param data: 16 bit value to be written to RAM
 * @return none
 */
void WriteData(pmp_device* dev, WORD data) {
    BYTE send;
    send = (data >> 8);
    WritePMD(dev, send);
    send = data;
    WritePMD(dev, send);
}

/**
 * @brief Reads data from controller's RAM
 *
 * SetAdress(...) must be called before. Chip select should be enabled.
 * @return 16 bit value written in RAM
 */
WORD ReadData(pmp_device* dev) {
    WORD data;
    BYTE aux;
    aux = ReadPMD(dev);
    data = (aux << 8);
    aux = ReadPMD(dev);
    data |= aux;
    return data;
}

/**
 * @brief Sets the address for read/write operations
 * @param adress
 * @return none
 */
void SetAddress(pmp_device* dev, DWORD address) {
    digitalWrite(LCD_RS, 0); // set RS line to low for command
    WritePMD(dev, ((DWORD_VAL)address).v[2] | 0x80);
    WritePMD(dev, ((DWORD_VAL)address).v[1]);
    WritePMD(dev, ((DWORD_VAL)address).v[0]);
    digitalWrite(LCD_RS, 1); // set RS line to high for data
}
/**
 * @brief Sets graphics controller register (byte access)
 * @param index - register number
 * @param value - value to be set
 */
void  SetReg(pmp_device* dev, WORD index, BYTE value) {
    char send;
    digitalWrite(LCD_RS, 0);       // set RS line to low for command
    digitalWrite(LCD_CS1, 0);        // enable SSD1926
    PMPWaitBusy(); // wait for the transmission end
    WritePMD(dev, 0x00);
    send = index >> 8;
    WritePMD(dev, send);
    send = index;
    WritePMD(dev, send);
    digitalWrite(LCD_RS, 1);       // set RS line to high for data
    WritePMD(dev, value);
    digitalWrite(LCD_CS1, 1);        // disable SSD1926
}
/**
 * @brief Returns graphics controller register value (byte access)
 * @param index - register number
 * @return graphics controller register value
 */
BYTE GetReg(pmp_device* dev, WORD index) {
    WORD value;
    digitalWrite(LCD_RS, 0);       // set RS line to low for command
    digitalWrite(LCD_CS1, 0);        // enable SSD1926
    PMPWaitBusy();         // wait for the transmission end
    WritePMD(dev, 0x00); // register access
    WritePMD(dev, ((WORD_VAL)index).v[1]);
    WritePMD(dev, ((WORD_VAL)index).v[0]);
    digitalWrite(LCD_RS, 1);       // set RS line to high for data
    value = ReadPMD(dev);
    value = ReadPMD(dev);
    digitalWrite(LCD_CS1, 1);        // disable SSD1926
    PMCONbits.PMPEN = 0;  // suspend PMP
    value = PMDIN1;        // read value
    PMCONbits.PMPEN = 1;  // resume PMP
    return value;
}



void TCON_CTRL(pmp_device* dev, BYTE mask, BYTE level) {
    if (level == 0)
        dev->valuetcon &= ~mask;
    else
        dev->valuetcon |= mask;

    SetReg(dev, 0xAC, dev->valuetcon);
}

void TCONWriteByte(pmp_device* dev, BYTE value) {
    BYTE mask;
    mask = 0x80;

    while (mask) {
        TCON_CTRL(dev, SCL, 0);

        //TCON_Delay();
        if (mask & value)
            TCON_CTRL(dev, SDO, 1);
        else
            TCON_CTRL(dev, SDO, 0);

        TCON_CTRL(dev, SCL, 1);
        mask >>= 1;
    }
}

void GPIO_TCON(pmp_device* dev, WORD index, WORD value) {
    TCON_CTRL(dev, CS, 0);
    // Index
    TCON_CTRL(dev, DC, 0);
    TCONWriteByte(dev, ((WORD_VAL)index).v[1]);
    TCONWriteByte(dev, ((WORD_VAL)index).v[0]);
    TCON_CTRL(dev, CS, 1);
    TCON_Delay();
    TCON_CTRL(dev, CS, 0);
    // Data
    TCON_CTRL(dev, DC, 1);
    TCONWriteByte(dev, ((WORD_VAL)value).v[1]);
    TCONWriteByte(dev, ((WORD_VAL)value).v[0]);
    TCON_CTRL(dev, CS, 1);
    TCON_Delay();
}

void TCON_Init(pmp_device* dev) {
    SetReg(dev, 0xA8, DC | CS | SDO | SCL);
    TCON_CTRL(dev, DC, 1);
    TCON_CTRL(dev, CS, 1);
    TCON_CTRL(dev, SDO, 1);
    TCON_CTRL(dev, SCL, 1);
    delay(20);
    GPIO_TCON(dev, 0x00, 0x0001);
    GPIO_TCON(dev, 0x03, 0xAAAC);
    GPIO_TCON(dev, 0x0C, 0x0002);
    delay(15);
    GPIO_TCON(dev, 0x0D, 0x000A);
    GPIO_TCON(dev, 0x0E, 0x2D00);
    GPIO_TCON(dev, 0x1E, 0x00BC);
    GPIO_TCON(dev, 0x01, 0x1A0C);
    delay(15);
    GPIO_TCON(dev, 0x01, 0x2B3F);
    GPIO_TCON(dev, 0x02, 0x0600);
    GPIO_TCON(dev, 0x10, 0x0000);
    GPIO_TCON(dev, 0x05, 0x0000);
    GPIO_TCON(dev, 0x06, 0x0000);
    delay(20);
}

