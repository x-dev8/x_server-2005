#pragma once

#define MOREENGINE_MAJOR_VERSION 3		// 大更新版本号。较前版本有大幅改善（性能，代码结构，数据结构等）。
#define MOREENGINE_MINOR_VERSION 0		// 小更新版本号。需要结构性更改客户端代码。
#define MOREENGINE_PATCH_VERSION 0		// 补丁版本号。内部小bug修改，不需要改动客户端。
#define MOREENGINE_BUILD_VERSION 866	// svn版本号。跟随svn变化。

#define MOREENGINE_SDK_VERSION \
	(MOREENGINE_MAJOR_VERSION << 24) | (MOREENGINE_MINOR_VERSION << 16) | \
	(MOREENGINE_PATCH_VERSION << 8) | (MOREENGINE_BUILD_VERSION << 0) 