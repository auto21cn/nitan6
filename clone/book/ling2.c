inherit F_UNIQUE;
#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(HIR "ʥ����" NOR, ({ "shenghuo ling", "ling" }) );
        set_weight(1000);
        if (clonep())
                destruct(this_object());
        else
        {
                set("unit", "��");
                set("value", 10000);
                set("material", "steel");
                set("no_sell", "�����̵ģ�����������ҲֵǮ��");
                set("long", CYN "����һ�����������ĺ��ƣ��ǽ��������"
                            "�ؼ�Ӳ�ޱȣ���͸������\n���������л����"
                            "�ڣ�ʵ��������ӳ�⣬��ɫ��á����Ͽ̵���"
                            "��\n�ٲ�˹�ģ��ƺ�����ѧ�йأ�������£�"
                            "����Ҫ��ϸ�ж�һ�����С�\n" NOR);
                set("wield_msg", HIR "$N" HIR "��ৡ���һ�����������"
                                 "��һƬ����������������С�\n" NOR);
                set("unwield_msg", HIR "$N" HIR "��ʥ���������䡣\n"
                                   NOR);
                set("skill", ([
                        "name":         "shenghuo-ling",
			            "family_name" : "����",
                        "exp_required": 1200000,
                        "jing_cost":    100,
                        "difficulty":   47,
                        "max_skill":    119,
                        "min_skill":    50,
                        "need" : ([ "sanscrit" : 150 ]),
                ]) );

        }
        init_sword(80);
        setup();
}