#ifndef SCENEHIERARCHYPANEL_H
#define SCENEHIERARCHYPANEL_H

#include <Bell.h>

namespace Bell::Editor
{
    class SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel() = default;
        SceneHierarchyPanel(const Ref<Scene> &scene);

        void SetContext(const Ref<Scene> &scene);

        void OnImGuiRender();

    private:
        void DrawEntityNode(Entity entity);
        void DrawComponents(Entity entity);

    private:
        Ref<Scene> m_Context;
        Entity m_SeletectionContext;
    };
} // namespace Bell::Editor

#endif // SCENEHIERARCHYPANEL_H