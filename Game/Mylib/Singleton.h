// ================================================================ 
// �t�@�C���� : Singleton.h
// �쐬�� : �i�R�ɓV
// ���� :  �V���O���g�����N���X
// ================================================================

#pragma once


template <typename T>
class Singleton {
public:
    // �V���O���g���C���X�^���X�̎擾
    static T* GetInstance() {
        if (instance == nullptr)
        {
            instance.reset(new T());
        }
        return instance.get();
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
protected:
    Singleton() = default;
    virtual ~Singleton() = default;

private:
    //���g�̃C���X�^���X
    static std::unique_ptr<T> instance;
};

template <typename T>
std::unique_ptr<T> Singleton<T>::instance = nullptr;