========================================================================
    CONSOLE APPLICATION : DataCenter Project Overview
========================================================================

一,生成排行榜数据
Rank.config:此为排行榜所需内容文件,排行榜为前100位

每组服务器需要不同的下载地址,下载地址在serverlist.config中配置,属性http内容
如:http=http://222.73.67.148:8888/ranks.config

排行榜数据为每日刷新,所以需要每日定时生成一份最新.每个客户端打开排行榜UI时,会检查文件时间,如果超过24小时则下载最新,

排行榜数据在数据库中的位置说明以及文件格式说明
1.	总经验排行榜
<Type Name="总经验排行榜">
			<Rank Rank = "1" CharacterName="123" Level="1" Country="ds" Guild="sdf" Reward="123" />
</Type>
Rank			:排名
CharacterName	:玩家名字(库:online_db,表: t_game_character,字段: CharName)
Level			:玩家等级(库:online_db,表: t_game_character,字段: Lev)
Country			:所属国家(库:online_db,表: t_game_character,字段: country)
Guild			:所属军团(库:online_db,表: guild,字段name)
Reward			:奖励(预留暂未实现,全部给0)
PS:
1,如果等级一样,则比较经验(库:online_db,表: t_game_character,字段: exp
2,通过库:online_db,表: t_game_character,中的CharName或者characterid,查询表: guildmember,中的guild获得军团ID,再从表guild中查找获得name

2.	荣誉排行榜
<Type Name="荣誉排行榜">
			<Rank Rank = "1" CharacterName="123" Honor="1" Country="ds" Guild="sdf" Reward="123" />
</Type>
Rank			:排名
CharacterName	:玩家名字(库:online_db,表: t_game_character,字段: CharName)
Honor			:荣誉值(库:online_db,表: t_game_character,字段: honour)
Country			:所属国家(库:online_db,表: t_game_character,字段: country)
Guild			:所属军团(库:online_db,表: guild,字段name)
Reward			:奖励(预留暂未实现,全部给0)


3.	军功排行榜
<Type Name="军功排行榜">
			<Rank Rank = "1" CharacterName="123" Offer="1" Country="ds" Guild="sdf" Reward="123" />
</Type>
Rank			:排名
CharacterName	:玩家名字(库:online_db,表: t_game_character,字段: CharName)
Offer			:军功(库: online_db,表: guildmember,字段: offer)
Country			:所属国家(库:online_db,表: t_game_character,字段: country)
Guild			:所属军团(库:online_db,表: guild,字段name)
Reward			:奖励(预留暂未实现,全部给0)

4.	功勋排行榜
<Type Name="功勋排行榜">
			<Rank Rank = "1" CharacterName="123" Fame="1" Country="ds" Guild="sdf" Reward="123" />
</Type>
Rank			:排名
CharacterName	:玩家名字(库:online_db,表: t_game_character,字段: CharName)
Fame			:功勋(库: online_db,表: guildmember,字段: exploit)
Country			:所属国家(库:online_db,表: t_game_character,字段: country)
Guild			:所属军团(库:online_db,表: guild,字段name)
Reward			:奖励(预留暂未实现,全部给0)

5.	杀敌排行榜
<Type Name="杀敌排行榜">
			<Rank Rank = "1" CharacterName="123" Kill="1" Country="ds" Guild="sdf" Reward="123" />
</Type>
Rank			:排名
CharacterName	:玩家名字(库:online_db,表: t_game_character,字段: CharName)
Kill				:杀人数(库: online_db,表: t_game_character,字段: KillPlayerSum)
Country			:所属国家(库:online_db,表: t_game_character,字段: country)
Guild			:所属军团(库:online_db,表: guild,字段name)
Reward			:奖励(预留暂未实现,全部给0)

6.	魅力排行榜
<Type Name="魅力排行榜">
			<Rank Rank = "1" CharacterName="123" Charm="1" Country="ds" Guild="sdf" Reward="123" />
</Type>
Rank			:排名
CharacterName	:玩家名字(库:online_db,表: t_game_character,字段: CharName)
Charm			:好友度(库: online_db,表: relationdata,字段: friendly)
Country			:所属国家(库:online_db,表: t_game_character,字段: country)
Guild			:所属军团(库:online_db,表: guild,字段name)
Reward			:奖励(预留暂未实现,全部给0)

7.	财富排行榜
<Type Name="财富排行榜">
			<Rank Rank = "1" CharacterName="123" Fortune="1" Country="ds" Guild="sdf" Reward="123" />
</Type>
Rank			:排名
CharacterName	:玩家名字(库:online_db,表: t_game_character,字段: CharName)
Fortune			:银子数量(库: online_db,表: t_game_character,字段: Money)
Country			:所属国家(库:online_db,表: t_game_character,字段: country)
Guild			:所属军团(库:online_db,表: guild,字段name)
Reward			:奖励(预留暂未实现,全部给0)

8.	红名排行榜
<Type Name="红名排行榜">
			<Rank Rank = "1" CharacterName="123" PK="1" Country="ds" Guild="sdf" Reward="123" />
</Type>
Rank			:排名
CharacterName	:玩家名字(库:online_db,表: t_game_character,字段: CharName)
PK				: PK值(库: online_db,表: t_game_character,字段: KillValue)
Country			:所属国家(库:online_db,表: t_game_character,字段: country)
Guild			:所属军团(库:online_db,表: guild,字段name)
Reward			:奖励(预留暂未实现,全部给0)

9.	军团排行榜
<Type Name="军团排行榜">
			<Rank Rank="1" GuildName="123" GuildPower="1" GuildMember="ds" GuildLevel="sdf" Country="123" />
</Type>
Rank			:排名
GuildName		:军团名字(库:online_db,表: guild,字段: name)
GuildPower		:军团实力
GuildMember		:军团人数
GuildLevel		:军团等级(库:online_db,表: guild,字段level)
Country			:所属国家(库:online_db,表: guild,字段: country)
PS:
1,军团实力计算公式:
（帮会总人数等级和/帮会最大人数）*（基础值+帮会等级*系数）
帮会总人数等级和	:通过遍历表guildmember获得level相加
帮会最大人数		:根据不同工会等级获得不同的最大人数,暂定如下:
					 	Level="1" MaxCount="60"
Level="2" MaxCount="80"
Level="3" MaxCount="100"
Level="4" MaxCount="120"
Level="5" MaxCount="140"
基础值				:配置文件中获得,暂定为0      
帮会等级			: (库:online_db,表: guild,字段level)
系数				:配置文件获得,暂定为1.0
具体配置文件中获得的数值请及时联系

2,军团人数计算:遍历(库:online_db,表: guildmember)根据id不同分别为不同军团的人数

10.	国家实力榜
<Type Name="国家实力榜">
		<Rank Rank = "1" Country="123" King="1" Power="ds" />
</Type>
Rank:		排名
Country:		国家ID(库:online_db,表: countrys,字段: id)
King:		国王名字(通过库:online_db,表: countrys,获得字段: kingguild国王帮的军团ID, 查找表: guild中master为会长的DBID,从t_game_character中获得国王名字)
Power:		国家实力(库:online_db,表: countrys,字段: strength)

11.	兵书排行榜
<Type Name="兵书排行榜">
		<Rank Rank = "1" Country="123" King="1" Tribute="ds" />
</Type>
Rank:		排名
Country:		国家ID(库:online_db,表: countrys,字段: id)
King:		国王名字(通过库:online_db,表: countrys,获得字段: kingguild国王帮的军团ID, 查找表: guild中master为会长的DBID,从t_game_character中获得国王名字)
Tribute:		国家实力(库:online_db,表: countrys,字段: Tribute) 



二,解析数据库中二进制块数据(没做捏)
/////////////////////////////////////////////////////////////////////////////
