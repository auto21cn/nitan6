// /d/playertown/road1.c ��ʯС��
// Build 1999.12.10 bmw

inherit BUILD_ROOM;

void create()
{
        set("short","��ש·");
        set("long",
"����һ���ǳ�ƽ������ש�̳ɵ�С·����Χ��һСƬ�յأ���ɫ����\n"
"�����ʺϽ�����\n"
);

        set("recordable_room",1);
        set("outdoors","playertown");        
        set("exits",([
                "north" : __DIR__"cunkou",
                "south" : __DIR__"road13",
        ]));
        setup();
        // replace_program(ROOM);
}