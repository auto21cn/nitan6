// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
���ﳣ���м������������ʳ��Ⱥ򴫻����Դ���Щ�˲���̫������
����(order)���ǾͿ����ˡ�
LONG );
        set("exits", ([
                "south" : __DIR__"changlang",
        ]));
        set("objects",([
                __DIR__"npc/yapu"     : 4,
                __DIR__"obj/chicken"  : 1,
                __DIR__"obj/xiangcha" : 1,
                   __DIR__"obj/baozi"    : 1,
                __DIR__"obj/fish"     : 1,
                __DIR__"obj/gao"     : 1,
                __DIR__"obj/cha"     : 1,
                __DIR__"npc/cheng"     : 1,
        ]));

        set("coor/x", 8990);
        set("coor/y", -2930);
        set("coor/z", 0);
        setup();

}

void init()
{
        add_action("do_order", "order");
}

int do_order()
{
        object ob1, ob2, *inv, me = this_player();
        int food_ind, water_ind, f, w, i;
        mapping myfam;

        myfam=query("family", me);
        if ( !myfam || myfam["family_name"] != "�һ���" )
                return notify_fail("����һ����ӣ�������ȡʳ�\n");

        inv = all_inventory(me);
        for (i=0; i<sizeof(inv); i++) {
                if( query("food_supply", inv[i]) && inv[i]->value() >= 0)f++;
                if( query("drink_supply", inv[i]) && inv[i]->value() >= 0)w++;
        }

        food_ind=query("food", me);
        water_ind=query("water", me);

        if ( (int)me->max_food_capacity()-food_ind < 10
        && (int)me->max_water_capacity()-water_ind < 10 )
                return notify_fail("���ѳԱ����㣬���ǵȻ����Ҫ�ɣ�\n");

        message_vision("$N����������һ��������Щʳ��Ժȡ�\n", me);

        if ( (int)me->max_food_capacity()-food_ind >= 40 && !f
        && !present( "chicken", environment(me) )
        && !present( "baozi", environment(me) )
        && !present( "fish", environment(me) ) ) {
           switch(random(3)) {
           case 0:
                ob1 = new(__DIR__"obj/chicken");
                break;
           case 1:
                ob1 = new(__DIR__"obj/baozi");
                break;
           case 2:
                ob1 = new(__DIR__"obj/fish");
                break;
           }
                ob1->move(me);
                message_vision("�������ޱ�����ó�"+ob1->name()+"��$N��\n", me);
        }
        else if ( (int)me->max_food_capacity()-food_ind >= 40 )
                message_vision("����ָ��ָ$N���ŵ�ʳ�ҡ��ҡͷ��\n", me);
        else message_vision("����ָ��ָ$N�Ķ��ӣ�ҡ��ҡ�֡�\n", me);

        if ( (int)me->max_water_capacity()-water_ind >= 40 && !w
        && !present("tea", environment(me)) ) {
                ob2 = new(__DIR__"obj/xiangcha");
                ob2->move(me);
                message_vision("�������ޱ�����ó�"+ob2->name()+"��$N��\n", me);
        }
        else if ( (int)me->max_water_capacity()-water_ind >= 40 )
                message_vision("����ָ��ָ$N���ŵ�ʳ�ҡ��ҡͷ��\n", me);
        else message_vision("����ָ��ָ$N�Ķ��ӣ�ҡ��ҡ�֡�\n", me);

        return 1;
}

int valid_leave(object me, string dir)
{
        object *inv;
        int i, f, w;
        inv = all_inventory(me);
        for (i=0; i<sizeof(inv); i++) {
                if( query("food_supply", inv[i]) && inv[i]->value() >= 0)f++;
                if( query("drink_supply", inv[i]) && inv[i]->value() >= 0)w++;
        }

        if ( (f>0 || w>0) && present("ya pu", environment(me)) ) 
                return notify_fail("���������㣬ָ��ָ�����ŵ�ʳ�ҡ��ҡͷ��\n");

        return ::valid_leave(me, dir);
}


