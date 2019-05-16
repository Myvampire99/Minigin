#pragma once

namespace dae {

	class SpriteComponent : public BaseComponent
	{
	public:
		SpriteComponent(int ID, dae::Sprite *sprite);
		~SpriteComponent();

		void Update(const float elapsedTime) override;
		void Draw() override;
		void Initialize() override;

		void AddSprite(int ID, dae::Sprite *sprite);
		void AddSprite(int ID, const std::string& path, int nrCols, int nrRows, int maxActs, float framePerSec);
		void SetCurrentSprite(int ID);

		void FlipSprite(bool flipSpriteV, bool flipSpriteH);
		void SetPause(bool pause);
	private:
		std::map<int, dae::Sprite*> m_Sprites;
		int m_CurrentState;
		bool m_FlipSpriteVert;
		bool m_FlipSpriteHor;
		bool m_Pause;
	};

}