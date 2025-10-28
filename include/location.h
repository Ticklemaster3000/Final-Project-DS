#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <vector>
#include "song.h"
using namespace std;
struct Location
{
    string name;
    vector<string> song_ids;
};
static vector<Location> locations;
Location *find_location(const string &name)
{
    for (auto &loc : locations)
    {
        if (loc.name == name)
            return &loc;
    }
    return nullptr;
}

Location *add_or_get_location(const string &name)
{
    Location *loc = find_location(name);
    if (loc)
        return loc;
    Location newLoc;
    newLoc.name = name;
    locations.push_back(newLoc);
    return &locations.back();
}

void link_song_to_location(const string &song_id, const string &loc_name)
{
    Location *loc = add_or_get_location(loc_name);
    loc->song_ids.push_back(song_id);
}

vector<string> get_song_ids_in_location(const string &loc_name)
{
    Location *loc = find_location(loc_name);
    if (!loc)
        return {};
    return loc->song_ids;
}

#endif
