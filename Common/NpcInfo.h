#ifndef __NPC_INFO_H__
#define __NPC_INFO_H__

#include "MeRTLibs.h"
#include "Array.h"
#ifdef _CLIENT_
#include "NpcAction.h"
#endif

#define theNpcInfo NpcInfo::Instance()   //ʵ���ӿ�

#define NpcErrorId 0xffff

#define File_Success 0        //���سɹ�
#define File_Error 1        //�����ļ�����
#define Param_Error 2        //��������    
#define Attribute_Error 3    //�ֶ����Դ���

#pragma warning ( push )
#pragma warning ( disable : 4267 )
class NpcInfo
{
/// typedef and structure.
public:


	struct SaluteData
	{
		short shId;
		short shType1;
		short shMin;
		short shMax;
		short shNeed;
		short shType2;
		std::string strSaluteName;
		short shProbability;
		short shDelayTime;
		short shView;
	};

	struct ActionData
    {
        std::string strAnimName;    // ��������
        short shProbability;    // ����
    };
    struct TalkData
    {
        int shStringId;       // ��ӦNpc.string
        short shProbability;    // ����
    };
    struct NpcActionData
    {
        short shId;
		short CycleId;//ѭ��id
        short shElapseTime;
        short shNextId;         // ��ɺ��¸�NpcActionData��ӦshId
        std::vector<ActionData> vctActions; // �����б�
        std::vector<TalkData> vctTalks;     // ˵���б�
    };

    struct FightInfo
    {
        enum EConstDefine
        {
            ECD_SkillCount = 3,
        };

        struct SSkillInfo
        {
            uint16 skillId   ; // ����ʹ�õļ���
            uint8  skillLevel; // ��ʹ�ü��ܵĵȼ�
            uint16 skillRate ; // ��ʹ�ü��ܵ�ʹ�ø���

            SSkillInfo()
            {
                skillId    = 0;
                skillLevel = 0;
                skillRate  = 0;
            }
        };

        Array<SSkillInfo, ECD_SkillCount> skills; // ����ʹ�õļ���
		short		npcId				  ;
        float       bodyLength            ; // �������ʹ�С
        uint16      level                 ; // ����
        //////////////////////////////////////////////////////////////////////////
        // ����ս������
        int         hpMax                ; // HP����
        int         mpMax                ; // MP����
        float       attackPhysics        ; // ��������
        float       attackMagic          ; // ħ�������� 
        float       defendPhysics        ; // �������
        float       defendMagic          ; // ħ������
        float       attackSpeed          ; // �����ٶ�
        float       moveSpeed            ; // �ƶ��ٶ�
        float       hpRestore            ; // HP�ָ�
        float       mpRestore            ; // MP�ָ�
        int16       exact                ; // ������
        int16       dodge                ; // ������
        int16       critical             ; // ������
        int16       tenacity             ; // ����
        int16       criticalIntensity    ; // �����˺�
        int16       backStrike           ; // �����˺�
        int16       backStrikeResist     ; // ��������
        int16       breakStrike          ; // �Ƽ��˺�
        int16       stabStrike           ; // �ᴩ�˺�
        int16       elementStrike        ; // Ԫ���˺�
        int16       toxinStrike          ; // �����˺�
        int16       spiritStrike         ; // �����˺�
        int16       breakResist          ; // �Ƽ׿���
        int16       stabResist           ; // �ᴩ����
        int16       elementResist        ; // Ԫ�ؿ���
        int16       toxinResist          ; // ���ؿ���
        int16       spiritResist         ; // ������
        //////////////////////////////////////////////////////////////////////////
        uint16      normalAttackMin       ; // ��ͨ������Сϵ��
        uint16      normalAttackMax       ; // ��ͨ�������ϵ��
        short       view                  ; // ��Ұ
        short       fightView             ; // ս����Ұ
        uint32      catchTime             ; // ׷��ʱ��
        float       moveStep              ; // �ܲ�����
        float       idleMoveSpeed         ; // ����ʱ�ƶ��ٶ�
        float       idleMoveStep          ; // ���߲���
        int         reliveTime            ; // ����ʱ��
        std::string deadScript            ; // ���������ű���ַ
        bool        isInitiative          ; // �Ƿ�������
        uint32      disappearTime         ; // ��ʧʱ��
        int         enmityDecRate         ; // ���˥������
        int         enmityView            ; // ���
        int         maxRange              ; // �����Χ
        int         changePassive         ; // ս��ʱ�Ƿ��Ϊ������
        int         passiveTime           ; // ��������ʱ��
        int         baseEnmityRange       ; // ������ޱ�������
        uint16      integral              ; // ����
        uint16      routeId               ; // ·��Id
		int			fightType			  ; // ����Ŀ�����ͣ�0 ֻ���ˣ� 1 ������֣����������ˣ� 2 ����
		int			fightCamp			  ; // ��Ӫ

        FightInfo(){ Clear(); }

        void Clear()
        {
			npcId			  = 0;
            bodyLength        = 0;
            level             = 0;   

            hpMax             = 0;
            mpMax             = 0;
            attackPhysics     = 0;
            attackMagic       = 0;
            defendPhysics     = 0;
            defendMagic       = 0;
            attackSpeed       = 0;
            moveSpeed         = 0;
            hpRestore         = 0;
            mpRestore         = 0;
            exact             = 0;
            dodge             = 0;
            critical          = 0;
            tenacity          = 0;
            criticalIntensity = 0;
            backStrike        = 0;
            backStrikeResist  = 0;
            breakStrike       = 0;
            stabStrike        = 0;
            elementStrike     = 0;
            toxinStrike       = 0;
            spiritStrike      = 0;
            breakResist       = 0;
            stabResist        = 0;
            elementResist     = 0;
            toxinResist       = 0;
            spiritResist      = 0;
            
            normalAttackMin   = 0;
            normalAttackMax   = 0;
            view              = 0;
            fightView         = 0;
            catchTime         = 0;
            moveStep          = 0;
            idleMoveSpeed     = 0;
            idleMoveStep      = 0;
            reliveTime        = 0;
            isInitiative      = 0;
            disappearTime     = 0;
            enmityDecRate     = 0;
            enmityView        = 0;
            maxRange          = 0;
            changePassive     = 0;
            passiveTime       = 0;
            baseEnmityRange   = 0;
            integral          = 0;
            routeId           = 0;
			fightType		  = 0;
			fightCamp		  = 0;
        }
    };

    struct Npc
    {     
        Npc() { Clear(); }

        int                        id       ;          // id
        int                        dynamicId;          // ��̬ID
        std::string                name     ;          // ����
        std::string                pinyin   ;          // ƴ��
        int                        mapId    ;          // ��ͼid
        int                        level    ;          // �ȼ�
        int                        type     ;          // ����
        int                        modelId  ;          // ģ��ID
        float                      x        ;          // x����
        float                      y        ;          // y����
        float                      z        ;          // z����
        int                        movePath ;          // npc�ƶ�·������
        int                        direction;          // ����
        bool                       canChangeDirection; // �Ƿ��ܸı䳯��
        std::string                triggerScript;      // �����ű�λ��
        std::string                actionScript ;      // ��Ϊ�ű�
        bool                       isMiniShow   ;      // �Ƿ���С��ͼ��ʾ 
        bool                       isWorldShow  ;      // �Ƿ��������ͼ����ʾ
        bool                       isCollision  ;      // �Ƿ��赲
        std::string                title        ;      // �ƺ�
        std::string                tip          ;      // ˵��
        std::string                strHeadPicture  ;   // ͷ��
        float                      bodyScale    ;      // ��������
        bool                       isDynamicCollision; // �ƶ��д���ײ����Ӱ��Ѱ·������
        unsigned char              uchCountryID ;      // ����
        unsigned char              phyle        ;      // ����
        int                        nTaskMenu    ;
        std::vector<NpcActionData> vctActionData;
		std::vector<SaluteData> vctSaluteData;
		std::string strSoundPath;			           // ����
        std::vector<FightInfo>     fightData    ;      // ս������

		float					   gutUIScale	;	   // GutUI����ֵ
		short					   gutUIOffsetX ;	   // GutUI X������ֵ
		short					   gutUIOffsetY	;	   // GutUI Y������ֵ


	
		//int						   ActionDataid;       //����+˵��ID
		//int						   npctime;			   //����ʱ��(��)
		//int						   NextId;			   //��һ������+˵��ID
		//std::string                ActionName;		   //��������
		//int						   ActionProbability;  //��������
		//int						   TalkStringid;	   //˵�Ļ���STRING�е�ID
		//int                        TalkshProbability;  //˵���ĸ���

	

#ifdef _CLIENT_
		CNpcAction                 npcAct;
#endif
        void operator =(Npc& npc)
        {
            id        = npc.id       ;
            dynamicId = npc.dynamicId;
            name      = npc.name     ;
            pinyin    = npc.pinyin   ;
            mapId     = npc.mapId    ;
            level     = npc.level    ;
            type      = npc.type     ;
            modelId   = npc.modelId  ;
            x         = npc.x        ;
            y         = npc.y        ;
            z         = npc.z        ;
            movePath  = npc.movePath ;
            direction = npc.direction;
            canChangeDirection = npc.canChangeDirection;
            triggerScript      = npc.triggerScript     ;
            actionScript       = npc.actionScript      ;
            isMiniShow         = npc.isMiniShow        ;
            isWorldShow        = npc.isWorldShow       ;
            isCollision  = npc.isCollision;
            title        = npc.title;
            tip          =  npc.tip;
            strHeadPicture  = npc.strHeadPicture;
            bodyScale    = npc.bodyScale;
            uchCountryID = npc.uchCountryID;
            nTaskMenu    = npc.nTaskMenu;
			strSoundPath = npc.strSoundPath;
			gutUIScale   = npc.gutUIScale;
			gutUIOffsetX = npc.gutUIOffsetX;
			gutUIOffsetY = npc.gutUIOffsetY;
	
			/*ActionDataid = npc.ActionDataid;
			npctime      = npc.npctime;
			NextId		 = npc.NextId;
			ActionName   = npc.ActionName;
			ActionProbability  = npc.ActionProbability;
			TalkStringid = npc.TalkStringid;
			TalkshProbability = npc.TalkshProbability;*/
	
            int nSize = npc.vctActionData.size();
            for (int i = 0;i < nSize;++i)
            {
                NpcActionData actionData;
                actionData.shId         = npc.vctActionData[i].shId;
                actionData.shElapseTime = npc.vctActionData[i].shElapseTime;
                actionData.shNextId     = npc.vctActionData[i].shNextId;

                int nAmount = npc.vctActionData[i].vctActions.size();
                for (int j = 0;j < nAmount;++j)
                    actionData.vctActions.push_back(npc.vctActionData[i].vctActions[j]);

                nAmount = npc.vctActionData[i].vctTalks.size();
                for (int z = 0;z < nAmount;++z)
                    actionData.vctTalks.push_back(npc.vctActionData[i].vctTalks[z]);

                vctActionData.push_back(actionData);
            }

			fightData = npc.fightData;
#ifdef _CLIENT_
			nSize = npc.npcAct.GetSize();
			for (int i = 0;i < nSize;++i)
			{
				npcAct.AddAction(*npc.npcAct.GetOneActionByIndex(i));
			}
#endif
        }
        void Clear()
        {
            id = NpcErrorId;
            dynamicId = -1;
            name.clear();
            mapId = -1;
            level = -1;
            type = -1;
            modelId = -1;
            x = 0.0f;
            y = 0.0f;
            z = 40000.f;
            movePath = -1;
            direction = 0;
            canChangeDirection = false;
            triggerScript.clear();
            actionScript.clear();
            isMiniShow = true;
            isWorldShow = true;
            isCollision = false;
            title.clear();
            tip.clear();
            nTaskMenu = -1;
            strHeadPicture.clear();
            bodyScale = 0.0f;
            uchCountryID = 0;
            phyle = 0;
			strSoundPath.clear();
			gutUIScale = 0.0f;	   // GutUI����ֵ zhuxincong 2012.7.18
			gutUIOffsetX = 0;	   // GutUI X������ֵ
			gutUIOffsetY = 0;	// GutUI Y������ֵ
			

			//ActionDataid = 0;       //����+˵��ID
			//npctime = 0;			   //����ʱ��(��)
			//NextId = 0;			   //��һ������+˵��ID
			//ActionName.clear();		   //��������
			//ActionProbability = 0;  //��������
			//TalkStringid = 0;	   //˵�Ļ���STRING�е�ID
			//TalkshProbability = 0;  //˵���ĸ���

			
#ifdef _CLIENT_
			npcAct.Clear();
#endif
        }
    };
    
    typedef std::multimap<int, Npc> Npcs;
    typedef Npcs::iterator NpcsIter;
#ifdef GAME_CLIENT
    typedef std::multimap<std::string, Npc> DynamicCollNpcs;
    typedef DynamicCollNpcs::iterator DynCollNpcsIter;
#endif
/// Constructor.
protected:
	NpcInfo(): m_bDialogPic(false) { npcs_.clear(); }
    
public:
    inline static NpcInfo& Instance()
    {
        static NpcInfo s_xNpcInfo;

        return s_xNpcInfo;
    }

/// Function.
public:
    ~NpcInfo() {}

    int LoadConfig( const char* path );

    Npc* GetNpcByStaticId(int id);   //id����
    Npc* FindNpcByDynamicId(int id); //��̬id
    Npc* GetNpcByName(std::string name,uint32 mapId = -1);  //���ֲ���

    void AddNpc(Npc &xNpc);
    inline int GetNpcCount() { return static_cast<int>(npcs_.size()); }

    uint32 GetNpcs(uint32 id, std::vector<Npc*>& outResult );   //Npcid���� 
    Npc* GetNpc(uint32 id, uint32 mapId );   //ID : Npcid MapId :MpaID
	int SaveNpcConfig( const char* path );


    struct FourNpc
    {
        Npc *(FourCountryNpc)[4];
    };

    FourNpc* GetFourNpc(int nID)
    {
        static FourNpc FNpc;

        pair<NpcsIter, NpcsIter> IterNpcContainer;
        IterNpcContainer = npcs_.equal_range(nID);
        NpcInfo::NpcsIter NIter = IterNpcContainer.first;
        if (NIter == IterNpcContainer.second)
        {
            return NULL;
        }

        int nCount = 0;
        while ( (NIter != IterNpcContainer.second) && (nCount < 4) )
        {
            FNpc.FourCountryNpc[nCount++] = &((NIter++)->second);
        }
        return &FNpc;
    }
    
#ifdef GAME_CLIENT
    Npc* GetDynamicCollNpcByName(std::string name, uint32 mapId);
#endif 

    //int SaveConfig( const char* path );

/// Attribute
public:
    Npcs npcs_;

#ifdef GAME_CLIENT
    DynamicCollNpcs dynamicCollNpcs_;    // ����̬��ײ���ܵ�NPC
#endif 

	// ������
	bool IsDialogPic() const { return m_bDialogPic; }
protected:
	void SetDialogPic(bool flag) { m_bDialogPic = flag; }
	bool m_bDialogPic;
};

#pragma warning ( pop )

#endif // __NPC_INFO_H__

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

