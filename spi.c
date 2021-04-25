/**
* \file spi.c
* \brief Generic functions for SPI peripherals
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

#include "spi.h"

int SpiSlaveGets(SPI_Driver* port, BYTE* buffer) {
    int nchars=0;

    while (available(&port->dev.src)) {
        buffer[nchars]=(BYTE)read(&port->dev.src);
        nchars++;
    }

    return nchars;
}

inline BYTE spi_slave_default_handler(BYTE c) {
    return c;
}

int spi_default_cs(spi_device* dev, BYTE cs) {
    return 0;
}

