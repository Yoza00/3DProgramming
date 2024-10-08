#include "Moon.h"

Moon::~Moon()
{
}

void Moon::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_moon, m_mWorld);
}

void Moon::Update()
{
	{
		// 自転の処理
		static float rotMine = 0.0f;

		Math::Matrix rot =
			Math::Matrix::CreateRotationY(rotMine);

		rotMine += 0.025f;

		// 公転の処理


		m_mWorld = rot;
	}
}

void Moon::Init()
{
	// 画像データをロード
	m_moon.Load("Asset/Data/LessonData/Planets/moon.gltf");
}
