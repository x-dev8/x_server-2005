#ifndef _T_OBJECT_POOL_T_H
#define _T_OBJECT_POOL_T_H
//add this file by lilong 2010.1.8
#include <list>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//增加重复释放等检测。
#include <assert.h>
#ifdef __GNUC__
#include <stdint.h>
#endif
template<class T>
class objectpool
{
public:
	enum objectpoolflag
	{
		objectflag__NODE_IS_USED = 0x54545454,	//使用中
		objectflag__NODE_UN_USED = 0x69696969	//未使用
	};
	struct debugflag_
	{
		intptr_t flag;
	};
	struct memnode_
	{
#ifndef NDEBUG
		struct debugflag_ debugflag;
#endif
		struct memnode_ *next;
	};
private:
	struct memnode_ *m_poolstart;			//释放整个池子时使用此指针（此的大小为m_poolnum*sizeof(T)）
	struct memnode_ *m_poolend;
	size_t m_poolnum;						//对象的数目
	size_t m_blocksize;						//块大小
	struct memnode_ *m_freelist;			//对象池的对象队列
	size_t m_has_num;						//对象池中当前的对象数目

	void list_add_( struct memnode_ *node )
	{
		assert( node );
		if( !node )
			return;
		node->next = m_freelist;
		m_freelist = node;
		m_has_num++;
	}

	struct memnode_ *list_pop_()
	{
		if( !m_freelist )
			return NULL;
		struct memnode_ *temp = m_freelist;
		m_freelist = m_freelist->next;
		m_has_num--;
		return temp;
	}

	//对象池初始化
	bool init()
	{
		m_poolstart = (struct memnode_*)malloc(m_poolnum * m_blocksize );
		if( !m_poolstart )
		{
			assert( false && "malloc memory error!  function init!\n");
			return false;
		}
		m_poolend = (struct memnode_*)((char*)m_poolstart + m_blocksize * m_poolnum);
		struct memnode_ *te = m_poolstart;
		for( size_t i = 0; i < m_poolnum; i++)
		{
#ifndef NDEBUG
			te->debugflag.flag = objectflag__NODE_UN_USED;
#endif
			list_add_( te );

			te = (struct memnode_*)( (char*)te + m_blocksize );
		}
		if(te != m_poolend)
		{
			printf("error\n");
			free( m_poolstart );
			m_poolstart = NULL;
			m_poolend = NULL;
			m_freelist = NULL;
			m_has_num = 0;
			return false;
		}

		return true;
	}						
public:
	size_t GetBlockSize () { return m_blocksize; }

	objectpool( size_t poolnum )
	{
		m_poolnum = poolnum;
		m_blocksize = 0;
#ifndef NDEBUG
		m_blocksize += sizeof( struct debugflag_ );
#endif
		m_blocksize += ( ( sizeof(T) + 7 )& ~7 );	/*按8字节对齐*/
		m_poolstart = NULL;
		m_poolend = NULL;
		m_freelist = NULL;
		m_has_num = 0;
		if( !init() )
		{
			printf("init pools is faild!\n");
		}
	}
	~objectpool()
	{
#ifndef NDEBUG
		struct memnode_ *node, *next;
		size_t nodenum = 0;
		for( node = m_freelist; node; node = next )
		{
			next = node->next;
			if( node->debugflag.flag == objectflag__NODE_IS_USED )
				assert( false && "node_list user allot memnode, but not free ! error!" );
			if( node->debugflag.flag != objectflag__NODE_UN_USED )
				assert( false && "node_list memory node flag is not using, and is not untapped!  falg is changed in sometime!!!error!" ); //标记被改变为未知值
			nodenum++;
		}

		node = m_poolstart;
		for( size_t i = 0; i < m_poolnum; i++ )
		{
			if( node->debugflag.flag == objectflag__NODE_IS_USED )
			{
				printf("user allot memnode, but not free ! error!, obj size:%d, objnum:%d\n", sizeof(T), m_poolnum);
				assert( false && "user allot memnode, but not free ! error!" );
			}
			if( node->debugflag.flag != objectflag__NODE_UN_USED )
				assert( false && "memory node flag is not using, and is not untapped!  falg is changed in sometime!!!error!" ); //标记被改变为未知值
			node = (struct memnode_ *)((char*)node + m_blocksize);
		}
		if( nodenum != m_poolnum )
		{
			assert( false && "free list node num not eq m_poolnum! error!" );
		}
#endif
		if( m_poolstart )
		{
			free( m_poolstart );
		}

		if( m_has_num != m_poolnum )
		{
			assert(false && "has memory not free!!\n");	//服务器关闭时，未回收从池子中取出的对象
#ifdef NDEBUG
			printf("has memory not free\n");
#endif
		}
		m_poolstart = NULL;
		m_poolend = NULL;
		m_freelist = NULL;
	}
#ifndef NDEBUG
	bool FlagIsNaturalForFreeObject( struct memnode_ *obj )
	{
		if( ( obj->debugflag.flag != objectflag__NODE_IS_USED ) && ( obj->debugflag.flag != objectflag__NODE_UN_USED ) )
		{	
			printf("memnode flag is bad!!error!");
			assert( false && "memnode flag is bad!!error!" );
		}
		if( obj->debugflag.flag == objectflag__NODE_UN_USED )
		{
			assert( false && "repeat free memnode!!! error!" );
		}
		if( obj->debugflag.flag == objectflag__NODE_IS_USED )
			return true;
		return false;
	}
#endif
	//回收对象
	void FreeObject(T *userobj)	
	{
		if( userobj == NULL )
			return;
		if( !IsInPool(userobj) )
		{
			return;
		}
		if( IsBadPoint( userobj ) )
		{
			assert(false && "pointer is between pools address, but is bad pointer!!!\n");
			printf("pointer is between pools address, but is bad pointer!!!\n");
			return;
		}
		struct memnode_ *obj;
#ifndef NDEBUG
		obj = (struct memnode_*)( (char*)userobj - (size_t)(&((struct memnode_*)0)->next ) );
		if( !FlagIsNaturalForFreeObject( obj ) )
			return;
#else
		obj = (struct memnode_*)userobj;
#endif

#ifndef NDEBUG
		obj->debugflag.flag = objectflag__NODE_UN_USED;
#endif	
		list_add_( obj );
	}

	//获取一个对象
	T *GetObject()
	{
		if( m_has_num != 0 )
		{
			struct memnode_ * _temp = list_pop_();
			if(_temp)
			{
				//返回T成员的地址，并且设置标志
#ifndef NDEBUG
				if( _temp->debugflag.flag != objectflag__NODE_UN_USED )
				{
					printf("sizeof(T):%d\n", sizeof(T));
					printf("memnode node flag is bad!!error!\n");
					assert( false && "memory node flag is bad!! error!" );	//节点标记被损坏或者其他原因导致改变
				}
				_temp->debugflag.flag = objectflag__NODE_IS_USED;
#endif
				return (T*)(&_temp->next);
			}
			else
			{
				printf("get null from pool!!!\n");
				assert( false && "get null from pool!!!\n");
			}
		}
		return NULL;
	}
	//此对象是否为此池子中的
	bool IsInPool( T *userobj )
	{
		struct memnode_ *obj;
#ifndef NDEBUG
		obj = (struct memnode_*)( (char*)userobj - (size_t)(&((struct memnode_*)0)->next ) );
#else
		obj = (struct memnode_*)userobj;
#endif
		//地址范围
		if( ((char*)obj < (char*)m_poolstart ) || (char*)obj >= (char*)m_poolend )
		{
			printf("free not in pool\n");
			return false;
		}
		return true;
	}
	//是否为此池子中的野指针，是野指针，返回true
	bool IsBadPoint( T *userobj )
	{
		struct memnode_ *obj;
#ifndef NDEBUG
		obj = (struct memnode_*)( (char*)userobj - (size_t)(&((struct memnode_*)0)->next ) );
#else
		obj = (struct memnode_*)userobj;
#endif
		if( ( ((char*)obj - (char*)m_poolstart)%m_blocksize ) != 0)
		{
			printf("free bad point\n");
			return true;
		}
		return false;
	}
	size_t getnum()
	{
		return m_has_num;
	}
	void writeinfotofile (FILE *fp, int index)
	{
		assert(fp != NULL);
		if (!fp)
			return;
		fprintf(fp, "%-16d|%-16d|%-15d|%-1d\n", index, m_blocksize, m_poolnum, m_has_num);
	}
};
class poolmgrbase
{
public:
	poolmgrbase(){}
	virtual ~poolmgrbase(){}
	virtual void writeinfotofile (FILE *fp) = 0;
};
//所有内存池集的详细信息
class poolmeminfo
{
public:
	poolmeminfo()
	{
		m_filename = "pools_meminfo_log.txt";
		m_infolist.clear();
	}
	~poolmeminfo()
	{
		m_infolist.clear();
	}
	static poolmeminfo &Instance ()
	{
		static poolmeminfo m;
		return m;
	}
	void AddInfo (poolmgrbase *info)
	{
		if (IsIn(info))
		{
			assert(false && "already in info list!");
			return;
		}
		m_infolist.push_back(info);
	}
	void RemoveInfo (poolmgrbase *info)
	{
		if (!IsIn(info))
		{
			assert(false && "why not in info list!");
			return;
		}
		m_infolist.remove(info);
	}
	void writeinfotofile ()
	{
		FILE *fp = fopen(m_filename.c_str(), "a");
		if (!fp)
			return;

		time_t tval;
		time( &tval );
		struct tm *currTM = localtime( &tval );
		fprintf(fp, "memory pool info data:	[%d/%02d/%02d %02d:%02d:%02d]\n", currTM->tm_year+1900, currTM->tm_mon+1, currTM->tm_mday, currTM->tm_hour, currTM->tm_min, currTM->tm_sec);
		fprintf(fp, "<+++++++++++++++++++++++++++++++++++++++++++++++++++++>\n");
		for (std::list<poolmgrbase*>::iterator itr = m_infolist.begin(); itr != m_infolist.end(); ++itr)
		{
			(*itr)->writeinfotofile(fp);
		}
		fprintf(fp, "<+++++++++++++++++++++++++++++++++++++++++++++++++++++>\n\n\n\n");
		fclose(fp);
	}
	void SetMeminfoFileName (const char *filename)
	{
		assert(filename != NULL);
		if (!filename)
			return;
		if (strcmp(filename, "") == 0)
			return;
		m_filename = filename;
	}
private:
	bool IsIn (poolmgrbase *info)
	{
		for (std::list<poolmgrbase*>::iterator itr = m_infolist.begin(); itr != m_infolist.end(); ++itr)
		{
			if ((*itr) == info)
				return true;
		}
		return false;
	}
private:
	std::string m_filename;
	std::list<poolmgrbase*> m_infolist;
};
#define sPoolInfo poolmeminfo::Instance()

template<class T>
class poolmgr:public poolmgrbase
{
public:
	typedef typename std::list<objectpool<T>*> _Type;
	typedef typename std::list<objectpool<T>*>::iterator _Typeitr;
private:
	_Type m_pool;
	objectpool<T> *m_selfpool;
	size_t m_objnum;			//池子中对象数目
	const char *m_poolsname;	//池子名字
public:
	int getsize()
	{
		return m_selfpool->getnum();
	}
	poolmgr( size_t num, const char *name/* = "null pool name!" */)
	{
		assert( num > 0);
		if( num == 0)
			num = 8;
		m_objnum = num;
		m_poolsname = name;
		m_selfpool = new objectpool<T>(m_objnum);
		m_pool.clear();
		sPoolInfo.AddInfo(this);
	}
	~poolmgr()
	{
		sPoolInfo.RemoveInfo(this);
		if( m_selfpool )
		{
			delete m_selfpool;
			m_selfpool = NULL;
		}
		for( _Typeitr itr = m_pool.begin(); itr != m_pool.end(); itr++)
		{
			if( (*itr) )
			{
				delete (*itr);
			}
		}
		m_pool.clear();
	}
	//获取对象
	T *GetObject()
	{
		T *_temp = NULL;
		if( m_selfpool->getnum() > 0 )	//自身池子够
		{
			_temp = m_selfpool->GetObject();
			if( !_temp )
			{
				printf("have obj,why return NULL??\n");
				assert( false && "have obj,why return NULL??\n");
				return NULL;
			}
			return _temp;
		}
		else	//从新池子拿
		{
			for( _Typeitr itr = m_pool.begin(); itr != m_pool.end(); itr++)
			{
				if( (*itr) )
				{
					if( (*itr)->getnum() > 0 )
					{
						_temp = (*itr)->GetObject();
						if( !_temp )
						{
							printf("m_pool have obj,why return NULL??\n");
							assert( false && "have obj,why return NULL??\n");
							return NULL;
						}
						return _temp;
					}
				}
			}

			//当拥有的池子链表中都无时，创建新池子

			objectpool<T> *_newpool = new objectpool<T>(m_objnum);
			if( !_newpool )
			{
				printf("new objectpool is error!\n");
				assert( false && "new objectpool is error!\n");
				return NULL;
			}
			m_pool.push_back( _newpool );
			_temp = _newpool->GetObject();
			if( !_temp )
			{
				printf("new pool,why return null??\n");
				assert( false && "new pool,why return null??\n");
				return NULL;
			}
			return _temp;
		}
	}
	//释放对象
	void FreeObject( T *obj )
	{
		if( !obj)
			return;
		if( m_selfpool->IsInPool( obj) )
		{			
			m_selfpool->FreeObject( obj );
			return;
		}
		else
			printf("m_selfpool %s:free not in pool\n",m_poolsname);

		for( _Typeitr itr = m_pool.begin(); itr != m_pool.end(); itr++)
		{
			if( (*itr) )
			{
				if( (*itr)->IsInPool( obj ) )
				{					
					(*itr)->FreeObject( obj );
					return;
				}
				else
					printf("m_pool %s:free not in pool\n",m_poolsname);
			}
		}

		printf("pointer is not this pools address!\n");
		assert(false && "pointer is not this pools address!\n");
	}
	void writeinfotofile (FILE *fp)
	{
		assert(fp != NULL);
		if (!fp)
			return;
		size_t size = m_selfpool->GetBlockSize()*m_objnum*(m_pool.size()+1);
		fprintf(fp, "%s:\n<<<<<<<<<<<<<<<<<<memorypool info begin<<<<<<<<<<<<<<<<<\nobject size:%u\nevery pool object num:%u\npools have pool num:%u\nmemory total: %u(byte), %u(kb), %u(mb)\n",
			m_poolsname, m_selfpool->GetBlockSize(), m_objnum, m_pool.size()+1, size, size/1024, size/(1024*1024));
		fprintf(fp, "pool number     |object size     |max_num        |current_num\n");
		int index = 0;
		m_selfpool->writeinfotofile(fp, index);
		for (_Typeitr itr = m_pool.begin(); itr != m_pool.end(); ++itr)
		{
			if (index >= 1000)
				break;

			++index;
			(*itr)->writeinfotofile(fp, index);
		}
		fprintf(fp, ">>>>>>>>>>>>>>>>>>memorypool info end>>>>>>>>>>>>>>>>>>\n\n");
	}
};
#endif
