#ifndef REGISTRY_H
#define REGISTRY_H

#include <string>
#include <vector>
#include "song.h"

using namespace std;
extern vector<Song> song_registry;
string add_song_reg(const Song &s);
bool has_fp(const string &fp);
Song get_song_by_id(const string &id);
vector<Song> get_all_songs();
vector<Song> find_by_title(const string &title);
bool delete_song_by_id(const string &id, const string &requester);

#endif
