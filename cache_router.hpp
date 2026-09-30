#pragma once

#include <string>
#include <unordered_map>

#include "consistent_hash_ring.hpp"
#include "server.hpp"

class CacheRouter
{
    public:
    void addServer(const std::string& serverName);

    void put(const std::string& key, const std::string& value);

    std::string get(const std::string& key);

    void showRing() const;

    void showServers() const;

    bool removeServer(const std::string& serverName);

    private:
    ConsistentHashRing ring_;

    std::unordered_map<std::string, Server> servers_;

    void remapKeys();
};