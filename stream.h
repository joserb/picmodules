

// This is a guard condition so that contents of this file are not included
// more than once.
#ifndef STREAM_H
#define	STREAM_H

#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "../Common/GenericTypeDefs.h"
#include "../dspic-common.h"

#define BUFF_SIZE 1024
#define BUFF_CMD_SIZE 512
#define PARSE_TIMEOUT 1000  // default number of milli-seconds to wait

typedef size_t uint16_t;

typedef struct {
    char* name;
    volatile BYTE buffer[BUFF_SIZE];
    volatile size_t windex;
    volatile size_t rindex;
} Stream;

bool find(Stream* src, const char* target, size_t length);
bool findUntil(Stream* src, const char* target, size_t targetLen,
               const char* terminate, size_t termLen);
long parseInt(Stream* src);
float parseFloat(Stream* src);
size_t readBytes(Stream* src, char* buffer, size_t length);
size_t readBytesUntil(Stream* src, char terminator, char* buffer,
                      size_t length);
int available(Stream* src);

BYTE read(Stream* src);
BYTE peek(Stream* src);
BYTE timedRead(Stream* src);
BYTE timedPeek(Stream* src);
uint8_t peekNextDigit(Stream* src);
int append(Stream* src, char c);

#endif	/* STREAM_H */

