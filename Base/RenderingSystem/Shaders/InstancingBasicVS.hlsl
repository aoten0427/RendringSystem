#include"Common.hlsli"

PS_INPUT main(INSTANCING_INPUT input)
{
    PS_INPUT result;
    
    input.mat = transpose(input.mat);
	//���_�̈ʒu��ϊ�
    float4 pos = float4(input.Pos.xyz, 1.0f);
	//���[���h�ϊ�
    pos = mul(pos, input.mat);
	//�r���[�ϊ�
    pos = mul(pos, View);
	//�ˉe�ϊ�
    pos = mul(pos, Projection);
	//�s�N�Z���V�F�[�_�ɓn���ϐ��ɐݒ�
    result.Pos = pos;
	//���C�e�B���O
    result.Normal = mul(input.Normal, (float3x3) input.mat);
    result.Normal = normalize(result.Normal);
	//�e�N�X�`��UV
    result.Tex = input.Tex;
    
    return result;
}
