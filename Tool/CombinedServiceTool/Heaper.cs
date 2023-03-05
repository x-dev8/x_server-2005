using System;
using System.Collections.Generic;
using System.Text;

namespace CombinedServiceTool
{
    public struct PlayerSum
    {
        public int AccountID;
        public List<int> list;
    };
    class GlobalVar
    {
        public static Dictionary<int, int> GuildIDMap = new Dictionary<int, int>(); //��¼����ID�ı仯
        public static Dictionary<int, int> PlayerIDMap = new Dictionary<int, int>();//��¼���ID�ı仯
        public static Dictionary<string, string> PlayerNameMap = new Dictionary<string, string>();//������Ʊ仯
        public static Dictionary<long, long> ItemIDMap = new Dictionary<long, long>();//��¼��ƷID�ı仯
        public static Dictionary<string, string> GuildNameMap = new Dictionary<string, string>();
        public static Dictionary<int, int> PlayerGuildMap = new Dictionary<int, int>();
        public static Dictionary<UInt32, UInt32> AccountYuanBaoMap = new Dictionary<UInt32, UInt32>();//�˺�Ԫ���ļ�¼

        public enum E_Global
        {
            E_GI =0,
            E_PI,
            E_PN,
            E_II,
            E_GN
        };
    }
}