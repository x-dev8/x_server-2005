//战场总控制器
//1.DB-- control --- manger ---- 
//Center
//1.读取数据库的数据
//2.读取配置文件数据
//3.加载全部的管理器 目前就1个
//4.运行Update函数 做具体的操作
//5.发送命令道GameServer去
//6.数据库的全部数据 分类 发送到不同的GameServer去
//7.战场的数据库状态转化 通知合适的玩家 
//8.战场的其他操作 转发到合适的GameServer
//9.
//GameServer
//1.加载CenterServer发送来的全部数据
//2.读取配置文件的数据
//3.接收CenterServer发送来的数据 创建战场的实际对象
//4.战场的内部操作全部在GameServer上进行
//5.战场的开始 状态 和 结束  奖励 等由GameServer发送到CenterServer进行结算
//6.玩家进入 和玩家离开 由GameServer进行处理

//1.修改加载数据库的方式
//MapID SrcGuildID  DestGuildID BeginTime Info

