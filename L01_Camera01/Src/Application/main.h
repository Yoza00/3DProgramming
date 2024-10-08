#pragma once

//============================================================
// アプリケーションクラス
//	APP.～ でどこからでもアクセス可能
//============================================================
class Application
{
// メンバ
public:

	// アプリケーション実行
	void Execute();

	// アプリケーション終了
	void End() { m_endFlag = true; }

	HWND GetWindowHandle() const { return m_window.GetWndHandle(); }
	int GetMouseWheelValue() const { return m_window.GetMouseWheelVal(); }

	int GetNowFPS() const { return m_fpsController.m_nowfps; }
	int GetMaxFPS() const { return m_fpsController.m_maxFps; }

private:

	void KdBeginUpdate();
	void PreUpdate();
	void Update();
	void PostUpdate();
	void KdPostUpdate();

	void KdBeginDraw(bool usePostProcess = true);
	void PreDraw();
	void Draw();
	void PostDraw();
	void DrawSprite();
	void KdPostDraw();

	// アプリケーション初期化
	bool Init(int w, int h);

	// アプリケーション解放
	void Release();

	// ゲームウィンドウクラス
	KdWindow		m_window;

	// FPSコントローラー
	KdFPSController	m_fpsController;

	// ゲーム終了フラグ trueで終了する
	bool		m_endFlag = false;

	// カメラ
	std::shared_ptr<KdCamera>					m_spCamera	= nullptr;

	//// ゲームオブジェクト(ハム太郎)の宣言
	//std::shared_ptr<KdGameObject>				m_Hamu		= nullptr;

	//// ゲームオブジェクト(地形)の宣言
	//std::shared_ptr<KdGameObject>				m_Terrain	= nullptr;

	// ゲームオブジェクトリスト
	std::vector<std::shared_ptr<KdGameObject>>m_GameObjList;
	// KdGameObject型のスマートポインタ型の可変長配列m_GameObjList
	// ポリモーフィズム：操作したいクラスを一律でKdGameObjectクラスとして扱うこと
	// 派生先クラスでは、派生元クラスの関数をoverrideしているため、各自で好きな処理を行うことができる

//=====================================================
// シングルトンパターン
//=====================================================
private:
	// 
	Application() {}

public:
	static Application &Instance(){
		static Application Instance;
		return Instance;
	}
};
