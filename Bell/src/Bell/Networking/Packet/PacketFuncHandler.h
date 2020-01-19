#ifndef _PACKET_FUNC_HANDLER_H
#define _PACKET_FUNC_HANDLER_H

#include <map>
#include "Bell/Networking/Network.h"
#include "Bell/Networking/NetworkTypes.h"
#include "Bell/Networking/NetworkCommand.h"
#include <Bell\Networking\Server\Server.h>

#define B_PACKET_FUNCTION_DEF(command, func) Bell::Network::GetPacketFunctionHandler().AddFunctionToMap((Bell::command_t)command, std::bind(&func, this, std::placeholders::_1))

namespace Bell
{
    class Packet;

    typedef std::function<void(Packet&)> PacketFunc;

    class PacketFuncHandler
    {
    public:
        PacketFuncHandler()
        {
        }

        bool AddFunctionToMap(command_t key, PacketFunc value)
        {
            if (PacketFuncHandler::m_CommandFunctionMap.find(key) == PacketFuncHandler::m_CommandFunctionMap.end())
            {
                PacketFuncHandler::m_CommandFunctionMap.insert(std::pair<command_t, PacketFunc>(key, value));
                B_CORE_INFO("  Packet Function was added to map: {0}", key);
                return true;
            }
            else
            {
                B_CORE_WARN("  Packet Function was already added to map {0}", key);
                return false;
            }

            B_CORE_WARN("  Packet Function failed to add to map: {0}", key);
            return false;
        }

        PacketFunc GetPacketFunction(command_t command)
        {
            return m_CommandFunctionMap[command];
        }

    private:
        std::map<command_t, PacketFunc> m_CommandFunctionMap;
    };
}


#endif // !_PACKET_FUNC_HANDLER_H


/// Probably can condense it just done to packethandler and in the constructor pass in the function we want to use
/// As well as the key value 

/// Might not work since member variables - std binding will solve this

/// Then we can define the function pointers in Server/Client layer and bind them there as well in the ctor
/// 