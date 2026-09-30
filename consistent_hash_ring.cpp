#include "consistent_hash_ring.hpp"

#include <iostream>
#include <functional>

std::size_t ConsistentHashRing::hashValue(const std::string& value) const
{
    return std::hash<std::string>{}(value);
}

void ConsistentHashRing::addServer(const std::string& serverName)
{
    std::size_t position = hashValue(serverName);

    ring_[position] = serverName;
}

bool ConsistentHashRing::removeServer(const std::string& serverName)
{
    std::size_t position = hashValue(serverName);

    std::size_t removed = ring_.erase(position);

    return removed > 0;
}



std::string ConsistentHashRing::getServer(const std::string& key) const
{
    if (ring_.empty())
    {
        return "";
    }

    std::size_t keyPosition = hashValue(key);

    auto server = ring_.lower_bound(keyPosition);

    if (server == ring_.end())
    {
        server = ring_.begin();
    }
    
    return server->second;
}

void ConsistentHashRing::showRing() const
{
    for (const auto& server : ring_)
    {
        std::cout
            << server.first
            << " -> "
            << server.second
            << "\n";
    }
}
