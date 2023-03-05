#pragma once

#include "DataDef.h"

//转换成ansi编码
std::string ToAnsi(const TString &src_);

//去除头尾的字符c
void TrimString(TString &src_, TCHAR c = _T(' '));