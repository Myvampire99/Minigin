#pragma once

#include "targetver.h"

//TODO: is it ok here ?
namespace dae {
	struct Vector2
	{
		Vector2() :x{}, y{}{}
		Vector2(float x, float y) :x{ x }, y{ y }{}
		float x, y;
	};
}
//


#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <tchar.h>
#include <memory> // smart pointers
#include <vector>



#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Log.h" // Various logging functions

#include <SDL.h>
#include <chrono>
#include "Renderer.h"
//#include "SceneManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "TextRendererComponent.h"
#include <thread>
#include "FPSComponent.h"



#include "Scene.h"
#include "SceneManager.h"


//#include <memory>
//
#include "Transform.h"
#include "Texture2D.h"
#include "SceneObject.h"
#include "BaseComponent.h"
#include <vector>

//#include "Minigin.h"
#include <thread>
#include <string>

////
//#include "FPSComponent.h"
//#include "TextRendererComponent.h"

