#include <room.h>
inherit TRANS_ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
���Ǳ����ǵ����ǣ����깩Ӧ���ʲ��ϡ������Թ����ӽ��£�ɶ
���й�أ��͵�Ҳ�ػ��ź��ˣ������ǻ����ǣ�����Ǻ����տ�����
����ι�����㣬��ϴˢ�ø�Ǭ������һֱ�ź򵽿�����·�������µ�
��ľ���϶��ſ���ľ�� (paizi)�������жѷ������Ѳ��ϣ�������һ
����ۡ�
LONG );
        set("outdoors", "beijing");
        set("no_fight", 1);
        set("objects", ([
                "/clone/horse/zaohongma": 1,
                "/clone/horse/huangbiaoma": 1,
                "/clone/horse/ziliuma": 1,
                "/clone/npc/mafu": 1,
                "/d/guanwai/npc/shenke" : 1,
        ]));

        set("exits",([
                "east" : __DIR__"niaoshi",
                "north"  : __DIR__"business",
                "up"   : "/clone/shop/beijing_shop",
        ]));
	set("coor/x", -2850);
	set("coor/y", 7680);
	set("coor/z", 0);
	setup();
        replace_program(TRANS_ROOM);
}