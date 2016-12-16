// buwei3.c

inherit ROOM;

void create()
{
        set("short", "ƫ��");
        set("long", @LONG
ƫ���﹩���Ż�ɽ������ʦ����λ�������񰸵�ǽ���ǻ�ɽ�ɿ�
ɽ��ʦ����ʦ�Ļ��󡣻��������������ǳ�����������¯�����
�������㣬��������������ɢ����һ��̴��ζ������������ͨ������
��������
LONG );
        set("exits", ([ /* sizeof() == 2 */
            "west" : __DIR__"buwei1",
        ]));
        set("no_clean_up", 0);
        set("valid_startroom","1");
        set("objects", ([ /* sizeof() == 2 */
                CLASS_D("huashan")+"/first": 1,
        ]));

        set("item_desc", ([
                      "picture" : "һ������������������������������һ�ѳ�����\n",
                "����" : "һ������������������������������һ�ѳ�����\n",
        ]));

        set("paper_count", 1);

        setup();
        "/clone/board/huashan_b"->foo();
        //replace_program(ROOM);
}

/*
void init()
{
        add_action("do_ketou","ketou");
           add_action("do_ketou","kneel");
}
*/

int do_ketou(string arg)
{
           object paper, me = this_player();
        int level1, level2, level3;

        message_vision("$N��������������ǰ�������Ϲ���������������λ����������ͷ��\n", me);
        me->receive_damage("qi", 5, "������������");
        me->start_busy(1);

        if( query("qi", me) <= 50 )
                write("��ֻ����������Щ�������ġ�\n");
        if( query("qi", me) <= 20 )
                write("�����������ת���ƺ����ϱ�Ҫ��ȥ��\n");

        if( !(query("family/family_name", me) == "��ɽ��"))return 1;

        if( !query("huashan/yin-jue", me) && query("huashan/yinjue", me)<500){
                addn("huashan/yinjue", 1, me);
                return 1;
        }

        level1 = me->query_skill("ziyin-yin", 1);
        level2 = me->query_skill("zhengqi-jue", 1);
        level3 = me->query_skill("zixia-gong", 1);

        if( level1 >= 120 && level2 >= 120 && level3 >= 150 && !query("huashan/yin-jue", me)){
                paper=new(__DIR__"obj/zixia_paper");
                if ( !paper ) return 1;

                paper->move(me);
                addn("paper_count", -1);
                set("huashan/yin-jue", 1, me);
                delete("huashan/yinjue", me);

                write("�������������ص�һ�ģ����ѵı��Ϻ�Ȼ���˿�����¶��һС��ֽ�㡣\n");
                write("����ϸ�Ľ�ֽ����һ����������������ļ����������ķ����ƺ�����ϼ\n");
                write("��һ����У���ȴ������¡�\n");
                write("��ϸ�����ã�ͻȻ��Ȼ����ԭ���������ϼ����ʧ����ʱ������һҳ��\n");
                write("����æ�����պá�\n");
        }

        return 1;
}