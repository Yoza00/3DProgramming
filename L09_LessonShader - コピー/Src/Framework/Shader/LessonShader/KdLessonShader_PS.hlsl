// 不要かもしれないが念のためのインクルード
#include "../inc_KdCommon.hlsli"
#include"inc_KdLessonShader.hlsli"

// テクスチャの受け取り(画像データ)
// ※そのままでは使用できない
Texture2D g_baseTex : register(t0);	// ベースカラーテクスチャ

// サンプラ
SamplerState g_ss : register(s0);	// 通常のテクスチャ描画用

float4 main(VSOutPut In) : SV_TARGET
{	
	// 色情報

	// 10/4の段階で、描画モデルのカラーが真っ白なのはこれのせい
	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
	
	return g_baseTex.Sample(g_ss, In.UV) * g_BaseColor * In.Color;
}
