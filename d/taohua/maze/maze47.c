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
                "east"  : __DIR__"maze49",
                "south" : __DIR__"maze64",
                "west"  : __DIR__"maze28",
                "north" : __DIR__"maze6",
        ]));

        set("item_desc", ([
                "shibei" : "
���������࣬�꣬���˼����޾̣����Բ��š�
������������������ľ�������Ĺȣ����겻����
�����Ŷ������ھ�ʳ����禷��������ú��룬���ף��޾̡�
��������������ʯ��������޼�������乬���������ޣ��ס�
�������ģ������죬���ڽ𳵣��ߣ����ա�
�������壺��뾣����ڳ�禣�������˵�����ü��롣
�������������ڸ���٣��ڡ��ڡ��ۣ�Ի���ڡ� �лڣ�������
���� �� �� ܳ �� ����Ʒ���ε� ��
���� �� �� �� Σ 
���� �� أ �� Σ
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 47, me);
        check_count(me, 47);
        return;
}