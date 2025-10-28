#include "../include/User.h"
#include <iostream>

// Helper function to convert enums to strings for display
std::string roleToString(UserRole role) {
    switch (role) {
        case UserRole::MUSICIAN: return "Musician";
        case UserRole::BAND: return "Band";
        case UserRole::LISTENER: return "Listener";
        case UserRole::STUDENT: return "Student";
        default: return "Unknown";
    }
}

std::string skillToString(SkillLevel level) {
    switch (level) {
        case SkillLevel::BEGINNER: return "Beginner";
        case SkillLevel::INTERMEDIATE: return "Intermediate";
        case SkillLevel::EXPERT: return "Expert";
        default: return "Not specified";
    }
}

User::User(const std::string& name, const std::string& email, UserRole role)
    : name(name), email(email), role(role), skillLevel(SkillLevel::BEGINNER) {}

std::string User::getName() const { return name; }
std::string User::getEmail() const { return email; }

void User::addInstrument(const std::string& instrument) {
    instrumentsPlayed.push_back(instrument);
}

void User::setSkillLevel(SkillLevel level) {
    skillLevel = level;
}

void User::displayProfile() const {
    std::cout << "\n--- User Profile ---" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Role: " << roleToString(role) << std::endl;
    std::cout << "Skill Level: " << skillToString(skillLevel) << std::endl;

    if (!instrumentsPlayed.empty()) {
        std::cout << "Instruments: ";
        for (const auto& instr : instrumentsPlayed) {
            std::cout << instr << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "--------------------" << std::endl;
}