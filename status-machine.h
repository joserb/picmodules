#ifndef STATUSMACHINE_H
#define STATUSMACHINE_H

#include <xc.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_STATES 16

typedef int (* stFunction)(int code);

typedef struct {
    int state_code;
    stFunction function;
} stateCallback;

typedef struct {
    char* name;
    stateCallback stateList[MAX_STATES];
    uint8_t nStates;
    stFunction defaultAction; // Pointer to the default handler function
} StatusMachine;

void StatusMachineConstructor(StatusMachine* stm);
int addState(StatusMachine* stm, int state_code, stFunction function);
void setDefaultStateHandler(StatusMachine* stm,  stFunction function);
int statusMachine(StatusMachine* stm, int status, int param);


#endif //STATUSMACHINE_H