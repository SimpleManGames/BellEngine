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
        //switch (static_cast<ClientCommand>(command))
        //{
        //    case ClientCommand::PlayerJoin:
        //        OnPlayerJoin(packet);
        //        break;
        //    case ClientCommand::PlayerLeave:
        //        OnPlayerLeave(packet);
        //        break;
        //    case ClientCommand::Snapshot:
        //        OnSnapshot(packet);
        //        break;
        //    default:
        //        break;
        //}
    }

    void Client::OnPlayerJoin(Packet& packet)
    {
        peer_id_t id;
        packet >> id;
        m_Entities[id].active = true;

        B_CORE_INFO("Player Joined, Client ID: {0}", (int)id);
    }

    void Client::OnPlayerLeave(Packet& packet)
    {
        peer_id_t id;
        packet >> id;
        m_Entities[id].active = false;

        B_CORE_INFO("Player Left, Client ID: {0}", (int)id);
    }

    void Client::OnSnapshot(Packet& packet)
    {
        int16_t updateEntityCount = 0;
        packet >> updateEntityCount;
        for (int16_t i = 0; i < updateEntityCount; i++)
        {
            peer_id_t id = 0;
            float x, y, z;
            packet >> id >> x >> y >> z;
            if (id != NetworkHost::GetPeerID())
            {
                auto* p = &m_Entities[id];
                p->position = { x,y,z };
                p->active = true;
            }
        }
    }
}