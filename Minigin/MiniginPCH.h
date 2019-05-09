#pragma once

#include "targetver.h"


#include <math.h> 
//TODO: new .h file
namespace dae {
	struct Vector2
	{
		Vector2() :x{}, y{}{}
		Vector2(float x, float y) :x{ x }, y{ y }{}

		float DistanceTo(Vector2 pos) {
			float X{ pos.x -x };
			float Y{ pos.y - y };
			return float(sqrt(X*X + Y * Y));
		}

		float x, y;
	};
}

namespace dae {
	struct Vector3
	{
		Vector3() :x{}, y{}, z{}{}
		Vector3(float x, float y, float z) :x{ x }, y{ y }, z{z}{}
		float x, y,z;
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
#include <XInput.h>
#include <unordered_map>
#include <map>


#include "Transform.h"

#include "Renderer.h"
//#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"

#include "BaseComponent.h"//


#include "ResourceManager.h"



#include "InputManager.h"
#include "TextRendererComponent.h"
#include <thread>
#include "FPSComponent.h"



//#include "Scene.h"
#include "SceneManager.h"

//
#include "Font.h"/*
#include "GameObject.h"*/
#include "Sprite.h"
//


//#include <memory>
////

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


#include "SpriteComponent.h"
#include "InputComponent.h"


//
#include "LevelObject.h"
#include "GridLevel.h"

#include "GridComponent.h"

#include "BaseCharacterComponent.h"

#include "ServiceLocator.h"
#include "Singleton.h"


#include "DiggerCharacterComponent.h"
#include "EmptyBlock.h"
#include "RockBlock.h"

#include "Command.h"