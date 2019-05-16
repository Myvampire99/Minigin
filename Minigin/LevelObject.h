#pragma once
class LevelObject
{
public:
	LevelObject(std::string path);
	~LevelObject();

	virtual void Update(float elapsedTime);
	void Draw();
	virtual void Initialize();

	//void SetTexture(dae::Texture2D * texture);
	void SetPos(dae::Vector2 pos);
	void SetSize(float size);
	dae::Vector2 GetPos();
	
private:
	std::shared_ptr<dae::Texture2D> m_Texture;
	dae::Vector2 m_Pos;
	float m_Size;
};

