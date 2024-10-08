#include "Character.h"
#include"../Camera/CameraBase.h"

void Character::Init()
{
	if (!m_spPoly)
	{
		m_spPoly = std::make_shared<KdSquarePolygon>();
		m_spPoly->SetMaterial("Asset/Data/LessonData/Character/Hamu.png");
		m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	}
}

void Character::Update()
{
	// キャラクターの移動速度(真似しちゃダメですよ)
	float moveSpd = 0.05f;
	Math::Vector3 nowPos = m_mWorld.Translation();

	Math::Vector3 moveVec = Math::Vector3::Zero;
	if (GetAsyncKeyState('D')) { moveVec.x = 1.0f; }
	if (GetAsyncKeyState('A')) { moveVec.x = -1.0f; }
	if (GetAsyncKeyState('W')) { moveVec.z = 1.0f; }
	if (GetAsyncKeyState('S')) { moveVec.z = -1.0f; }

	const std::shared_ptr<CameraBase> _spCamera = m_wpCamera.lock();
	if (_spCamera)
	{
		moveVec = moveVec.
			TransformNormal(moveVec, _spCamera->GetRotationYMatrix());
		// 進行方向のベクトルをカメラが向いているベクトルに変更する

		// TransformNormal(a,b)
		// 第一引数のベクトルを第二引数の回転行列を使用して新しいベクトルにして返してもらう関数
	}

	moveVec.Normalize();
	moveVec *= moveSpd;
	nowPos += moveVec;

	// キャラクターの回転角度を求める
	UpdateRotate(moveVec);

	// キャラクターのワールド行列を創る処理
	Math::Matrix _rotation =
		Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_WorldRot.y));
	m_mWorld = _rotation * Math::Matrix::CreateTranslation(nowPos);
}

void Character::DrawLit()
{
	if (!m_spPoly) return;

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}

void Character::UpdateRotate(const Math::Vector3& _srcMoveVec)
{
	// 何も入力がない場合は処理しない(無駄な処理を省いていく)
	// _srcMoveVecには何も入力がないと{0.0f,0.0f,0.0f}が入っている
	// 3つの要素をチェックするのではなく、3つのベクトルの長さでみれば一発
	// length()は長さを求める関数だがやや重たいので、
	// ただ長さを調べるだけならlengthsquared()の方が良い(軽い)
	if (_srcMoveVec.LengthSquared() == 0.0f)return;

	// キャラの正面方向ベクトル
	// Backwardは後方とか後ろなどの意味だが、このプログラム上では前方という意味
	Math::Vector3	 _nowDir	= GetMatrix().Backward();

	// 移動方向のベクトル
	Math::Vector3	_targetDir	= _srcMoveVec;
	
	_targetDir.Normalize();		// 念のための補正

	float	_nowAng		= atan2(_nowDir.x, _nowDir.z);
	_nowAng		= DirectX::XMConvertToDegrees(_nowAng);

	float	_TargetAng	= atan2(_targetDir.x, _targetDir.z);
	_TargetAng	= DirectX::XMConvertToDegrees(_TargetAng);

	//角度の差分を求める
	float	_betweenAng = _TargetAng - _nowAng;
	if (_TargetAng > 180.0f)
	{
		_betweenAng -= 360.0f;
	}
	else if (_betweenAng < -180.0f)
	{
		_betweenAng += 360.0f;
	}

	float	_rotateAng = std::clamp(_betweenAng, -8.0f, 8.0f);
	m_WorldRot.y += _rotateAng;
}	