#include "Character.h"
#include"../../main.h"

void Character::Init()
{
	if (!m_spPoly)
	{
		m_spPoly = std::make_shared<KdSquarePolygon>();
		m_spPoly->SetMaterial("Asset/Data/LessonData/Character/Hamu.png");
		m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	}

	if (!m_spNamePlate)
	{
		m_spNamePlate = std::make_shared<KdTexture>();
		m_spNamePlate->Load("Asset/Textures/charNme.png");
	}
}

void Character::Update()
{
	// 右クリック
	if (GetAsyncKeyState(VK_RBUTTON))
	{
		// ①マウス座標を取得
		POINT _mousePos;			// マウスの座標を格納する変数
		GetCursorPos(&_mousePos);	// マウスの座標を格納する
		// ディスプレイ左上を基準(0,0)として座標を算出する

		// マウス座標を補正する
		ScreenToClient(Application::Instance().GetWindowHandle(), &_mousePos);

		std::shared_ptr<KdCamera> _cam = m_wpCam.lock();

		if (_cam)
		{
			// カメラの座標
			Math::Vector3 _camPos = _cam->GetCameraMatrix().Translation();

			// レイの角度
			Math::Vector3 _rayDir = Math::Vector3::Zero;

			// レイの長さ(そこそこの長さ)
			float _rayRange = 1000.0f;

			// ②レイの発射方向を求める(_rayDir)
			_cam
				->GenerateRayInfoFromClientPos(_mousePos, _camPos, _rayDir, _rayRange);
			// この関数を通過すると_rayDirの角度が求まる

			// ③実際にレイを飛ばして衝突位置を求める
			const std::shared_ptr<KdGameObject> _terrain = m_wpTerrain.lock();
			// NULLチェック
			if (_terrain)
			{
				// 地面タイプと当たり判定をする
				// レイのスタート位置はカメラの位置
				// レイのエンド位置はカメラの位置から計算で算出した角度にレイの長さ伸ばした座標
				Math::Vector3 _endRayPos = _camPos + (_rayDir * _rayRange);
				KdCollider::RayInfo _rayInfo(KdCollider::TypeGround, _camPos, _endRayPos);
				
				// 実際の当たり判定の処理
				std::list < KdCollider::CollisionResult> _results;
				_terrain->Intersects(_rayInfo, &_results);

				// 結果が1つでも帰ってきていたら
				if (_results.size())
				{
					for (KdCollider::CollisionResult &result : _results)
					{
						m_TargetPos = result.m_hitPos;
					}
				}
			}
		}
	}

	// キャラクターの移動速度(真似しちゃダメですよ)
	float			moveSpd = 0.05f;
	Math::Vector3	nowPos = GetPos();
	//Math::Vector3 nowPos = m_mWorld.Translation();
	//Math::Vector3 nowPos = m_TargetPos;

	Math::Vector3 moveVec = m_TargetPos - nowPos;
	// ターゲット(マウスでクリックされた座標) - 現在のキャラの座標
	/*if (GetAsyncKeyState('D')) { moveVec.x = 1.0f; }
	if (GetAsyncKeyState('A')) { moveVec.x = -1.0f; }
	if (GetAsyncKeyState('W')) { moveVec.z = 1.0f; }
	if (GetAsyncKeyState('S')) { moveVec.z = -1.0f; }*/

	// キャラクターが震える原因=目的地までの距離より１フレームの移動量よりも少なくて
	// 永遠に計算し続けてしまうから

	// キャラクターの震えを止めてあげる
	// 移動速度の補正
	if (moveVec.Length() < moveSpd)moveSpd = moveVec.Length();

	moveVec.Normalize();
	moveVec *= moveSpd;
	nowPos += moveVec;

	// キャラクターのワールド行列を創る処理
	m_mWorld = Math::Matrix::CreateTranslation(nowPos);
}

void Character::DrawLit()
{
	if (!m_spPoly) return;

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}

void Character::DrawSprite()
{
	// KdCameraクラスにある座標変換関数の実行結果を格納するための変数
	Math::Vector3 _result = Math::Vector3::Zero;
	// 赤い点が常にハムスターの原点(足元)に追従するように
	// ①ハムスターの3D座標を2D座標へ変換する
	std::shared_ptr<KdCamera> _cam = m_wpCam.lock();	// shared_ptrのローカル変数 _camを作成し、親カメラが存在しているかどうかをチェックする

	// 親カメラが存在している場合に実行される処理
	if (_cam)
	{
		Math::Vector3 _pos = GetPos();
		_pos.y += 1.5f;
		// KdCameraにある座標変換関数を呼び出す
		_cam->ConvertWorldToScreenDetail(_pos, _result);
	}

	// ↓2D座標を使用して2D描画している
	/*KdShaderManager::Instance().
		m_spriteShader.DrawCircle(_result.x, _result.y, 10, &kRedColor);*/
	// ↑座標変換した結果を用いて描画を行う

	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spNamePlate.get(), (int)_result.x, (int)_result.y);
}