#pragma once

#define MOREENGINE_MAJOR_VERSION 3		// ����°汾�š���ǰ�汾�д�����ƣ����ܣ�����ṹ�����ݽṹ�ȣ���
#define MOREENGINE_MINOR_VERSION 0		// С���°汾�š���Ҫ�ṹ�Ը��Ŀͻ��˴��롣
#define MOREENGINE_PATCH_VERSION 0		// �����汾�š��ڲ�Сbug�޸ģ�����Ҫ�Ķ��ͻ��ˡ�
#define MOREENGINE_BUILD_VERSION 866	// svn�汾�š�����svn�仯��

#define MOREENGINE_SDK_VERSION \
	(MOREENGINE_MAJOR_VERSION << 24) | (MOREENGINE_MINOR_VERSION << 16) | \
	(MOREENGINE_PATCH_VERSION << 8) | (MOREENGINE_BUILD_VERSION << 0) 