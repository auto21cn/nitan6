//shao.c ����
//6/12/97 -qingyun
inherit NPC;
#include <ansi.h>
string ask_me();
void create()
{
        set_name("����",({"shao gong","shao","gong"}));
        set("long",  "����һ����ˮ���ˡ�\n");
        set("age", 40);
        set("attitude", "friendly");
        set("shen_type", 0);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);
        set("combat_exp", 1000);
        set_skill("cuff",20);
        set_skill("dodge",20);
        set_skill("force", 20);
        set_skill("parry", 20);        
        set("inquiry", ([
             "����" : (: ask_me :),
             "here" : "���������������ڣ�λ���ǻƵ�������ʮ�塢����ʮ������룬���Ҫ�����Ŷ��\n",
             "rumors" : "���ﾭ�����������Է籩����Ҫ���ע�⡣\n",         
          ]));
        set("chat_chance", 3);
        set("chat_msg", ({
"��������˵������������һֻ��������û�й黹���Һ���ǰ׬��һЩ�ϱ����¹�һֻ������\n",                
"����˵��������������˵���м�ֻ�洬�ڻƵ������ĸ��������˴�籩�������ǻز����ˡ���\n",
"����˵���������˳�������˵���������м����ɵ�������ס�����ˣ���֪�����Ǽ١���\n",
        }));
        setup();
        add_money("silver", 1);
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/d/mingjiao/obj/luopan");
}

string ask_me()
{
        object me;
        object ob;
        ob=this_player();
        me=this_object();
        set_temp("marks/��1", 1, ob);
        return "�ɴ˳�����Ϊ���գ��ҿɲ�ȥ�����ҵĴ����Խ���㣬�����Ժ������.....";
}        

int accept_object(object me, object ob)
{
        me=this_player();
        if( query("money_id", ob) && ob->value() >= 5000
                 && query_temp("marks/��1", me)){
                command("whisper"+query("id", me)+"��Ҫȥ����ͽ�(yell)�ҵĺ���(chuan)�ɡ�\n");
                set_temp("haichuan_paid", 1, me);
                delete_temp("marks/��1", me);
                return 1;
        }
        return 0;
}