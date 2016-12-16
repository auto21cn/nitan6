// guxu.c ����

//#include "daozhang.h"
inherit NPC;
//inherit F_MASTER;

string ask_me();

void create()
{
        set_name("�������", ({ "qingxu daozhang", "qingxu" }));
        set("long",
                "�����������۵ĵ������������\n"
                "�������ʮ���꣬���ܸ���۵����¡�\n"
                "ר�������￴�ر��ɵĸ��ֵ���");
        set("gender", "����");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 22);
        set("int", 22);
        set("con", 22);
        set("dex", 22);

        set("max_qi", 1800);
        set("max_jing", 900);
        set("neili", 2400);
        set("max_neili", 2400);
        set("jiali", 30);

        set("combat_exp", 70000);
        set("score", 8500);

        set_skill("force", 85);
        set_skill("yinyun-ziqi", 85);
        set_skill("dodge", 80);
        set_skill("tiyunzong", 80);
        set_skill("strike", 85);
        set_skill("wudang-zhang", 85);
        set_skill("parry", 80);
        set_skill("sword", 80);
        set_skill("wudang-jian", 80);
        set_skill("taoism", 50);
          set_skill("literate", 50);

        map_skill("force", "yinyun-ziqi");
        map_skill("dodge", "tiyunzong");
        map_skill("parry", "wudang-jian");
        map_skill("sword", "wudang-jian");
        map_skill("strike", "wudang-zhang");

        prepare_skill("strike", "wudang-zhang");

        create_family("�䵱��", 3, "����");
        set("class", "taoist");

        set("inquiry", ([
                "���¾�" : (: ask_me :),
                "�䵱��" : "ƶ�������䵱�ɵ��ӣ���֪��λ"+ RANK_D->query_respect(this_player())+"�кμ��̣�",
                "̫������" : "�š������Ҳ�����������ȥ�ʳ���ʦ�֡�",
                "�䵱��" : "�š����䵱�����ʵ����Ͳ��㣬��Ӳ�״࣬�Է����ʹ������е����������Ӳ��Ӳײ��",
                "���ǽ���" : "���ǽ���������������������ᣬ���΢�ޱȡ�",
                "�䵱���ǽ�" : "���ǽ���������������������ᣬ���΢�ޱȡ�",
                "��ָ�ὣ" : "��·�����ҿɲ���ʹ��",
                "����ʮ����" : "��·�����ҿɲ���ʹ��",
                "�䵱��ȭ" : "ȭ�Ź����ƶ��������",
                "����" : "ȭ�Ź����ƶ��������",
                "��ɽ��" : "ȭ�Ź����ƶ��������",
                "��צ������" : "�š�������˵��������һ·�书������δ��ʦ��ʦ��ʹ����",
                "������" : "���ɴ�����ʦ������������չز�����",
                "������" : "���ɴ�����ʦ������������չز�����",
                "��Զ��" : "���Ǳ������Ŵ�ʦ����",
                "�δ���" : "���Ǳ������Ŵ�ʦ����",
                "������" : "���Ƕ�ʦ����",
                "�����" : "���Ƕ�ʦ����",
                "�����" : "������ʦ����",
                "������" : "������ʦ����",
                "����Ϫ" : "ƶ������ҵ��ʦ",
                "������" : "ƶ������ҵ��ʦ",
                "�Ŵ�ɽ" : "����������ƶ������ʦ�塣",
                "������" : "����������ƶ������ʦ�塣",
                "����ͤ" : "������ʦ�塣",
                "������" : "������ʦ�塣",
                "Ī����" : "������ʦ�塣",
                "Ī����" : "������ʦ�塣",
                "������" : "�þ�û������ʦ���ˣ���˵����Ī���峳���ܣ��ʹ���û���䵱����",
                "����" : "����ƶ����ʦ�֣�����������Ҳ������ʹ̫��������",
                "�������" : "����ƶ����ʦ�֣�����������Ҳ������ʹ̫��������",
                "����" : "����ʦ�������������е�ٮٮ�ߣ�������������ɽ�������䵱����",
                "�������" : "����ʦ�������������е�ٮٮ�ߣ�������������ɽ�������䵱����",
                "�������" : "ƶ���������飬��֪��λ"+ RANK_D->query_respect(this_player())+"�кμ��̣�",
                "����" : "����ʦ�������湬�������������",
                "�������" : "����ʦ�������湬�������������",
                "����" : "����ʦ�������湬�������������",
                "�������" : "����ʦ�������湬�������������",
                "����" : "����ʦ����ɽ�ţ�����Ӵ����͡�",
                "�������" : "����ʦ����ɽ�ţ�����Ӵ����͡�",
                "֪��" : "����ʦ����ɽ�ţ�����Ӵ����͡�",
                "֪�͵���" : "����ʦ����ɽ�ţ�����Ӵ����͡�",
                "�ɸ�" : "����ƶ����ʦֶ����ǰ����ƶ��������ס��ʮ���꣬���ڸ�������÷԰��",
                "�ɸߵ���" : "����ƶ����ʦֶ����ǰ����ƶ��������ס��ʮ���꣬���ڸ�������÷԰��",
                "��԰" : "����ƶ����ʦֶ����ǰ����ƶ��������ס��ʮ���꣬���ڸ�������÷԰��",
                "��԰����" : "����ƶ����ʦֶ����ǰ����ƶ��������ס��ʮ���꣬���ڸ�������÷԰��",
                "ըҩ" : "�š������Ҳ�����������ȥ�ʳɸ�ʦֶ��",
                "��ҩ" : "�š������Ҳ�����������ȥ�ʳɸ�ʦֶ��",
                "����ըҩ" : "�š������Ҳ�����������ȥ�ʳɸ�ʦֶ��",
                "�����ҩ" : "�š������Ҳ�����������ȥ�ʳɸ�ʦֶ��",
                "����" : "ƶ�����������򵱵ع���ѧ����������֮����",
                "��������" : "ƶ�����������򵱵ع���ѧ��������",
        ]));

        set("book_count", 1);

        setup();
        carry_object(WEAPON_DIR"changjian")->wield();
        carry_object(CLOTH_DIR"dao-cloth")->wear();
        carry_object(CLOTH_DIR"dao-shoe")->wear();
}


string ask_me()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player()) )
            || fam["family_name"] != "�䵱��")
        {
                return RANK_D->query_respect(this_player()) +
                       "�뱾��������������֪�˻��Ӻ�̸��";
        }

        if (query("book_count") < 1)
                return "�������ˣ����ɵĵ����澭���ڴ˴���";

        addn("book_count", -1);
        ob = new("/clone/book/daodejing-ii");
        ob->move(this_player());
        return "�ðɣ��Ȿ�����¾������û�ȥ�ú����С�";
}