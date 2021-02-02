#ifndef SCRIPTABLEENTITY_H
#define SCRIPTABLEENTITY_H

#include "Entity.h"

namespace Bell
{
    class ScriptableEntity
    {
    public:
        template <typename T>
        T &GetComponent()
        {
            B_CORE_ASSERT(m_Entity.HasComponent<T>(), "Scriptable Entity you are trying to get a component from does NOT have Component Type");
            return m_Entity.GetComponent<T>();
        }
    private:
        Entity m_Entity;
        friend class Scene;
    };
} // namespace Bell

#endif // SCRIPTABLEENTITY_H