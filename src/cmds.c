#include <stdio.h>
#include <gpod/itdb.h>
#include <stdlib.h>
#include <glib.h>

/* add_song: add a song from a file (mp3 file) */
int add_song(char* file);

/* delete_song: delete a track from ipod */
int delete_song(Itdb_Track* song, Itdb_iTunesDB* itdb);

/* play_song: play a track from ipod (use ffmpeg/ffplay) */
void play_song(Itdb_Track* song, Itdb_iTunesDB* itdb);

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

