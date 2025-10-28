#ifndef NETWORK_H
#define NETWORK_H

#include "User.h"
#include "Graph.h"
#include <vector>
#include <string>

// The Network class manages all users and their connections.
class Network {
public:
    Network();

    // User Management
    void addUser(const std::string& name, const std::string& email, UserRole role);
    void displayUserProfile(const std::string& email) const;
    void displayAllUsers() const;

    // Connection Management
    void createConnection(const std::string& email1, const std::string& email2);
    void showConnections() const;
    
    // Search & Filtering
    void findMusiciansByInstrument(const std::string& instrument) const;

    // Getter
    std::vector<User> getAllUsers() const;
    User* getUserByEmail(const std::string& email);

private:
    std::vector<User> users;
    Graph userConnections;

    // Helper function to find a user's index by their email.
    int findUserIndexByEmail(const std::string& email) const; // returns -1 if not found
};

#endif // NETWORK_H
