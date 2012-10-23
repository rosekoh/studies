// TestDebug.cpp
//

#include "StdAfx.h"
#include "SimpTest.h"
#include "TestDebug.h"

////////////////////////////////////////////////////////////////////////////////
// 名字空间
////////////////////////////////////////////////////////////////////////////////

using Simp::tstring;
using Simp::tcin;
using Simp::tcout;
using Simp::tcerr;

////////////////////////////////////////////////////////////////////////////////
// 测试用例
////////////////////////////////////////////////////////////////////////////////

void TestDbgout_01(BOOL turnOn);

////////////////////////////////////////////////////////////////////////////////
// 测试函数
////////////////////////////////////////////////////////////////////////////////

void TestDbgout(BOOL turnOn)
{
    SIMP_OFF_DO(turnOn, return);
    TestDbgout_01(TRUE);
}

////////////////////////////////////////////////////////////////////////////////
// 测试用例
////////////////////////////////////////////////////////////////////////////////

// 测试 Windows API 调试输出 OutputDebugString
void TestDbgout_01(BOOL turnOn)
{
    SIMP_OFF_DO(turnOn, return);
    PRINT_FUNC_BEGIN;

    tstring str = Simp::MakeString<BUF_SIZE>(_T("%s%s: This is a test for Debug Report"), MODULE_NAME, _T("!") _T(__FUNCTION__));

    // 不同于 CRT, Windows API OutputDebugString 在 Debug/Release 版下都可以调用
    OutputDebugString(str.c_str());

    PRINT_FUNC_END;
}
