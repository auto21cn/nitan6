// Room: /d/wuyi/path11.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "С·");
        set("long", @LONG
��������з��е�һ��С·��·���ǵ���ʯ���̾͵ģ����߶��Ǹ�
�ʵ�ɽ�塣·���������߿���С�������������������峺��Ȫˮ��ˮ��
ʱ�����ִ����������㡣С·ʱ��ʱխ��խʱ�������ߣ����ֿɸ�ɽ�ҡ�
����Ҳ�����ɣ�·�߱㶼�ǲ���Ĳ��֡��ұ������ʵ�Ȫˮ��������һ
ƬƬ���̵�ϣ����
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "south"     : __DIR__"dahongpao",
                "northwest" : __DIR__"liuxiangjian",
                "northeast" : __DIR__"yonglechansi",
        ]));
        set("objects", ([
                "/d/huashan/npc/youke" : random(3),
        ]));
        set("coor/x", 1390);
        set("coor/y", -4940);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}