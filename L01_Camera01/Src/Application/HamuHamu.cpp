#include"HamuHamu.h"

HamuHamu::HamuHamu()
{

}

HamuHamu::~HamuHamu()
{

}

void HamuHamu::Init()
{
	m_spPoly = std::make_shared<KdSquarePolygon>();
	m_spPoly->
		SetMaterial("Asset/Data/LessonData/Character/Hamu.png");

	// 板ポリゴンの原点の座標を、画像の真ん中の底にする
	m_spPoly->
		SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
}

void HamuHamu::Update()
{
	// キャラクターの移動速度(真似しちゃだめですよ)
	float moveSpd = 0.05f;
	Math::Vector3 nowPos = m_mWorld.Translation();		// m_mHamuWorldの_41,_42,_43をvector3型で返してくれる

	// 移動したい「方向ベクトル」= 絶対に長さが「１」で無ければならない！！！
	Math::Vector3 moveVec = Math::Vector3::Zero;

	if (GetAsyncKeyState('W')) { moveVec.z = 1.0f; }		// 向きに力の大きさを格納する
	if (GetAsyncKeyState('S')) { moveVec.z = -1.0f; }
	if (GetAsyncKeyState('A')) { moveVec.x = -1.0f; }
	if (GetAsyncKeyState('D')) { moveVec.x = 1.0f; }

	// ベクトルの正規化(ノーマライズ)
	moveVec.Normalize();			// 絶対行う
	moveVec *= moveSpd;		// {_41,_42,_43}をそれぞれ*moveSpdする
	nowPos += moveVec;		// ↑の結果をnowPosに加算する

	// キャラクターのワールド行列を創る処理
	m_mWorld = Math::Matrix::CreateTranslation(nowPos);
}

void HamuHamu::DrawLit()
{
	KdShaderManager::Instance().
		m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}