/**
* \file status-machine.c
* \brief Generic handler for organizing Status-Machine logics
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
* \date     19/05/2020
*
*/

#include "status-machine.h"

/**
 * Constructor makes sure some things are set.
 */
void StatusMachineConstructor(StatusMachine* stm) {
    stm->name = "Default St-M.";
    stm->nStates = 0;
    stm->defaultAction = NULL;
}

/**
 * Adds a new function and makes it corresponding to a certain state number
 */
int addState(StatusMachine* stm, int state_code, stFunction function) {
    if (stm->nStates >= MAX_STATES) {
        return 1;
    }

    stm->stateList[stm->nStates].state_code = state_code;
    stm->stateList[stm->nStates].function = function;
    stm->nStates++;
    return 0;
}

/**
 * This sets up a function to be called when active state is not defined
 */
void setDefaultStateHandler(StatusMachine* stm,  stFunction function) {
    stm->defaultAction = function;
}

/**
 * This function executes the function associated to the active machine-state
 */
int statusMachine(StatusMachine* stm, int status, int param) {
    bool st_found = 0;
    int i;
    int resp = 0;

    for (i = 0; i < stm->nStates; i++) {
        if (status == stm->stateList[i].state_code) {
            st_found = 1;
            resp = stm->stateList[i].function(param);
            break;
        }
    }

    if (!st_found && (stm->defaultAction != NULL)) {
        resp = stm->defaultAction(param);
    }

    return resp;
}

