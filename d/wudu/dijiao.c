inherit ROOM;

void create()
{
        set("short", "�ؽ�");
        set("long", @LONG
����һ�������ĵؽѣ�ͷ����һ�Ų�ϯ(xi)��ס�˹��ߡ��ؽ���
�����һЩ׼��������ʳ�������Ķѷ���ľ���ϡ�
LONG);
        set("objects", ([
                __DIR__"obj/shibing": 2,
                __DIR__"obj/huluobu": 1,
                __DIR__"obj/tudou": 1,
        ]));
        set("item_desc", ([
                "xi" : "\nһ�ź��Ĳ�ϯ���ڶ��ڣ���ס����������⡣\n" ,
        ]));

        setup();
}

void init()
{
        add_action("do_move", "pull");
}

int do_move(string arg)
{
        object me,hole;
        string dir;

        me = this_player();
        if (! arg || arg == "") return 0;
        if (arg == "xi")
        {
                message_vision("\n$N�ƿ����ڶ��ڵĲ�ϯ������ȥ��\n", this_player());
                me->move(__DIR__"minju10");
                message_vision("\n���ڵ��ϵĲ�ϯ��Ȼһ�ƣ�$N���������˳�����\n",me);
        } else
        {
                message_vision("\n$N˫���ڿ��бȻ��˼��£����ƺ�ʲôҲûץס��\n", this_player());
        }               
        return 1;
}