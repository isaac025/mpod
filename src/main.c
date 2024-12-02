#include <stdio.h>
#include <gpod/itdb.h>
#include <stdlib.h>
#include <glib.h>

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
