#include <iostream>
#include <string>
#include <vector>
#include "include/Network.h"
#include "include/registry.h"
#include "include/location.h"
using namespace std;

User* currentUser = nullptr;
Network network;

UserRole selectRole() {
    int roleChoice;
    cout << "Select role (1=Musician, 2=Band, 3=Listener, 4=Student): ";
    cin >> roleChoice;
    cin.ignore();
    if (roleChoice == 2) return UserRole::BAND;
    if (roleChoice == 3) return UserRole::LISTENER;
    if (roleChoice == 4) return UserRole::STUDENT;
    return UserRole::MUSICIAN;
}

void registerUser() {
    string name, email;
    cout << "Enter name: ";
    getline(cin, name);
    cout << "Enter email: ";
    getline(cin, email);
    UserRole role = selectRole();
    network.addUser(name, email, role);
}

void loginUser() {
    string email;
    cout << "Enter email: ";
    getline(cin, email);
    currentUser = network.getUserByEmail(email);
    if (currentUser)
        cout << "Logged in as " << currentUser->getName() << endl;
    else
        cout << "No such user. Please register first.\n";
}

void uploadSong(User& user) {
    Song s;
    cout << "Song ID: ";
    getline(cin, s.id);
    cout << "Title: ";
    getline(cin, s.title);
    s.uploader = user.getName();
    cout << "Audio file: ";
    getline(cin, s.audio);
    cout << "Duration (sec): ";
    cin >> s.duration;
    cin.ignore();
    string id = add_song_reg(s);
    if (id.empty()) cout << "Duplicate song.\n";
    else cout << "Song uploaded.\n";
}

void deleteSong(User& user) {
    string id;
    cout << "Enter song ID to delete: ";
    getline(cin, id);
    Song s = get_song_by_id(id);
    if (s.id.empty()) { cout << "No results found.\n"; return; }
    bool ok = delete_song_by_id(id, user.getName());
    if (ok) cout << "Song deleted successfully.\n";
    else cout << "Failed: either not found or you are not the uploader.\n";
}

void viewMySongs(User& user) {
    vector<Song> songs = get_all_songs();
    bool found = false;
    for (auto& s : songs) {
        if (s.uploader == user.getName()) {
            cout << "ID: " << s.id << " | Title: " << s.title << endl;
            found = true;
        }
    }
    if (!found) cout << "No results found.\n";
}

void viewAllSongs() {
    vector<Song> songs = get_all_songs();
    if (songs.empty()) { cout << "No results found.\n"; return; }
    for (auto& s : songs)
        cout << "ID: " << s.id << " | Title: " << s.title << " | Uploader: " << s.uploader << endl;
}

void searchSongsByTitle() {
    string query;
    cout << "Enter part of the title to search: ";
    getline(cin, query);
    vector<Song> all = get_all_songs();
    vector<Song> matches;
    string q;
    for (char c : query) q += (c >= 'A' && c <= 'Z') ? c + 32 : c;
    for (auto& s : all) {
        string t;
        for (char c : s.title) t += (c >= 'A' && c <= 'Z') ? c + 32 : c;
        bool found = false;
        if (q.empty()) found = true;
        else {
            for (size_t i = 0; i + q.size() <= t.size(); i++) {
                bool match = true;
                for (size_t j = 0; j < q.size(); j++) {
                    if (t[i + j] != q[j]) { match = false; break; }
                }
                if (match) { found = true; break; }
            }
        }
        if (found) matches.push_back(s);
    }
    if (matches.empty()) cout << "No results found.\n";
    else for (auto& s : matches)
        cout << "ID: " << s.id << " | Title: " << s.title << " | Uploader: " << s.uploader << endl;
}

void linkSongToLocation(User& user) {
    string song_id, loc;
    cout << "Enter your song ID: ";
    getline(cin, song_id);
    Song s = get_song_by_id(song_id);
    if (s.id.empty()) { cout << "No results found.\n"; return; }
    if (s.uploader != user.getName()) { cout << "You can only link your own songs.\n"; return; }
    cout << "Enter location: ";
    getline(cin, loc);
    link_song_to_location(song_id, loc);
    cout << "Linked successfully.\n";
}

void searchSongsByLocation() {
    string query;
    cout << "Enter part of the location name: ";
    getline(cin, query);
    string q;
    for (char c : query) q += (c >= 'A' && c <= 'Z') ? c + 32 : c;
    vector<string> matchedIds;
    for (auto& loc : locations) {
        string name;
        for (char c : loc.name) name += (c >= 'A' && c <= 'Z') ? c + 32 : c;
        bool match = false;
        if (q.empty()) match = true;
        else {
            for (size_t i = 0; i + q.size() <= name.size(); i++) {
                bool ok = true;
                for (size_t j = 0; j < q.size(); j++) {
                    if (name[i + j] != q[j]) { ok = false; break; }
                }
                if (ok) { match = true; break; }
            }
        }
        if (match) matchedIds.insert(matchedIds.end(), loc.song_ids.begin(), loc.song_ids.end());
    }
    if (matchedIds.empty()) { cout << "No results found.\n"; return; }
    for (auto& id : matchedIds) {
        Song s = get_song_by_id(id);
        if (!s.id.empty()) cout << "ID: " << s.id << " | Title: " << s.title << " | Uploader: " << s.uploader << endl;
    }
}

void addInstrument(User& user) {
    string instr;
    cout << "Instrument: ";
    getline(cin, instr);
    user.addInstrument(instr);
    cout << "Instrument added.\n";
}

void setSkillLevel(User& user) {
    int lvl;
    cout << "Skill (1=Beginner,2=Intermediate,3=Expert): ";
    cin >> lvl;
    cin.ignore();
    if (lvl < 1 || lvl > 3) { cout << "Invalid choice.\n"; return; }
    user.setSkillLevel(static_cast<SkillLevel>(lvl - 1));
    cout << "Skill level set.\n";
}

void searchUserDetails() {
    string query;
    cout << "Enter part of the user's name: ";
    getline(cin, query);
    string q;
    for (char c : query) q += (c >= 'A' && c <= 'Z') ? c + 32 : c;
    const vector<User>& all = network.getAllUsers();
    bool found = false;
    for (const auto& u : all) {
        string name;
        for (char c : u.getName()) name += (c >= 'A' && c <= 'Z') ? c + 32 : c;
        bool match = false;
        if (q.empty()) match = true;
        else {
            for (size_t i = 0; i + q.size() <= name.size(); i++) {
                bool ok = true;
                for (size_t j = 0; j < q.size(); j++) {
                    if (name[i + j] != q[j]) { ok = false; break; }
                }
                if (ok) { match = true; break; }
            }
        }
        if (match) { u.displayProfile(); found = true; }
    }
    if (!found) cout << "No results found.\n";
}

void musicianMenu(User& user) {
    int choice;
    while (true) {
        cout << "\n===== MAIN MENU =====\n";
        cout << "----- USER FUNCTIONS -----\n";
        cout << "1. View Profile\n";
        cout << "2. Add Instrument\n";
        cout << "3. Set Skill Level\n";
        cout << "4. Connect with Another User\n";
        cout << "5. Search User Details\n";
        cout << "----- SONG FUNCTIONS -----\n";
        cout << "6. Upload Song\n";
        cout << "7. Delete Song\n";
        cout << "8. View My Songs\n";
        cout << "9. View All Songs\n";
        cout << "10. Search Songs by Title\n";
        cout << "----- LOCATION FUNCTIONS -----\n";
        cout << "11. Link Song to Location\n";
        cout << "12. Search Songs by Location\n";
        cout << "13. View My Connections\n";
        cout << "----- OTHER -----\n";
        cout << "0. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        if (choice == 0) break;
        if (choice == 1) user.displayProfile();
        else if (choice == 2) addInstrument(user);
        else if (choice == 3) setSkillLevel(user);
        else if (choice == 4) {
            string other;
            cout << "Enter email to connect: ";
            getline(cin, other);
            network.createConnection(user.getEmail(), other);
        }
        else if (choice == 5) searchUserDetails();
        else if (choice == 6) uploadSong(user);
        else if (choice == 7) deleteSong(user);
        else if (choice == 8) viewMySongs(user);
        else if (choice == 9) viewAllSongs();
        else if (choice == 10) searchSongsByTitle();
        else if (choice == 11) linkSongToLocation(user);
        else if (choice == 12) searchSongsByLocation();
        else if (choice == 13) network.displayUserConnections(user.getEmail());
    }
}

int main() {
    int mainChoice;
    while (true) {
        cout << "\n===== WELCOME TO MUSIC NETWORK =====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. View All Connections\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> mainChoice;
        cin.ignore();
        if (mainChoice == 0) break;
        else if (mainChoice == 1) registerUser();
        else if (mainChoice == 2) {
            loginUser();
            if (currentUser) musicianMenu(*currentUser);
            currentUser = nullptr;
        }
        else if (mainChoice == 3) network.showConnections();
    }
    cout << "Goodbye.\n";
    return 0;
}
