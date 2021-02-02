// ----- Bell's Common Includes 
// ----- Used for Application to include all useful files
// -----

#ifndef _BELL_H
#define _BELL_H

#include "Bell/Base/Application.h"
#include "Bell/Layer/Layer.h"
#include "Bell/Base/Log.h"

#include "Bell/Base/Time.h"
#include "Bell/Debug/Instrumentor.h"

// Input
#include "Bell/Base/Input/Input.h"
#include "Bell/Base/Input/KeyCodes.h"
#include "Bell/Base/Input/MouseButtonCodes.h"

#include "Bell/ImGui/ImGuiLayer.h"

// ---- ESC Includes ----
// ----------------------

#include "Bell/Scene/Scene.h"
#include "Bell/Scene/Entity.h"
#include "Bell/Scene/ScriptableEntity.h"
#include "Bell/Scene/Components.h"

// ---- Renderer Includes ----
// ---------------------------

#include "Bell/Renderer/Renderer.h"
#include "Bell/Renderer/Renderer2D.h"
#include "Bell/Renderer/RenderCommand.h"
#include "Bell/Renderer/Camera/OrthographicCamera.h"

#include "Bell/Renderer/Shader.h"
#include "Bell/Renderer/Texture.h"
#include "Bell/Renderer/SubTexture2D.h"
#include "Bell/Renderer/Data/Buffer.h"
#include "Bell/Renderer/FrameBuffer.h"
#include "Bell/Renderer/Data/VertexArray.h"

#include "Bell/Renderer/Camera/OrthographicCameraController.h"

//#include "Bell/Renderer/Particle/ParticleSystem.h"

// ---- Entry Point Definition ----
// --------------------------------

#ifdef __MAIN_FILE__
#include "Bell/Base/EntryPoint.h"
#endif

#endif _BELL_H