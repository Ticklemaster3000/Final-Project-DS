#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <vector>
#include "Song.h"
using namespace std;

struct Location
{
    string name;
    vector<string> song_ids;
};

extern vector<Location> locations;

Location *find_location(const string &name);
Location *add_or_get_location(const string &name);
void link_song_to_location(const string &song_id, const string &loc_name);
vector<string> get_song_ids_in_location(const string &loc_name);

#endif
