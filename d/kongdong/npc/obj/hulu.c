#include <ansi.h>
inherit ITEM;
inherit F_LIQUID;


void create()
{
        set_name(YEL "葫芦" NOR, ({"hu lu","pot","hu"}));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一个用来装水的大葫芦，外皮金黄，里面能装好几斤清水。\n");
                set("unit", "个");
                set("value",3);
                set("max_liquid", 10);
        }
        set("liquid", ([
                "type": "water",
                "name": "清水",
                "remaining": 10,
                "drunk_apply": 30,
        ]));
}
