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
    /// ログレベルを文字列に変換
    /// </summary>
    /// <param name="level">ログレベル</param>
    /// <returns>ログレベル文字列</returns>
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
    /// プラットフォーム固有の出力処理
    /// </summary>
    /// <param name="message">出力メッセージ</param>
    static void platformOutput(const std::string& message) {
#ifdef _WIN32
        OutputDebugStringA(message.c_str());
#else
        std::cerr << message << std::flush;
#endif
    }

public:

    /// <summary>
    /// 基本的な文字出力
    /// </summary>
    /// <param name="message">出力メッセージ</param>
    static void Output(const std::string& message) {
        std::lock_guard<std::mutex> lock(s_mutex);
        std::string fullMessage = message + "\n";
        platformOutput(fullMessage);
    }

    /// <summary>
    /// ログレベル付きの出力
    /// </summary>
    /// <param name="level">ログレベル</param>
    /// <param name="message">出力メッセージ</param>
    static void Output(LogLevel level, const std::string& message) {
        std::ostringstream oss;
        oss << levelToString(level) << message;
        Output(oss.str());
    }

    /// <summary>
    /// デバッグログ出力
    /// </summary>
    /// <param name="message">デバッグメッセージ</param>
    static void Debug(const std::string& message) {
        Output(LogLevel::DEBUG, message);
    }

    /// <summary>
    /// 情報ログ出力
    /// </summary>
    /// <param name="message">情報メッセージ</param>
    static void Info(const std::string& message) {
        Output(LogLevel::INFO, message);
    }

    /// <summary>
    /// 警告ログ出力
    /// </summary>
    /// <param name="message">警告メッセージ</param>
    static void Warning(const std::string& message) {
        Output(LogLevel::WARNING, message);
    }

    /// <summary>
    /// 致命的エラーログ出力（プログラム終了）
    /// </summary>
    /// <param name="message">エラーメッセージ</param>
    [[noreturn]] static void Fatal(const std::string& message) {
        Output(LogLevel::FATAL, message);

#ifdef _WIN32
        // UTF-8からワイド文字への適切な変換
        int size = MultiByteToWideChar(CP_UTF8, 0, message.c_str(), -1, nullptr, 0);
        if (size > 0) {
            std::vector<wchar_t> wmessage(size);
            if (MultiByteToWideChar(CP_UTF8, 0, message.c_str(), -1, wmessage.data(), size) > 0) {
                MessageBoxW(nullptr, wmessage.data(), L"Fatal Error", MB_OK | MB_ICONERROR);
            }
        }
#endif

        // 確実にプログラムを終了
        std::abort();
    }

    // ユーティリティクラスとしてインスタンス化を禁止
    Log() = delete;
    Log(const Log&) = delete;
    Log(Log&&) = delete;
    Log& operator=(const Log&) = delete;
    Log& operator=(Log&&) = delete;
    ~Log() = delete;
};