//Room: bingying3.c

inherit ROOM;

void create ()
{
        set ("short", "��Ӫ");
        set("long", @LONG
������һ���ٽֶ����ı�Ӫ�����볤���ı�����ֻ�м���֮ң��
��Ӫ�ſ����Ʈ�ż�����Կ�����ʿ�������ڣ����Ҳ�����ɫ��Ѳ
�������ܡ���Ӫ���浽�����йٱ������ػص��߶�����һ���佫����
ָ��ʿ���жӲ�����
LONG );
         set("exits", ([ /* sizeof() == 1 */
                 "northwest" : "/d/changan/xian-daokou",
         ]));
         set("objects", ([ /* sizeof() == 5 */
                 "/d/changan/npc/fujiang" : 1,
                 "/d/changan/npc/guanbing" : 4,
         ]));

         set("outdoors", "changan");
        set("coor/x", -10750);
	set("coor/y", 1910);
	set("coor/z", 0);
	setup();
         replace_program(ROOM);
}