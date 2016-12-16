#include <ansi.h>

inherit NPC;

void create()
{
        set_name("��", ({ "mai jing", "mai", "jing" }) );
        set("long",
                  "���Ǿ޾�������󾨣������߳ߣ�����\n���룬��ò�������͡�\n");
        set("attitude", "heroism");
        set("title", WHT "�޾������" NOR);
        set("age", 47);
        set("combat_exp", 800000);
        set("max_neili", 1500+random(1000));
 
        set_skill("unarmed", 100+random(50));
        set_skill("parry", 100+random(50));
        set_skill("dodge", 100+random(50));
        set_skill("force", 100+random(50));

        set("max_qi", 2500+random(1000)); 
        set("max_jing", 2500+random(1000)); 


        setup();

        carry_object("/d/beijing/npc/obj/cloth6")->wear();
}

int accept_fight(object who)
{
        command("say �Ҳ���������ֻ�����(bi)һЩˮ�Ϲ���");
        return 0;
}

int accept_hit(object who)
{
        command("say �Ҳ���������ֻ�����(bi)һЩˮ�Ϲ���");
        return 0;
}

int accept_kill(object who)
{
        command("say ��ô������������ͷǵ�Ҫ���ײ��ɣ�");
        return 1;
}

int accept_ansuan(object who)
{
        return notify_fail("����밵�㣬����ֻ���᳡���ѹѹ�ļ������ˣ��������������\n");
}

int begin()
{
        object me=this_player();
        if (objectp(present("yuan guangbo",environment()))) 
        return 0;

        command("nod");
        command("say �Ҿ޾���ľ���������ʹ��ˮ�Ϲ���");
        command("say ������Ҹ���ʪ����죬����һ��ˮ�Ϲ�����Σ�");

        message_vision(HIW "$n��$N��ȡʪ�࣬���Ͽڱǡ�\n" NOR,
                           this_object(),me);
        set_temp("bi", 1, me);
        set("anti",me);
        me->apply_condition("nishui",random(4)+1);
        this_object()->apply_condition("nishui",random(10)+10);
        call_out("guo",6,me);
        return 1;
}

void die()
{
        if (objectp(query("anti")))
        {
                message_vision(HIR"\n\n$N���������£�һ����û���ϣ����ڵ���һ�������ˡ�\n"NOR,this_object());
                set_temp("win_mai", 1, query("anti"));
                delete_temp("bi", query("anti"));
                query("anti")->apply_condition("nishui",0);
        }
::die();
}

void unconcious()
{
        if (objectp(query("anti")))
        {
                message_vision(HIR"\n\n$N���������£�һ����û���ϣ����ڵ���һ�������ˡ�\n"NOR,this_object());
                set_temp("win_mai", 1, query("anti"));
                delete_temp("bi", query("anti"));
                query("anti")->apply_condition("nishui",0);
        }
::die();
}

void guo(object me)
{
        if (objectp(present("guo sanquan",environment()))) present("guo sanquan",environment())->begin(me);
}

void init()
{
        add_action("do_get","get");
        add_action("begin","bi");
}

int do_get(string arg)
{
        object obj,env,ding;
        string what,where;

        if(!arg) 
        return 0;

        if (objectp(obj=present("yuan guangbo",environment()))) 
        return 0;

        if(sscanf(arg,"%s from %s",what, where) !=2)
        return 0;

        obj=this_object();
        if(where == "ding")
        {
                message_vision(CYN "$N��ɫ������λӢ�����ˣ�\n" NOR,
                                   obj);

                message_vision(CYN "$N˵�������������˲���֮����Ҫ�ô˵������(bi)������أ�\n" NOR,
                                   obj);

                delete_temp("bi", this_player());
                return 1;
        }
        return 0;
}