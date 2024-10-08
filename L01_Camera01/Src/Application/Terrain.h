#pragma once

class Terrain :public KdGameObject
{
public:
	Terrain();
	~Terrain()		override;

public:

	// override指定子は、オーバーライドされた関数であることを明示するための指定子
	// 継承先で、継承元と違う振る舞いをする。(ポリモーフィズム)
	void Init()		override;
	void Update()	override;
	void DrawLit()	override;

private:

	// モデルデータ
	std::shared_ptr<KdModelData>		m_spModel = nullptr;
};