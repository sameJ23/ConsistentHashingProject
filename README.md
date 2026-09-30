# Distributed Cache Router using Consistent Hashing

## Overview

A C++ command-line distributed cache simulator that uses consistent hashing to route keys to servers. It supports adding/removing servers and automatically remapping existing keys when server ownership changes. Servers are simulated as objects within the program rather than real networked machines.

## Features

- Adds/Removes cache servers
- Store key/value pairs
- Retrieve values by key
- Display the consistent hash ring
- Display the contents of each server
- Automatically remap affected keys when servers are added or removed

## Project Structure

- `main.cpp` - handles the command-line interface and user commands
- `consistent_hash_ring.hpp/.cpp` - implements the consistent hash ring and server lookup
- `cache_router.hpp/.cpp` - routes cache operations and manages servers/remapping
- `server.hpp/cpp` - represents an individual cache server and stores key/value pairs

## Requirements

- C++17 compatible compiler
- Tested using g++

## Build

From the project directory:

```bash
g++ main.cpp consistent_hash_ring.cpp server.cpp cache_router.cpp -o hash_ring
```
## Run

On Windows:
```
.\hash_ring.exe
```

On Linux/macOS:
```
.\hash_ring
```

## Commands

```
add-server <name>
remove-server <name>
put <key> <value>
get <key>
show-ring
show-servers
help
quit
```

## Example Usage

```
> add-server ServerA
Added ServerA

> add-server ServerB
Added ServerB

> put user_123 James
user_123 routed to ServerB

> get user_123
user_123 -> James

> show-servers
```

When a key is stored, it is hashed and routed to the first server clockwise from its hash position on the ring. If servers are added or removed, affected keys are remapped to their new server.

## How Consisten Hashing Is Used

Server names and cache keys are hashed into the smae hash space using std::hash<std::string>.
Server positions are stored in an ordered std::map.

When a key needs to be routed, std::map::lower_bound() is used to find the first server at or after the key's hash position. If the search reaches the end of the map, it wraps back to begin().

The hash ring only stores server positions. The actual key/value pairs are stored inside each server object's std::unordered_map

## Limitations

- Servers are simulated as objects within one program rather than real networked machines.
- Each server has one position on the hash ring.
- Load distribution was not formally benchmarked.

## Video Walkthrough

A short video walkthrough of my implementation is available below:

https://www.youtube.com/watch?v=2X2Hlevb-Es
