/*
 * 2017-9-27  增加srio组播功能
 * 			     
 * 2017-8-29  对代码进行了优化，并增加了异步通信功能
 * 
 * */
#ifndef __EIPC_H__
#define __EIPC_H__

#include <reworks/types.h>
#include <netinet/in.h>
#include <time.h>

#ifdef __cplusplus
extern "C"
{
#endif 

#define MASTER        				0x00000001/*MSG接收端口*/
#define SLAVE	     				0x00000010/*MSG发送端口*/
#define O_NOBLOCK   				0x00000100
#define USE_MCAST					0x00001000

#define GET_PORT_ATTR				0x00100001
#define SET_PORT_NONNLK				0x00100002
#define GET_DEFAULT_TIMEOUT			0x00100003
#define SET_DEFAULT_TIMEOUT			0x00100004
#define SET_PORT_MemNum				0x00100006
#define GET_PORT_MemNum				0x00100007

#define NO_DEBUG_EIPC				0

#define SUPPORTED_TASK_NUM			4


enum LINKTYPE{
	SHARE_MEM = 0,
	RAPIDIO,
	NET
};
enum MSGTYPE{
	BLK_DATA = 0,
	MSG_DATA,
};

typedef struct __PORT_ATTR__
{
	s8 portname[16];
	u8 transflag;
	u8 nonblk;
	u8 linktype;
	u8 connection;
	int MemNum;
	int MemIndex;
	
}PORT_ATTR;

typedef struct eipc_iovec
{
	char * buffer;	/*in*/
	int size;		/*inout*/
}DATA_BUF;

s32 eipc_init(u8 domainid);

s32 eipc_init_check();

s32 eipc_open(s8 *name, s32 flags ,u8 MemNum,u8 Memindex);

s32 eipc_hunt(s32 handle,s32 timeout);

s32 eipc_send(s32 handle,u8 msgtype, u8 linktype,s32 offset, s8 *buffer, s32 nBytes, s32 timeout, s32 tag);

s32 eipc_recv(s32 handle,u8 msgtype,u8 linktype,s8 *buffer, s32 maxBytes, s32 timeout, int * memindex, s32 tag);

s32 eipc_receive(s32 handle,u8 msgtype,u8 linktype,s8 *buffer, s32 maxBytes, s32 timeout, int * memindex, s32 tag);

s32 eipc_gather(s32 handle,s8 *buffer, s32 nBytes, s32 timeout);

s32 eipc_segment_gather(s32 handle,DATA_BUF *rcv, s32 count, s32 timeout);

s32 eipc_scatter(s32 handle,u8 msgtype, u8 linktype,s8 *buffer, s32 nBytes, s32 timeout);

s32 eipc_barrier(s32 handle,s32 memnum,s32 timeout);

s32 eipc_close(s32 handle,s32 timeout);

s32 eipc_errno_get(s32 isprint);

int eipc_wait(s32 handle);

int eipc_test(s32 handle);

s32 eipc_i_send(s32 handle, s8 *buf, s32 size);

s32 eipc_i_recv(s32 handle, s8 *buf, s32 size);

s32 eipc_i_scatter(s32 handle, s8  * buf,s32 size);

s32 eipc_i_gather(s32 handle, s8  * buf,s32 size);

s32 eipc_scatter2(s32 handle,s8 *buffer, s32 nBytes, s32 timeout);

s32 eipc_updata(s32 handle,int timeout);

s32 eipc_get_members(s32 handle);

void eipc_info(int detail);

/*以下接口给其它程序使用*/

void eipc_info(int detail);

s32 eipc_ioctl(u32 cmd,s32 handle,void * para);

s32 eipc_print_attr(s32 handle);

s32 eipc_traf_ctrl(u32 flag);

s32 eipc_msg_port_num(int *NumSnd, int *NumRcv);

s32 eipc_blk_port_num(int *NumSnd, int *NumRcv);

s32 eipc_msg_traf_count(void *mem, u32 size);

s32 eipc_blk_traf_count(void *mem, u32 size);




#ifdef __cplusplus
}
#endif

#endif
