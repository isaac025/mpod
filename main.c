#include <stdio.h>
#include <gpod/itdb.h>
#include <stdlib.h>
#include <glib.h>

/* help: print all commands with description 
 * @cmd if a command name is provided print
 * only that description. 
*/
void help(char* cmd)
{
    if(cmd) {
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
    }
}

/* repl: read eval print loop function */
int repl()
{


    return 0;
}

/* list_tracks: list all tracks on ipod */
void list_tracks(Itdb_iTunesDB* itdb)
{
    if(!itdb) {
        fprintf(stderr, "Failed to load iPod db from %s\n", ipod_path);
        return 1;
    }

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

int main(int argc, char* argv[])
{
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <path-to-ipod>\n", argv[0]);
    }
    const char* ipod_path = argv[1];
    GError** error = NULL;
    Itdb_iTunesDB* itdb = itdb_parse(ipod_path, error);

    while(1) {

    }

    itdb_free(itdb);
    return 0;
}
