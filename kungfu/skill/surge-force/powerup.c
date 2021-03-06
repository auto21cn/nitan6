// powerup.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用怒涛潮涌提升自己的战斗力。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的内力不够。\n");

        if( query_temp("powerup", me) )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");

        addn("neili", -200, me);
        me->receive_damage("qi", 0);

        message_combatd(HIC "$N" HIC"一声长啸，激起一阵狂风，气"
                        "浪翻翻滚滚，向两旁散开。\n霎时之间，便"
                        "似长风动起，气云聚合，天地渺然，有如海"
                        "浪滔滔。\n" NOR, me);

        addn_temp("apply/attack", skill*2/5, me);
        addn_temp("apply/defense", skill*2/5, me);
        addn_temp("apply/unarmed_damage", skill*4, me);
        set_temp("powerup", 1, me);
        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill :), skill);
        if (me->is_fighting()) me->start_busy(3);
        return 1;
}

void remove_effect(object me, int skill)
{
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -(skill*2/5), me);
                addn_temp("apply/defense", -(skill*2/5), me);
                addn_temp("apply/unarmed_damage", -(skill*4), me);
                delete_temp("powerup", me);
                tell_object(me, "你的怒涛潮涌运行完毕，将内力收回丹田。\n");
        }
}