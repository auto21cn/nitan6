// Code of ShenZhou
// Room: didao_n_3.c �ص���
// Zhangchi 7/00

inherit ROOM;
#include "didao.h"

void create()
{
        set("short", "�ص�");
        set("long", @LONG
����һ���ո��ڳɵĵص������������������졣
LONG );
        set("exits", ([
                "south": "/d/mingjiao/didao/didao_n_2",
]));
        
        set("cost", 1);
        set("valid_dig","north");

        setup();
//        replace_program(ROOM);
}

void init()
{
        int num=get_room("north");
        if (num >= 4)
                set("exits/north","/d/mingjiao/didao/didao_n_4");
        else
                delete("exits/north");

        add_action("do_dig","wa");
        add_action("do_dig","dig");
}