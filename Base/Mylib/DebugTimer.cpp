#include "pch.h"
#include "DebugTimer.h"
#include "Log.h"

DebugTimer::DebugTimer(const std::string& message)
    : m_message(message)
    , m_start(std::chrono::steady_clock::now()) 
{
}

DebugTimer::~DebugTimer()
{
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - m_start);

    std::string output = m_message + ": " + std::to_string(duration.count()) + " É s";
    Log::Debug(output);
}