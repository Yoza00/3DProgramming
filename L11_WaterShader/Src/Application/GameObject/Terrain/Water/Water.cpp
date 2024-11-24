#include "Water.h"

void Water::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/LessonData/Stage/Water/Water.gltf");

		SetPos({ 0,0.5f,0 });
	}
}

void Water::Update()
{
	m_UVOffset.x += 0.0001f;
	m_UVOffset.y += 0.0001f;
}

void Water::DrawLesson()
{
	if (!m_spModel) return;

	KdShaderManager::Instance().m_LessonShader.SetUVOffset(m_UVOffset);
	KdShaderManager::Instance().m_LessonShader.DrawModel(*m_spModel->GetData(),m_mWorld);
}

