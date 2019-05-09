#include "MiniginPCH.h"
#include "EmptyBlock.h"


EmptyBlock::EmptyBlock()
	:LevelObject("Resources/Textures/point.jpg")//Resources/Textures/point.jpg
{
}


EmptyBlock::~EmptyBlock()
{
}

void EmptyBlock::Update(float elapsedTime) {
	UNREFERENCED_PARAMETER(elapsedTime);
}
void EmptyBlock::Initialize() {}