#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <vector>

enum class UserRole {
    MUSICIAN,
    BAND,
    LISTENER,
    STUDENT
};

enum class SkillLevel {
    BEGINNER,
    INTERMEDIATE,
    EXPERT
};

class User {
public:
    //Constructors
    User(const std::string& name, const std::string& email, UserRole role);

    //Public Methods
    void displayProfile() const;
    void addInstrument(const std::string& instrument);
    void setSkillLevel(SkillLevel level);

    //Getters
    std::string getName() const;
    std::string getEmail() const;

private:
    std::string name;
    std::string email; 
    std::string phone; // Optional
    UserRole role;

    std::vector<std::string> instrumentsPlayed;
    SkillLevel skillLevel;
};

#endif
