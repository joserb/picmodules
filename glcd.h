/*
 * File:   GLCD.h
 * Author: Jose
 *
 * Created on 14 de abril de 2020, 18:15
 */

#ifndef GLCD_H
#define	GLCD_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "../Common/GenericTypeDefs.h"

typedef struct {
    char* name;
    WORD _color;
    WORD  bg_color;
    DWORD my_address;
    WORD my_x, my_y;
    WORD text_size;
} glcd_device;

typedef struct {
    void (*glcdinit)(glcd_device* dev);
    void (*cleardevice)(glcd_device* dev);
    void (*glcdsetcolor)(glcd_device* dev, WORD color);
    void (*glcdsetbgcolor)(glcd_device* dev, WORD color);
    void (*glcdtextsize)(glcd_device* dev, WORD size);
    void (*glcdgotoxy)(glcd_device* dev, int x, int y);
    void (*glcdputpixel)(glcd_device* dev, int x, int y);
    WORD (*glcdgetpixel)(glcd_device* dev, int x, int y);
    void (*glcdputs)(glcd_device* dev, const char* str);
    void (*glcdxyputs)(glcd_device* dev, int x, int y, const char* str);
    void (*glcdrectangle)(glcd_device* dev, int sizex, int sizey);
    void (*glcdhline)(glcd_device* dev, int length);
    void (*glcdvline)(glcd_device* dev, int length);
} glcd_ops;

typedef struct {
    glcd_device dev;
    glcd_ops ops;
} glcd_driver;

inline static void GLCDInit(glcd_driver* drv) {
    drv->ops.glcdinit(&drv->dev);
}

inline static void GLCDClearDevice(glcd_driver* drv) {
    drv->ops.cleardevice(&drv->dev);
}

inline static void GLCDSetColor(glcd_driver* drv, WORD color) {
    drv->ops.glcdsetcolor(&drv->dev, color);
}

inline static void GLCDSetBgColor(glcd_driver* drv, WORD color) {
    drv->ops.glcdsetbgcolor(&drv->dev, color);
}

inline static void GLCDTextSize(glcd_driver* drv, WORD size) {
    drv->ops.glcdtextsize(&drv->dev, size);
}

inline static void GLCDGotoXY(glcd_driver* drv, int x, int y) {
    drv->ops.glcdgotoxy(&drv->dev, x, y);
}

inline static void GLCDPutPixel(glcd_driver* drv, int x, int y) {
    drv->ops.glcdputpixel(&drv->dev, x, y);
}

inline static WORD GLCDGetPixel(glcd_driver* drv, int x, int y) {
    return drv->ops.glcdgetpixel(&drv->dev, x, y);
}

inline static void GLCDPuts(glcd_driver* drv, const char* str) {
    drv->ops.glcdputs(&drv->dev, str);
}

inline static void GLCDXYPuts(glcd_driver* drv, int x, int y, const char* str) {
    drv->ops.glcdxyputs(&drv->dev, x, y, str);
}

inline static void GLCDDrawRect(glcd_driver* drv, int sizex, int sizey) {
    drv->ops.glcdrectangle(&drv->dev, sizex, sizey);
}

inline static void GLCDDrawHLine(glcd_driver* drv, int length) {
    drv->ops.glcdhline(&drv->dev, length);
}

inline static void GLCDDrawVLine(glcd_driver* drv, int length) {
    drv->ops.glcdvline(&drv->dev, length);
}

#ifdef	__cplusplus
}
#endif

#endif	/* GLCD_H */

