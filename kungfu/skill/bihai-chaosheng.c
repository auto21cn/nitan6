#include <ansi.h>

inherit SKILL;

string type() { return "knowledge"; }

int valid_enable(string usage) { return usage == "chuixiao-jifa"; }

int valid_learn(object me)
{
        if (me->query_skill("chuixiao-jifa", 1) < 100)
                return notify_fail("��Ĵ�������ˮƽ������������������˵�ɣ�\n");

        if (me->query_skill("chuixiao-jifa", 1) < me->query_skill("bihai-chaosheng", 1))
                return notify_fail("��Ĵ�������ˮƽ���ޣ��޷���������ı̺���������\n");

        return 1;
}

int practice_skill(object me)
{
        object ob;

        if( !objectp(ob=query_temp("handing", me)) || 
            ! ob->valid_as_xiao())
                return notify_fail("���ø��������ϣ�����ô��ϰ��\n");

        if( query("jing", me)<80 )
                return notify_fail("��ľ��񲻹��ã�û����ϰ�ˡ�\n");

        if( query("qi", me)<30 )
                return notify_fail("�����ڿڸ����ʵ����̫���ˡ�\n");

        me->receive_damage("jing", 45);
        me->receive_damage("qi", 20);

        return 1;
}

void do_effect(object me)
{
        object *obs;
        int lvl;
        int i;
        int damage;

        lvl = me->query_skill("chuixiao-jifa", 1) / 2 +
              me->query_skill("bihai-chaosheng", 1);

        if( query("no_fight", environment(me) )
            || query("skybook", environment(me) )
           || lvl < 150)
                return;

        lvl = lvl / 5 + me->query_skill("force");
        lvl /= 2;

        // special effort
        obs = all_inventory(environment(me));
        for (i = 0; i < sizeof(obs); i++)
        {
                if (! obs[i]->is_character() || obs[i] == me || ! living(obs[i]))
                        continue;

                // ��������������Ҳ����˺�
                if ((int)obs[i]->query_condition("die_guard"))
                        continue;

                if (me->query_skill("bihai-chaosheng") * 2 / 3 <
                    obs[i]->query_skill("bihai-chaosheng"))
                        continue;

                if (lvl + random(lvl) < obs[i]->query_skill("force"))
                {
                        tell_object(obs[i], HIM "���������в���΢΢һ�����������������а���֮����\n" NOR);
                        continue;
                }

                damage=query("max_neili", me)-query("max_neili", obs[i]);
                if (damage < 500)
                {
                        tell_object(obs[i], HIM "���Ȼ����һ�����ң���æ����һ�����������ѹ�����\n" NOR);
                        continue;
                }

                damage /= 10;
                me->want_kill(obs[i]);
                me->fight_ob(obs[i]);
                obs[i]->kill_ob(me);
                obs[i]->receive_damage("jing", damage, me);
                obs[i]->receive_wound("jing", damage / 3, me);
                
                tell_object(obs[i], HIM "��ֻ�����������ң��̲�סҪ�������衭��\n" NOR);
        }
}