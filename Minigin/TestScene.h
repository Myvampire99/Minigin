#pragma once
//#include "Scene.h"
//#include "Font.h"
//#include "GameObject.h"
//#include "Sprite.h"

//class GameObject;
class TestScene :public dae::Scene
{
public:
	TestScene();

	

private:
	void SceneUpdate() override;
	void SceneInitialize() override;

	std::shared_ptr<dae::GameObject> txt;
	std::shared_ptr<dae::GameObject> go;

};

