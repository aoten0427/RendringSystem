// ================================================================ 
// ファイル名 : ConstantBuffer.h
// 作成者 : 景山碧天
// 説明 :  定数バッファラッパー
// ================================================================
#pragma once

template<typename T>
class ConstantBuffer
{
private:
    //バッファー
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;
    //保存データ
    T m_data;
public:
    // バッファ作成
    ConstantBuffer(ID3D11Device* device,
        D3D11_USAGE usage = D3D11_USAGE_DEFAULT,
        UINT bindflag = D3D11_BIND_CONSTANT_BUFFER,
        UINT accessFlag = 0)
    {
        D3D11_BUFFER_DESC desc = {};
        desc.Usage = usage;
        desc.ByteWidth = sizeof(T);
        desc.BindFlags = bindflag;
        desc.CPUAccessFlags = accessFlag;
        desc.MiscFlags = 0;

        device->CreateBuffer(&desc, nullptr, &m_buffer);
    }

    //データセット
    void SetData(const T& data)
    {
        if (std::memcmp(&m_data, &data, sizeof(T)) != 0)
        {
            m_data = data;
        }
    }

    //データ更新
    void Update(ID3D11DeviceContext* context)
    {
       context->UpdateSubresource(m_buffer.Get(), 0, nullptr, &m_data, 0, 0);  
    }

    //バッファゲット
    ID3D11Buffer* GetBuffer() const { return m_buffer.Get(); }
    //データゲット
    const T& GetData() const { return m_data; }
};