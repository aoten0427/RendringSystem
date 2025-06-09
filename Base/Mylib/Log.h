#pragma once
#include <string>
#include <mutex>
#include <sstream>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#else
#include <iostream>
#endif

class Log {
public:
    enum class LogLevel {
        DEBUG = 0,
        INFO = 1,
        WARNING = 2,
        FATAL = 3
    };

private:
    static std::mutex s_mutex;

    /// <summary>
    /// ���O���x���𕶎���ɕϊ�
    /// </summary>
    /// <param name="level">���O���x��</param>
    /// <returns>���O���x��������</returns>
    static const char* levelToString(LogLevel level) noexcept {
        switch (level) {
        case LogLevel::DEBUG:     return "[DEBUG] ";
        case LogLevel::INFO:      return "[INFO]  ";
        case LogLevel::WARNING:   return "[WARN]  ";
        case LogLevel::FATAL:     return "[FATAL] ";
        default:                  return "[UNKNOWN] ";
        }
    }

    /// <summary>
    /// �v���b�g�t�H�[���ŗL�̏o�͏���
    /// </summary>
    /// <param name="message">�o�̓��b�Z�[�W</param>
    static void platformOutput(const std::string& message) {
#ifdef _WIN32
        OutputDebugStringA(message.c_str());
#else
        std::cerr << message << std::flush;
#endif
    }

public:

    /// <summary>
    /// ��{�I�ȕ����o��
    /// </summary>
    /// <param name="message">�o�̓��b�Z�[�W</param>
    static void Output(const std::string& message) {
        std::lock_guard<std::mutex> lock(s_mutex);
        std::string fullMessage = message + "\n";
        platformOutput(fullMessage);
    }

    /// <summary>
    /// ���O���x���t���̏o��
    /// </summary>
    /// <param name="level">���O���x��</param>
    /// <param name="message">�o�̓��b�Z�[�W</param>
    static void Output(LogLevel level, const std::string& message) {
        std::ostringstream oss;
        oss << levelToString(level) << message;
        Output(oss.str());
    }

    /// <summary>
    /// �f�o�b�O���O�o��
    /// </summary>
    /// <param name="message">�f�o�b�O���b�Z�[�W</param>
    static void Debug(const std::string& message) {
        Output(LogLevel::DEBUG, message);
    }

    /// <summary>
    /// ��񃍃O�o��
    /// </summary>
    /// <param name="message">��񃁃b�Z�[�W</param>
    static void Info(const std::string& message) {
        Output(LogLevel::INFO, message);
    }

    /// <summary>
    /// �x�����O�o��
    /// </summary>
    /// <param name="message">�x�����b�Z�[�W</param>
    static void Warning(const std::string& message) {
        Output(LogLevel::WARNING, message);
    }

    /// <summary>
    /// �v���I�G���[���O�o�́i�v���O�����I���j
    /// </summary>
    /// <param name="message">�G���[���b�Z�[�W</param>
    [[noreturn]] static void Fatal(const std::string& message) {
        Output(LogLevel::FATAL, message);

#ifdef _WIN32
        // UTF-8���烏�C�h�����ւ̓K�؂ȕϊ�
        int size = MultiByteToWideChar(CP_UTF8, 0, message.c_str(), -1, nullptr, 0);
        if (size > 0) {
            std::vector<wchar_t> wmessage(size);
            if (MultiByteToWideChar(CP_UTF8, 0, message.c_str(), -1, wmessage.data(), size) > 0) {
                MessageBoxW(nullptr, wmessage.data(), L"Fatal Error", MB_OK | MB_ICONERROR);
            }
        }
#endif

        // �m���Ƀv���O�������I��
        std::abort();
    }

    // ���[�e�B���e�B�N���X�Ƃ��ăC���X�^���X�����֎~
    Log() = delete;
    Log(const Log&) = delete;
    Log(Log&&) = delete;
    Log& operator=(const Log&) = delete;
    Log& operator=(Log&&) = delete;
    ~Log() = delete;
};