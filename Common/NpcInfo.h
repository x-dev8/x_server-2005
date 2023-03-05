#ifndef __NPC_INFO_H__
#define __NPC_INFO_H__

#include "MeRTLibs.h"
#include "Array.h"
#ifdef _CLIENT_
#include "NpcAction.h"
#endif

#define theNpcInfo NpcInfo::Instance()   //实例接口

#define NpcErrorId 0xffff

#define File_Success 0        //加载成功
#define File_Error 1        //加载文件错误
#define Param_Error 2        //参数错误    
#define Attribute_Error 3    //字段属性错误

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
        std::string strAnimName;    // 动作名称
        short shProbability;    // 概率
    };
    struct TalkData
    {
        int shStringId;       // 对应Npc.string
        short shProbability;    // 概率
    };
    struct NpcActionData
    {
        short shId;
		short CycleId;//循环id
        short shElapseTime;
        short shNextId;         // 完成后下个NpcActionData对应shId
        std::vector<ActionData> vctActions; // 动作列表
        std::vector<TalkData> vctTalks;     // 说话列表
    };

    struct FightInfo
    {
        enum EConstDefine
        {
            ECD_SkillCount = 3,
        };

        struct SSkillInfo
        {
            uint16 skillId   ; // 可能使用的技能
            uint8  skillLevel; // 可使用技能的等级
            uint16 skillRate ; // 可使用技能的使用概率

            SSkillInfo()
            {
                skillId    = 0;
                skillLevel = 0;
                skillRate  = 0;
            }
        };

        Array<SSkillInfo, ECD_SkillCount> skills; // 可能使用的技能
		short		npcId				  ;
        float       bodyLength            ; // 怪物体型大小
        uint16      level                 ; // 级别
        //////////////////////////////////////////////////////////////////////////
        // 二级战斗属性
        int         hpMax                ; // HP上限
        int         mpMax                ; // MP上限
        float       attackPhysics        ; // 物理攻击力
        float       attackMagic          ; // 魔法攻击力 
        float       defendPhysics        ; // 物理防御
        float       defendMagic          ; // 魔法防御
        float       attackSpeed          ; // 攻击速度
        float       moveSpeed            ; // 移动速度
        float       hpRestore            ; // HP恢复
        float       mpRestore            ; // MP恢复
        int16       exact                ; // 命中率
        int16       dodge                ; // 闪避率
        int16       critical             ; // 暴击率
        int16       tenacity             ; // 韧性
        int16       criticalIntensity    ; // 暴击伤害
        int16       backStrike           ; // 背击伤害
        int16       backStrikeResist     ; // 背击抗性
        int16       breakStrike          ; // 破甲伤害
        int16       stabStrike           ; // 贯穿伤害
        int16       elementStrike        ; // 元素伤害
        int16       toxinStrike          ; // 毒素伤害
        int16       spiritStrike         ; // 精神伤害
        int16       breakResist          ; // 破甲抗性
        int16       stabResist           ; // 贯穿抗性
        int16       elementResist        ; // 元素抗性
        int16       toxinResist          ; // 毒素抗性
        int16       spiritResist         ; // 精神抗性
        //////////////////////////////////////////////////////////////////////////
        uint16      normalAttackMin       ; // 普通攻击最小系数
        uint16      normalAttackMax       ; // 普通攻击最大系数
        short       view                  ; // 视野
        short       fightView             ; // 战斗视野
        uint32      catchTime             ; // 追击时间
        float       moveStep              ; // 跑步步长
        float       idleMoveSpeed         ; // 空闲时移动速度
        float       idleMoveStep          ; // 行走步长
        int         reliveTime            ; // 复活时间
        std::string deadScript            ; // 怪物死亡脚本地址
        bool        isInitiative          ; // 是否主动怪
        uint32      disappearTime         ; // 消失时间
        int         enmityDecRate         ; // 仇恨衰减比率
        int         enmityView            ; // 仇恨
        int         maxRange              ; // 最大活动范围
        int         changePassive         ; // 战斗时是否变为被动怪
        int         passiveTime           ; // 被动持续时间
        int         baseEnmityRange       ; // 基础仇恨保持区域
        uint16      integral              ; // 积分
        uint16      routeId               ; // 路径Id
		int			fightType			  ; // 攻击目标类型（0 只打人， 1 主动打怪，不主动打人， 2 都打）
		int			fightCamp			  ; // 阵营

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
        int                        dynamicId;          // 动态ID
        std::string                name     ;          // 名称
        std::string                pinyin   ;          // 拼音
        int                        mapId    ;          // 地图id
        int                        level    ;          // 等级
        int                        type     ;          // 类型
        int                        modelId  ;          // 模型ID
        float                      x        ;          // x坐标
        float                      y        ;          // y坐标
        float                      z        ;          // z坐标
        int                        movePath ;          // npc移动路径索引
        int                        direction;          // 朝向
        bool                       canChangeDirection; // 是否能改变朝向
        std::string                triggerScript;      // 触发脚本位置
        std::string                actionScript ;      // 行为脚本
        bool                       isMiniShow   ;      // 是否在小地图显示 
        bool                       isWorldShow  ;      // 是否在世界地图上显示
        bool                       isCollision  ;      // 是否阻挡
        std::string                title        ;      // 称号
        std::string                tip          ;      // 说明
        std::string                strHeadPicture  ;   // 头像
        float                      bodyScale    ;      // 体型修正
        bool                       isDynamicCollision; // 移动中带碰撞，会影响寻路，慎用
        unsigned char              uchCountryID ;      // 国家
        unsigned char              phyle        ;      // 种族
        int                        nTaskMenu    ;
        std::vector<NpcActionData> vctActionData;
		std::vector<SaluteData> vctSaluteData;
		std::string strSoundPath;			           // 声音
        std::vector<FightInfo>     fightData    ;      // 战斗属性

		float					   gutUIScale	;	   // GutUI缩放值
		short					   gutUIOffsetX ;	   // GutUI X轴修正值
		short					   gutUIOffsetY	;	   // GutUI Y轴修正值


	
		//int						   ActionDataid;       //动作+说话ID
		//int						   npctime;			   //消耗时间(秒)
		//int						   NextId;			   //下一个动作+说话ID
		//std::string                ActionName;		   //动作名字
		//int						   ActionProbability;  //动作概率
		//int						   TalkStringid;	   //说的话在STRING中的ID
		//int                        TalkshProbability;  //说话的概率

	

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
			gutUIScale = 0.0f;	   // GutUI缩放值 zhuxincong 2012.7.18
			gutUIOffsetX = 0;	   // GutUI X轴修正值
			gutUIOffsetY = 0;	// GutUI Y轴修正值
			

			//ActionDataid = 0;       //动作+说话ID
			//npctime = 0;			   //消耗时间(秒)
			//NextId = 0;			   //下一个动作+说话ID
			//ActionName.clear();		   //动作名字
			//ActionProbability = 0;  //动作概率
			//TalkStringid = 0;	   //说的话在STRING中的ID
			//TalkshProbability = 0;  //说话的概率

			
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

    Npc* GetNpcByStaticId(int id);   //id查找
    Npc* FindNpcByDynamicId(int id); //动态id
    Npc* GetNpcByName(std::string name,uint32 mapId = -1);  //名字查找

    void AddNpc(Npc &xNpc);
    inline int GetNpcCount() { return static_cast<int>(npcs_.size()); }

    uint32 GetNpcs(uint32 id, std::vector<Npc*>& outResult );   //Npcid查找 
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
    DynamicCollNpcs dynamicCollNpcs_;    // 带动态碰撞功能的NPC
#endif 

	// 半身像
	bool IsDialogPic() const { return m_bDialogPic; }
protected:
	void SetDialogPic(bool flag) { m_bDialogPic = flag; }
	bool m_bDialogPic;
};

#pragma warning ( pop )

#endif // __NPC_INFO_H__

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

