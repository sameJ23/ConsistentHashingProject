#include "cache_router.hpp"

#include <iostream>
#include <vector>

void CacheRouter::addServer(const std::string& serverName)
{
    auto result = servers_.emplace(serverName, Server(serverName));

    if (!result.second)
    {
        std::cout
            << serverName
            << " already exists.\n";

        return;
    }

    ring_.addServer(serverName);

    std::cout
        <<"Added "
        << serverName
        << "\n";
    
        remapKeys();
}

void CacheRouter::remapKeys()
{
    struct KeyMove
    {
        std::string key;
        std::string value;
        std::string oldServer;
        std::string newServer;
    };

    std::vector<KeyMove> moves;

    for (const auto& [serverName, server] : servers_)
    {
        for (const auto& [key, value] : server.getContents())
        {
            std::string correctServer = ring_.getServer(key);

            if (correctServer != serverName)
            {
                moves.push_back({key, value, serverName, correctServer});
            }
        }
    }

    for (const auto& move : moves)
    {
        servers_.at(move.newServer).put(move.key, move.value);

        servers_.at(move.oldServer).remove(move.key);

        std::cout
            << "Moved "
            << move.key
            << ": "
            << move.oldServer
            << " -> "
            << move.newServer
            << "\n";
    }

}

void CacheRouter::put(const std::string& key, const std::string& value)
{
    std::string serverName = ring_.getServer(key);

    if (serverName.empty())
    {
        std::cout << "No servers available.\n";
        return;
    }

    servers_.at(serverName).put(key, value);

    std::cout
        << key
        << " routed to "
        << serverName
        << "\n";
}

std::string CacheRouter::get(const std::string& key)
{
    std::string serverName = ring_.getServer(key);

    if (serverName.empty())
    {
        return "";
    }

    return servers_.at(serverName).get(key);
}

void CacheRouter::showRing() const
{
    ring_.showRing();
}

void CacheRouter::showServers() const
{
    std::cout << "--- Server Contents ---\n";

    for (const auto& [serverName, server] : servers_)
    {
        server.showContents();

        std::cout << "\n";
    }
}

bool CacheRouter::removeServer(const std::string& serverName)
{
    auto server = servers_.find(serverName);

    if (server == servers_.end())
    {
        std::cout
            << serverName
            << " does not exist.\n";
        
        return false;
    }

    if (servers_.size() == 1)
    {
        std::cout
            << "Cannot remove the final server.\n";
        
        return false;
    }

    std::vector<std::pair<std::string, std::string>> keysToMove;

    for (const auto& [key, value] : server->second.getContents())
    {
        keysToMove.push_back({key, value});
    }

    ring_.removeServer(serverName);

    for (const auto& [key, value] : keysToMove)
    {
        std::string newServer = ring_.getServer(key);

        servers_.at(newServer).put(key, value);

        std::cout
            << "Moved "
            << key
            << ": "
            <<serverName
            << " -> "
            <<newServer
            << "\n";
    }

    servers_.erase(serverName);

    std::cout
        << "Removed "
        << serverName
        << "\n";
    
        return true;
}