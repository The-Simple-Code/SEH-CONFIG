#ifndef __MASTER_CONFIG_H
#define __MASTER_CONFIG_H

#include "C:\\BCB_PROJECT\\SHAREDMEMORY\\sharedmemory.h"
/*
사용파일 경로를 SEH GRADE MASTER에서 CONFIG로 변경함
*/
//const String DEVICE_LIST_FILE_NAME      ="C:\\Program Files\\S&P SYSTEM\\CONFIG\\device.sdd";
//const String PORT_LIST_FILE_NAME        ="C:\\Program Files\\S&P SYSTEM\\CONFIG\\port.spd";
//const String MASTER_CONFIG_FILE_NAME    ="C:\\Program Files\\S&P SYSTEM\\CONFIG\\SEH_MASTER.mcf";
//const String DEVICE_LIST_FILE_BAK_NAME  ="C:\\Program Files\\S&P SYSTEM\\CONFIG\\device_bak.sdd";
//const String PORT_LIST_FILE_BAK_NAME    ="C:\\Program Files\\S&P SYSTEM\\CONFIG\\port_bak.spd";

/*
typedef struct __SHITEMS
{
        char name[20];
        int  service;
        float min;
        float max;
        int maker;
        int item ;
        int extra[8];
}SHITEMS;


typedef struct __SHPORT
{
        int port[8];
        int maker;
        int link[3];
        int svc_init;
        int svc_read;
        int svc_write;
}SHPORT;


typedef struct __SHMCFG
{
        char customer[200];
        char work_dir[200];
        char work_fn[200];
        int  lane;
        int  drop;
        int  itn;
        bool labeller;
        bool totalizer;
        bool do_ext;
        bool bextra[4];
        int  iextra[10];
        SHITEMS  item[5];
        SHPORT   shport[15];

}SHMCFG;
*/


typedef struct __DDF
{
        String maker;
        String item[5];
        String calc[50];
}DDF;
typedef struct __PDF
{
        String init[50];
        String read[50];
        String write[50];
        String maker[50];
}PDF;
#endif
