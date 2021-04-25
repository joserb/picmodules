#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <xc.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_CMD_SIZE 32
#define MAX_COMMANDS 64

#define DEFAULT_END_CHAR ';'
#define DEFAULT_HDR_SIZE 1
#define DFAULT_COMMAND_SIZE 1

typedef int (* cbFunction)(char* param, int len, char* response);

typedef struct {
    char header[2];
    cbFunction function;
} commandCallback;

typedef struct {
    char* name;
    commandCallback commandList[MAX_COMMANDS];
    uint8_t nCommands;
    cbFunction defaultHandler; // Pointer to the default handler function
    char buffer[MAX_CMD_SIZE];
    int bufPos;
    uint8_t command_size;
    uint8_t hdr_size;
    char end_char;
} CommandHandler;

void CommandHandlerConstructor(CommandHandler* cmd);
int processCommand(CommandHandler* cmd, char* command, char* response);
int processCommandLen(CommandHandler* cmd, char* command, int length,
                      char* response);
int addCommand(CommandHandler* cmd, const char* header, cbFunction function);
void setDefaultHandler(CommandHandler* cmd, cbFunction function);



#endif //COMMANDHANDLER_H