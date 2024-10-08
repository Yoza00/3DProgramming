#include "Sun.h"

Sun::~Sun()
{

}

void Sun::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_sun, m_mWorld);
}

void Sun::Update()
{
	{
		static float _deg = 0.0f;

		Math::Matrix _rot
			= Math::Matrix::CreateRotationY(_deg);

		_deg += 1.0f;
		if (_deg >= 360.0f)_deg -= 360.0f;

		m_mWorld = _rot;
	}
}

void Sun::Init()
{
	// 画像データをロード
	m_sun.Load("Asset/Data/LessonData/Planets/sun.gltf");
}
