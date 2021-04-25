#ifndef SERIAL_H
#define SERIAL_H

#include <xc.h>
#include <stdio.h>
#include <stdarg.h>
#include "stream.h"

typedef struct {
    Stream src;
    long baudsetting;
    int overrun;
} serial_device;

typedef struct {
    void (*begin)(serial_device* dev, long speed);
    int (*puts)(serial_device* dev, const char* text);
    int (*nputs)(serial_device* dev, const char*, int length);
    int (*printf)(serial_device* dev, const char* str, ...);

} serial_ops;

typedef struct {
    serial_device dev;
    serial_ops ops;
} Serial;


inline static int SerialPrintf(Serial* port, const char* str, ...) {
    char str_format[255];
    va_list args;
    va_start(args, str);
    vsprintf(str_format, str, args);
    va_end(args);
    return port->ops.puts(&port->dev, str_format);
}

inline static void SerialBegin(Serial* port, long speed) {
    port->ops.begin(&port->dev, speed);
}
inline static int SerialPuts(Serial* port, const char* text) {
    return port->ops.puts(&port->dev, text);
}
inline static int SerialNPuts(Serial* port, const char* text, int length) {
    return port->ops.nputs(&port->dev, text, length);
}
inline static int SerialRead(Serial* port) {
    return read(&port->dev.src);
}
inline static int SerialAvailable(Serial* port) {
    return available(&port->dev.src);
}

int SerialGets(Serial* port, char* text);

#endif  // SERIAL_H

