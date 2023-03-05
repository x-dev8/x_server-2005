#ifndef __MODELCONFIG_H__
#define __MODELCONFIG_H__


/************************************************************************
          
		Id					如果有编辑器是自动生成的（递增）不显示出来，在无编辑器是先手动写
		FilePath			模型的文件路径，相对于Data目录
		HeadPicture			头像的文件路径，相对于Data目录
************************************************************************/

#include <string>
#include <map>

#define theModelConfig ModelConfig::Instance()

class ModelConfig
{
public:
	enum ModelId
	{
		ErrorId = -1,   //无效id
	};

	struct ModelData
	{
		ModelData() : Id(ErrorId), FilePath(""), HeadPicture("Data/Ui/HeadPicture/unkown_t.dds"), Description("") { }

		unsigned short Id;
		std::string FilePath;
		std::string HeadPicture;
		std::string Description;			//描述,显示用,无实质作用

		inline bool operator == (unsigned short nId) { return (this->Id == nId); }
		inline bool operator < (const ModelData& xModelData) { return (this->Id < xModelData.Id); }

		inline ModelData& operator = (const ModelData& xModelData)
		{	
			if(this != &xModelData)
			{
				Id = xModelData.Id;
				FilePath = xModelData.FilePath;
				HeadPicture = xModelData.HeadPicture;
				Description = xModelData.Description;
			}

			return *this;
		}
	};

protected:
	ModelConfig() { m_mapModelData.clear(); }

public:
	~ModelConfig() {}

	inline static ModelConfig& Instance()
	{
		static ModelConfig s_xModelConfig;

		return s_xModelConfig;
	}

	inline unsigned int ModelDataCount() { return static_cast<unsigned int>(m_mapModelData.size()); }

	bool LoadModelConfig(const char* szFile);
	bool SaveModelConfig(const char* szFile);

	inline bool IsEmpty() { return m_mapModelData.empty(); }
	inline void Clear() { m_mapModelData.clear(); }

	bool AddModelData(ModelData& xModelData, bool bReplace = false);
	bool RemoveModelData(unsigned short nId);

	ModelData* GetModelDataById(unsigned short nId);

public:
	std::map<unsigned short, ModelData> m_mapModelData;

	typedef std::map<unsigned short, ModelData>::iterator modeliter;
};


#endif