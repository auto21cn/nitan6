inherit ROOM;

void create()
{
        set("short", "ԡ��");
        set("long", @LONG
ÿ������³����գ����ж�������ˮ��ϴ��Щ���񡣳�Ϊϴ��
��ϴ��Ĳ�ˮ���˵�ͷ��������£�����������Ȼˮ���࣬�����
����������ˮ����Ȼ��ٹ����ǲ��ᵱ���Ǳ��������������ר�ŵ�
Сԡ�ҹ�����ʹ�á�
LONG );
        set("objects", ([
                __DIR__"npc/zhangzao" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"zhongyuan",
                "west" : __DIR__"yushi2",
        ]));

	set("coor/x", -5050);
	set("coor/y", 2200);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}