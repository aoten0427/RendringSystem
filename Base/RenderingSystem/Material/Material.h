#pragma once
#include"IMaterial.h"
#include"Base/Mylib/ConstantBuffer.h"

class Material :public IMaterial
{
public:
    //基本マテリアルデータ
    struct MaterialData
    {
        DirectX::SimpleMath::Vector4 LightDir;
        DirectX::SimpleMath::Vector4 Emissive;
        DirectX::SimpleMath::Vector4 Diffuse;
        DirectX::SimpleMath::Vector4 Specular;
    };
protected:
    //頂点シェーダー
    Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
    //ピクセルシェーダ
    Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
    //インプットレイアウト
    Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
    //使用テクスチャ
    std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_textures;
    //マテリアルバッファ
    std::unique_ptr<ConstantBuffer<MaterialData>> m_materialBuffer;
public:
    //コンストラクタ
    Material();
    //デストラクタ
    virtual ~Material() = default;
    //初期化
    void Initialize(ID3D11Device* device);
    //シェーダー設定
    void Bind(ID3D11DeviceContext* context) override;
    //データリセット
    void Clean(ID3D11DeviceContext* context) override;
    //画像設定
    void BindTexture(ID3D11DeviceContext* context);
    //派生先シェーダー設定
    virtual void InitializeShaders(ID3D11Device* device) = 0;
    //派生先インプットレイアウト設定
    virtual void InitializeInputLayout(ID3D11Device* device) = 0;
};
