inherit ROOM;

void create()
{
  set("short", "雪山寺");
        set("long", @LONG
这里是雪山寺的山门，门前是络绎不绝的进香朝圣的信徒而有的
甚至来自乌丝藏西南的波丝。山门前站了个手持法器的葛伦布在维持
秩序，东方是一条青石板铺成的山路。
LONG );
        set("outdoors", "xueshan");
        set("exits", ([
                "north"    : __DIR__"frontyard",
                "eastdown" : "/d/xuedao/nroad4",
        ]));
        set("objects", ([
                CLASS_D("xueshan") + "/gelunbu": 1,
                "/d/wudang/npc/guest": 2,
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
        object glb;

        if (dir != "north" ||
            ! objectp(glb = present("ge lunbu", this_object())))
                return ::valid_leave(me, dir);

        return glb->permit_pass(me, dir);
}