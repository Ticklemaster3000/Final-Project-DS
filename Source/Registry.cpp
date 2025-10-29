#include "../include/Registry.h"
using namespace std;

vector<Song> song_registry;

string add_song_reg(const Song &s)
{
    for (const Song &x : song_registry)
    {
        if (x.title == s.title && x.uploader == s.uploader && x.duration == s.duration)
        {
            return "";
        }
    }
    song_registry.push_back(s);
    return s.id;
}

bool has_fp(const string &dummy)
{
    return false;
}

Song get_song_by_id(const string &id)
{
    for (const Song &x : song_registry)
    {
        if (x.id == id)
            return x;
    }
    return Song();
}

vector<Song> get_all_songs()
{
    return song_registry;
}

vector<Song> find_by_title(const string &title)
{
    vector<Song> results;
    string query = "";
    for (char c : title)
        query += (c >= 'A' && c <= 'Z') ? (c + 32) : c;

    for (auto &s : song_registry)
    {
        string lowerTitle = "";
        for (char c : s.title)
            lowerTitle += (c >= 'A' && c <= 'Z') ? (c + 32) : c;

        bool found = false;
        for (size_t i = 0; i + query.size() <= lowerTitle.size(); i++)
        {
            bool match = true;
            for (size_t j = 0; j < query.size(); j++)
            {
                if (lowerTitle[i + j] != query[j])
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
            results.push_back(s);
    }
    return results;
}

bool delete_song_by_id(const string &id, const string &requester)
{
    for (auto it = song_registry.begin(); it != song_registry.end(); ++it)
    {
        if (it->id == id)
        {
            if (it->uploader == requester)
            {
                song_registry.erase(it);
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}
