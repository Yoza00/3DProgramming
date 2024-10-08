#include "CCTVCamera.h"

void CCTVCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();

	// 基準点(ターゲット)の目線
	m_mLocalPos = Math::Matrix::CreateTranslation(0, 6.0f, -10.0f);

	// 一旦行列を確定させておく
	m_mWorld	= m_mLocalPos;
}

void CCTVCamera::PostUpdate()
{
	// ターゲットの行列(有効な場合利用する)
	Math::Matrix								_targetMat = Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject>	_spTarget = m_wpTarget.lock();
	if (_spTarget)
	{
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	}

	// カメラの回転
	// Translation()_transMatの_41_42,_43要素をvector3型にして返してくれる
	UpdateLookAtRotate(_targetMat.Translation());
}

void CCTVCamera::UpdateLookAtRotate(const Math::Vector3& _targetPos)
{
	// XMMatrixLookAtLH(どこから見るか, どこを見るか, どこを向くか)
	// あるものからあるものを見る際の行列を作成してくれる関数
	Math::Matrix	_shadowVP = DirectX::XMMatrixLookAtLH(GetPos(), _targetPos, Math::Vector3::Up);

	// ワールド行列は、先ほど作成した変数(行列)の逆行列を求めて作成する
	m_mWorld = _shadowVP.Invert();
}