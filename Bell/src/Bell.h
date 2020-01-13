// ----- Bell's Common Includes 
// ----- Used for Application to include all useful files
// -----

#ifndef _BELL_H
#define _BELL_H

#include "Bell/Core/Application.h"
#include "Bell/Layer/Layer.h"
#include "Bell/Core/Log.h"

#include "Bell/Core/Time.h"
#include "Bell/Debug/Instrumentor.h"

// Input
#include "Bell/Core/Input/Input.h"
#include "Bell/Core/Input/KeyCodes.h"
#include "Bell/Core/Input/MouseButtonCodes.h"

#include "Bell/ImGui/ImGuiLayer.h"

// ---- Renderer Includes ----
// ---------------------------

#include "Bell/Renderer/Renderer.h"
#include "Bell/Renderer/Renderer2D.h"
#include "Bell/Renderer/RenderCommand.h"
#include "Bell/Renderer/Camera/OrthographicCamera.h"

#include "Bell/Renderer/Buffer.h"
#include "Bell/Renderer/Shader.h"
#include "Bell/Renderer/Texture.h"
#include "Bell/Renderer/VertexArray.h"

#include "Bell/Renderer/Camera/OrthographicCameraController.h"

// ---- Network Includes ----
// --------------------------

// ---- Entry Point Definition ----
// --------------------------------

#ifdef __MAIN_FILE__
#include "Bell/Core/EntryPoint.h"
#endif

#endif _BELL_H