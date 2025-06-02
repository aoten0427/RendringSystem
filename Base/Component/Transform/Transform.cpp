// ================================================================ 
// �t�@�C���� : Transform.cpp
// �쐬�� : �i�R�ɓV
// ���� :  �ʒu�A��]�A�傫��������
// ================================================================
#include"pch.h"
#include"Transform.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="object">�����I�u�W�F�N�g</param>
Transform::Transform(Object* object):Component(object)
	,
	m_position{DirectX::SimpleMath::Vector3(0,0,0)},
	m_scale{DirectX::SimpleMath::Vector3(1,1,1)},
	m_rotate{DirectX::SimpleMath::Quaternion::Identity},
	m_isCompute{false},
	m_parent{nullptr},
	m_children{}
{
	
}



/// <summary>
/// ���[���h�s��擾
/// </summary>
/// <returns>���[���h�s��</returns>
DirectX::SimpleMath::Matrix Transform::GetWorldMatrix()
{
	using namespace DirectX::SimpleMath;

	//�v�Z�t���O��true�Ȃ�v�Z
	if (m_isCompute)
	{
		//scale,rotate,position���ōs����v�Z����
		m_matrix = Matrix::CreateScale(m_scale);
		m_matrix *= Matrix::CreateFromQuaternion(m_rotate);
		m_matrix *= Matrix::CreateTranslation(m_position);
		m_isCompute = false;
	}
	Matrix worldMatrix = m_matrix;

	//�e������ꍇ�e�̍s���������
	if (m_parent != nullptr)
	{
		worldMatrix *= m_parent->GetWorldMatrix();
	}

	return worldMatrix;
}

/// <summary>
/// ���[���h�|�W�V������Ԃ�
/// </summary>
/// <returns>���[���h�|�W�V����</returns>
DirectX::SimpleMath::Vector3 Transform::GetWorldPosition()
{
	DirectX::SimpleMath::Vector3 worldpos = m_position;
	//�e������ꍇ�e�̃|�W�V�����𑫂�
	if (m_parent != nullptr)
	{
		worldpos += m_parent->GetWorldPosition();
	}
	return worldpos;
}

/// <summary>
/// ���[���h�X�P�[����Ԃ�
/// </summary>
/// <returns>���[���h�X�P�[��</returns>
DirectX::SimpleMath::Vector3 Transform::GetWorldScale()
{
	DirectX::SimpleMath::Vector3 worldscale = m_scale;
	//�e������ꍇ�e�̃X�P�[���𑫂�
	if (m_parent != nullptr)
	{
		worldscale += m_parent->GetWorldScale();
	}
	return worldscale;
}

/// <summary>
/// ���[���h��]��Ԃ�
/// </summary>
/// <returns>���[���h��]</returns>
DirectX::SimpleMath::Quaternion Transform::GetWorldRotate()
{
	DirectX::SimpleMath::Quaternion worldrotate = m_rotate;
	//�e������ꍇ�e�̉�]��������
	if (m_parent != nullptr)
	{
		worldrotate *= m_parent->GetWorldRotate();
	}
	return worldrotate;
}

/// <summary>
/// �|�W�V�����Z�b�g
/// </summary>
/// <param name="position">�Z�b�g�|�W�V����</param>
void Transform::SetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_position = position;
	m_isCompute = true;
}

/// <summary>
/// �|�W�V�����ړ�(���Z)
/// </summary>
/// <param name="position">���Z��</param>
void Transform::Translate(const DirectX::SimpleMath::Vector3& position)
{
	m_position += position;
	m_isCompute = true;
}

/// <summary>
/// �X�P�[���Z�b�g
/// </summary>
/// <param name="scale">�Z�b�g�X�P�[��</param>
void Transform::SetScale(const DirectX::SimpleMath::Vector3& scale)
{
	m_scale = scale;
	m_isCompute = true;
}


/// <summary>
/// �X�P�[���ω�(���Z)
/// </summary>
/// <param name="scale">���Z��</param>
void Transform::TransScale(const DirectX::SimpleMath::Vector3& scale)
{
	m_scale += scale;
	m_isCompute = true;
}

/// <summary>
/// �X�P�[���ω�(��Z)
/// </summary>
/// <param name="scale">��Z��</param>
void Transform::TransScale(const float& scale)
{
	m_scale *= scale;
	m_isCompute = true;
}

/// <summary>
/// ���e�[�g�Z�b�g
/// </summary>
/// <param name="rotate">�Z�b�g���e�[�g</param>
void Transform::SetRotate(const DirectX::SimpleMath::Quaternion& rotate)
{
	m_rotate = rotate;
	m_isCompute = true;
}


/// <summary>
/// ��](�N�H�[�^�j�I��)
/// </summary>
/// <param name="rotate">��]��</param>
void Transform::TransRotate(const DirectX::SimpleMath::Quaternion& rotate)
{
	m_rotate = m_rotate * rotate;
	m_isCompute = true;
}

/// <summary>
/// ��](���A�p�x)
/// </summary>
/// <param name="axis">��]��</param>
/// <param name="angle">��]��(�ʓx�@)</param>
void Transform::TransRotate(const DirectX::SimpleMath::Vector3& axis, const float& angle)
{
	DirectX::SimpleMath::Quaternion quaternion = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(axis, DirectX::XMConvertToRadians(angle));
	TransRotate(quaternion);
}

/// <summary>
/// ���[�J����](���A�p�x)
/// </summary>
/// <param name="axis">��]��</param>
/// <param name="angle">��]��(�ʓx�@)</param>
void Transform::LocalTransRotate(const DirectX::SimpleMath::Vector3& axis, const float& angle)
{
	DirectX::SimpleMath::Vector3 localaxis = GetWorldAxisFromLocal(axis);
	TransRotate(localaxis, angle);
}

/// <summary>
/// ���g�̎p���ɑ΂��鎲�̕�����Ԃ�
/// </summary>
/// <param name="axis">�w�莲</param>
/// <returns>�w�莲�̃��[���h����</returns>
DirectX::SimpleMath::Vector3 Transform::GetWorldAxisFromLocal(const DirectX::SimpleMath::Vector3& axis)
{
	DirectX::SimpleMath::Vector3 worldaxis = DirectX::SimpleMath::Vector3::Transform(axis, m_rotate);
	worldaxis.Normalize();
	return worldaxis;
}

/// <summary>
/// �e�̉�]���l�������|�W�V������Ԃ�
/// </summary>
/// <returns>��]���݃|�W�V����</returns>
DirectX::SimpleMath::Vector3 Transform::GetRotatePosition()
{
	using namespace DirectX::SimpleMath;

	if (m_parent == nullptr)return m_position;
	Vector3 distance = m_position * m_parent->m_scale;
	distance = DirectX::SimpleMath::Vector3::Transform(distance, m_parent->GetWorldRotate());
	return m_parent->GetRotatePosition() + distance;
}

/// <summary>
/// �e���Z�b�g
/// </summary>
/// <param name="parent">�e</param>
void Transform::SetParent(Transform* parent)
{
	if (parent == nullptr)
	{
		if (m_parent != nullptr)//������null�Őe�����݂��Ă���ꍇ
		{
			//�e�̏�񂩂�t�Z�������ɂ���
			CalculationReMoveParent();
			//�e�������
			m_parent->ReMoveChild(this);
			m_parent = nullptr;
		}
	}
	else
	{
		if (m_parent != parent)//���������݂��āA���݂̐e�ƈႤ�ꍇ
		{
			if (m_parent != nullptr)
			{
				//���̐e�̏�񂩂�t�Z�������ɂ���
				CalculationReMoveParent();
			}
			m_parent = parent;
			m_parent->SetChild(this);
			CalculationSetParent();
		}
	}
}

/// <summary>
/// �q���擾
/// </summary>
/// <param name="num">�C���f�b�N�X�ԍ�</param>
/// <returns>�q</returns>
Transform* Transform::GetChild(int num)
{
	if (num >= m_children.size())
	{
		return nullptr;
	}

	return m_children[num];
}

/// <summary>
/// �q���폜
/// </summary>
/// <param name="child">�폜�q</param>
void Transform::ReMoveChild(Transform* child)
{
	auto searchChile = std::find(m_children.begin(), m_children.end(), child);

	if (searchChile != m_children.end())
	{
		m_children.erase(searchChile);
	}
	
}

/// <summary>
/// �e��ݒ肵���ۂ̏��ύX
/// </summary>
void Transform::CalculationSetParent()
{
	using namespace DirectX::SimpleMath;

	//�|�W�V�����ړ�
	m_position -= m_parent->m_position;
	//�X�P�[���ϊ�
	m_scale = DirectX::SimpleMath::Vector3
	{
		m_scale.x / m_parent->m_scale.x,
		m_scale.y / m_parent->m_scale.y,
		m_scale.z / m_parent->m_scale.z,
	};
	//��]�ϊ�
	Quaternion invers = m_parent->m_rotate;
	invers.Inverse(invers);
	m_rotate *= invers;


	//��]�ړ�
	Vector3 dire = m_position;
	dire = Vector3(
		dire.x / m_parent->m_scale.x,
		dire.y / m_parent->m_scale.y,
		dire.z / m_parent->m_scale.z
	);

	Matrix mat = Matrix::CreateFromQuaternion(invers);
	m_position = Vector3::Transform(dire, mat);

	m_isCompute = true;
}

/// <summary>
/// �e�����������ۂ̏��ύX
/// </summary>
void Transform::CalculationReMoveParent()
{
	using namespace DirectX::SimpleMath;

	Quaternion invers = m_parent->GetWorldRotate();
	Vector3 dire = m_position;
	dire = Vector3(
		dire.x * m_parent->m_scale.x,
		dire.y * m_parent->m_scale.y,
		dire.z * m_parent->m_scale.z
	);

	Matrix mat = Matrix::CreateFromQuaternion(invers);
	m_position = Vector3::Transform(dire, mat);

	m_position += m_parent->m_position;
	m_scale = DirectX::SimpleMath::Vector3
	{
		m_scale.x * m_parent->m_scale.x,
		m_scale.y * m_parent->m_scale.y,
		m_scale.z * m_parent->m_scale.z,
	};

	m_rotate *= m_parent->m_rotate;

	m_isCompute = true;
}
