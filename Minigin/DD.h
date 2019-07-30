#pragma once
class DD : public dae::Singleton<DD>
{
public:
	DD();
	~DD();

	void DrawQuad(const dae::Vector2 &pos1, const dae::Vector2 &WH,int color = 0);
	void DrawLine(const dae::Vector2 &pos1, const dae::Vector2 &pos2);
	void Draw() const;

	void Clear();
private:
	std::vector<dae::Vector2> m_Lines;
	std::vector<dae::Vector2> m_Quads;
	std::vector<int> m_quadColor;
};

