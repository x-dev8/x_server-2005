#ifndef __ITEMCOMPOSECONFIG_H__
#define __ITEMCOMPOSECONFIG_H__

/************************************************************************

    //�ºϳ�����, ��1 - n����ͬ����Ʒ�ϳ�һ���߼����µ���Ʒ

************************************************************************/
#include <vector>
#include <map>
#include "GlobalDef.h"

class ComposeData
{
protected:
    typedef std::map< unsigned short, float, std::greater<unsigned short> > ModulusContainer;
    typedef ModulusContainer::iterator                                      ModulusContainerIter;
    typedef ModulusContainer::const_iterator                                ModulusContainerConstIter;

public:
    ComposeData()
    {
        m_ustItemID     = 0;
        m_ustMaterialID = 0;
        m_ustNewItemID  = 0;
        m_nCostMoney    = 0;
        m_Modulus.clear();
        m_Modulus.insert( ModulusContainer::value_type( 0, 0.0f ) );
    }

    void SetItemID    ( unsigned short ustValue ) { m_ustItemID     = ustValue; }
    void SetMaterialID( unsigned short ustValue ) { m_ustMaterialID = ustValue; }
    void SetNewItemID ( unsigned short ustValue ) { m_ustNewItemID  = ustValue; }
    void SetCostMoney ( unsigned int   nMoney )   { m_nCostMoney    = nMoney  ; }

    void AddModulus   ( unsigned short count, float fValue ) { m_Modulus.insert( ModulusContainer::value_type( count, fValue) ); }

    unsigned short GetItemID()     const { return m_ustItemID    ; }
    unsigned short GetMaterialID() const { return m_ustMaterialID; }
    unsigned short GetNewItemID()  const { return m_ustNewItemID ; }
    unsigned int   GetCostMoney()  const { return m_nCostMoney   ; }

    float GetModulus( unsigned short ustCount ) const
    {
        ModulusContainerConstIter it = m_Modulus.find( ustCount );
        if ( it == m_Modulus.end() )
        { return 0.0f; }

        return it->second;
    }

    float GetModulus( unsigned short ustCount, unsigned short& activeCount ) const
    { 
        ModulusContainerConstIter it = m_Modulus.lower_bound( ustCount );
        if ( it == m_Modulus.end() )
        { return 0.0f; }

        activeCount = it->first;
        return it->second;
    }

private:
    unsigned short   m_ustItemID    ; // Ҫ�ϳɵ�ID
    unsigned short   m_ustMaterialID; // ��Ҫ�Ĳ���ID
    unsigned short   m_ustNewItemID ; // �����µ�ID 
    unsigned int     m_nCostMoney   ; // ���ѵĽ�Ǯ
    ModulusContainer m_Modulus      ; // ��Ӧ���ӵĸ���
};

class ComposeData2
{
public:
    struct SMaterial
    {
        unsigned short  nMaterialID ;
		unsigned short  nMaterialID2;	//�����ֶ�,�ȼ۲���ID
		unsigned short	nMaterialID3;	//�����ֶ�,�ȼ۲���ID
        unsigned short  nCount      ;
        unsigned short  nModulus    ;
    };

    void SetItemID    ( unsigned short ustValue ) { m_nItemID     = ustValue; }
    void SetNewItemID ( unsigned short ustValue ) { m_nNewItemID  = ustValue; }
    void SetCostMoney ( unsigned int   ustValue ) { m_nCostMoney  = ustValue; }
    void SetProbility ( unsigned short ustValue ) { m_nProbility  = ustValue; }

    unsigned short GetItemID()     const { return m_nItemID    ; }
    unsigned short GetNewItemID()  const { return m_nNewItemID ; }
    unsigned int   GetCostMoney()  const { return m_nCostMoney ; }
    unsigned short GetProbility()  const { return m_nProbility ; }

    void AddMaterial(SMaterial xMaterial){  m_vecMaterial.push_back( xMaterial ); }

    const std::vector<ComposeData2::SMaterial> & GetMaterialList() const { return m_vecMaterial; }

public:
    ComposeData2()
    {
        m_nItemID     = 0;
        m_nNewItemID  = 0;
        m_nCostMoney  = 0;
        m_nProbility  = 0;

        m_vecMaterial.clear();
    }

private:
    unsigned short   m_nItemID      ; // Ҫ�ϳɵ�ID
    unsigned short   m_nNewItemID   ; // �����µ�ID 
    unsigned int     m_nCostMoney   ; // ���ѵĽ�Ǯ
    unsigned short   m_nProbility   ; // ��Ӧ��������

    std::vector<SMaterial> m_vecMaterial;   // ԭ��
};


#define theItemComposeConfig ItemComposeConfig::Instance()

class ItemComposeConfig
{
protected:
    typedef std::map< unsigned short, ComposeData > ComposeDataMap;
    typedef ComposeDataMap::iterator ComposeDataMapIter;
    typedef ComposeDataMap::const_iterator ComposeDataMapConstIter;

    typedef std::multimap< unsigned short, ComposeData2 > ComposeData2Map ;
    typedef ComposeData2Map::iterator ComposeData2MapIter ;
    typedef ComposeData2Map::const_iterator ComposeData2MapConstIter ;

    ItemComposeConfig()
    {
        m_mapComposeData.clear();
        m_mapComposeData2.clear();
    }

    bool AddItemComposeData( const ComposeData& xData )
    {
        ComposeDataMapIter iter = m_mapComposeData.find( xData.GetItemID() );
        if ( iter != m_mapComposeData.end() )
        { return false; }

        return m_mapComposeData.insert( std::make_pair( xData.GetItemID(), xData ) ).second;
    }

    bool AddItemComposeData2( const ComposeData2& xData )
    {
//         ComposeData2MapIter iter = m_mapComposeData2.find( xData.GetItemID() );
//         if ( iter != m_mapComposeData2.end() )
//         { return false; }
// 
//         return m_mapComposeData2.insert( std::make_pair( xData.GetItemID(), xData ) ).second;
		m_mapComposeData2.insert( std::make_pair( xData.GetItemID(), xData) );
		return true;
    }

public:
    static ItemComposeConfig& Instance()
    {
        static ItemComposeConfig s_xConfig;
        return s_xConfig;
    }

    const ComposeData* GetItemComposeData( unsigned short ustItemID ) const
    {
        ComposeDataMapConstIter iter = m_mapComposeData.find( ustItemID );
        if ( iter == m_mapComposeData.end() )
        { return NULL; }

        return &( iter->second );
    }

    const ComposeData2* GetItemComposeData2( unsigned short ustItemID ) const
    {
        ComposeData2MapConstIter iter = m_mapComposeData2.find( ustItemID );
        if ( iter == m_mapComposeData2.end() )
        { return NULL; }

        return &( iter->second );
    }
	const ComposeData2* GetComposeData( SCharItem* pCharItem[], int nItemCount );	//ƥ�䱦ʯ�ϳ��䷽
	const ComposeData2* GetComposeDataNew(uint16 itemid, int nCount);

    bool LoadItemComposeConfig  ( const char* szFile );
    bool LoadItemComposeConfig2 ( const char* szFile );

private:
    ComposeDataMap m_mapComposeData;
    ComposeData2Map m_mapComposeData2;
};

#endif