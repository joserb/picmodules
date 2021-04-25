/**
* \file digital_io.c
* \brief Primary control of digital IO ports in uSTAT410 - (R) Metrohm DropSens S.L.
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
* \date     22/04/2020
*
*/

#include "digital-io.h"

static int mux_init(multiplexer* dev);

/** **************************************************************************************
 * \section LEDs Status leds control funtions
 */
int NewBicolorLed(led_driver* drv, char pin) {
    drv->ops.set_color = bicolor_led_set_color;
    drv->dev.led_1 = pin;
    pinMode(drv->dev.led_1, OUTPUT);
    digitalWrite(drv->dev.led_1, OFF);
    return 0;
}

int NewTricolorLed(led_driver* drv, char redp, char greenp) {
    drv->ops.set_color = tricolor_led_set_color;
    drv->dev.led_1 = redp;
    drv->dev.led_2 = greenp;
    pinMode(drv->dev.led_1, OUTPUT);
    pinMode(drv->dev.led_2, OUTPUT);
    digitalWrite(drv->dev.led_1, OFF);
    digitalWrite(drv->dev.led_2, OFF);
    return 0;
}

void tricolor_led_set_color(led_device* dev, char color) {
    digitalWrite(dev->led_1, (color&GREENLED)>0);
    digitalWrite(dev->led_2, (color&REDLED)>0);
}

void bicolor_led_set_color(led_device* dev, char state) {
    digitalWrite(dev->led_1, state>OFF);
}


/** **************************************************************************************
 * \section Multiplexer Analog switch and multiplexer control functions
 */

int NewMux1x8(multiplexer* dev, uint8_t a0, uint8_t a1, uint8_t a2) {
    int ret = 0;
    dev->mux_controls[0] = a0;
    dev->mux_controls[1] = a1;
    dev->mux_controls[2] = a2;
    dev->nb_controls = 3;
    ret = mux_init(dev);
    return ret;
}

int NewMux4SPST(multiplexer* dev, uint8_t a0, uint8_t a1, uint8_t a2,
                uint8_t a3) {
    int ret = 0;
    dev->mux_controls[0] = a0;
    dev->mux_controls[1] = a1;
    dev->mux_controls[2] = a2;
    dev->mux_controls[2] = a3;
    dev->nb_controls = 4;
    ret = mux_init(dev);
    return ret;
}

int NewMux3SPDT(multiplexer* dev, uint8_t a0, uint8_t a1, uint8_t a2) {
    int ret = 0;
    dev->mux_controls[0] = a0;
    dev->mux_controls[1] = a1;
    dev->mux_controls[2] = a2;
    dev->nb_controls = 3;
    ret = mux_init(dev);
    return ret;
}

static int mux_init(multiplexer* dev) {
    int i;

    for (i=0; i<dev->nb_controls; i++) {
        pinMode(dev->mux_controls[i], OUTPUT);
        digitalWrite(dev->mux_controls[i], OFF);
        dev->mux_status[i] = OFF;
    }

    return 0;
}


int SetMux(multiplexer* dev, uint8_t value) {
    int i;

    for (i=0; i<dev->nb_controls; i++) {
        dev->mux_status[i] = (value & (1<<i)) > 0;
        digitalWrite(dev->mux_controls[i], dev->mux_status[i]);
    }

    return 0;
}


int SetMuxPos(multiplexer* dev, uint8_t pos, uint8_t value) {
    if (pos>dev->nb_controls) return -1;

    dev->mux_status[pos] = (value & (1<<pos)) > 0;
    digitalWrite(dev->mux_controls[pos], dev->mux_status[pos]);
    return 0;
}


int GetMux(multiplexer* dev) {
    int i, ret=0;

    for (i=0; i<dev->nb_controls; i++) {
        if (dev->mux_status[i]>0)
            ret |= 1<<i;
    }

    return ret;
}

uint8_t GetMuxPos(multiplexer* dev, uint8_t pos) {
    if (pos>dev->nb_controls) return -1;
    else return dev->mux_status[pos];
}