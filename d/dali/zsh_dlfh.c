//zsh_bjfh.c
#include <ansi.h>

inherit ROOM;

#define PLACE "dl"
#define TYPE  "good"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", MAG"���������"NOR);
        set("long", @LONG
���������������ڴ����ķֻᣬ���й��˺ܶ൤���ͼ��������
���е��ử�����е�ĥī������һ�������ߣ������ֻӺ�����������
����������ǽ������һ������(paizi)�����������Ա������������ȡ
�ø�������ȥ��ɡ�
LONG );

        set("objects", ([ 
               "/d/dali/npc/zsh_xiao"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([ 
                "north" : "/d/dali/zsh_dldamen",
        ]));

	set("coor/x", -19150);
	set("coor/y", -6910);
	set("coor/z", 0);
	setup();
}
#include <bang_good.h>