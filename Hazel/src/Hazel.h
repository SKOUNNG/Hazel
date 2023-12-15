#pragma once

//For use by Hazel applications

#include "Hazel/Application.h"
#include "Hazel/Log.h"
#include "Hazel/Layer.h"

#include "Hazel/Core/Timestep.h"

#include "Hazel/Input.h"
#include "Hazel/KeyCodes.h"
#include "Hazel/MouseButtonCodes.h"
#include "Hazel/ImGui/ImGuiLayer.h"

//----Renderer-----------------------
#include "Hazel/Renderer/RenderCommand.h"
#include "Hazel/Renderer/Renderer.h"

#include "Hazel/Renderer/Buffer.h"
#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/VertexArray.h"

#include "Hazel/Renderer/OrthoGraphicCamera.h"
//-----------------------------------

//----EntryPoint---------------------
#include "Hazel/EntryPoint.h"
//-----------------------------------

//---glm-----------------------------
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi
//-----------------------------------