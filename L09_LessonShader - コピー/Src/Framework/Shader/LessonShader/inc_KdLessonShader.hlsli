// 定数バッファ(メッシュ単位)
cbuffer cbMesh : register(b1)
{
	// オブジェクト情報
	row_major float4x4 g_mWorld;		// ワールド変換行列
}

// 定数バッファ(マテリアル単位)
cbuffer cbMaterial : register(b2)
{
	float4	g_BaseColor;				// ベース色
	float3	g_Emissive;					// 自己発光色
	float	g_Metallic;					// 金属度(キラキラ？濁っている？)
	float	g_Roughness;				// 粗さ(つるつる？ざらざら？)
}

// 頂点シェーダーから出力するデータ
struct VSOutPut
{
	float4 Pos		: SV_Position;
	float2 UV		: TEXCOORD1;
	float4 Color 	: TEXCOORD2;
};
