#pragma once
#include "BaseCharacterComponent.h"
class PengoCharacterComponent : public BaseCharacterComponent
{
public:
	PengoCharacterComponent(GridManager*);
	~PengoCharacterComponent();

	void LocalUpdate(float elapsedTime) override;
	void Push();
	void AddSubject(Subject *sub);
private:

	float m_SpeedBlocks;
	bool m_reset = false;

	GridManager* m_GridManager;
	void localIni() override;
	Subject *m_Subject;
};

