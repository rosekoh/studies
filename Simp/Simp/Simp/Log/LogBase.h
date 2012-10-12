////////////////////////////////////////////////////////////////////////////////
// ��    �� : LogBase.h
// ����˵�� :
//   ��־�����
//
// ��    �� : 1.0
// ��    �� : Breaker Zhao <breaker.zy_AT_gmail>
// ��    �� : 2011-10
// ��Ȩ���� : Microsoft Public License <http://www.microsoft.com/en-us/openness/licenses.aspx#MPL>
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <Simp/Depends.h>
#include <Simp/Defs.h>

#include <Simp/Pattern/Uncopyable.h>

SIMP_NS_BEGIN

////////////////////////////////////////////////////////////////////////////////
// ��־����ģ�� LogBaseT
////////////////////////////////////////////////////////////////////////////////

// ��־��������
typedef int LOG_LEVEL;

// ��־����ֵ
namespace LOG_LVL {
enum LEVEL_VALUE {
    LEVEL_DEBUG,
    LEVEL_INFO,
    LEVEL_WARNING,
    LEVEL_ERROR,
    LEVEL_CRITICAL
};
}   // namespace LOG_LVL

template <typename CharT>
class LogBaseT : private Uncopyable {
public:
    LogBaseT(LOG_LEVEL baseLevel) : m_BaseLevel(baseLevel), m_LastLevel(baseLevel) {}

    virtual ~LogBaseT() {}

    virtual void Destroy() {}

    virtual void DoLog(const CharT* format, va_list args) = 0;

    void Log(LOG_LEVEL level, const CharT* format, ...) {
        if (level < m_BaseLevel)
            return;

        va_list args;
        va_start(args, format);
        this->DoLog(format, args);
        m_LastLevel = level;
        va_end(args);
    }

    void Log(const CharT* format, ...) {
        if (m_LastLevel < m_BaseLevel)
            return;

        va_list args;
        va_start(args, format);
        this->DoLog(format, args);
        va_end(args);
    }

public:
    void SetBaseLevel(LOG_LEVEL level) {
        m_BaseLevel = level;
    }

    LOG_LEVEL GetBaseLevel() const {
        return m_BaseLevel;
    }

private:
    LOG_LEVEL   m_BaseLevel;    // ��׼��־����
    LOG_LEVEL   m_LastLevel;    // ��һ�μ�¼��־�ļ���
};

SIMP_NS_END