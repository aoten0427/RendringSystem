// ================================================================ 
// �t�@�C���� : ConstantBuffer.h
// �쐬�� : �i�R�ɓV
// ���� :  �萔�o�b�t�@���b�p�[
// ================================================================
#pragma once

template<typename T>
class ConstantBuffer
{
private:
    //�o�b�t�@�[
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;
    //�ۑ��f�[�^
    T m_data;
public:
    // �o�b�t�@�쐬
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

    //�f�[�^�Z�b�g
    void SetData(const T& data)
    {
        if (std::memcmp(&m_data, &data, sizeof(T)) != 0)
        {
            m_data = data;
        }
    }

    //�f�[�^�X�V
    void Update(ID3D11DeviceContext* context)
    {
       context->UpdateSubresource(m_buffer.Get(), 0, nullptr, &m_data, 0, 0);  
    }

    //�o�b�t�@�Q�b�g
    ID3D11Buffer* GetBuffer() const { return m_buffer.Get(); }
    //�f�[�^�Q�b�g
    const T& GetData() const { return m_data; }
};