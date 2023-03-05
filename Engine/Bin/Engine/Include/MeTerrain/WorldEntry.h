/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	WorldEntry.h
* Create: 	10/06/2006
* Desc:		±à¼­Æ÷Ê¹ÓÃ
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef _NDL_WORLDENTRY_H__
#define _NDL_WORLDENTRY_H__
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
class CWorldEntry		/*: public NiRefObject*/
{
public:
						CWorldEntry();
						~CWorldEntry();
						
						// Get			
	const Vector&		GetPos() const;			
	Vector&			GetPos();			
	const Vector&		GetRot() const;			
	Vector&			GetRot();			
	const flt32&		GetScl() const;			
						
						// Set
	virtual void		SetPos( const Vector& pos );
	virtual void		SetRot( const Vector& rot );
	virtual void		SetScl( const flt32	& scl );
		
protected:
	Vector			m_pos;
	Vector			m_rot;
	flt32				m_scl;
	
};


#endif	// _NDL_WORLDENTRY_H__
