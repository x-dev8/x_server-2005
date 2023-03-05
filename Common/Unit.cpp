#include "Unit.h"
UnitManager::UnitManager()
{
	CreateCrc32Table();
}
UnitManager::~UnitManager()
{
	
}
void UnitManager::CreateCrc32Table()
{
	int i,j;
	unsigned int crcT;
	for (i = 0; i < 256; i++)
	{
		crcT = i;
		for (j = 0; j < 8; j++)
		{
			if (crcT & 1)
				crcT = (crcT >> 1) ^ 0xEDB88320;
			else
				crcT >>= 1;
		}
		Crc32Table[i] = crcT;
	}
}
unsigned int UnitManager::Crc32(std::string& str)
{
	unsigned int crc(0xffffffff);
	int len;
	unsigned char* buffer;
	len =static_cast<int>(str.size());
	buffer = (unsigned char*)str.c_str();

	while(len--)
		crc = (crc >> 8) ^ Crc32Table[(crc & 0xFF) ^ *buffer++];
	return crc^0xffffffff;
}