#include <iostream>
#include <string>
#include <vector>
#include "song.h"
#include "registry.h"
#include "location.h"

using namespace std;

int read_choice()     //get user choice
{
    int c;
    if (!(cin >> c))
    {
        cin.clear();
        string dummy;
        getline(cin, dummy);
        return -1;
    }
    string dummy;
    getline(cin, dummy);
    return c;
}
string read_line_prompt(const string &prompt)
{
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}
string make_id()    //generate song id
{
    vector<Song> all = get_all_songs();
    int n = (int)all.size();
    return string("s") + to_string(n + 1);
}

int main()
{
    cout << "Folk Music Archive\n";

    while (true)
    {
        cout << "\nChoose an option:\n";
        cout << "1) Upload / add a song\n";
        cout << "2) Find song by exact title\n";
        cout << "3) List all songs\n";
        cout << "4) Exit\n";
        cout << "5) List songs by location\n";
        cout << "Enter choice: ";
        int choice = read_choice();

        if (choice == 1)    //upload a song
        {
            string title = read_line_prompt("Enter title: ");
            string uploader = read_line_prompt("Enter uploader name/id: ");
            string audio = read_line_prompt("Enter audio file path or URL: ");
            string loc = read_line_prompt("Enter location name: ");

            cout << "Enter duration in seconds: ";
            int dur;
            if (!(cin >> dur))
            {
                cin.clear();
                string dummy;
                getline(cin, dummy);
                cout << "Invalid duration. Song not added.\n";
                continue;
            }
            string dummy;
            getline(cin, dummy);

            Song s;
            s.id = make_id();
            s.title = title;
            s.uploader = uploader;
            s.audio = audio;
            s.duration = dur;

            string res = add_song_reg(s);
            if (res.empty())
                cout << "Song not added — duplicate detected (title+uploader+duration).\n";
            else
            {
                cout << "Added song with id: " << res << "\n";
                link_song_to_location(s.id, loc);
            }
        }
        else if (choice == 2)      //search by title
        {
            string title = read_line_prompt("Enter exact title to search: ");
            vector<Song> found = find_by_title(title);
            if (found.empty())
            {
                cout << "No songs found with that exact title.\n";
            }
            else
            {
                cout << "Found " << found.size() << " result(s):\n";
                for (const Song &x : found)
                {
                    cout << "ID: " << x.id << " | Title: " << x.title
                         << " | Uploader: " << x.uploader << " | Duration: " << x.duration << "s\n";
                }
            }
        }
        else if (choice == 3)       //list all songs
        {
            vector<Song> all = get_all_songs();
            if (all.empty())
            {
                cout << "No songs stored yet.\n";
            }
            else
            {
                cout << "\nAll Songs\n";
                for (const Song &s : all)
                {
                    cout << "ID: " << s.id << "\n";
                    cout << "Title: " << s.title << "\n";
                    cout << "Uploader: " << s.uploader << "\n";
                    cout << "Audio: " << s.audio << "\n";
                    cout << "Duration: " << s.duration << " sec\n\n";
                }
            }
        }
        else if (choice == 4)      //exit
        {
            cout << "Exiting. Bye.\n";
            break;
        }
        else if (choice == 5)     //search by location
        {
            string loc = read_line_prompt("Enter location name to view songs: ");
            vector<string> ids = get_song_ids_in_location(loc);
            if (ids.empty())
            {
                cout << "No songs found for this location.\n";
            }
            else
            {
                cout << "\nSongs from " << loc << ":\n";
                for (const string &id : ids)
                {
                    Song s = get_song_by_id(id);
                    cout << "- " << s.title << " (Uploader: " << s.uploader << ")\n";
                }
            }
        }
        else
        {
            cout << "Invalid choice. Enter 1-5.\n";
        }
    }

    return 0;
}
