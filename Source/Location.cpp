#include "location.h"
#include "song.h"
#include <string>
#include <vector>

std::vector<Location> locations; // Definition of global variable

Location* find_location(const string &name)
{
    // convert search query to lowercase
    string query = "";
    for (char c : name)
        query += (c >= 'A' && c <= 'Z') ? c + 32 : c;

    for (auto &loc : locations)
    {
        string lowerName = "";
        for (char c : loc.name)
            lowerName += (c >= 'A' && c <= 'Z') ? c + 32 : c;

        // manual substring search
        bool found = false;
        for (size_t i = 0; i + query.size() <= lowerName.size(); i++)
        {
            bool match = true;
            for (size_t j = 0; j < query.size(); j++)
            {
                if (lowerName[i + j] != query[j])
                {
                    match = false;
                    break;
                }
            }
            if (match)
            {
                found = true;
                break;
            }
        }

        if (found)
            return &loc;
    }

    return nullptr;
}

vector<string> get_song_ids_in_location(const string &loc_name)
{
    Location* loc = find_location(loc_name);
    if (!loc)
        return {};
    return loc->song_ids;
}


Location *add_or_get_location(const std::string &name)
{
    Location *loc = find_location(name);
    if (loc)
        return loc;
    Location newLoc;
    newLoc.name = name;
    locations.push_back(newLoc);
    return &locations.back();
}

void link_song_to_location(const std::string &song_id, const std::string &loc_name)
{
    Location *loc = add_or_get_location(loc_name);
    loc->song_ids.push_back(song_id);
}

