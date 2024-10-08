#include"TPSCamera.h"

void TPSCamera::Update()
{
	// ターゲットの行列
	Math::Matrix _targetMat = Math::Matrix::Identity;

	const std::shared_ptr<const KdGameObject>
		_spTarget = m_wpTarget.lock();

	if (_spTarget)
	{
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	}

	// カメラの回転
	UpdateRotateByMouse();

	m_mRatation = GetRotationMatrix();

	m_mWorld =  m_mLocalPos * m_mRatation  * _targetMat;

	// ↓めり込み防止の為の座標補正計算！(ワールドを決定した後にするのが良い(設計思想によるが))
	// ①当たり判定(レイ判定)用の情報作成
	KdCollider::RayInfo	_rayInfo;

	//==============================================
	// レイの情報を設定する
	//==============================================
	// レイの発射位置を設定
	_rayInfo.m_pos		= GetPos();								// カメラのm_mWorldの_41,_42,_43をもらう
	// レイの発射方向を設定
	_rayInfo.m_dir		= Math::Vector3::Down;					// 下方向
	// レイの長さ;
	_rayInfo.m_range	= 1000.0f;
	// 当たり判定をしたいタイプを設定
	_rayInfo.m_type		= KdCollider::TypeGround;				// 地面のみと当たり判定を行う

	// カメラに収めるターゲットが存在している場合だけ実行される処理
	if (_spTarget)
	{
		Math::Vector3	_targetPos	= _spTarget->GetPos();		// ターゲット(今回はキャラクター)の座標
		_targetPos.y				+= 0.1f;
		_rayInfo.m_dir				= _targetPos - GetPos();
		_rayInfo.m_range			= _rayInfo.m_dir.Length();
		_rayInfo.m_dir.Normalize();
	}

	// ②HIT対象オブジェクト(地面タイプのオブジェクト)に総当たり
	for (std::weak_ptr<KdGameObject> _wpGameObj : m_wpHitObjectList)
	{
		std::shared_ptr<KdGameObject>	_spGameObj = _wpGameObj.lock();
		if (_spGameObj)
		{
			std::list < KdCollider::CollisionResult>	_retRayList;
			_spGameObj->Intersects(_rayInfo, &_retRayList);

			// ③結果を使って座標を補完する
			// レイに当たったリストから一番近いオブジェクトを検出
			float			_maxOverLap = 0.0f;
			Math::Vector3	_hitPos		= {};
			bool			_hit		= false;

			for (auto& _ret : _retRayList)
			{
				// レイを遮断し、オーバーした長さが
				// 一番長いものを探す
				if (_maxOverLap < _ret.m_overlapDistance)
				{
					_maxOverLap = _ret.m_overlapDistance;
					_hitPos		= _ret.m_hitPos;
					_hit		= true;
				}
			}

			if (_hit)
			{
				// 何かしら障害物に当たっている
				Math::Vector3	_hoseiPos	= _hitPos;
				//	* 0.4fは補正値
				_hoseiPos					+= _rayInfo.m_dir * 0.4f;
				SetPos(_hoseiPos);
			}
		}
	}

	CameraBase::Update();
}

void TPSCamera::Init()
{
	// 基準点(ターゲットからどれだけ離れているか)
	m_mLocalPos = Math::Matrix::CreateTranslation(0.0f, 1.5f, -10.0f);

	// ↓画面中央
	m_FixMousePos.x = 640.0f;
	m_FixMousePos.y = 320.0f;

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	CameraBase::Init();
}