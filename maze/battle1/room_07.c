// This program is a part of NT MudLIB

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG"山道"NOR);
        set("long", @LONG
这里是一条陡峭的山道，通望险峻的山峰。这里地势险要，真是一关把道，万夫莫行。
LONG
    );
        set("exits", ([
                "east"  : __DIR__"room_09",
                "north" : __DIR__"room_06",
                "south" : __DIR__"room_08",
        ]));
        set("outdoors", "battle");
        setup();
}
