#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "��Ӣ��¥��¥");
        set("long", @LONG
��¥�����νྻ�����п������κ��ݣ�ʮ���Ǹ��̴�֡������
�Ը�������Ͻ��ǵ�ȫ����
LONG );
        set("exits", ([
                "down" : "/d/beijing/huiying",
        ]));
        set("objects", ([
                CLASS_D("gaibang") + "/ada" : 1,
                "/d/tulong/yitian/npc/zhaomin2" : 1,
                "/d/tulong/yitian/npc/zhao1" : 1,
                "/d/tulong/yitian/npc/qian2" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2790);
	set("coor/y", 7640);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}