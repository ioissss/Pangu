#pragma once

// 用户使用的头文件
#include"PANGU/Application.h"
#include"PANGU/Log.h"
#include"PANGU/ImGui/ImGuiLayer.h"

#include"PANGU/Core/KeyCode.h"
#include"PANGU/Core/MouseCode.h"
#include"PANGU/Core/Core.h"
#include"PANGU/Core/TimeStep.h"

#include"PANGU/Camera/OrthographicCameraController.h"

#include"PANGU/Events/Event.h"
#include"PANGU/Platform/Windows/WindowsInput.h"

#include"PANGU/Render/Buffer.h"
#include"PANGU/Render/GraphicsContext.h"
#include"PANGU/Render/RenderCommand.h"
#include"PANGU/Render/Renderer.h"
#include"PANGU/Render/Shader.h"
#include"PANGU/Render/VertexArray.h"
#include"PANGU/Render/Texture.h"

#include"PANGU/Platform/OpenGL/OpenGLShader.h"

// -------------------------入口函数---------------------
#include"PANGU/EntryPoint.h"