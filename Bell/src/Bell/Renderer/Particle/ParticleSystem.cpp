#include "bpch.h"
#include "ParticleSystem.h"

#include "Bell/Core/Random.h"
#include "Bell/Renderer/Renderer2D.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

#include "imgui.h"
#include <glm/gtc/type_ptr.hpp>

Bell::ParticleSystem::ParticleSystem(int32_t maxParticles)
    : m_MaxParticles(maxParticles)
{
    m_ParticlePool.resize(m_MaxParticles - 1);
}

Bell::ParticleSystem::~ParticleSystem()
{
}

void Bell::ParticleSystem::OnUpdate(Bell::Timestep timeStep)
{
    for (auto& particle : m_ParticlePool)
    {
        if (particle.IsActive == false)
        {
            continue;
        }

        if (particle.LifetimeRemaining <= 0.0f)
        {
            particle.IsActive = false;
            continue;
        }

        particle.LifetimeRemaining -= timeStep;
        particle.Position += particle.Velocity * (float)timeStep;
        particle.Rotation += particle.Rotation * (float)timeStep;
    }
}

void Bell::ParticleSystem::OnRender(Bell::OrthographicCamera& camera)
{
    Bell::Renderer2D::BeginScene(camera);

    for (auto& particle : m_ParticlePool)
    {
        if (particle.IsActive == false)
        {
            continue;
        }

        float life = particle.LifetimeRemaining / particle.Lifetime;
        glm::vec4 color = glm::lerp(particle.ColorEnd, particle.ColorBegin, life);
        color.a = 1.0f;

        float size = glm::lerp(particle.SizeEnd, particle.SizeBegin, life);

        Bell::Renderer2D::DrawQuad(particle.Position, { size, size }, particle.Rotation.y, color);
    }
    Bell::Renderer2D::EndScene();
}

void Bell::ParticleSystem::OnImGuiRender()
{
    ImGui::Begin("Particle System");

    if (ImGui::DragInt("Max Particle Count", &m_MaxParticles, 1.0f, 0, 100000))
    {
        if (m_MaxParticles < 0)
        {
            m_MaxParticles = 1;
        }
        m_ParticlePool.resize(m_MaxParticles);
    }
    int i = 0;
    for (auto& particle : m_ParticlePool)
    {
        i++; 
        if (ImGui::CollapsingHeader(("Particle %d", std::to_string(i)).c_str()))
        {
            ImGui::Text("Active: %s", (particle.IsActive) ? "True" : "False");
            ImGui::DragFloat3("Position", glm::value_ptr(particle.Position));
            ImGui::DragFloat3("Rotation", glm::value_ptr(particle.Rotation));
            ImGui::Text("LifeTime / Remaining: %f / %f", particle.Lifetime, particle.LifetimeRemaining);
        }
    }

    ImGui::End();
}

void Bell::ParticleSystem::Emit(const ParticleProperties& props)
{
    if (m_MaxParticles <= 0 || m_ParticlePool.size() <= 0 || m_PoolIndex > m_ParticlePool.size())
    {
        m_PoolIndex = 0;
        return;
    }

    Particle& particle = m_ParticlePool[m_PoolIndex];
    particle.IsActive = true;
    particle.Position = props.Postion;
    particle.Rotation = { 0.0f, Random::Float() * 2.0f * glm::pi<float>(), 0.0f };

    // Velocity
    particle.Velocity = props.Velocity;
    particle.Velocity.x += props.VelocityVariation.x * (Random::Float() - 0.5f);
    particle.Velocity.y += props.VelocityVariation.y * (Random::Float() - 0.5f);

    // Color
    particle.ColorBegin = props.ColorBegin;
    particle.ColorEnd = props.ColorEnd;

    particle.Lifetime = props.LifeTime;
    particle.LifetimeRemaining = props.LifeTime;
    particle.SizeBegin = props.SizeBegin + props.SizeVariation * (Random::Float() - 0.5f);
    particle.SizeEnd = props.SizeEnd;

    m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
}