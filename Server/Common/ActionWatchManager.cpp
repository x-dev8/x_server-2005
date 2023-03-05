#include "ActionWatchManager.h"
#include "GamePlayer.h"
#include "GameTime.h"
#include "XmlStringLanguage.h"

//MsgReqScript             ����ű�
//MsgScriptAckShowQuestDlg �������� MsgScriptReqShowQuestDlg �յ���ʾ�����

//MsgAbandonTask           ��������

ActionWatchManager::ActionWatchManager() : _pBeWatcher( NULL )
{
}

long ActionWatchManager::Action( uint16 actionId )
{
    return ER_Success;

    ItrActionWatchContainer it = _actionWatchs.find( actionId );

    if ( it != _actionWatchs.end() )
    { // �ҵ�
        SWatchData& data = it->second;
        if ( !GameTime::IsPassCurrentTime( data.startTime, data.limitIntervalTime ) )
        { // ������ʱ����
            ++data.count;
            if ( data.count > data.limitCount )
            { // �����涨����
                if ( _pBeWatcher)
                { 
                    //_pBeWatcher->Log("�����Ϊ action[%d] count[%d:%d] limitTime[%u]", actionId, data.count, data.limitCount, data.limitIntervalTime );
					 _pBeWatcher->Log(theXmlString.GetString(eServerLog_WaiGuaXingWei), actionId, data.count, data.limitCount, data.limitIntervalTime );

                    MsgAckResult msg;
                    msg.result = ER_ActionHighFrequency;
                    GettheServer().SendMsgToSingle( &msg, _pBeWatcher );
                }
                return ER_ActionHighFrequency;
            }

            return ER_Success;
        }

        data.startTime = HQ_TimeGetTime();
        data.count     = 1;
        return ER_Success;
    }
    
    // ����������
    SWatchData data;
    data.count     = 1;
    data.startTime = HQ_TimeGetTime();
    _actionWatchs.insert( ActionWatchContainer::value_type( actionId, data ) );
    return ER_Success;
}
