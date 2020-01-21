#include "bpch.h"
#include "Client.h"
#include "Bell/Networking/Network.h"
#include <Bell\Networking\NetworkCommand.h>
#include "Bell/Networking/Packet/PacketFuncHandler.h"

namespace Bell
{
    void Client::OnPeerConnect(ENetPeer* peer)
    {
    }

    void Client::OnPeerDisconnect(ENetPeer* peer)
    {

    }

    void Client::OnPeerTimeout(ENetPeer* peer)
    {
    }

    void Client::OnCommandReceive(ENetPeer* peer, Packet& packet, command_t command)
    {
        Network::GetPacketFunctionHandler().GetPacketFunction(command)(packet);
    }
}