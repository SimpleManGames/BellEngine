#ifndef _PARTICLE_SYSTEM_H
#define _PARTICLE_SYSTEM_H

#include "bpch.h"

#include "Bell/Core/Time.h"

#include "Bell/Renderer/Camera/OrthographicCamera.h"
#include "Bell/Renderer/Shader.h"
#include "Bell/Renderer/Texture.h"

namespace Bell
{
    struct ParticleProperties
    {
        glm::vec3 Postion;
        glm::vec3 Velocity, VelocityVariation, VelocityOverTime;
        glm::vec4 ColorBegin, ColorEnd;
        float SizeBegin, SizeEnd, SizeVariation;
        float LifeTime = 1.0f;
    };

    class ParticleSystem
    {
    public:
        ParticleSystem(int maxParticles = 1000);
        ~ParticleSystem();

        void OnUpdate(Bell::Timestep timeStep);
        void OnRender(Bell::OrthographicCamera& camera);
        void OnImGuiRender();

        void Emit(const ParticleProperties& props);

    private:
        /// Definition of a single particle
        struct Particle
        {
            // Position at the time of creation
            glm::vec3 Position;
            // Rotation at the time of creation
            glm::vec3 Rotation, RotationOverTime;
            // Velocity at the time of creation
            glm::vec3 Velocity;
            // Color at the time of creation
            glm::vec4 ColorBegin, ColorEnd;
            float SizeBegin, SizeEnd;
            // How long the particle will be alive for
            float Lifetime = 1.0f;
            float LifetimeRemaining = 0.0f;

            bool IsActive = false;
        };

        int m_MaxParticles;
        std::vector<Particle> m_ParticlePool;
        uint32_t m_PoolIndex = 0;

        Bell::Ref<Bell::Shader> m_Shader;
        Bell::Ref<Bell::Texture> m_Texture;
    };

}
#endif // !_PARTICLE_SYSTEM_H