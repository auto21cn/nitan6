// wan.c

inherit NPC;
#include <ansi.h>;
void create()
{
        set_name("万大平", ({ "wan daping", "daping", "wan" }) );
        set("gender", "男性");
        set("class", "swordsman");
        set("age", 25);
        set("attitude", "peaceful");
        set("str", 26);
        set("con", 30);
        set("dex", 30);
        set("int", 28);

        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 30);
        set("max_qi",1000);
        set("max_jing",700);
        set("combat_exp", 100000);
        set("shen_type", -1);

        set_skill("literate", 50);
        set_skill("strike", 60);
        set_skill("hand", 60);
        set_skill("sword", 60);
        set_skill("force", 60);
        set_skill("parry", 60);
        set_skill("dodge", 60);
        set_skill("songshan-sword", 90);
        set_skill("songyang-strike", 90);
        set_skill("poyun-hand", 90);
        set_skill("hanbing-zhenqi", 60);
        set_skill("fuguanglueying", 90);
        map_skill("strike", "songyang-strike");
        map_skill("hand", "poyun-hand");
        map_skill("sword", "songshan-sword");
        map_skill("parry", "songshan-sword");
        map_skill("dodge", "fuguanglueying");
        map_skill("force", "hanbing-zhenqi");
        prepare_skill("strike", "songyang-strike");
        prepare_skill("hand", "poyun-hand");
        create_family("嵩山派", 14, "弟子");
        set("env/wimpy", 60);
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "sword.shuiyuan" :),
                (: perform_action, "sword.jianqi" :),
                (: perform_action, "sword.feiwu" :),
                (: perform_action, "strike.yinyang" :),
                (: perform_action, "hand.chanyun" :),
                (: exert_function, "powerup" :),
                (: exert_function, "regenerate" :),
                (: exert_function, "recover" :),
        }) );
        setup();

        carry_object(WEAPON_DIR+"kuojian")->wield();
        carry_object(__DIR__"obj/yellow-cloth")->wear();
}
