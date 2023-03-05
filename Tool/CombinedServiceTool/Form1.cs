using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using MySql.Data.MySqlClient;
using System.Net;
using System.Threading;
using System.IO;
namespace CombinedServiceTool
{
    public partial class Form1 : Form
    {
        MySqlConnection mySQL_SoruceDataBaseConn = null;
        MySqlConnection mySQL_BeUseDataBaseConn = null;
        MySqlConnection mySQL_TargetDataBaseConn = null;
        MySqlDataAdapter mySQL_Da = null;

        string[] DataBaseTableList =
                {
                    "account_billing",
                    "account_billing_log",
                    "account_wallow",
                    "accountyuanbaostates",
                    "consignmentaccount",
                    "consignmenthistroy",
                    "consignmentlist",
                    "countrys",
                    "countryinfo",
                    "consumescore",
                    "consumescore_billinglog",
                    "family",
                    "familymember",
                    "globaldb",
                    "guild",
                    "guildcampbattledata",
                    "guildmember",
                    "level_limit",
                    "mails",
                    "platform_objects",
                    "questentrust",
                    "relationattribute",
                    "relationdata",
                    "systemvar",
                    "t_game_achieve",
                    "t_game_character",
                    "t_game_gminfo",
                    "t_game_identify",
                    "t_game_item",
                    "t_game_itemdropcontrol",
                    "t_game_mount",
                    "t_game_pet",
                    "t_game_scriptvar",
                    "t_game_test",
                    "t_game_visualinfo",
                    "t_game_killplayer",
                    "shopping_log",
                    
                };

        public Form1()
        {
            InitializeComponent();
        }
        private void Button1_Click(object sender, EventArgs e)
        {
            //开始合并数据库
            BeginComBinedThread();
        }
        private bool CheckAndOpenSourceDataBase()
        { 
            //试图开启源数据库的连接 并且坚持数据库是否符合要求
            IPAddress ip;
            try
            {
                ip = System.Net.IPAddress.Parse(textBox1.Text);
            }
            catch (Exception ex)
            {
                ShowErrorInfo("源数据库IP地址格式不正确");
                return false;
            }
            string DataBaseAccount = textBox2.Text;
            string PassWard = textBox3.Text;
            string DataBaseName = textBox4.Text;
            if (DataBaseAccount == "")
            {
                ShowErrorInfo("源数据库账号名称为空");
                return false;
            }
            if (DataBaseName == "")
            {
                ShowErrorInfo("源数据库账号名称为空");
                return false;
            }
            string strConn = string.Format("Server={0};Uid={1};Pwd={2};DataBase={3};CharSet=utf8;Allow Zero Datetime=True", ip.ToString(), DataBaseAccount, PassWard, DataBaseName);
            if (mySQL_SoruceDataBaseConn != null)
            {
                mySQL_SoruceDataBaseConn.Close();
            }
            mySQL_SoruceDataBaseConn = new MySqlConnection(strConn);
            try
            {
                mySQL_SoruceDataBaseConn.Open();
            }
            catch (Exception ex)
            {
                mySQL_SoruceDataBaseConn = null;
                ShowErrorInfo("源数据库连接失败");
                return false;
            }
            //数据库已经成功打开连接 我们开去测试数据库是否符合要求
            if (!CheckDataBaseTable(DataBaseName, mySQL_SoruceDataBaseConn))
            {
                ShowErrorInfo("源数据库不存在 或 表不符合要求");
                return false;
            }
            ShowSeccInfo("源数据库检查成功 连接成功开启");
            return true;
        }
        private bool CheckAndOpenBeUseDataBase()
        {
            IPAddress ip;
            try
            {
                ip = System.Net.IPAddress.Parse(textBox5.Text);
            }
            catch (Exception ex)
            {
                ShowErrorInfo("待合并数据库IP地址格式不正确");
                return false;
            }
            string DataBaseAccount = textBox6.Text;
            string PassWard = textBox7.Text;
            string DataBaseName = textBox8.Text;
            if (DataBaseAccount == "")
            {
                ShowErrorInfo("待合并数据库账号名称为空");
                return false;
            }
            if (DataBaseName == "")
            {
                ShowErrorInfo("待合并数据库账号名称为空");
                return false;
            }
            string strConn = string.Format("Server={0};Uid={1};Pwd={2};DataBase={3};CharSet=utf8;Allow Zero Datetime=True", ip.ToString(), DataBaseAccount, PassWard, DataBaseName);
            if (mySQL_BeUseDataBaseConn != null)
            {
                mySQL_BeUseDataBaseConn.Close();
            }
            mySQL_BeUseDataBaseConn = new MySqlConnection(strConn);
            try
            {
                mySQL_BeUseDataBaseConn.Open();
            }
            catch (Exception ex)
            {
                mySQL_BeUseDataBaseConn = null;
                ShowErrorInfo("待合并数据库连接失败");
                return false;
            }
            //数据库已经成功打开连接 我们开去测试数据库是否符合要求
            if (!CheckDataBaseTable(DataBaseName, mySQL_BeUseDataBaseConn))
            {
                ShowErrorInfo("待合并数据库不存在 或 表不符合要求");
                return false;
            }
            ShowSeccInfo("待合并数据库检查成功 连接成功开启");
            return true;
        }
        private bool CreateAndOpenTargetDataBase()
        { 
            //创建并且打开数据库连接
            IPAddress ip;
            try
            {
                ip = System.Net.IPAddress.Parse(textBox9.Text);
            }
            catch (Exception ex)
            {
                ShowErrorInfo("目标数据库IP地址格式不正确");
                return false;
            }
            string DataBaseAccount = textBox10.Text;
            string PassWard = textBox11.Text;
            string DataBaseName = textBox12.Text;
            if (DataBaseAccount == "")
            {
                ShowErrorInfo("目标数据库账号名称为空");
                return false;
            }
            if (DataBaseName == "")
            {
                ShowErrorInfo("目标数据库账号名称为空");
                return false;
            }
            string strConn = string.Format("Server={0};Uid={1};Pwd={2};CharSet=utf8;Allow Zero Datetime=True", ip.ToString(), DataBaseAccount, PassWard);
            if (mySQL_TargetDataBaseConn != null)
            {
                mySQL_TargetDataBaseConn.Close();
            }
            mySQL_TargetDataBaseConn = new MySqlConnection(strConn);
            try
            {
                mySQL_TargetDataBaseConn.Open();
            }
            catch (Exception ex)
            {
                mySQL_TargetDataBaseConn = null;
                ShowErrorInfo("目标数据库连接失败");
                return false;
            }
            //创建数据库
            string CreateDataBaseStr = string.Format("CREATE DATABASE {0}", DataBaseName);
            MySqlCommand commond = new MySqlCommand(CreateDataBaseStr, mySQL_TargetDataBaseConn);
            try
            {
                if (commond.ExecuteNonQuery() == -1)
                {
                    mySQL_TargetDataBaseConn.Close();
                    mySQL_TargetDataBaseConn = null;
                    ShowErrorInfo("创建目标数据库失败");
                    return false;
                }
            }
            catch (Exception ex)
            {
                mySQL_TargetDataBaseConn.Close();
                mySQL_TargetDataBaseConn = null;
                ShowErrorInfo("创建目标数据库失败");
                return false;
            }
            //修改数据库连接
            if (mySQL_TargetDataBaseConn !=null && mySQL_TargetDataBaseConn.State == ConnectionState.Open)
                mySQL_TargetDataBaseConn.Close();
            mySQL_TargetDataBaseConn.ConnectionString = string.Format("Server={0};Uid={1};Pwd={2};DataBase={3};CharSet=utf8;Allow Zero Datetime=True", ip.ToString(), DataBaseAccount, PassWard, DataBaseName);
            try
            {
                mySQL_TargetDataBaseConn.Open();
            }
            catch (Exception ex)
            {
                mySQL_TargetDataBaseConn = null;
                ShowErrorInfo("目标数据库连接失败");
                return false;
            }
            commond.Connection = mySQL_TargetDataBaseConn;
            //创建数据表
            for (int i = 0; i < DataBaseTableList.Length; ++i)
            {
                commond.CommandText = string.Format("use {0};create table {1} like {2}.{1};", DataBaseName, DataBaseTableList[i], textBox4.Text);
                try
                {
                    if (commond.ExecuteNonQuery() == -1)
                    {
                        mySQL_TargetDataBaseConn.Close();
                        mySQL_TargetDataBaseConn = null;
                        ShowErrorInfo(string.Format("创建目标数据库{0}数据表失败 请手动删除创建的数据库", DataBaseTableList[i]));
                        return false;
                    }
                }
                catch (Exception ex)
                {
                    mySQL_TargetDataBaseConn.Close();
                    mySQL_TargetDataBaseConn = null;
                    ShowErrorInfo(string.Format("创建目标数据库{0}数据表失败  请手动删除创建的数据库", DataBaseTableList[i]));
                    return false;
                }
            }
            string LogStr = string.Format("use {0};create table CombinedLog(PID int auto_increment,name varchar(20),info varchar(120),primary key(PID));", DataBaseName);
            commond.CommandText = LogStr;
            try
            {
                if (commond.ExecuteNonQuery() == -1)
                {
                    mySQL_TargetDataBaseConn.Close();
                    mySQL_TargetDataBaseConn = null;
                    ShowErrorInfo(string.Format("创建目标数据库{0}数据表失败 请手动删除创建的数据库", "CombinedLog"));
                    return false;
                }
            }
            catch (Exception ex)
            {
                mySQL_TargetDataBaseConn.Close();
                mySQL_TargetDataBaseConn = null;
                ShowErrorInfo(string.Format("创建目标数据库{0}数据表失败  请手动删除创建的数据库", "CombinedLog"));
                return false;
            }
            ShowSeccInfo("目标数据库检测成功");
            return true;
        }

        private void BeginComBinedThread()
        {
            //Thread thread = new Thread(new ThreadStart(HandleMain));
            //thread.Start();
            HandleMain();
        }
        private void HandleMain()
        {
            EnabledControleDataBase(false);
            if (CheckAndOpenSourceDataBase() && CheckAndOpenBeUseDataBase() && CreateAndOpenTargetDataBase())
            {
                //开始正式的数据库合并工作
                if (!ComBinedDataBase())
                {
                    ShowErrorInfo("数据库合并失败 请手动删除目标数据库 重新开始");
                    ClearAllInfo(false);
                }
                else
                    ClearAllInfo(true);
            }
            else
                ClearAllInfo(false);
            EnabledControleDataBase(true);
        }
        private bool ComBinedDataBase()
        { 
            //处理数据表 我们创建新的线程去合并表
            bool result = true;
            if (!HandleAccount_BillingTable())
                result = false;
            else if (!HandleConsumeScoreTable())
                result = false;
            else if (!HandleCharacterTable())
                result = false;
            else if (!HandleGuildTable())
                result = false;
            else if (!HandleGuildMemberTable())
                result = false;
            else if (!HandlePlayerGuildStates())
                result = false;
            else if (!HandleConsignmentaccountTable())
                result = false;
            else if (!HandleMailsTable())
                result = false;
            else if (!HandleRelationattribute())
                result = false;
            else if (!HandleRelationdata())
                result = false;
            else if (!HandleAchieve())
                result = false;
            else if (!HandleIdentify())
                result = false;
            else if (!HandleItem())
                result = false;
            else if (!HandleMount())
                result = false;
            else if (!HandlePet())
                result = false;
            else if (!HandleVisualInfo())
                result = false;
            else if (!HandleGuildCampBattleData())
                result = false;
            else if (!HandleQuestEntrustData())
                result = false;
            //else if (!HandlePlayerSum())
            //    result = false;
            else
                result = true;
            return result;
        }


        private bool HandleAccount_BillingTable()
        {
            string tableName = "account_billing";
            ShowSeccInfo(string.Format("开始合并数据表{0}", tableName));
            if(!SetDataToGridView(tableName))
            {
                ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
                return false;
            }
            //try
            //{
                // 0 ,1add
                ShowTableInfo(tableName);
                Dictionary<UInt32, UInt32> pMap = new Dictionary<UInt32, UInt32>();
                DataTable dt= ((DataTable)dataGridView3.DataSource);
                ShowTableInfo(string.Format("待处理数据行数 {0}",dataGridView1.Rows.Count+dataGridView2.Rows.Count));
                for(int i =0;i<dataGridView1.Rows.Count;++i)
                {
                    DataRow  dr = ((DataTable)dataGridView1.DataSource).Rows[i];
                    UInt32 ID = Convert.ToUInt32(dr["guid"]);
                    UInt32 Value = Convert.ToUInt32(dr["point"]);
                    pMap.Add(ID, Value);
                    ShowTableInfo(string.Format("处理行数 {0}",i));
                }
                for(int i =0;i<dataGridView2.Rows.Count;++i)
                {
                    DataRow  dr = ((DataTable)dataGridView2.DataSource).Rows[i];
                    UInt32 ID = Convert.ToUInt32(dr["guid"]);
                    UInt32 Value = Convert.ToUInt32(dr["point"]);
                    if (pMap.ContainsKey(ID))
                    {
                        pMap[ID] += Value;
                        LogCombinedInfo(tableName,string.Format("有相同ID的数据 进行合并 ID为{0} 值1为{1} 值2为{2} 合并后值为{3}",ID,pMap[ID]-Value,Value,pMap[ID]));
                    }
                    else
                    {
                        pMap.Add(ID, Value);
                    }
                    ShowTableInfo(string.Format("处理行数 {0}", i+dataGridView1.Rows.Count));
                }
                if(pMap.Count >0)
                {
                    UInt32[] arraysKey = new UInt32[pMap.Count];
                    pMap.Keys.CopyTo(arraysKey,0);
                    for (int i = 0; i < pMap.Count; ++i)
                    {
                        UInt32 ID = arraysKey[i];
                        UInt32 Value = pMap[ID];
                        GlobalVar.AccountYuanBaoMap.Add(ID, Value);
                        dt.Rows.Add(ID, Value);
                    }
                    SaveData(dt);
                }
                ShowSeccInfo(string.Format("合并数据表{0}成功", tableName));
                return true;
            //}
            //catch(Exception ex)
            //{
            //    ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
            //    return false;
            //}
        }
        private bool HandleConsumeScoreTable()
        {
            //账户ID进行合并
            string tableName = "consumescore";
            ShowSeccInfo(string.Format("开始合并数据表{0}", tableName));
            if (!SetDataToGridView(tableName))
            {
                ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
                return false;
            }
            //try
            //{
                // 0 ,1add
                ShowTableInfo(tableName);
                Dictionary<int, int> pMap = new Dictionary<int, int>();
                DataTable dt = ((DataTable)dataGridView3.DataSource);
                ShowTableInfo(string.Format("待处理数据行数 {0}", dataGridView1.Rows.Count + dataGridView2.Rows.Count));
                for (int i = 0; i < dataGridView1.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView1.DataSource).Rows[i];
                    int ID = Convert.ToInt32(dr["guid"]);
                    int Value = Convert.ToInt32(dr["point"]);
                    pMap.Add(ID, Value);
                    ShowTableInfo(string.Format("处理行数 {0}", i));
                }
                for (int i = 0; i < dataGridView2.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView2.DataSource).Rows[i];
                    int ID = Convert.ToInt32(dr["guid"]);
                    int Value = Convert.ToInt32(dr["point"]);
                    if (pMap.ContainsKey(ID))
                    {
                        pMap[ID] += Value;
                        LogCombinedInfo(tableName, string.Format("有相同ID的数据 进行合并 ID为{0} 值1为{1} 值2为{2} 合并后值为{3}", ID, pMap[ID] - Value, Value, pMap[ID]));
                    }
                    else
                    {
                        pMap.Add(ID, Value);
                    }
                    ShowTableInfo(string.Format("处理行数 {0}", i + dataGridView1.Rows.Count));
                }
                if (pMap.Count > 0)
                {
                    int[] arraysKey = new int[pMap.Count];
                    pMap.Keys.CopyTo(arraysKey, 0);
                    for (int i = 0; i < pMap.Count; ++i)
                    {
                        int ID = arraysKey[i];
                        int Value = pMap[ID];
                        dt.Rows.Add(ID, Value);
                    }
                    SaveData(dt);
                }
                ShowSeccInfo(string.Format("合并数据表{0}成功", tableName));
                return true;
            //}
            //catch (Exception ex)
            //{
            //    ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
            //    return false;
            //}
        }
        private bool HandleCharacterTable()
        {
            string tableName = "t_game_character";
            //玩家ID 玩家名称 玩家名称状态 玩家公会ID状态.
            ShowSeccInfo(string.Format("开始合并数据表{0}", tableName));
            if (!SetDataToGridView(tableName))
            {
                ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
                return false;
            }
            //try
            //{
                //1 2
                ShowTableInfo(tableName);
                ShowTableInfo(string.Format("待处理数据行数 {0}", dataGridView1.Rows.Count + dataGridView2.Rows.Count));
                DataTable dt = ((DataTable)dataGridView3.DataSource);
                List<int> list = new List<int>();
                List<string> listName = new List<string>();
                for (int i = 0; i < dataGridView1.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView1.DataSource).Rows[i];
                    int ID = Convert.ToInt32(dr["characterid"]);
                    list.Add(ID);
                    string Name = Convert.ToString(dr["CharName"]);
                    listName.Add(Name);
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i));
                }
                int beginID = GetBegInID(list);

                StreamWriter sw = new StreamWriter("SqlItemUpdate.txt", true);
                for (int i = 0; i < dataGridView2.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView2.DataSource).Rows[i];
                    int ID = Convert.ToInt32(dr["characterid"]);
                    string Name = Convert.ToString(dr["CharName"]);
                    if (list.Contains(ID))
                    {
                        while (list.Contains(beginID))
                        {
                            ++beginID;
                        }
                        GlobalVar.PlayerIDMap.Add(ID, beginID);
                        LogCombinedInfo(tableName, string.Format("玩家ID有重复的 旧玩家ID为{0} 新玩家ID为{1}", ID, beginID));

                        string FileInfo = string.Format("update t_game_item set CharacterId = {0} where CharacterId={1};", beginID, ID);
                        //将数据写入到文件里面去
                        sw.WriteLine(FileInfo);
                       
                        dr["characterid"] = beginID;
                        ++beginID;
                    }
                    if (listName.Contains(Name))
                    {
                        LogCombinedInfo(tableName, string.Format("玩家名称有重复的 玩家名称为{0} 设置玩家的状态为待改名的状态", Name));
                        dr["changeName"] = Convert.ToInt32(dr["characterid"]);
                        dr["CharName"] = Name + "-" + textBox14.Text;//修改玩家名称
                        GlobalVar.PlayerNameMap.Add(Name, Convert.ToString(dr["CharName"]));
                    }
                    list.Add(Convert.ToInt32(dr["characterid"]));
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i + dataGridView1.Rows.Count));
                }
                string EndFileInfo = "update t_game_character set changename = characterid where changename !=0 and changename != characterid;";
                sw.WriteLine(EndFileInfo);
                sw.Close();
                //遍历所有玩家数据 修改玩家元宝数量
                for (int i = 0; i < dt.Rows.Count; ++i)
                {
                    UInt32 AccountID = Convert.ToUInt32(dt.Rows[i]["AccountID"]);
                    UInt32 YuanBao = Convert.ToUInt32(dt.Rows[i]["jinding"]);
                    if (GlobalVar.AccountYuanBaoMap.ContainsKey(AccountID))
                    {
                        UInt32 NowYuanBao = GlobalVar.AccountYuanBaoMap[AccountID];
                        if (NowYuanBao != YuanBao)
                        {
                            LogCombinedInfo(tableName, string.Format("修改账号下玩家的元宝数量 AccountID为%d,源元宝ID为%d,目前元宝ID为:%d", AccountID, YuanBao, NowYuanBao));
                            dt.Rows[i]["jinding"] = NowYuanBao;
                        }
                    }
                }

                MySqlCommandBuilder build = new MySqlCommandBuilder(mySQL_Da);
                mySQL_Da.Update(dt);
                //SaveData(dt);
                ShowSeccInfo(string.Format("合并数据表{0}成功", tableName));

                //dt 是最新的数据 我们直接处理玩家的位置数据
                Dictionary<int, PlayerSum> pMap = new Dictionary<int, PlayerSum>();
                for (int i = 0; i < dt.Rows.Count; ++i)
                {
                    int AccountID = Convert.ToInt32(dt.Rows[i]["AccountID"]);
                   // int IsDel = Convert.ToInt32(dt.Rows[i]["IsDel"]);
                    int CharacterID = Convert.ToInt32(dt.Rows[i]["characterid"]);
                    //if (IsDel == 1)//删除的角色不做处理
                    //    continue;
                    if (pMap.ContainsKey(AccountID))
                    {
                        pMap[AccountID].list.Add(CharacterID);
                    }
                    else
                    {
                        PlayerSum ps = new PlayerSum();
                        ps.list = new List<int>();
                        ps.AccountID = AccountID;
                        ps.list.Add(CharacterID);
                        pMap.Add(AccountID, ps);
                    }
                    ShowTableInfo(string.Format("处理角色ID {0}", CharacterID));
                }
                LogCombinedInfo(tableName, string.Format("开始玩家位置处理 获取到玩家的全部数据成功 读取的账号数据条数为:{0}", pMap.Count));
                //集合创建完毕后 我们开始处理集合的数据
                int[] Keys = new int[pMap.Count];
                pMap.Keys.CopyTo(Keys, 0);
                LogCombinedInfo(tableName, string.Format("开始玩家位置处理 获取到玩家的全部数据成功 读取的账号数据条数为:{0}", Keys.Length));
                ShowTableInfo(string.Format("待处理数据行数 {0}", Keys.Length));
                for (int i = 0; i < Keys.Length; ++i)
                {
                    int AccountID = Keys[i];
                    LogCombinedInfo(tableName, string.Format("账号数据处理 账号ID:{0},验证ID为:{1},玩家数量为:{2},", pMap[AccountID].AccountID, AccountID, pMap[AccountID].list.Count));
                    if (pMap[AccountID].AccountID != AccountID)
                        continue;
                    //if (pMap[AccountID].list.Count <= 3)
                    //    continue;
                   // LogCombinedInfo(tableName, string.Format("账号数据处理 玩家数量大于3 开始处理 账号ID:{0},验证ID为:{1},玩家数量为:{2},", pMap[AccountID].AccountID, AccountID, pMap[AccountID].list.Count));
                    //账号内玩家角色多于3个 取角色等级最高的3个设置好 其他的设置为删除状态
                    for (int j = 0; j < pMap[AccountID].list.Count; ++j)
                    {
                        //修改角色的位置
                        LogCombinedInfo(tableName, string.Format("设置指定角色的位置 角色ID为{0} 位置为{1}", Convert.ToInt32(pMap[AccountID].list[j]), j));
                        string str = string.Format("update {0} set CharSlot = {1}  where characterid= {2}", tableName, j, Convert.ToInt32(pMap[AccountID].list[j]));
                        MySqlCommand commond1 = new MySqlCommand(str, mySQL_TargetDataBaseConn);
                        if (commond1.ExecuteNonQuery() != 1)
                        {
                            ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
                            return false;
                        }
                    }
                    ShowTableInfo(string.Format("处理行数 {0}", i));
                }
                ShowSeccInfo(string.Format("合并数据表{0}成功", tableName));
                LogCombinedInfo(tableName, "开始玩家位置处理 玩家角色数据修改成功");
                return true;
            //}
            //catch (Exception ex)
            //{
            //    ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
            //    return false;
            //}
        }
        private bool HandleGuildTable()
        {
            //公会ID 公会名称
            string tableName = "guild";
            ShowSeccInfo(string.Format("开始合并数据表{0}", tableName));
            if(!SetDataToGridView(tableName))
            {
                ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
                return false;
            }
            //try
            //{
                // 0 1  master
                ShowTableInfo(tableName);
                DataTable dt = ((DataTable)dataGridView3.DataSource);
                List<int> list = new List<int>();
                List<string> listName = new List<string>();
                ShowTableInfo(string.Format("待处理数据行数 {0}", dataGridView1.Rows.Count + dataGridView2.Rows.Count));
                for (int i = 0; i < dataGridView1.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView1.DataSource).Rows[i];
                    int ID = Convert.ToInt32(dr["id"]);
                    list.Add(ID);
                    string Name = Convert.ToString(dr["name"]);
                    listName.Add(Name);
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i));
                }
                int beginID = GetBegInID(list);
                for (int i = 0; i < dataGridView2.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView2.DataSource).Rows[i];
                    int ID = Convert.ToInt32(dr["id"]);
                    string Name = Convert.ToString(dr["name"]);
                    int masterID = Convert.ToInt32(dr["master"]);
                    if (list.Contains(ID))
                    {
                        while (list.Contains(beginID))
                        {
                            ++beginID;
                        }
                        GlobalVar.GuildIDMap.Add(ID, beginID);
                        LogCombinedInfo(tableName, string.Format("公会ID有重复的 旧公会ID为{0}  新的公会ID为{1}", ID, beginID));
                       
                        dr["id"] = beginID;
                        ++beginID;
                    }
                    if (listName.Contains(Name) && !GlobalVar.GuildNameMap.ContainsKey(Name))
                    {
                        GlobalVar.GuildNameMap.Add(Name, Name +"-" + textBox14.Text);
                        LogCombinedInfo(tableName, string.Format("公会名称有重复的 旧公会名称为{0} 新公会名称为{1}", Name, Name + "-" + textBox14.Text));
                        dr["name"] = Name + "-" + textBox14.Text;
                        //修改指定列 表示公会可以改名
                        dr["changename"] = 1;
                    }
                    if (GlobalVar.PlayerIDMap.ContainsKey(masterID))
                    {
                        LogCombinedInfo(tableName, string.Format("因为合服 公会会长ID变化 旧ID为{0} 新ID为{1}", masterID, GlobalVar.PlayerIDMap[masterID]));
                        dr["master"] = GlobalVar.PlayerIDMap[masterID];
                    }
                    list.Add(Convert.ToInt32(dr["id"]));
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i+dataGridView1.Rows.Count));
                }
                //MySqlCommandBuilder build = new MySqlCommandBuilder(mySQL_Da);
                //mySQL_Da.Update(dt);
                SaveData(dt);
                ShowSeccInfo(string.Format("合并数据表{0}成功", tableName));
                return true;
            //}
            //catch(Exception ex)
            //{
            //    ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
            //    return false;
            //}
        }
        private bool HandleGuildMemberTable()
        {
            string tableName = "guildmember";
            ShowSeccInfo(string.Format("开始合并数据表{0}", tableName));
            if(!SetDataToGridView(tableName))
            {
                ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
                return false;
            }
            //try
            //{
                //玩家ID 玩家名称 公会ID
                ShowTableInfo(tableName);
                ShowTableInfo(string.Format("待处理数据行数 {0}", dataGridView1.Rows.Count + dataGridView2.Rows.Count));

                DataTable dt = ((DataTable)dataGridView3.DataSource);
                for (int i = 0; i < dataGridView1.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView1.DataSource).Rows[i];
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i));
                }
                for (int i = 0; i < dataGridView2.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView2.DataSource).Rows[i];
                    int ID = Convert.ToInt32(dr["id"]);
                    string Name = Convert.ToString(dr["name"]);
                    int guildID = Convert.ToInt32(dr["guild"]);
                    if (GlobalVar.PlayerIDMap.ContainsKey(ID))
                    {
                        dr["id"] = GlobalVar.PlayerIDMap[ID];
                        LogCombinedInfo(tableName,string.Format("公会成员玩家ID 因为合服玩家ID变动 旧ID为{0} 新ID为{1}",ID,GlobalVar.PlayerIDMap[ID]));
                    }
                    if (GlobalVar.PlayerNameMap.ContainsKey(Name))
                    {
                        dr["name"] = GlobalVar.PlayerNameMap[Name];
                        LogCombinedInfo(tableName, string.Format("公会成员玩家名称 因为合服玩家名称变化 旧名称为{0} 新名称为{1}", Name, GlobalVar.PlayerNameMap[Name]));
                    }
                    if (GlobalVar.GuildIDMap.ContainsKey(guildID))
                    {
                        dr["guild"] = GlobalVar.GuildIDMap[guildID];
                        LogCombinedInfo(tableName, string.Format("公会成员公会ID 因为合服公会ID变化 旧ID为{0} 新ID为{1}", guildID, GlobalVar.GuildIDMap[guildID]));
                        GlobalVar.PlayerGuildMap.Add(Convert.ToInt32(dr["id"]), Convert.ToInt32(dr["guild"]));
                    }
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i + dataGridView1.Rows.Count));
                }
                //MySqlCommandBuilder build = new MySqlCommandBuilder(mySQL_Da);
                //mySQL_Da.Update(dt);
                SaveData(dt);
                ShowSeccInfo(string.Format("合并数据表{0}成功", tableName));
                return true;
            //}
            //catch (Exception ex)
            //{
            //    ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
            //    return false;
            //}
        }
        private bool HandlePlayerGuildStates()
        { 
            string tableName = "t_game_character";
            //玩家ID 玩家名称 玩家名称状态 玩家公会ID状态.
            ShowSeccInfo(string.Format("开始合并数据表{0}", tableName));
            if(!SetDataToGridView(tableName))
            {
                ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
                return false;
            }
            //try
            //{
                ShowTableInfo(tableName);
                ShowTableInfo(string.Format("待处理数据行数 {0}", dataGridView3.Rows.Count));
                for (int i = 0; i < dataGridView3.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView3.DataSource).Rows[i];
                    int ID = Convert.ToInt32(dr["characterid"]);
                    if (GlobalVar.PlayerGuildMap.ContainsKey(ID))
                    { 
                        //修改玩家的公会改变状态
                        int GuildID = GlobalVar.PlayerGuildMap[ID];
                        dr["guild"] = GuildID;
                        LogCombinedInfo(tableName, string.Format("修改玩家状态为公会ID待修改状态 玩家ID为{0} 修改后公会ID为{1}", ID, GuildID));
                    }
                    ShowTableInfo(string.Format("处理行数 {0}", i));
                }
                MySqlCommandBuilder build = new MySqlCommandBuilder(mySQL_Da);
                mySQL_Da.Update((DataTable)dataGridView3.DataSource);
                ShowSeccInfo(string.Format("合并数据表{0}成功", tableName));
                return true;
            //}
            //catch (Exception ex)
            //{
            //    ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
            //    return false;
            //}
        }
        private bool HandleConsignmentaccountTable()
        {
            string tableName = "consignmentaccount";
            ShowSeccInfo(string.Format("开始合并数据表{0}", tableName));
            if(!SetDataToGridView(tableName))
            {
                ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
                return false;
            }
            //try
            //{
                //玩家ID进行合并
                ShowTableInfo(tableName);
                ShowTableInfo(string.Format("待处理数据行数 {0}", dataGridView1.Rows.Count + dataGridView2.Rows.Count));

                DataTable dt = ((DataTable)dataGridView3.DataSource);
                for (int i = 0; i < dataGridView1.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView1.DataSource).Rows[i];
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i));
                }
                for (int i = 0; i < dataGridView2.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView2.DataSource).Rows[i];
                    int ID = Convert.ToInt32(dr["playerid"]);
                    if (GlobalVar.PlayerIDMap.ContainsKey(ID))
                    {
                        dr["playerid"] = GlobalVar.PlayerIDMap[ID];
                        LogCombinedInfo(tableName, string.Format("修改玩家ID 因为合服 玩家ID发生变化 旧ID为{0} 新ID为{1}", ID, GlobalVar.PlayerIDMap[ID]));
                    }
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i + dataGridView1.Rows.Count));
                }
                SaveData(dt);
                ShowSeccInfo(string.Format("合并数据表{0}成功", tableName));
                return true;
            //}
            //catch (Exception ex)
            //{
            //    ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
            //    return false;
            //}
        }
        private bool HandleMailsTable()
        { 
            //处理邮件
            string tableName = "mails";
            ShowSeccInfo(string.Format("开始合并数据表{0}", tableName));
            if (!SetDataToGridView(tableName))
            {
                ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
                return false;
            }
            //try
            //{
                //玩家ID进行合并
                ShowTableInfo(tableName);
                ShowTableInfo(string.Format("待处理数据行数 {0}", dataGridView1.Rows.Count + dataGridView2.Rows.Count));

                List<int> list = new List<int>();
                DataTable dt = ((DataTable)dataGridView3.DataSource);
                for (int i = 0; i < dataGridView1.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView1.DataSource).Rows[i];
                    int ID = Convert.ToInt32(dr["id"]);
                    list.Add(ID);
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i));
                }
                int beginID = GetBegInID(list);
                for (int i = 0; i < dataGridView2.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView2.DataSource).Rows[i];
                    //玩家ID 玩家名称的变化
                    int ID = Convert.ToInt32(dr["id"]);
                    if (list.Contains(ID))
                    {
                        while (list.Contains(beginID))
                        {
                            ++beginID;
                        }
                        LogCombinedInfo(tableName,string.Format("邮件ID发生变化 旧ID为{0} 新ID为{1}",ID,beginID));
                       
                        dr["id"] = beginID;
                        ++beginID;
                    }
                    int PlayerID = Convert.ToInt32(dr["char_id"]);
                    if(GlobalVar.PlayerIDMap.ContainsKey(PlayerID))
                    {
                        dr["char_id"] = GlobalVar.PlayerIDMap[PlayerID];
                        LogCombinedInfo(tableName, string.Format("因为合服 玩家ID发生变化 旧玩家ID为{0} 新玩家ID为{1}", PlayerID, GlobalVar.PlayerIDMap[PlayerID]));
                    }
                    for (int j = 0; j < 8; ++j)
                    { 
                        //8个转发人
                        int NID = Convert.ToInt32(dr[string.Format("owner_id_{0}", j)]);
                        string Name = Convert.ToString(dr[6 + j * 2]);
                        if (GlobalVar.PlayerIDMap.ContainsKey(NID))
                        {
                            LogCombinedInfo(tableName, string.Format("因为合服 玩家ID发生变化 旧玩家ID为{0} 新玩家ID为{1}", NID, GlobalVar.PlayerIDMap[NID]));
                            dr[string.Format("owner_id_{0}", j)] = GlobalVar.PlayerIDMap[NID];
                        }
                        if (GlobalVar.PlayerNameMap.ContainsKey(Name))
                        {
                            LogCombinedInfo(tableName, string.Format("因为合服 玩家名称发送变化 待玩家进入游戏改名 旧玩家名称为{0}", Name));
                            dr[string.Format("owner_name_{0}", j)] = GlobalVar.PlayerNameMap[Name];
                        }
                    }
                    list.Add(Convert.ToInt32(dr["id"]));
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i + dataGridView1.Rows.Count));
                }
                SaveData(dt);
                ShowSeccInfo(string.Format("合并数据表{0}成功", tableName));
                return true;
            //}
            //catch (Exception ex)
            //{
            //    ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
            //    return false;
            //}
        }
        private bool HandleRelationattribute()
        {
            string tableName = "relationattribute";
            ShowSeccInfo(string.Format("开始合并数据表{0}", tableName));
            if (!SetDataToGridView(tableName))
            {
                ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
                return false;
            }
            //try
            //{
                //玩家ID 玩家名称
                ShowTableInfo(tableName);
                ShowTableInfo(string.Format("待处理数据行数 {0}", dataGridView1.Rows.Count + dataGridView2.Rows.Count));

                DataTable dt = ((DataTable)dataGridView3.DataSource);
                for (int i = 0; i < dataGridView1.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView1.DataSource).Rows[i];
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i));
                }
                for (int i = 0; i < dataGridView2.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView2.DataSource).Rows[i];
                    int ID = Convert.ToInt32(dr["id"]);
                    int GuildID = Convert.ToInt32(dr["guildid"]);
                    string Name = Convert.ToString(dr[1]);
                    if (GlobalVar.PlayerIDMap.ContainsKey(ID))
                    {
                        dr["id"] = GlobalVar.PlayerIDMap[ID];
                        LogCombinedInfo(tableName, string.Format("因为合服 玩家ID发生变化 旧玩家ID为{0} 新玩家ID为{1}", ID, GlobalVar.PlayerIDMap[ID]));
                    }
                    if (GlobalVar.GuildIDMap.ContainsKey(GuildID))
                    {
                        dr["guildid"] = GlobalVar.GuildIDMap[GuildID];
                        LogCombinedInfo(tableName, string.Format("因为合服 公会ID发生变化 旧公会ID为{0} 新公会ID为{1}", GuildID, GlobalVar.GuildIDMap[GuildID]));
                    }
                    if (GlobalVar.PlayerNameMap.ContainsKey(Name))
                    {
                        dr["name"] = GlobalVar.PlayerNameMap[Name];
                        LogCombinedInfo(tableName, string.Format("因为合服 玩家名称发送变化 待玩家进入游戏改名 旧玩家名称为{0}", Name));
                    }
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i + dataGridView1.Rows.Count));
                }
                SaveData(dt);
                ShowSeccInfo(string.Format("合并数据表{0}成功", tableName));
                return true;
            //}
            //catch (Exception ex)
            //{
            //    ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
            //    return false;
            //}
        }
        private bool HandleRelationdata()
        {
            string tableName = "relationdata";
            ShowSeccInfo(string.Format("开始合并数据表{0}", tableName));
            if (!SetDataToGridView(tableName))
            {
                ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
                return false;
            }
            //try
            //{
                //玩家ID 玩家名称
                ShowTableInfo(tableName);
                ShowTableInfo(string.Format("待处理数据行数 {0}", dataGridView1.Rows.Count + dataGridView2.Rows.Count));

                DataTable dt = ((DataTable)dataGridView3.DataSource);
                for (int i = 0; i < dataGridView1.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView1.DataSource).Rows[i];
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i));
                }
                for (int i = 0; i < dataGridView2.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView2.DataSource).Rows[i];
                    int ID = Convert.ToInt32(dr["id1"]);
                    if (GlobalVar.PlayerIDMap.ContainsKey(ID))
                    {
                        dr["id1"] = GlobalVar.PlayerIDMap[ID];
                        LogCombinedInfo(tableName, string.Format("因为合服 玩家ID发生变化 旧玩家ID为{0} 新玩家ID为{1}", ID, GlobalVar.PlayerIDMap[ID]));
                    }
                    ID = Convert.ToInt32(dr["id2"]);
                    if (GlobalVar.PlayerIDMap.ContainsKey(ID))
                    {
                        dr["id2"] = GlobalVar.PlayerIDMap[ID];
                        LogCombinedInfo(tableName, string.Format("因为合服 玩家ID发生变化 旧玩家ID为{0} 新玩家ID为{1}", ID, GlobalVar.PlayerIDMap[ID]));
                    }
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i + dataGridView1.Rows.Count));
                }
                SaveData(dt);
                ShowSeccInfo(string.Format("合并数据表{0}成功", tableName));
                return true;
            //}
            //catch (Exception ex)
            //{
            //    ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
            //    return false;
            //}
        }
        private bool HandleAchieve()
        {
            string tableName = "t_game_achieve";
            ShowSeccInfo(string.Format("开始合并数据表{0}", tableName));
            if (!SetDataToGridView(tableName))
            {
                ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
                return false;
            }
            //try
            //{
                //玩家ID 玩家名称
                ShowTableInfo(tableName);
                ShowTableInfo(string.Format("待处理数据行数 {0}", dataGridView1.Rows.Count + dataGridView2.Rows.Count));

                DataTable dt = ((DataTable)dataGridView3.DataSource);
                for (int i = 0; i < dataGridView1.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView1.DataSource).Rows[i];
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i));
                }
                for (int i = 0; i < dataGridView2.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView2.DataSource).Rows[i];
                    int ID = Convert.ToInt32(dr["CharacterID"]);
                    if (GlobalVar.PlayerIDMap.ContainsKey(ID))
                    {
                        dr["CharacterID"] = GlobalVar.PlayerIDMap[ID];
                        LogCombinedInfo(tableName, string.Format("因为合服 玩家ID发生变化 旧玩家ID为{0} 新玩家ID为{1}", ID, GlobalVar.PlayerIDMap[ID]));
                    }
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i + dataGridView1.Rows.Count));
                }
                SaveData(dt);
                ShowSeccInfo(string.Format("合并数据表{0}成功", tableName));
                return true;
            //}
            //catch (Exception ex)
            //{
            //    ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
            //    return false;
            //}
        }
        private bool HandleIdentify()
        {
            string tableName = "t_game_identify";
            ShowSeccInfo(string.Format("开始合并数据表{0}", tableName));
            if (!SetDataToGridView(tableName))
            {
                ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
                return false;
            }
            //try
            //{
                //玩家ID 玩家名称
                ShowTableInfo(tableName);
                ShowTableInfo(string.Format("待处理数据行数 {0}", dataGridView1.Rows.Count + dataGridView2.Rows.Count));

                DataTable dt = ((DataTable)dataGridView3.DataSource);
                for (int i = 0; i < dataGridView1.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView1.DataSource).Rows[i];
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i));
                }
                for (int i = 0; i < dataGridView2.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView2.DataSource).Rows[i];
                    int ID = Convert.ToInt32(dr["CharacterID"]);
                    if (GlobalVar.PlayerIDMap.ContainsKey(ID))
                    {
                        dr["CharacterID"] = GlobalVar.PlayerIDMap[ID];
                        LogCombinedInfo(tableName, string.Format("因为合服 玩家ID发生变化 旧玩家ID为{0} 新玩家ID为{1}", ID, GlobalVar.PlayerIDMap[ID]));
                    }
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i + dataGridView1.Rows.Count));
                }
                SaveData(dt);
                ShowSeccInfo(string.Format("合并数据表{0}成功", tableName));
                return true;
            //}
            //catch (Exception ex)
            //{
            //    ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
            //    return false;
            //}
        }
        private bool HandleItem()
        {
            return true;
            string tableName = "t_game_item";
            ShowSeccInfo(string.Format("开始合并数据表{0}", tableName));
            if (!SetDataToGridView(tableName))
            {
                ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
                return false;
            }
            //try
            //{
                //玩家ID 物品唯一ID
                ShowTableInfo(tableName);
                ShowTableInfo(string.Format("待处理数据行数 {0}", dataGridView1.Rows.Count + dataGridView2.Rows.Count));

                DataTable dt = ((DataTable)dataGridView3.DataSource);
                List<Int64> list = new List<long>();
                for (int i = 0; i < dataGridView1.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView1.DataSource).Rows[i];
                    Int64 GuID = Convert.ToInt64(dr["ItemGUID"]);
                    list.Add(GuID);
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i));
                }
                Int64 beginID = GetBegInID(list);
                for (int i = 0; i < dataGridView2.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView2.DataSource).Rows[i];
                    int ID = Convert.ToInt32(dr["CharacterID"]);
                    if (GlobalVar.PlayerIDMap.ContainsKey(ID))
                    {
                        LogCombinedInfo(tableName, string.Format("因为合服 玩家ID发生变化 旧玩家ID为{0} 新玩家ID为{1}", ID, GlobalVar.PlayerIDMap[ID]));
                        dr["CharacterID"] = GlobalVar.PlayerIDMap[ID];
                    }
                    Int64 GuID = Convert.ToInt64(dr["ItemGUID"]);
                    if (list.Contains(GuID) && !GlobalVar.ItemIDMap.ContainsKey(GuID))
                    {
                        while (list.Contains(beginID))
                        {
                            ++beginID;
                        }
                        LogCombinedInfo(tableName, string.Format("物品唯一ID发生变化 旧ID为{0} 新ID为{1}", GuID, beginID));
                        GlobalVar.ItemIDMap.Add(GuID, beginID);
                        dr["ItemGUID"] = beginID;
                        ++beginID;
                    }
                    list.Add(Convert.ToInt64(dr["ItemGUID"]));
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i + dataGridView1.Rows.Count));
                }
                SaveData(dt);
                ShowSeccInfo(string.Format("合并数据表{0}成功", tableName));
                return true;
            //}
            //catch (Exception ex)
            //{
            //    ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
            //    return false;
            //}
        }
        private bool HandleMount()
        {
            string tableName = "t_game_mount";
            ShowSeccInfo(string.Format("开始合并数据表{0}", tableName));
            if (!SetDataToGridView(tableName))
            {
                ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
                return false;
            }
            //try
            //{
                //玩家ID 物品唯一ID
                ShowTableInfo(tableName);
                ShowTableInfo(string.Format("待处理数据行数 {0}", dataGridView1.Rows.Count + dataGridView2.Rows.Count));

                DataTable dt = ((DataTable)dataGridView3.DataSource);
                for (int i = 0; i < dataGridView1.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView1.DataSource).Rows[i];
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i));
                }
                for (int i = 0; i < dataGridView2.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView2.DataSource).Rows[i];
                    int ID = Convert.ToInt32(dr["CharacterID"]);
                    if (GlobalVar.PlayerIDMap.ContainsKey(ID))
                    {
                        dr["CharacterID"] = GlobalVar.PlayerIDMap[ID];
                        LogCombinedInfo(tableName, string.Format("因为合服 玩家ID发生变化 旧玩家ID为{0} 新玩家ID为{1}", ID, GlobalVar.PlayerIDMap[ID]));
                    }
                    Int64 GuID = Convert.ToInt64(dr["GUID"]);
                    if (GlobalVar.ItemIDMap.ContainsKey(GuID))
                    {
                        dr["GUID"] = GlobalVar.ItemIDMap[GuID];
                        LogCombinedInfo(tableName, string.Format("因为合服 物品唯一ID发生变化 旧物品ID为{0} 新物品ID为{1}", GuID, GlobalVar.ItemIDMap[GuID]));
                    }
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i + dataGridView1.Rows.Count));
                }
                SaveData(dt);
                ShowSeccInfo(string.Format("合并数据表{0}成功", tableName));
                return true;
            //}
            //catch (Exception ex)
            //{
            //    ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
            //    return false;
            //}
        }
        private bool HandlePet()
        {
            string tableName = "t_game_pet";
            ShowSeccInfo(string.Format("开始合并数据表{0}", tableName));
            if (!SetDataToGridView(tableName))
            {
                ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
                return false;
            }
            //try
            //{
                //玩家ID 物品唯一ID
                ShowTableInfo(tableName);
                ShowTableInfo(string.Format("待处理数据行数 {0}", dataGridView1.Rows.Count + dataGridView2.Rows.Count));

                DataTable dt = ((DataTable)dataGridView3.DataSource);
                for (int i = 0; i < dataGridView1.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView1.DataSource).Rows[i];
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i));
                }
                for (int i = 0; i < dataGridView2.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView2.DataSource).Rows[i];
                    int ID = Convert.ToInt32(dr["CharacterID"]);
                    if (GlobalVar.PlayerIDMap.ContainsKey(ID))
                    {
                        LogCombinedInfo(tableName, string.Format("因为合服 玩家ID发生变化 旧玩家ID为{0} 新玩家ID为{1}", ID, GlobalVar.PlayerIDMap[ID]));
                        dr["CharacterID"] = GlobalVar.PlayerIDMap[ID];
                    }
                    Int64 GuID = Convert.ToInt64(dr["GUID"]);
                    if (GlobalVar.ItemIDMap.ContainsKey(GuID))
                    {
                        LogCombinedInfo(tableName, string.Format("因为合服 物品唯一ID发生变化 旧物品ID为{0} 新物品ID为{1}", GuID, GlobalVar.ItemIDMap[GuID]));
                        dr["GUID"] = GlobalVar.ItemIDMap[GuID];
                    }
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i + dataGridView1.Rows.Count));
                }
                SaveData(dt);
                ShowSeccInfo(string.Format("合并数据表{0}成功", tableName));
                return true;
            //}
            //catch (Exception ex)
            //{
            //    ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
            //    return false;
            //}
        }
        private bool HandleVisualInfo()
        {
            string tableName = "t_game_visualinfo";
            LogCombinedInfo(tableName, "开始玩家外观处理");
            ShowSeccInfo(string.Format("开始合并数据表{0}", tableName));
            if (!SetDataToGridView(tableName))
            {
                ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
                return false;
            }
            //try
            //{
                //玩家ID 物品唯一ID
                ShowTableInfo(tableName);
                ShowTableInfo(string.Format("待处理数据行数 {0}", dataGridView1.Rows.Count + dataGridView2.Rows.Count));

                DataTable dt = ((DataTable)dataGridView3.DataSource);
                for (int i = 0; i < dataGridView1.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView1.DataSource).Rows[i];
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i));
                }
                for (int i = 0; i < dataGridView2.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView2.DataSource).Rows[i];
                    int ID = Convert.ToInt32(dr["CharacterID"]);
                    if (GlobalVar.PlayerIDMap.ContainsKey(ID))
                    {
                        LogCombinedInfo(tableName, string.Format("因为合服 玩家ID发生变化 旧玩家ID为{0} 新玩家ID为{1}", ID, GlobalVar.PlayerIDMap[ID]));
                        dr["CharacterID"] = GlobalVar.PlayerIDMap[ID];
                    }
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i + dataGridView1.Rows.Count));
                }
                SaveData(dt);
                ShowSeccInfo(string.Format("合并数据表{0}成功", tableName));
                return true;
            //}
            //catch (Exception ex)
            //{
            //    ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
            //    return false;
            //}
        }
        private bool HandleQuestEntrustData()
        { 
            //处理任务委托
            string tableName = "questentrust";
            ShowSeccInfo(string.Format("开始合并数据表{0}", tableName));
            if (!SetDataToGridView(tableName))
            {
                ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
                return false;
            }
            //try
            //{
                //玩家ID 物品唯一ID
                ShowTableInfo(tableName);
                ShowTableInfo(string.Format("待处理数据行数 {0}", dataGridView1.Rows.Count + dataGridView2.Rows.Count));

                DataTable dt = ((DataTable)dataGridView3.DataSource);
                int MaxID = 0;
                for (int i = 0; i < dataGridView1.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView1.DataSource).Rows[i];
                    int ID = Convert.ToInt32(dr["id"]);
                    if (MaxID <= ID)
                        MaxID = ID;
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i));
                }
                MaxID++;
                for (int i = 0; i < dataGridView2.Rows.Count; ++i, ++MaxID)
                {
                    DataRow dr = ((DataTable)dataGridView2.DataSource).Rows[i];
                    int ID = Convert.ToInt32(dr["id"]);
                    LogCombinedInfo(tableName, string.Format("因为合服 唯一ID发生变化 旧ID为{0} 新ID为{1}", ID, MaxID));
                    dr["id"] = MaxID;
                    //源玩家ID
                    int SrcPlayerID = Convert.ToInt32(dr["srcplayerid"]);
                    if (GlobalVar.PlayerIDMap.ContainsKey(SrcPlayerID))
                    {
                        LogCombinedInfo(tableName, string.Format("因为合服 源玩家ID发生变化 旧源玩家ID为{0} 新源玩家ID为{1}", SrcPlayerID, GlobalVar.PlayerIDMap[SrcPlayerID]));
                        dr["srcplayerid"] = GlobalVar.PlayerIDMap[SrcPlayerID];
                    }
                    //源玩家名称
                    string srcName = Convert.ToString(dr["srcplayername"]);
                    if (GlobalVar.PlayerNameMap.ContainsKey(srcName))
                    {
                        LogCombinedInfo(tableName, string.Format("因为合服 源玩家名称发生变化 旧源玩家名称为{0} 新源玩家名称为{1}", srcName, GlobalVar.PlayerNameMap[srcName]));
                        dr["srcplayername"] = GlobalVar.PlayerNameMap[srcName];
                    }
                    //目标玩家ID
                    int DestPlayerID = Convert.ToInt32(dr["destplayerid"]);
                    if (GlobalVar.PlayerIDMap.ContainsKey(DestPlayerID))
                    {
                        LogCombinedInfo(tableName, string.Format("因为合服 目标玩家ID发生变化 旧目标玩家ID为{0} 新目标玩家ID为{1}", DestPlayerID, GlobalVar.PlayerIDMap[DestPlayerID]));
                        dr["destplayerid"] = GlobalVar.PlayerIDMap[DestPlayerID];
                    }
                    //目标玩家名称
                    string destName = Convert.ToString(dr["destplayername"]);
                    if (GlobalVar.PlayerNameMap.ContainsKey(destName))
                    {
                        LogCombinedInfo(tableName, string.Format("因为合服 目标玩家名称发生变化 旧目标玩家名称为{0} 新目标玩家名称为{1}", destName, GlobalVar.PlayerNameMap[destName]));
                        dr["destplayername"] = GlobalVar.PlayerNameMap[destName];
                    }
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i + dataGridView1.Rows.Count));
                }
                SaveData(dt);
                ShowSeccInfo(string.Format("合并数据表{0}成功", tableName));
                return true;
            //}
            //catch (Exception ex)
            //{
            //    ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
            //    return false;
            //}
        }
        private bool HandleGuildCampBattleData()
        { 
            //公会约战数据处理
            //1.顺序ID累加
            //2.公会ID修改
            string tableName = "guildcampbattledata";
            ShowSeccInfo(string.Format("开始合并数据表{0}", tableName));
            if (!SetDataToGridView(tableName))
            {
                ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
                return false;
            }
            //try
            //{
                //玩家ID 物品唯一ID
                ShowTableInfo(tableName);
                ShowTableInfo(string.Format("待处理数据行数 {0}", dataGridView1.Rows.Count + dataGridView2.Rows.Count));

                DataTable dt = ((DataTable)dataGridView3.DataSource);
                int MaxID = 0;
                for (int i = 0; i < dataGridView1.Rows.Count; ++i)
                {
                    DataRow dr = ((DataTable)dataGridView1.DataSource).Rows[i];
                    int ID = Convert.ToInt32(dr["ID"]);
                    if (MaxID <= ID)
                        MaxID = ID;
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i));
                }
                MaxID++;
                for (int i = 0; i < dataGridView2.Rows.Count; ++i, ++MaxID)
                {
                    DataRow dr = ((DataTable)dataGridView2.DataSource).Rows[i];
                    int ID = Convert.ToInt32(dr["ID"]);
                    LogCombinedInfo(tableName, string.Format("因为合服 唯一ID发生变化 旧ID为{0} 新ID为{1}", ID,MaxID));
                    dr["ID"] = MaxID;
                    //修改公会名称
                    int SrcGuildID = Convert.ToInt32(dr["SrcGuildID"]);
                    if (GlobalVar.GuildIDMap.ContainsKey(SrcGuildID))
                    {
                        LogCombinedInfo(tableName, string.Format("因为合服 源公会ID发生变化 旧源公会ID为{0} 新源公会ID为{1}", SrcGuildID, GlobalVar.GuildIDMap[SrcGuildID]));
                        dr["SrcGuildID"] = GlobalVar.GuildIDMap[SrcGuildID];
                    }
                    int DestGuildID = Convert.ToInt32(dr["DestGuildID"]);
                    if (GlobalVar.GuildIDMap.ContainsKey(DestGuildID))
                    {
                        LogCombinedInfo(tableName, string.Format("因为合服 目标公会ID发生变化 旧目标公会ID为{0} 新目标公会ID为{1}", DestGuildID, GlobalVar.GuildIDMap[DestGuildID]));
                        dr["DestGuildID"] = GlobalVar.GuildIDMap[DestGuildID];
                    }   
                    AddDataRow(dt, dr);
                    ShowTableInfo(string.Format("处理行数 {0}", i + dataGridView1.Rows.Count));
                }
                SaveData(dt);
                ShowSeccInfo(string.Format("合并数据表{0}成功", tableName));
                return true;
            //}
            //catch (Exception ex)
            //{
            //    ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
            //    return false;
            //}
        }
        private bool HandlePlayerSum()
        { 
            //修改所有账号下角色的数量 每个账号3个 并且修改指定角色的位置
            //查询全部的角色
            string tableName = "t_game_character";
            LogCombinedInfo(tableName, "开始玩家位置处理");
            string sql = string.Format("select * from {0}  order by Lev desc;", tableName);
            //try
            //{
                //if (!SetDataToGridView(tableName))
                //{ 
                //    //读取数据错误
                //    ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
                //    return false;
                //}
                //DataSet ds = new DataSet();
                //MySqlCommand commondTarget = new MySqlCommand(sql, mySQL_TargetDataBaseConn);
                //mySQL_Da.SelectCommand = commondTarget;
                //mySQL_Da.Fill(ds, "Target");
                //dataGridView3.DataSource = ds.Tables["Target"];
                MySqlCommand commond = new MySqlCommand(sql, mySQL_TargetDataBaseConn);
                MySqlDataReader reader = commond.ExecuteReader();
                ShowTableInfo(tableName);
                ShowTableInfo(string.Format("待处理数据行数 {0}", reader.FieldCount));
                LogCombinedInfo(tableName, string.Format("待处理数据行数 {0}", reader.FieldCount));
                if (!reader.HasRows)
                {
                    LogCombinedInfo(tableName,"查询数据为空 无数据");
                }
                Dictionary<int, PlayerSum> pMap = new Dictionary<int, PlayerSum>();
                while (reader.Read())
                {
                    int AccountID = Convert.ToInt32(reader["AccountID"]);
                    //int IsDel = Convert.ToInt32(reader["IsDel"]);
                    int CharacterID = Convert.ToInt32(reader["characterid"]);
                    //if (IsDel == 1)//删除的角色不做处理
                    //    continue;
                    if (pMap.ContainsKey(AccountID))
                    {
                        pMap[AccountID].list.Add(CharacterID);
                    }
                    else
                    {
                        PlayerSum ps = new PlayerSum();
                        ps.list = new List<int>();
                        ps.AccountID = AccountID;
                        ps.list.Add(CharacterID);
                        pMap.Add(AccountID, ps);
                    }
                    ShowTableInfo(string.Format("处理角色ID {0}", CharacterID));
                }
                reader.Close();
                commond.Dispose();
                //for (int i = 0; i < dataGridView3.Rows.Count; ++i)
                //{
                //    DataRow dr = ((DataTable)dataGridView3.DataSource).Rows[i];
                //    int AccountID = Convert.ToInt32(dr["AccountID"]);
                //    int IsDel = Convert.ToInt32(dr["IsDel"]);
                //    if (IsDel == 1)//删除的角色不做处理
                //        continue;
                //    if (pMap.ContainsKey(AccountID))
                //    {
                //        pMap[AccountID].list.Add(i);
                //    }
                //    else
                //    {
                //        PlayerSum ps = new PlayerSum();
                //        ps.list = new List<int>();
                //        ps.AccountID = AccountID;
                //        ps.list.Add(i);
                //        pMap.Add(AccountID, ps);
                //    }
                //    ShowTableInfo(string.Format("处理行数 {0}", i));
                //}
                LogCombinedInfo(tableName, string.Format("开始玩家位置处理 获取到玩家的全部数据成功 读取的账号数据条数为:{0}",pMap.Count));
                //集合创建完毕后 我们开始处理集合的数据
                int[] Keys = new int[pMap.Count];
                pMap.Keys.CopyTo(Keys, 0);
                LogCombinedInfo(tableName, string.Format("开始玩家位置处理 获取到玩家的全部数据成功 读取的账号数据条数为:{0}", Keys.Length));
                ShowTableInfo(string.Format("待处理数据行数 {0}", Keys.Length));
                for (int i = 0; i < Keys.Length; ++i)
                {
                    int AccountID = Keys[i];
                    LogCombinedInfo(tableName,string.Format("账号数据处理 账号ID:{0},验证ID为:{1},玩家数量为:{2},",pMap[AccountID].AccountID,AccountID,pMap[AccountID].list.Count));
                    if (pMap[AccountID].AccountID != AccountID)
                        continue;
                    if (pMap[AccountID].list.Count <= 3)
                        continue;
                    LogCombinedInfo(tableName, string.Format("账号数据处理 玩家数量大于3 开始处理 账号ID:{0},验证ID为:{1},玩家数量为:{2},", pMap[AccountID].AccountID, AccountID, pMap[AccountID].list.Count));
                    //账号内玩家角色多于3个 取角色等级最高的3个设置好 其他的设置为删除状态
                    for (int j = 0; j < pMap[AccountID].list.Count; ++j)
                    {
                        //修改角色的位置
                        LogCombinedInfo(tableName, string.Format("设置指定角色的位置 角色ID为{0} 位置为{1}", Convert.ToInt32(pMap[AccountID].list[j]), j));
                        //dataGridView3.Rows[pMap[AccountID].list[j]].Cells["CharSlot"].Value = j;

                        string str = string.Format("update {0} set CharSlot = {1}  where characterid= {2}", tableName, j, Convert.ToInt32(pMap[AccountID].list[j]));
                        MySqlCommand commond1 = new MySqlCommand(str, mySQL_TargetDataBaseConn);
                        if (commond1.ExecuteNonQuery() != 1)
                        {
                            ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
                            return false;
                        }
                        
                        //if (j >= 3)
                        //{
                        //    dataGridView3.Rows[pMap[AccountID].list[j]].Cells["IsDel"].Value = 1;
                        //    LogCombinedInfo(tableName, string.Format("设置指定角色的状态为待删除 角色ID为{0}", Convert.ToInt32(dataGridView3.Rows[pMap[AccountID].list[j]].Cells["characterid"].Value)));
                        //}
                        //else
                        //{
                        //    LogCombinedInfo(tableName, string.Format("设置指定角色的位置 角色ID为{0} 位置为{1}", Convert.ToInt32(dataGridView3.Rows[pMap[AccountID].list[j]].Cells["characterid"].Value), j));
                        //    dataGridView3.Rows[pMap[AccountID].list[j]].Cells["CharSlot"].Value = j;
                        //}
                    }
                    ShowTableInfo(string.Format("处理行数 {0}", i));
                }
                //SaveData(((DataTable)dataGridView3.DataSource));
                //MySqlCommandBuilder build = new MySqlCommandBuilder(mySQL_Da);
                //mySQL_Da.Update(((DataTable)dataGridView3.DataSource));
                ShowSeccInfo(string.Format("合并数据表{0}成功", tableName));
                LogCombinedInfo(tableName, "开始玩家位置处理 玩家角色数据修改成功");
                return true;
            //}
            //catch (Exception ex)
            //{
            //    LogCombinedInfo(tableName, "开始玩家位置处理 发送异常 失败");
            //    ShowErrorInfo(string.Format("合并数据表{0}失败", tableName));
            //    return false;
            //}
        }
        private bool CheckDataBaseTable(string DataBaseName, MySqlConnection connection)
        {
            if (connection == null || connection.State != ConnectionState.Open)
                return false;
            string sql = GetAllTableCheckSql(DataBaseName);
            if (sql == "")
                return false;
            MySqlCommand commond = new MySqlCommand(sql, connection);
            try
            {
                int Count = Convert.ToInt32(commond.ExecuteScalar());
                if (Count != DataBaseTableList.Length)
                    return false;
            }
            catch (Exception ex)
            {
                return false;
            }
            return true;
        }
        private string GetAllTableCheckSql(string DataBaseName)
        {
            StringBuilder tableList = new StringBuilder("");
            for (int i = 0; i < DataBaseTableList.Length; ++i)
            {
                tableList.Append("table_name='").Append(DataBaseTableList[i]).Append("'");
                if (i != DataBaseTableList.Length - 1)
                {
                    tableList.Append(" or ");
                }
            }
            return string.Format("select count(table_name) from information_schema.tables where table_schema = '{0}' and ({1})", DataBaseName, tableList.ToString());
        }
        private void EnabledControleDataBase(bool IsEnabled)
        {
            Button1.Enabled = IsEnabled;
            textBox1.Enabled = IsEnabled;
            textBox2.Enabled = IsEnabled;
            textBox3.Enabled = IsEnabled;
            textBox4.Enabled = IsEnabled;
            textBox5.Enabled = IsEnabled;
            textBox6.Enabled = IsEnabled;
            textBox7.Enabled = IsEnabled;
            textBox8.Enabled = IsEnabled;
            textBox9.Enabled = IsEnabled;
            textBox10.Enabled = IsEnabled;
            textBox11.Enabled = IsEnabled;
            textBox12.Enabled = IsEnabled;
            textBox14.Enabled = IsEnabled;
        }
        private void ShowErrorInfo(string Info)
        {
            MessageBox.Show(Info);
            textBox13.AppendText(Info);
            textBox13.AppendText("\r\n");
            textBox13.ScrollToCaret();
        }
        private void ShowSeccInfo(string Info)
        {
            textBox13.AppendText(Info);
            textBox13.AppendText("\r\n");
            textBox13.ScrollToCaret();
        }
        private bool ClearAllInfo(bool Result)
        {
            //合服已经结束 成功 我们清理下
            try
            {
                if (mySQL_SoruceDataBaseConn != null && mySQL_SoruceDataBaseConn.State == ConnectionState.Open)
                    mySQL_SoruceDataBaseConn.Close();
            }
            catch (Exception ex)
            {
                ShowErrorInfo("源数据库连接断开失败");
                return false;
            }
            ShowSeccInfo("源数据库连接断开成功");

            try
            {
                if (mySQL_BeUseDataBaseConn != null && mySQL_BeUseDataBaseConn.State == ConnectionState.Open)
                    mySQL_BeUseDataBaseConn.Close();
            }
            catch (Exception ex)
            {
                ShowErrorInfo("待合并数据库连接断开失败");
                return false;
            }
            ShowSeccInfo("待合并数据库连接断开成功");

            try
            {
                if (mySQL_TargetDataBaseConn != null && mySQL_TargetDataBaseConn.State == ConnectionState.Open)
                    mySQL_TargetDataBaseConn.Close();
            }
            catch (Exception ex)
            {
                ShowErrorInfo("目标数据库连接断开失败");
                return false;
            }
            ShowSeccInfo("目标数据库连接断开成功");
            if (Result)
                MessageBox.Show(string.Format("请手动备份创建的数据库 {0}", textBox12.Text));
            else
                MessageBox.Show(string.Format("请手动删除创建的数据库 {0}", textBox12.Text));
            Application.Exit();
            return true;
        }
        private void LogCombinedInfo(string TableName, string Info)
        {
            try
            {
                string sql = string.Format("insert into CombinedLog(name,info)  values('{0}','{1}')", TableName, Info);
                MySqlCommand commnd = new MySqlCommand(sql, mySQL_TargetDataBaseConn);
                if (commnd.ExecuteNonQuery() == -1)
                {
                    return;
                }
            }
            catch (Exception ex)
            {
                return;
            }
        }
        private void ClearAllDataGridView()
        {
            mySQL_Da = new MySqlDataAdapter();
            dataGridView1.DataSource = null;
            dataGridView1.Rows.Clear();
            dataGridView1.Columns.Clear();
            dataGridView2.DataSource = null;
            dataGridView2.Rows.Clear();
            dataGridView2.Columns.Clear();
            dataGridView3.DataSource = null;
            dataGridView3.Rows.Clear();
            dataGridView3.Columns.Clear();
        }
        private bool SetDataToGridView(string tableName)
        {
            //将同样的SQl语句用3种不同的查询绑定到DataGridView
            try
            {
                ClearAllDataGridView();
                //1.查询源数据库的数据到控件
                string sqlSource = string.Format("select * from {0};", tableName);
                MySqlCommand commondSource = new MySqlCommand(sqlSource, mySQL_SoruceDataBaseConn);
                mySQL_Da.SelectCommand = commondSource;
                DataSet ds = new DataSet();
                mySQL_Da.Fill(ds, "Source");//将数据填充到Ds里面去
                dataGridView1.DataSource = ds.Tables["Source"];
                //2.查询待合并数据库的数据到控件
                string sqlBeUse = string.Format("select * from {0};", tableName);
                MySqlCommand commondBeUse = new MySqlCommand(sqlBeUse, mySQL_BeUseDataBaseConn);
                mySQL_Da.SelectCommand = commondBeUse;
                mySQL_Da.Fill(ds, "BeUse");
                dataGridView2.DataSource = ds.Tables["BeUse"];
                //3.目标数据库的数据也查询出来
                string sqlTarget = string.Format("select * from {0};", tableName);
                MySqlCommand commondTarget = new MySqlCommand(sqlTarget, mySQL_TargetDataBaseConn);
                mySQL_Da.SelectCommand = commondTarget;
                mySQL_Da.Fill(ds, "Target");
                dataGridView3.DataSource = ds.Tables["Target"];

                if (dataGridView1.Columns.Count != dataGridView2.Columns.Count || dataGridView1.Columns.Count != dataGridView3.Columns.Count || dataGridView2.Columns.Count != dataGridView3.Columns.Count)
                {
                    //表的列数错误
                    return false;
                }
            }
            catch (Exception ex)
            {
                return false;
            }
            return true;
        }
        private bool LoadSourceDataToTarget()
        {
            for (int i = 0; i < dataGridView1.Rows.Count; ++i)
            {
                DataRow dr = ((DataTable)dataGridView1.DataSource).Rows[i];
                ((DataTable)dataGridView3.DataSource).ImportRow(dr);
            }
            return true;
        }
        private int GetBegInID(List<int> list)
        {
            int beginid = 0;
            for (int i = 0; i < list.Count; ++i)
            {
                if (list[i] > beginid)
                    beginid = list[i];
            }
            beginid++;
            return beginid;
        }
        private long GetBegInID(List<long> list)
        {
            long beginid = 0;
            for (int i = 0; i < list.Count; ++i)
            {
                if (list[i] > beginid)
                    beginid = list[i];
            }
            beginid++;
            return beginid;
        }
        private void AddDataRow(DataTable dt, DataRow dr)
        {
            dt.Rows.Add(dr.ItemArray);
        }
        private void SaveData(DataTable dt)
        {
            ShowTableInfo("正在将合并后数据写入数据库...");
            MySqlCommandBuilder build = new MySqlCommandBuilder(mySQL_Da);
            mySQL_Da.Update(dt);
        }
        private void ShowTableInfo(string str)
        {
            textBox15.AppendText(str+"\r\n");
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            System.Windows.Forms.Control.CheckForIllegalCrossThreadCalls = false;
        }
    }
}