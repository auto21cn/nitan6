inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
��ɽ��Ľֵ���ب���������߲�Զ�������ưܵ����������һ
����ΰ�Ľ�����������д�š�Ӣ�ۻ�ݡ��ĸ����֡�
LONG );
        set("objects", ([
                "/d/city/npc/liumang": 1,
        ]));
        set("outdoors", "foshan");
        set("exits", ([
                "south" : __DIR__"pm_restroom",
                "west"  : __DIR__"street1",
                "east"  : __DIR__"street3",
        ]));
	set("coor/x", -6580);
	set("coor/y", -9750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}