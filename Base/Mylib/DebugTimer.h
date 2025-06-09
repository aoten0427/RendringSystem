#pragma once
#include <string>
#include <chrono>

class DebugTimer
{
private:
    std::string m_message;
    std::chrono::steady_clock::time_point m_start;

public:
    // const�Q�Ƃŕ�������󂯎��A�R�s�[�R�X�g���팸
    explicit DebugTimer(const std::string& message = "Timer");

    // �f�X�g���N�^
    ~DebugTimer();
};