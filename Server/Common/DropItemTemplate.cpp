#include "DropItemTemplate.h"
#include "SearchFile.h"
#include "NewWithDebug.h"

TSingleton<CItemDropTemplate> theItemDropTemplate;

void BindItemDropTemplate()
{
    std::vector<std::string> vecFileList = SearchFileToVector( "itemdrop", "*.txt" );
  

    theItemDropTemplate.Register( "<void>", CNewWithDebug<CItemDropTemplate>::Alloc(1, "BindItemDropTemplate()中Register添加CItemDropTemplate"));

    size_t iSize = vecFileList.size();
    for( size_t i = 0; i < iSize; i++ )
    {
        std::string strFileName = "itemdrop\\";
        strFileName += vecFileList[i];
        CItemDropTemplate *pIDT = CNewWithDebug<CItemDropTemplate>::Alloc(1, "BindItemDropTemplate()中创建CItemDropTemplate");
        pIDT->LoadFromFile( strFileName.c_str() );
        std::string strName = vecFileList[i];
        strName.erase( strName.find_first_of(".") );
        theItemDropTemplate.Register( strName.c_str(), pIDT );
    }
}

class CAutoBinding
{
public:
    CAutoBinding();
};

CAutoBinding::CAutoBinding()
{
    BindItemDropTemplate();
}

//CAutoBinding theAutoBinding;

CItemDropTemplate *GetItemDropTemplate( const char *szTempName )
{
    CItemDropTemplate *pIDT = theItemDropTemplate.Lookup( szTempName );
    if( pIDT )
        return pIDT;
    
    return theItemDropTemplate.Lookup( "<void>" );
}

//////////////////////////////////////////////////////////////////////////

CItemDropTemplate::CItemDropTemplate()
{
    //CItemDropTemplate::ItemDropRate idr;

    //idr.strName = "铜剑";
    //idr.fRate = 1.0f;
    //m_vecItemDropRate.push_back(idr);
    //

    //idr.strName = "大刀";
    //idr.fRate = 1.0f;
    //m_vecItemDropRate.push_back(idr);
    //    

    //idr.strName = "左文字";
    //idr.fRate = 1.0f;
    //m_vecItemDropRate.push_back(idr);


    //idr.strName = "袖里剑";
    //idr.fRate = 1.0f;
    //m_vecItemDropRate.push_back(idr);
}

CItemDropTemplate::~CItemDropTemplate()
{

}

bool CItemDropTemplate::LoadFromFile( const char *szFileName )
{
    FILE *fp = fopen( szFileName, "rt" );
    if( fp == NULL )
        return false;
    char szItemName[64];
    float fItemRate;
    while( fscanf( fp, "%s %f\n", szItemName, &fItemRate ) != EOF )
    {
        CItemDropTemplate::ItemDropRate idr;
        idr.strName = szItemName;
        idr.fRate = fItemRate;

        m_vecItemDropRate.push_back( idr );
    }
    fclose(fp);
    return true;
}
