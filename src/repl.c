#include <stdio.h>
#include <gpod/itdb.h>
#include <stdlib.h>
#include <glib.h>
#include <readline/readline.h>
#include <readline/history.h>

#define REPL_SUCCESS 1
#define REPL_FAILURE -1

/* help: print all commands with description 
 * @cmd if a command name is provided print
 * only that description. 
*/
void help(char* cmd)
{
    printf("help - print help menu\n");
    printf("list - list all tracks of ipod\n");
    printf("quit - quit mipod\n");
}

/* parse_cmd: parse a cmd from the repl.
 * @cmd the command to parse
 * @itdb the iPod's database (iTunes)
*/
int parse_cmd(char* cmd, Itdb_iTunesDB* itdb)
{
    if(strcmp(cmd, "help") == 0) {
        help(NULL);
        return 1;
    }
    else if(strcmp(cmd, "list") == 0) {
        list_tracks(itdb);
        return 1;
    }

    else if(strcmp(cmd, "quit") == 0) {
        return 0;
    }
    else {
        printf("Command %s not found\n", cmd);
        return 1;
    }
}

/* repl: read eval print loop function */
int repl(Itdb_iTunesDB* itdb)
{
    char* input = readline("mpod> ");
    if(parse_cmd(input, itdb)) {
        free(input);
        return REPL_SUCCESS;
    }
    else {
        free(input);
        return REPL_FAILURE;
    }
}
