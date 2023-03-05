#include "QuestionConfig.h"
#include "tstring.h"
#include "RapidXml/MeRapidXml.h"
#include "application_config.h"


QuestionConfig::QuestionConfig()
{
    m_vecQuestion.clear();
    m_vecAnswer.clear()  ;
}

QuestionConfig::~QuestionConfig()
{

}

bool QuestionConfig::AddQuestion(QuestionConfig::Question &xQuestion, bool bReplace /* = false*/)
{
    QuestionIter iter = find(m_vecQuestion.begin(), m_vecQuestion.end(), xQuestion.nId);
    if (iter != m_vecQuestion.end())
    {
        if (bReplace)
        {
            *iter = xQuestion;
        }
        return bReplace;
    }

    if( xQuestion.nId >= m_vecQuestion.size() )
    {  m_vecQuestion.resize( xQuestion.nId + 100 ); }

    m_vecQuestion[xQuestion.nId] = xQuestion;

    return true;
}

bool QuestionConfig::RemoveQuestion(uint16 Id)
{
    QuestionIter iter = find(m_vecQuestion.begin(), m_vecQuestion.end(), Id);
    if (iter != m_vecQuestion.end())
    {
        m_vecQuestion.erase(iter);
        return true;
    }

    return false;
}

bool QuestionConfig::LoadQuestionConfig(const char* szFile)
{
    if (szFile == NULL || *szFile == 0)
    { return false;	}

    m_vecQuestion.clear();

    MeXmlDocument xMeXml;
    if (!xMeXml.LoadFile(szFile, 1))
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
    if (pRoot == NULL )
    { return false; }

    MeXmlElement* pQuestions = pRoot->FirstChildElement("Questions");
    if (pQuestions == NULL) 
    { return false; }

    MeXmlElement* pQuestionElement = pQuestions->FirstChildElement("Question");
    while (pQuestionElement != NULL)
    {	
        Question question;

        int nId = -1;
        pQuestionElement->Attribute("Id", &nId);
        question.nId = nId;

        Common::_tstring strDescribe;
        strDescribe.fromUTF8( pQuestionElement->Attribute("Describe") );
        if (strDescribe.empty()) { return false; }
        question.strDescribe = strDescribe;

        Common::_tstring strAnswerDesc1;
        strAnswerDesc1.fromUTF8( pQuestionElement->Attribute("AnswerDesc1") );
        if (strAnswerDesc1.empty()) { return false; }
        question.strAnswerDesc1 = strAnswerDesc1;

        Common::_tstring strAnswerDesc2;
        strAnswerDesc2.fromUTF8( pQuestionElement->Attribute("AnswerDesc2") );
        if (strAnswerDesc2.empty()) { return false; }
        question.strAnswerDesc2 = strAnswerDesc2;

        Common::_tstring strAnswerDesc3;
        strAnswerDesc3.fromUTF8( pQuestionElement->Attribute("AnswerDesc3") );
        if (strAnswerDesc3.empty()) { return false; }
        question.strAnswerDesc3 = strAnswerDesc3;

        Common::_tstring strAnswerDesc4;
        strAnswerDesc4.fromUTF8( pQuestionElement->Attribute("AnswerDesc4") );
        if (strAnswerDesc4.empty()) { return false; }
        question.strAnswerDesc1 = strAnswerDesc4;

        if (!AddQuestion(question)) 
        { return false; }

        //next
        pQuestionElement = pQuestionElement->NextSiblingElement();
    }

    return true;
}

bool QuestionConfig::LoadAnswerConfig  (const char* szFile)
{
    if (szFile == NULL || *szFile == 0)
    { return false;	}

    m_vecAnswer.clear();

    MeXmlDocument xMeXml;
    if (!xMeXml.LoadFile(szFile, 1))
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
    if (pRoot == NULL )
    { return false; }

    MeXmlElement* pAnswers = pRoot->FirstChildElement("Answers");
    if (pAnswers == NULL) 
    { return false; }

    MeXmlElement* pAnswerElement = pAnswers->FirstChildElement("Answer");
    while (pAnswerElement != NULL)
    {	
        int nId = -1;
        pAnswerElement->Attribute("Id", &nId);
        if ( nId < 0 )
        { return false; }
        
        int nCorrectAnswer = -1;
        pAnswerElement->Attribute("CorrectAnswer", &nCorrectAnswer);
        if (nCorrectAnswer <= Answer_Invalid || nCorrectAnswer >= Answer_Max )
        { return false; }

        if( nId >= m_vecAnswer.size() )
        { m_vecAnswer.resize( nId + 100 ); }

        m_vecAnswer[nId] = nCorrectAnswer;
    }
    
    return true;
}
