#ifndef DIGITAL_IO_H
#define DIGITAL_IO_H

#include "../dspic-common.h"


/** **************************************************************************************
 * \section LEDs Status leds control funtions
 */

enum TRILED_COLORS {
    NONELED,
    GREENLED,
    REDLED,
    ORANGELED
};

enum BILED_STATES {
    OFF,
    ON
};

typedef struct {
    char* name;
    char led_1;
    char led_2;
} led_device;

typedef struct {
    void (*set_color)(led_device* dev, char color);
} led_ops;

typedef struct {
    led_device dev;
    led_ops ops;
} led_driver;

void tricolor_led_set_color(led_device* dev, char color);
void bicolor_led_set_color(led_device* dev, char color);
int NewBicolorLed(led_driver* drv, char pin);
int NewTricolorLed(led_driver* drv, char redp, char greenp);

inline static void SetLedColor(led_driver* drv, char color) {
    drv->ops.set_color(&drv->dev, color);
}

/** **************************************************************************************
 * \section Multiplexer Analog switch and multiplexer control functions
 */
typedef struct {
    char* name;
    uint8_t mux_controls[4];
    uint8_t mux_status[4];
    uint8_t nb_controls;
} multiplexer;

int NewMux1x8(multiplexer* drv, uint8_t a0, uint8_t a1, uint8_t a2);
int NewMux4SPST(multiplexer* drv, uint8_t a0, uint8_t a1, uint8_t a2,
                uint8_t a3);
int NewMux3SPDT(multiplexer* drv, uint8_t a0, uint8_t a1, uint8_t a2);

int SetMux(multiplexer* drv, uint8_t color);
int SetMuxPos(multiplexer* drv, uint8_t pos, uint8_t value);
int GetMux(multiplexer* drv);
uint8_t GetMuxPos(multiplexer* drv, uint8_t pos);



#endif  //DIGITAL_IO_H