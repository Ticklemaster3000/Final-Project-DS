# Social Network for Musicians

https://github.com/Ticklemaster3000/Final-Project-DS/tree/main

This is a simple console-based C++ application that simulates a basic social and music-sharing network. Users can register profiles, connect with other users, and manage a registry of songs.

This project was developed to demonstrate the use of core data structures and object-oriented principles, including vectors, lists, and a custom graph implementation.

## Features

* **User Management:** Register a new user with a specific role (Musician, Band, Listener, or Student) and Login.
* **Profile Customization:** Add instruments you play and set your skill level (Beginner, Intermediate, Expert).
* **Social Network:** Connect with other users on the platform using a graph data structure to manage connections.
* **Song Management:** Upload new songs, delete your own songs, view a list of your songs, and view a list of all songs in the registry.
* **Location Linking:** Link your songs to a specific location (e.g., "Nashville", "Appalachia").
* **Search:**
    * Search for other users by name.
    * Search for songs by title.
    * Search for songs by location.

## Getting Started

### Prerequisites

* A C++17 compatible compiler (e.g., `g++`)
* The `make` utility

### Compilation

The project includes a `makefile` for easy compilation. From the root directory, simply run:

```bash
make
