// qiangdao.c ǿ��
// lag.2000/3/17

inherit NPC;
#include <ansi.h>
void move();

void create()
{       object me;
        int myskill;
        me=this_player();
        if (! me) return;
        myskill=me->query_skill("force");
        set_name(HIC"��ң����ͽ"NOR,({query("id", me)+"-pantu"}));
        set("title",query("name", me)+"���µ�");
        set("gender", "����");
        set("age", 28);
        set("long", "����һ����ң����ͽ��\n");

        set("attitude", "peaceful");
        set("qi",query("qi", me)*4/5);
        set("max_qi",query("max_qi", me)*4/5);
        set("jing",query("jing", me)*4/5);
        set("neili",query("neili", me)*4/5);
        set("max_neili",query("max_neili", me)*4/5);
        set("max_jing",query("max_jing", me)*4/5);
        set("str",query("str", me)*4/5);
        set("dex",query("dex", me)*4/5);
        set("per",query("per", me)*4/5);
        set("killer",query("id", me));
        set("combat_exp",query("combat_exp", me)*4/5);
// ������5������ǿ���Զ��ߣ���������������˵����ѣ�-��ԲSMILE
        set("chat_chance_combat", 30);
        set("chat_msg_combat", ({
                (: perform_action, "blade.wanshi" :),
                (: perform_action, "blade.wanshi" :),
                (: perform_action, "blade.ruyi" :),
                (: perform_action, "blade.ruyi" :),
                (: perform_action, "dodge.lingbo" :),
                (: perform_action, "dodge.lingbo" :),
                (: exert_function, "strike.zhong" :),
                (: exert_function, "strike.zhong" :),
        }) );
             set("chat_chance", 30);
             set("chat_msg", ({
              (: random_move :)
        }) );


        set_skill("hand", myskill * 4 / 5);
        set_skill("dodge", myskill * 4 / 5);
        set_skill("unarmed", myskill* 4 / 5);
        set_skill("parry", myskill* 4 / 5);
        set_skill("force", myskill* 4 / 5);
        set_skill("blade", myskill* 4 / 5);
        set_skill("lingbo-weibu", myskill* 4 / 5);
        set_skill("ruyi-dao", myskill* 4 / 5);
        set_skill("liuyang-zhang", myskill* 4 / 5);
        set_skill("zhemei-shou", myskill* 4 / 5);
        map_skill("unarmed", "liuyang-zhang");
        map_skill("parry", "ruyi-dao");
        map_skill("blade", "ruyi-dao");
        map_skill("dodge", "lingbo-weibu");
        map_skill("force", "beiming-shengong");
        prepare_skill("hand","zhemei-shou");
        prepare_skill("strike","liuyang-zhang");
        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);
        set_temp("apply/armor", 100);
        set_temp("apply/damage", 250);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/gangdao")->wield();

}

void init()
{
        remove_call_out("leave");
        call_out("leave",60);
}

void leave()
{
        object ob = this_object();
        if (!ob->is_fighting()) {
                message_vision(HIC "��ң����ͽ���·�ߵ��Ӳݣ������ˡ�\n" NOR,this_object());
                destruct(this_object());
                }
        else call_out("leave",30);
}

void die()
{
        object ob;
        message_vision("$N���һ�����Ҳ����ģ���ʧ�ˡ�\n", this_object());
        ob = new("/d/xiaoyao/obj/zhi");
        ob->move(environment(this_object()));
        destruct(this_object());
}