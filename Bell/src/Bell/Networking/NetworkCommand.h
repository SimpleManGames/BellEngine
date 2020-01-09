#ifndef _NETWORK_COMMAND_H
#define _NETWORK_COMMAND_H

#include "Bell/Networking/Packet/Packet.h"
#include "Bell/Networking/NetworkConstants.h"

namespace Bell
{
    enum class ClientCommand : command_t
    {
        PeerID,
        PlayerJoin,
        PlayerLeave,
        Snapshot,
        SpawnPoint
    };

    enum class ServerCommand : command_t
    {
        PlayerPosition
    };

    template <typename CommandType>
    Packet& operator>>(Packet& packet, CommandType& command)
    {
        command_t commandId;
        packet >> commandId;
        command = static_cast<CommandType>(commandId);
        return packet;
    }

    template <typename CommandType>
    Packet& operator<<(Packet& packet, CommandType command)
    {
        packet << static_cast<command_t>(command);
        return packet;
    }
}

#endif // !_NETWORK_COMMAND_H