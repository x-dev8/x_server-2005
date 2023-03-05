//�������ǵ������ļ�  �������Ϳͻ��˶���Ҫʹ��
//<Mount StarLevel="" Money="" DownStar0="" DownStar1="" DownStar2="" DownStar3="">
//      <Item ItemID="" ItemSum=""/>
//  </Mount>
#pragma once
#include <vector>
#include <map>
struct MountMoveStatStruct
{
	unsigned int Star;
	unsigned int Money;
	std::vector<unsigned int> DownStarVec;//�ɹ�����
	std::map<unsigned int,unsigned int> ItemMap;//���ĵĲ���
	unsigned int GetDowmStar()
	{
		//���һ���� �������� ���������� �ͻ��˲�����
		//rand() % nValue;
		unsigned int Sum = 0;
		if(DownStarVec.empty())
			return 0;
		else
		{
			std::vector<unsigned int>::iterator Iter = DownStarVec.begin();
			for(;Iter != DownStarVec.end();++Iter)
			{
				Sum += *Iter;
			}
			int Value = rand() % Sum;
			Iter = DownStarVec.begin();
			unsigned int Star = 0;
			Sum =0;
			for(;Iter != DownStarVec.end();++Iter,++Star)
			{
				Sum += *Iter;
				if(Value > Sum)
					continue;
				else
					return Star;
			}
			return 0;
		}
	}
};
class MountMoveStarConfig
{
public:
	MountMoveStarConfig();
	~MountMoveStarConfig();
	static MountMoveStarConfig& Instance()
    {
        static MountMoveStarConfig s_xConfig;
        return s_xConfig;
    }
	bool LoadMountMoveStarConfig(const char* FilePath);
	MountMoveStatStruct* GetConfigStruct(unsigned int Star);
private:
	std::map<unsigned int,MountMoveStatStruct> m_ConfigMap;
};