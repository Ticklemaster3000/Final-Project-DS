#ifndef NETWORK_H
#define NETWORK_H

#include "User.h"
#include "Graph.h"
#include <vector>
#include <string>

class Network {
public:
    Network();

    void addUser(const std::string& name, const std::string& email, UserRole role);
    void displayUserProfile(const std::string& email) const;
    void displayAllUsers() const;

    void createConnection(const std::string& email1, const std::string& email2);
    void showConnections() const;
    
    void findMusiciansByInstrument(const std::string& instrument) const;
    void displayUserConnections(const std::string& email) const;

    // Getter
    std::vector<User> getAllUsers() const;
    User* getUserByEmail(const std::string& email);

private:
    std::vector<User> users;
    Graph userConnections;

    int findUserIndexByEmail(const std::string& email) const; // returns -1 if not found
};

#endif 
