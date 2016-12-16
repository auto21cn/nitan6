// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

#include "maze.h"

void create()
{
        set("short", "ʯ��");
        set("long", @LONG
����һ����ԼĪ���˶�ߵĴ�ʯ�鹹�ɵ���ʯ�󣬹�ģ�ƺ����󣬵�
̧����ȥ�����ܾ������ص�������Ᾱ�ʯ����ȫ��������·ͨ��ʯ��֮�⣬
��֮���г�������������������������ͷ����ʯ������һ��б����ʯ��(s
hibei)�������ڸ����С�
LONG );

        set("exits", ([
                "east"  : __DIR__"maze37",
                "south" : __DIR__"maze29",
                "west"  : __DIR__"maze57",
                "north" : __DIR__"maze40",
        ]));

        set("item_desc", ([
                "shibei" : "
���������ࡣ ��������������󴨣����ꡣ
����������������׳������
�����Ŷ������������������
�������������乪���޻ڡ�
�������ģ�����Ⱥ��Ԫ���� �����𣬷�����˼��
�������壺�������ţ������ӣ��޾̡�
�����Ͼţ�����Ѫ��ȥ�ѳ����޾̡�
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 59, me);
        check_count(me, 59);
        return;
}