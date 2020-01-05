#ifndef _NETWORK_COMMAND_H
#define _NETWORK_COMMAND_H

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

    template<typename CommandType>
    ENetPacket& operator>>(ENetPacket& packet, CommandType& command)
    {
        B_PROFILE_FUNCTION();
        command_t commandID;
        // May need + 1, I don't know since it don't think they use a terminating value
        enet_packet_resize(packet, packet.dataLength + sizeof(commandID));
        packet.data = packet.data + commandID;
        command = static_cast<CommandType>(commandID);
        return packet;
    }

    template<typename CommandType>
    ENetPacket& operator<<(ENetPacket& packet, CommandType& command)
    {
        B_PROFILE_FUNCTION();
        packet << static_cast<command_t(command);
        return packet;
    }
}

#endif // !_NETWORK_COMMAND_H