#include "CharacterTimeStatus.h"

CharacterTimeStatus::CharacterTimeStatus() : m_fsExtend(efs_Normal )
{
}

void CharacterTimeStatus::Process()
{
	for ( int n=0; n<efs_StatusMax; n++ )
	{
		m_fsExtendTimers[n].Run();
	}
    switch(m_fsExtend)
    {
    case efs_Normal:
        break;
    case efs_CanNotNormalAttack:
		if( IsCannotNormalAttackDone() )
		{
			m_fsExtend = efs_Normal;
		}
        break;
    case efs_ReliveTime:
		if( IsReliveDone() )
		{
			m_fsExtend = efs_Normal;
		}
        break;
	case efs_ActionTime:
		if( IsActionDone() )
		{
			m_fsExtend = efs_Normal;
		}
		break;
    default:
        // ToLog(false);
        break;
    }
}

