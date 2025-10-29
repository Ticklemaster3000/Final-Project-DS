#include "../include/Network.h"
#include <string>
using namespace std;

Network::Network() : userConnections(100) {}

//find user by email
int Network::findUserIndexByEmail(const std::string& email) const {
    for (int i = 0; i < (int)users.size(); ++i) {
        if (users[i].getEmail() == email) {
            return i;
        }
    }
    return -1;
}

//add new user
void Network::addUser(const std::string& name, const std::string& email, UserRole role) {
    if (findUserIndexByEmail(email) != -1) {
        std::cout << "Error: User with email " << email << " already exists." << std::endl;
        return;
    }
    if (users.size() >= 100) {
        std::cout << "Error: Maximum number of users reached." << std::endl;
        return;
    }
    users.emplace_back(name, email, role);
    std::cout << "User '" << name << "' added successfully." << std::endl;
}

//show user details
void Network::displayUserProfile(const std::string& email) const {
    int index = findUserIndexByEmail(email);
    if (index != -1) {
        users[index].displayProfile();
    } else {
        std::cout << "Error: User with email " << email << " not found." << std::endl;
    }
}

//list all users
void Network::displayAllUsers() const {
    if (users.empty()) {
        std::cout << "No users in the network." << std::endl;
        return;
    }
    std::cout << "\n--- All Users in Network ---" << std::endl;
    for (const auto& user : users) {
        std::cout << "- " << user.getName() << " (" << user.getEmail() << ")" << std::endl;
    }
    std::cout << "--------------------------" << std::endl;
}

//connect two users
void Network::createConnection(const std::string& email1, const std::string& email2) {
    int index1 = findUserIndexByEmail(email1);
    int index2 = findUserIndexByEmail(email2);

    if (index1 != -1 && index2 != -1) {
        userConnections.addEdge(index1, index2);
        std::cout << "Connection created between " << users[index1].getName()
                  << " and " << users[index2].getName() << "." << std::endl;
    } else {
        if (index1 == -1) std::cout << "Error: User " << email1 << " not found." << std::endl;
        if (index2 == -1) std::cout << "Error: User " << email2 << " not found." << std::endl;
    }
}

//display the connection
void Network::showConnections() const {
    std::cout << "\n=== User Connection Network ===\n";
    bool any = false;

    for (size_t i = 0; i < users.size(); ++i) {
        auto connections = userConnections.getConnectionsOf(i);
        if (!connections.empty()) {
            any = true;
            std::cout << "\n" << users[i].getName() << " (" << users[i].getEmail() << ")\n";
            std::cout << "-> Connected with:\n";

            for (int connectedIndex : connections) {
                std::cout << "      - " << users[connectedIndex].getName()
                          << " (" << users[connectedIndex].getEmail() << ")\n";
            }
        }
    }

    if (!any)
        std::cout << "No user connections found yet.\n";

    std::cout << "===============================\n";
}


void Network::findMusiciansByInstrument(const std::string& instrument) const {
    std::cout << "\nSearching for musicians who play " << instrument << "..." << std::endl;
    std::cout << "(Feature not fully implemented)" << std::endl;
}

std::vector<User> Network::getAllUsers() const {
    return users;
}

User* Network::getUserByEmail(const string& email) {
    for (auto &u : users) {
        if (u.getEmail() == email) return &u;
    }
    return nullptr;
}

void Network::displayUserConnections(const std::string& email) const {
    int index = findUserIndexByEmail(email);
    if (index == -1) {
        std::cout << "Error: User not found.\n";
        return;
    }

    auto connections = userConnections.getConnectionsOf(index);

    std::cout << "\n--- Connections for " << users[index].getName() << " ---" << std::endl;
    if (connections.empty()) {
        std::cout << "No connections found.\n";
        return;
    }

    for (int connectedIndex : connections) {
        std::cout << "- " << users[connectedIndex].getName() 
                  << " (" << users[connectedIndex].getEmail() << ")" << std::endl;
    }
    std::cout << "-------------------------------\n";
}

