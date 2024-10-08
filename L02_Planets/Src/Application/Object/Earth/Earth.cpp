#include "Earth.h"

Earth::~Earth()
{
}

void Earth::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_earth, m_mWorld);
}

void Earth::Update()
{
	// 地球の自転・公転処理
	{
		static float _degY = 0.0f;

		Math::Matrix _rot =
			Math::Matrix::CreateRotationY(_degY);

		// ↑自転用の回転行列

		Math::Matrix _trans =
			Math::Matrix::CreateTranslation(0, 0, -5.0f);

		Math::Matrix _Cir =
			Math::Matrix::CreateRotationY(_degY * 0.75f);

		_degY += 0.025f;

		m_mWorld = (_rot * _trans) * _Cir;
	}
}

void Earth::Init()
{
	// 画像データをロード
	m_earth.Load("Asset/Data/LessonData/Planets/earth.gltf");
}
