#ifndef GLCD_BUS_DRIVER_H
#define GLCD_BUS_DRIVER_H

#include <stdio.h>
#include "../dspic-common.h"
#include "../Common/GenericTypeDefs.h"

#define PMPWaitBusy()  asm("NOP; NOP;")

#define CS      0x01
#define SCL     0x02
#define SDO     0x04
#define DC      0x08

#define LCD_RST     0
#define LCD_RS      0
#define LCD_WR      0
#define LCD_RD      0
#define LCD_CS1     0
#define LCD_BL      0

typedef struct {
    char* name;
    BYTE valuetcon;
} pmp_device;

typedef struct {
    void (*pmpinit)(pmp_device* dev);
    void (*tconinit)(pmp_device* dev);
    void (*pmpsetreg)(pmp_device* dev, WORD index, BYTE value);
    BYTE (*pmpgetreg)(pmp_device* dev, WORD index);
    void (*writedata)(pmp_device* dev, WORD data);
    WORD (*readdata)(pmp_device* dev);
    void (*setaddress)(pmp_device* dev, DWORD address);
} pmp_ops;

typedef struct {
    pmp_device dev;
    pmp_ops ops;
} pmp_driver;

extern pmp_driver GLCDBus;

inline static void TCON_Delay() {
    WORD timeOut = 200;

    while (timeOut--);
}

inline static void PMPInit(pmp_driver* drv) {
    drv->ops.pmpinit(&drv->dev);
}

inline static void PMPTCONInit(pmp_driver* drv) {
    drv->ops.tconinit(&drv->dev);
}

inline static void PMPSetReg(pmp_driver* drv, WORD index, BYTE value) {
    drv->ops.pmpsetreg(&drv->dev, index, value);
}

inline static BYTE PMPGetReg(pmp_driver* drv, WORD index) {
    return drv->ops.pmpgetreg(&drv->dev, index);
}

inline static void PMPWriteData(pmp_driver* drv, WORD data) {
    drv->ops.writedata(&drv->dev, data);
}

inline static WORD PMPReadData(pmp_driver* drv) {
    return drv->ops.readdata(&drv->dev);
}

inline static void PMPSetAddress(pmp_driver* drv, DWORD address) {
    drv->ops.setaddress(&drv->dev, address);
}

void InitPMP(pmp_device* dev);
void TCON_Init(pmp_device* dev);
void SetReg(pmp_device* dev, WORD index, BYTE value);
BYTE GetReg(pmp_device* dev, WORD index);
void WriteData(pmp_device* dev, WORD data);
WORD ReadData(pmp_device* dev);
void SetAddress(pmp_device* dev, DWORD address);

void WritePMD(pmp_device* dev, uint8_t data);
uint8_t ReadPMD(pmp_device* dev);
void GPIO_TCON(pmp_device* dev, WORD index, WORD value);
void TCONWriteByte(pmp_device* dev, BYTE value);
void TCON_CTRL(pmp_device* dev, BYTE mask, BYTE level);
//void TCON_Delay();


#endif  //GLCD_BUS_DRIVER_H