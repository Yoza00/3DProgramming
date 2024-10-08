#include "GameScene.h"
#include"../SceneManager.h"

#include "../../GameObject/Terrain/Terrain.h"
#include "../../GameObject/Character/Character.h"

#include "../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include "../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include"../../GameObject/Camera/CCTVCamera/CCTVCamera.h"

// 少数第n位で四捨五入する
void round_n(float& number, int n)
{
	number = number * pow(10, n - 1);
	number = round(number);
	number /= pow(10, n - 1);
}

void GameScene::Init()
{
	//===================================================================
	// ステージ初期化
	//===================================================================
	std::shared_ptr<Terrain> _terrain = std::make_shared<Terrain>();
	_terrain->Init();
	AddObject(_terrain);

	//===================================================================
	// キャラクター初期化
	//===================================================================
	std::shared_ptr<Character> _character = std::make_shared<Character>();
	_character->Init();
	AddObject(_character);

	//===================================================================
	// カメラ初期化
	//===================================================================
	//std::shared_ptr<FPSCamera>		_camera = std::make_shared<FPSCamera>();
	//std::shared_ptr<TPSCamera>		_camera = std::make_shared<TPSCamera>();
	std::shared_ptr<CCTVCamera>	_camera = std::make_shared<CCTVCamera>();
	_camera->Init();
	_camera->SetTarget(_character);			// カメラに追尾対象のアドレスを教えてあげる
	_camera->RegistHitObject(_terrain);		// カメラと当たり判定をするオブジェクトのアドレスを教えてあげる
	_character->SetCamera(_camera);
	AddObject(_camera);

	//====================================================================
	// 乱数実験場
	//====================================================================
	//int randRes[10] = {};

	// rand()を使用ver.

	// 如何にrand()が偏るか実験する
	//srand((unsigned)time(NULL));
	//for (int i = 0; i < 100000000; ++i)
	//{
	//	// 0～32767 % 10000() = (0～9999)
	//	int	_tmp = rand() % 10000;
	//	int	_idx = _tmp / 1000;

	//	randRes[_idx]++;
	//}

	//// 結果を出力
	//OutputDebugStringA("------------------------------------------------\n");

	//for (int i = 0; i < 10; ++i)
	//{
	//	std::stringstream	_ss;
	//	_ss << "取得した値が" << i * 1000 << "～" << (i + 1) * 1000 << "の件数：\t" << randRes[i] << "\n";
	//	std::string			_str = _ss.str();
	//	OutputDebugStringA(_str.c_str());
	//}

	//OutputDebugStringA("------------------------------------------------\n");

	// メルセンヌツイスタを使用ver.

	//for (int i = 0; i < 100000000; ++i)
	//{
	//	// 0～32767 % 10000() = (0～9999)
	//	int	_tmp = KdGetInt(0, 9999);
	//	int	_idx = _tmp / 1000;

	//	randRes[_idx]++;
	//}

	//// 結果を出力
	//OutputDebugStringA("------------------------------------------------\n");

	//for (int i = 0; i < 10; ++i)
	//{
	//	std::stringstream	_ss;
	//	_ss << "取得した値が" << i * 1000 << "～" << (i + 1) * 1000 << "の件数：\t" << randRes[i] << "\n";
	//	std::string			_str = _ss.str();
	//	OutputDebugStringA(_str.c_str());
	//}

	//OutputDebugStringA("------------------------------------------------\n");

	// レッスン その１：CカードとRカードをそれぞれ50％の確率で起動時に表示せよ！
	// レッスン その２：Cカードの排出率を99.5%、Rカードの解出率を0.5%の確率で起動時に表示せよ!
	// レッスン その３：CカードとRカードとSRカードの解出率をそれぞれ34%,33%,33%の確率で起動時に表示せよ!
	// レッスン その４：CカードとRカードとSRカードをそれぞれ50%,49.5%,0.5%の確率で起動時に表示せよ！
	
	//int _bunbo		= 1000;				// 確率分母
	//int _bunbo		= 100;
	int _bunbo		= 1000;
	//int _randNum[3] = { 34,33,33 };			// 抽選値(排出確率(分子))
	int _randNum[3] = { 500, 495,5 };			// 抽選値(排出確率(分子))
	int Thusenum	= 10000000;
	//int TosenNum[2] = { 0,0 };
	int TosenNum[3] = { 0,0,0 };

	for (int i = 0; i < Thusenum; ++i)
	{
		int _rand = KdGetInt(0, _bunbo - 1);	// 0～999を抽選
		
		// 3ループ(34,33,33)
		for (int j = 0; j < std::size(_randNum); ++j)
		{
			_rand -= _randNum[j];				// _randに_randNum[j]の中身を引く

			// 減算した結果、値が負の数になった時の処理
			if (_rand < 0)
			{
				TosenNum[j]++;					// このif文に入る = 当選していることになる
				
				/*	
				1ループ目で通ると、Cカードの当選数が加算される
				2ループ目で通ると、Rカードの当選数が加算される
				3ループ目で通ると、SRカードの当選数が加算される

				レア度の種類が増えた場合は、_randNumの要素を増やすことで対応できる
				*/

				break;
			}
		}

		// レッスン２用
		/*if (_rand <= 4)
		{
			TosenNum[1]++;
		}
		else
		{
			TosenNum[0]++;
		}*/

		// レッスン3用
		// 自分で考えたやつ
		/*if (_rand <= 33)
		{
			TosenNum[0]++;
		}
		else if (_rand <= 66)
		{
			TosenNum[1]++;
		}
		else
		{
			TosenNum[2]++;
		}*/
		// 授業のやつ


		// 自分で考えたやつ
		/*int _rand = KdGetInt(0, 999);

		if (_rand < 995)
		{
			_rand = 0;
		}
		else
		{
			_rand = 1;
		}*/

		//TosenNum[_rand]++;
	}
	
	OutputDebugStringA("------------------------------------------------\n");
	
	float _prob = 0;
	// 8バイト分ループを回す -> 誤
	//for (int i = 0; i < sizeof(TosenNum); ++i)
	
	// TosenNumの要素分ループを回す
	for (int i = 0; i < std::size(TosenNum); ++i)
	{
		std::stringstream	_ss;
		_prob = ((float)TosenNum[i] / (float)Thusenum) * 100;
		round_n(_prob, 3);

		switch (i)
		{
		case 0:
			_ss << "Cカード！" << "当選回数 = " << TosenNum[0] << " " << "当選確率 = " << _prob << "%" << "\n";
			break;
		case 1:
			_ss << "Rカード！" << "当選回数 = " << TosenNum[1] << " " << "当選確率 = " << _prob << "%" << "\n";
			break;
		case 2:
			_ss << "SRカード！" << "当選回数 = " << TosenNum[2] << " " << "当選確率 = " << _prob << "%" << "\n";
			break;
		}

		std::string	_str = _ss.str();
		OutputDebugStringA(_str.c_str());
	}
	
	OutputDebugStringA("------------------------------------------------\n");
}

void GameScene::Event()
{
}