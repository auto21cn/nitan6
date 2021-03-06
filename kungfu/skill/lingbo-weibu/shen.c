// This program is a part of NITAN MudLIB

#include <ansi.h>

string name() { return MAG "神光离合" NOR; }

void remove_effect(object me);

int perform(object me, object target)
{
        string msg;

        if( !query("reborn/times", me) )
                return notify_fail("你尚未转世重生，无法施展" + name() + "。\n" NOR);

        if( me->query_skill("lingbo-weibu", 1) < 1000 )
                return notify_fail("你的凌波微步还不够熟练，难以施展" + name() + "。\n" NOR);

        if( query("jingli", me)<2000 )
                return notify_fail("你现在真气不足，难以施展" + name() + "。\n" NOR);

        if( query("neili", me)<5000 )
                return notify_fail("你现在内力不够，难以施展" + name() + "。\n" NOR);

        if( query_temp("immortal", me) )
                return notify_fail("你已经运起" + name() + "。\n" NOR);

        if( time() - query_temp("last_immortal", me) < 20 )
                return notify_fail("你无法连续无限制的使用" + name() + "。\n" NOR);

        addn("neili", -1000, me);
        me->receive_damage("qi", 0);
        set_temp("immortal", 1, me);

        msg = MAG "\n$N" MAG "提起真气，施展" + name() + "，身形虚晃，神光交错，离合难分，让人难以看清所在。\n" NOR;

        message_combatd(msg, me);
        set_temp("last_immortal", time(), me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), 30);

        if( me->is_fighting() ) me->start_busy(2);
        return 1;

}

void remove_effect(object me)
{
        if( query_temp("immortal", me) )
        {
                delete_temp("immortal", me);
                tell_object(me, "你的「神光离合」运功完毕，将内力收回丹田。\n");
        }
}
