#pragma once
#include <string>
#include <chrono>

class DebugTimer
{
private:
    std::string m_message;
    std::chrono::steady_clock::time_point m_start;

public:
    // const参照で文字列を受け取り、コピーコストを削減
    explicit DebugTimer(const std::string& message = "Timer");

    // デストラクタ
    ~DebugTimer();
};