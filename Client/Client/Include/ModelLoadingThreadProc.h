#pragma once

#include <MeFoundation/MeFoundationPCH.h>
#include <MeFoundation/MeLoopThreadProcedure.h>

class ModelLoadingThreadProc :
	public MeLoopThreadProcedure
{
public:
	ModelLoadingThreadProc();
	virtual ~ModelLoadingThreadProc();

	// post process the processed request
	virtual void MainThreadProcess();

protected:
	bool LoadMexFromReq2( MeLoopThreadReq* pReq );

	virtual void ClearAckList();


protected:
	// store string list
	typedef std::map< std::string, bool > MexBackListStrings;
	MexBackListStrings m_MexBackListString;

	// store integer list
	typedef std::map< int, bool > MexBackListInts;
	MexBackListInts m_MexBackListInt;
};