inherit ROOM;
void create()
{
        set("short", "����յ�");
        set("long", @LONG
���ǳ���Ŀյأ�һЩ�ɹű��ļ�ϸ�ͼ��ֳ��������߮����Ѱ
�����Ǹ���Ȥ�������ʱ�м�ö�����ͷ��ವطɹ������˷���ʤ
����
LONG );
        set("outdoors", "xiangyang");
        set("no_clean_up", 0);
        set("step",2);
        set("no_fly",1);     
        set("exits", ([
               "east" : __DIR__"east_out4", 
               "west" : __DIR__"east_out2", 
        ]));
        set("coor/x", -7830);
	set("coor/y", -770);
	set("coor/z", 0);
	setup();
}