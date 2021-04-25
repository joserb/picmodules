/**
* \file command-handler.c
* \brief Generic handler for managing serial I/O communications
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
* \date     01/05/2020
*
*/

#include "command-handler.h"



/**
 * Constructor makes sure some things are set.
 */
void CommandHandlerConstructor(CommandHandler* cmd) {
    cmd->name = "generic hnd.";
    cmd->nCommands = 0;
    cmd->bufPos = 0;
    cmd->defaultHandler = NULL;
    cmd->hdr_size = DEFAULT_HDR_SIZE;
    cmd->end_char = DEFAULT_END_CHAR;
    cmd->command_size = DFAULT_COMMAND_SIZE;
}

/**
 * Adds a "command" and a handler function to the list of available commands.
 * This is used for matching a found token in the buffer, and gives the pointer
 * to the handler function to deal with it.
 */
int addCommand(CommandHandler* cmd, const char* header, cbFunction function) {
    if (cmd->nCommands >= MAX_COMMANDS) {
        return 1;
    }

    strncpy(cmd->commandList[cmd->nCommands].header, header, cmd->command_size);
    cmd->commandList[cmd->nCommands].function = function;
    cmd->nCommands++;
    return 0;
}

/**
 * This sets up a handler to be called in the event that the receveived command string
 * isn't in the list of commands.
 */
void setDefaultHandler(CommandHandler* cmd, cbFunction function) {
    cmd->defaultHandler = function;
}

/**
 * This checks the Serial stream for characters, and assembles them into a buffer.
 * When the terminator character (default '\n') is seen, it starts parsing the
 * buffer for a prefix command, and calls handlers setup by addCommand() member
 */
int processCommand(CommandHandler* cmd, char* command, char* response) {
    bool cmd_found = 0;
    int i;
    int param_len = 0;
    int resp_len = 0;
    char* newcommand, *param;
    newcommand = command + cmd->hdr_size;
    param = command + cmd->hdr_size + cmd->command_size;

    for (i=0, param_len=0; i<MAX_CMD_SIZE; i++, param_len++) {
        if (*(param+i)==cmd->end_char)
            break;
    }

    for (i = 0; i < cmd->nCommands; i++) {
        if (strncmp(cmd->commandList[i].header, newcommand, cmd->command_size) == 0) {
            cmd_found = 1;
            resp_len = cmd->commandList[i].function(param, param_len, response);
            break;
        }
    }

    if (!cmd_found && (cmd->defaultHandler != NULL)) {
        resp_len = cmd->defaultHandler(param, 0, response);
    }

    return resp_len;
}

/**
 * This checks the Serial stream for characters, and assembles them into a buffer.
 * It starts parsing the buffer for a prefix command, and calls handlers setup by
 * addCommand() member
 */
int processCommandLen(CommandHandler* cmd, char* command, int length,
                      char* response) {
    bool cmd_found = 0;
    int i;
    uint8_t param_len = 0;
    int resp_len = 0;
    char* newcommand, *param;
    newcommand = command + cmd->hdr_size;
    param = command + cmd->hdr_size + cmd->command_size;
    param_len = length - cmd->hdr_size - cmd->command_size;

    for (i = 0; i < cmd->nCommands; i++) {
        if (strncmp(cmd->commandList[i].header, newcommand, cmd->command_size) == 0) {
            cmd_found = 1;
            resp_len = cmd->commandList[i].function(param, param_len, response);
            break;
        }
    }

    if (!cmd_found && (cmd->defaultHandler != NULL)) {
        resp_len = cmd->defaultHandler(param, 0, response);
    }

    return resp_len;
}