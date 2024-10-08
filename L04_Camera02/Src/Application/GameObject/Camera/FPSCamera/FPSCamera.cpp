#include"FPSCamera.h"

void FPSCamera::Update()
{
	// ターゲットの行列
	Math::Matrix _targetMat = Math::Matrix::Identity;

	const std::shared_ptr<const KdGameObject>
		_spTarget = m_wpTarget.lock();

	if (_spTarget)
	{
		// 3D空間上のどの位置にターゲットがいるかを取得し、行列を作成する
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	}

	// カメラの回転
	UpdateRotateByMouse();		// 画面中心からマウスカーソルがどれだけ移動したかを求める
								// 角度情報を取得する

	m_mRatation = GetRotationMatrix();	// 角度をもとに回転行列を作成する

	m_mWorld = m_mRatation * m_mLocalPos * _targetMat;
	// m_mRotationとm_mLocalPosはローカル行列で、ワールド行列からみて
	// どうあってほしいかの行列である。
	// _targetMatはワールド行列で、普段使用している行列と同じ
	
	// この合成行列では、_targetMat(プレイヤー)からみて、
	// マウスの角度を求め、どれだけカメラを移動させたかをm_mWorkdに格納している

	CameraBase::Update();
}

void FPSCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();	
	// カメラが存在していない場合にはカメラを作成し
	// カメラがすでに存在している場合には何もしない

	// 基準点(ターゲットからどれだけ離れているか)
	m_mLocalPos = Math::Matrix::CreateTranslation(0.0f, 1.5f, 0.0f);

	// ↓画面中央
	m_FixMousePos.x = 640.0f;
	m_FixMousePos.y = 320.0f;

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);
}