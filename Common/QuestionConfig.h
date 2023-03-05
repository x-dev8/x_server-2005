#ifndef __QUESTION_CONFIG_H__
#define __QUESTION_CONFIG_H__

#pragma once

/**************************************

Id 				题目编号 从0开始
Describe		题目描述 
CorrectAnswer	正确答案 填写 1 2 3 4
AnswerDesc1		答案描述1
AnswerDesc2		答案描述2
AnswerDesc3		答案描述3
AnswerDesc4		答案描述4

***************************************/

#define theQuestionConfig QuestionConfig::Instance()   //实例接口

#include <string>
#include <vector>
#include <map>

#include "GlobalDef.h"

class QuestionConfig
{
public:
    enum EAnswerConst
    {
        Answer_Invalid,
        Answer_A,
        Answer_B,
        Answer_C,
        Answer_D,
        Answer_Max,
    };

public:
    struct Question
    {
        uint16      nId 			;
        std::string strDescribe		;
        std::string strAnswerDesc1	;	
        std::string strAnswerDesc2	;	
        std::string strAnswerDesc3	;	
        std::string strAnswerDesc4	;	

        Question() : nId(0),  strDescribe(""), strAnswerDesc1(""), strAnswerDesc2(""), strAnswerDesc3(""), strAnswerDesc4("")
        { 
        }

        Question(const Question& xQuestion)
        {
            *this = xQuestion;
        }

        Question& operator = (const Question& xQuestion)
        {
            if (this != &xQuestion)
            {
                nId             = xQuestion.nId;
                strDescribe     = xQuestion.strDescribe;
                strAnswerDesc1  = xQuestion.strAnswerDesc1;
                strAnswerDesc2  = xQuestion.strAnswerDesc2;
                strAnswerDesc3  = xQuestion.strAnswerDesc3;
                strAnswerDesc4  = xQuestion.strAnswerDesc4;
            }

            return *this;
        }

        bool operator == (const int Id) { return (this->nId == Id); }

        const uint16 GetID() const { return nId; }
        const char*  GetQuestionDesc()  const { return strDescribe.c_str(); }
        const char*  GetAnswerDesc1()   const { return strAnswerDesc1.c_str(); }
        const char*  GetAnswerDesc2()   const { return strAnswerDesc2.c_str(); }
        const char*  GetAnswerDesc3()   const { return strAnswerDesc3.c_str(); }
        const char*  GetAnswerDesc4()   const { return strAnswerDesc4.c_str(); }
        
    };

protected:
    QuestionConfig();
public:
    ~QuestionConfig();

    inline static QuestionConfig& Instance()
    {
        static QuestionConfig s_xQuestion;
        return s_xQuestion;
    }

    bool  LoadQuestionConfig(const char* szFile);
    bool  LoadAnswerConfig  (const char* szFile);

    bool    AddQuestion(Question &xQuestion, bool bReplace = false);
    bool    RemoveQuestion(uint16 Id);

    uint32  GetQuestionCount()  { return static_cast<uint32>(m_vecQuestion.size());  }
    uint32  GetAnswerCount()    { return static_cast<uint32>(m_vecAnswer.size());  }

    Question* GetQuestionById(uint16 Id)
    {
        if ( Id >= m_vecQuestion.size())
        { return NULL; }

        return &m_vecQuestion[Id];
    }

    uint8   GetCorrectAnswer(uint16 Id)
    {
        if ( Id >= m_vecAnswer.size())
        { return Answer_Invalid; }

        return m_vecAnswer[Id];
    }

    const std::vector<Question>& GetQuestionList() const{ return m_vecQuestion; }

private:
    std::vector<Question> m_vecQuestion;
    std::vector<uint8>    m_vecAnswer  ;

public:
    typedef std::vector<Question>::iterator QuestionIter;
};

#endif

