#pragma once
#include "Texture2D.h"//=============================================

namespace dae
{
	class Sprite
	{
	public:
		Sprite(const std::string& path, int nrCols, int nrRows, int maxActs, float framePerSec);
		~Sprite();

		void Update(float elapsedSec);
		void Draw(const dae::Vector2& pos, float scale);

	private:

		std::shared_ptr<dae::Texture2D> m_pTexture;
		int m_Cols, m_Rows;
		float m_FrameSec;
		float m_AccuSec;
		int m_ActFrame;

		int m_CountActs;

		float m_Width;
		float m_Height;

	};
}
