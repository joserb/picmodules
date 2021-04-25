/**
* \file stream.c
* \brief General functions concerning streaming communications- (R) Metrohm DropSens S.L.
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
* \date     26/04/2020
*
*/

#include "stream.h"

int available(Stream* src) {
    return (unsigned int) ((BUFF_SIZE + src->windex - src->rindex) % BUFF_SIZE);
}

int append(Stream* src, char c) {
    size_t newindex = src->windex;
    newindex += 1;
    newindex %= BUFF_SIZE;

    if (newindex != src->rindex) {
        src->buffer[src->windex] = c;
        src->windex = newindex;
        return 0;
    } else {
        return -1;  //write overrun
    }
}

BYTE read(Stream* src) {
    BYTE c;

    if (src->windex != src->rindex) {
        c = src->buffer[src->rindex];
        src->rindex += 1;
        src->rindex %= BUFF_SIZE;
        return c;
    } else {
        return 0;
    }
}


BYTE peek(Stream* src) {
    if (src->windex != src->rindex) {
        return src->buffer[src->rindex];
    } else {
        return 0;
    }
}

// private method to read stream with timeout
BYTE timedRead(Stream* src) {
    BYTE c;
    int _startMillis = PARSE_TIMEOUT;

    do {
        c = read(src);

        if (c >= 0)
            return c;
        else {
            _startMillis--;
            delay(1);
        }
    } while (_startMillis>0);

    return 0;
}

// private method to peek stream with timeout
BYTE timedPeek(Stream* src) {
    BYTE c;
    int _startMillis = PARSE_TIMEOUT;

    do {
        c = peek(src);

        if (c >= 0)
            return c;
        else {
            _startMillis--;
            delay(1);
        }
    } while (_startMillis>0);

    return 0;
}

// returns peek of the next digit in the stream or -1 if timeout
// discards non-numeric characters
BYTE peekNextDigit(Stream* src) {
    BYTE c;

    while (1) {
        c = timedPeek(src);

        if (c < 0)
            return c;  // timeout

        if (c == '-')
            return c;

        if (c >= '0' && c <= '9')
            return c;

        read(src);  // discard non-numeric
    }
}


bool findUntil(Stream* src, const char* target, size_t targetLen,
               const char* terminate, size_t termLen) {
    size_t index = 0;  // maximum target string length is 64k bytes!
    size_t termIndex = 0;
    BYTE c;

    if (*target == 0)
        return true;   // return true if target is a null string

    while ((c = timedRead(src)) > 0) {
        if (c != target[index])
            index = 0; // reset index if any char does not match

        if (c == target[index]) {
            if (++index >= targetLen) { // return true if all chars in the target match
                return true;
            }
        }

        if (termLen > 0 && c == terminate[termIndex]) {
            if (++termIndex >= termLen)
                return false;       // return false if terminate string found before target string
        } else
            termIndex = 0;
    }

    return false;
}

// reads data from the stream until the target string of given length is found
// returns true if target string is found, false if timed out
bool find(Stream* src, const char* target, size_t length) {
    return findUntil(src, target, length, NULL, 0);
}

// read characters from stream into buffer
// terminates if length characters have been read, or timeout (see setTimeout)
// returns the number of characters placed in the buffer
// the buffer is NOT null terminated.
//
size_t readBytes(Stream* src, char* buffer, size_t length) {
    size_t count = 0;

    while (count < length) {
        BYTE c = timedRead(src);

        if (c < 0)
            break;

        *buffer++ = (char) c;
        count++;
    }

    return count;
}

// as readBytes with terminator character
// terminates if length characters have been read, timeout, or if the terminator character  detected
// returns the number of characters placed in the buffer (0 means no valid data found)
size_t readBytesUntil(Stream* src, char terminator, char* buffer,
                      size_t length) {
    if (length < 1)
        return 0;

    size_t index = 0;

    while (index < length) {
        BYTE c = timedRead(src);

        if (c < 0 || c == terminator)
            break;

        *buffer++ = (char) c;
        index++;
    }

    return index; // return number of characters, not including null terminator
}


// as above but a given skipChar is ignored
// this allows format characters (typically commas) in values to be ignored
long parseInt(Stream* src) {
    bool isNegative = false;
    long value = 0;
    BYTE c;
    c = peekNextDigit(src);

    // ignore non numeric leading characters
    if (c < 0)
        return 0; // zero returned if timeout

    do {
        if (c == '-')
            isNegative = true;
        else if (c >= '0' && c <= '9')       // is c a digit?
            value = value * 10 + c - '0';

        read(src);  // consume the character we got with peek
        c = timedPeek(src);
    } while (c >= '0' && c <= '9');

    if (isNegative)
        value = -value;

    return value;
}

// as above but the given skipChar is ignored
// this allows format characters (typically commas) in values to be ignored
float parseFloat(Stream* src) {
    bool isNegative = false;
    bool isFraction = false;
    long value = 0;
    BYTE c;
    float fraction = 1.0;
    c = peekNextDigit(src);

    // ignore non numeric leading characters
    if (c < 0)
        return 0; // zero returned if timeout

    do {
        if (c == '-')
            isNegative = true;
        else if (c == '.')
            isFraction = true;
        else if (c >= '0' && c <= '9') {     // is c a digit?
            value = value * 10 + c - '0';

            if (isFraction)
                fraction *= 0.1;
        }

        read(src);  // consume the character we got with peek
        c = timedPeek(src);
    } while ((c >= '0' && c <= '9') || c == '.');

    if (isNegative)
        value = -value;

    if (isFraction)
        return value * fraction;
    else
        return value;
}