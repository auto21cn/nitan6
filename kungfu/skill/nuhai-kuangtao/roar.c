// roar.c 黯然销魂吟

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        object *ob;
        int i, skill, damage;

        if( query("neili", me)<150 )
                return notify_fail("你长叹一声，大家吓了一跳。\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("这里不能攻击别人! \n");

        skill = me->query_skill("force", 1);

        addn("neili", -150, me);
        me->receive_damage("qi", 10);

        me->start_busy(3);
        message_combatd(
                MAG "$N右手抚胸，低声长吟出一曲「黯然销魂」。\n" NOR, me);

        ob = all_inventory(environment(me));
        for (i = 0; i < sizeof(ob); i++)
        {
                if (! ob[i]->is_character() || ob[i] == me)
                        continue;

                if (! living(ob[i]) || wizardp(ob[i]) ||
                    (query("age", ob[i])<17 && userp(ob[i])) )
                        continue;

                if (skill / 2 + random(skill / 2) < (int)ob[i]->query_con() * 2)
                        continue;

                if (userp(ob[i]) && !ob[i]->die_protect(me))
                        continue;

                me->want_kill(ob[i]);
                me->fight_ob(ob[i]);
                ob[i]->kill_ob(me);

                damage=skill-(query("max_neili", ob[i])/20);
                if (damage > 0)
                {
                        set("last_damage_from", me, ob[i]);
                        ob[i]->receive_damage("jing", damage * 2, me);
                        if( query("neili", ob[i])<skill*2 )
                                ob[i]->receive_wound("jing", damage, me);
                        tell_object(ob[i], "你忽然觉得一阵寒意扑面而来，心神朦胧中漂移不定。\n");
                }
        }

        return 1;
}

