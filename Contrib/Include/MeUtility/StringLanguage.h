/********************************************************************
    Filename:    StringLanguage.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __UTILITY_STRINGLANGUAGE_H__
#define __UTILITY_STRINGLANGUAGE_H__

#pragma once

#include <string>

class StringLanguage
{
public:
    StringLanguage() : id(0),value(""),filePath(""),
        line(0),column(0){}

    unsigned long id;
    std::string   value;
    std::string   filePath;
    unsigned long line;
    unsigned long column;
};

#define STRING_LANGUAGE_FILENAME "string.language"
#define STRING_TAG_BEGIN "GetString(("
#define STRING_TAG_END "))"
#define STRING_TAG_END_CHARCOUNT 2
#define STRING_TAG "GetString((%u))"
#define STRING_CODE "utf-8"

#endif // __UTILITY_STRINGLANGUAGE_H__
