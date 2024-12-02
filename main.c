#include <stdio.h>
#include <gpod/itdb.h>
#include <stdlib.h>
#include <glib.h>
#include <readline/readline.h>
#include <readline/history.h>

/* list_tracks: list all tracks on ipod */
void list_tracks(Itdb_iTunesDB* itdb)
{
    GList* tracks = itdb->tracks;
    int count = 1;
    for(GList* iter = tracks; iter != NULL; iter = iter->next) {
        Itdb_Track* track = (Itdb_Track *)iter->data;
        char* track_title = track->title ? track->title : "Unknown Title";
        char* track_artist = track->artist ? track->artist : "Unknown Artist";
        printf("%d. %s - %s\n", count, track_title, track_artist);
        count++;
    }
}

/* help: print all commands with description 
 * @cmd if a command name is provided print
 * only that description. 
*/
void help(char* cmd)
{
/*    if(cmd) {
        switch(cmd) {
            case "help":
                printf("help - print help menu\n");
                break;
            case "list":
                printf("list - list all tracks of ipod\n");
                break;
            case "quit":
                printf("quit - quit mipod\n");
                break;
            default:
                printf("command %s not found\n", cmd);
                break;
        }
    }
    else {
        printf("help - print help menu\n");
        printf("list - list all tracks of ipod\n");
        printf("quit - quit mipod\n");
    }*/
    printf("help - print help menu\n");
    printf("list - list all tracks of ipod\n");
    printf("quit - quit mipod\n");
}

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
        return 1;
    }
    else {
        free(input);
        return 0;
    }
}

int main(int argc, char* argv[])
{
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <path-to-ipod>\n", argv[0]);
    }
    const char* ipod_path = argv[1];
    GError** error = NULL;
    Itdb_iTunesDB* itdb = itdb_parse(ipod_path, error);

    if(!itdb) {
        fprintf(stderr, "Failed to load iPod db from %s\n", ipod_path);
        return 1;
    }

    int repl_result = 1;
    while(repl_result = repl(itdb)); 

    itdb_free(itdb);
    return 0;
}
