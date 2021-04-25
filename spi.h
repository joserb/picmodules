/*
 * File:   Spi.h
 * Author: Jose
 *
 * Created on 22 de abril de 2020, 18:15
 */

#ifndef SPI_H
#define	SPI_H

#include <stdint.h>
#include "stream.h"

enum SPI_DATAMODES_1 {
    CLOW_FALLING,
    CLOW_RISING,
    CHIGH_RISING,
    CHIGH_FALLING
};

enum SPI_DATAMODES_2 {
    SPI_MODE0,
    SPI_MODE1,
    SPI_MODE2,
    SPI_MODE3
};


enum SPI_CLOCK_DIVIDERS {
    SPI_CLK_64,
    SPI_CLK_16,
    SPI_CLK_4,
    SPI_CLK_1
};

#define SPI_TX_BUFF_SIZE    200

typedef struct {
    Stream src;
    int bitorder;
    int datamode;
    int clockdivider;
    int endframe;
    BYTE buf_out[BUFF_CMD_SIZE];
    int buf_out_cnt;
} spi_device;

typedef struct {
    int (*begin)(spi_device* dev, int spi_mode);
    int (*begintransaction)(spi_device* dev);
    int (*transfer)(spi_device* dev, BYTE* buf_write, BYTE* buf_read, size_t len);
    int (*chip_select)(spi_device* dev, BYTE cs);
    BYTE (*interrupt_handler)(BYTE in_char);
} spi_ops;

typedef struct {
    spi_device dev;
    spi_ops ops;
} SPI_Driver;

inline static int SpiBegin(SPI_Driver* port, int spi_mode) {
    return port->ops.begin(&port->dev, spi_mode);
}
inline static int SpiBeginTransaction(SPI_Driver* port) {
    return port->ops.begintransaction(&port->dev);
}
inline static int SpiTransfer(SPI_Driver* port, BYTE* buf_write, BYTE* buf_read,
                              size_t len) {
    return port->ops.transfer(&port->dev, buf_write, buf_read, len);
}
inline static int SpiChipSelect(SPI_Driver* port, BYTE cs) {
    return port->ops.chip_select(&port->dev, cs);
}

inline static void SpiSetBitorder(SPI_Driver* port, int order) {
    port->dev.bitorder = order;
}
inline static void SpiSetDatamode(SPI_Driver* port, int mode) {
    port->dev.datamode = mode;
}
inline static void SpiSetClockDivider(SPI_Driver* port, int divider) {
    port->dev.clockdivider = divider;
}
inline static int SpiSlaveAvailable(SPI_Driver* port) {
    return available(&port->dev.src);
}

int SpiSlaveGets(SPI_Driver* port, BYTE* buffer);
inline BYTE spi_slave_default_handler(BYTE c);
int spi_default_cs(spi_device* dev, BYTE cs);

#endif	/* SPI_H */

