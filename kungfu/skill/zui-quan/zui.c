// zui.c 罗汉醉酒

#include <ansi.h>

#define PFM_NAME        "罗汉醉酒"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int count;
        int skill;
 
        if( query("neili", me)<150 )
                return notify_fail("你的真气不足以施展「" + PFM_NAME + "」。\n");

        if( query_temp("zui-quan_zui", me) )
                return notify_fail("你已经竭力提升你的身法了。\n");
        
        if ((int)me->query_skill("zui-quan", 1) < 80)
                return notify_fail("你的醉拳还不到家，无法施展「" + PFM_NAME + "」。\n");

        msg = HIY "$N" HIY "忽地身形一变，双拳虚握，使出一招「" + PFM_NAME +
              HIY "」，犹如金杯在手。\n"
              HIG "看似步履踉跄，醉态可拘，但身形却灵活之极！\n" NOR;

        message_combatd(msg, me);
        addn("neili", -100, me);

        skill = me->query_skill("zui-quan", 1);
        count = skill * (3 + random(5)) / 10;
        addn_temp("dex", count, me);
        me->start_call_out((: call_other, __FILE__, "remove_effect",
                           me, count :), skill / 3);

        set_temp("zui-quan_zui", 1, me);

        me->start_busy(1 + random(3));
        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("zui-quan_zui", me) )
        {
                addn_temp("dex", -amount, me);
                delete_temp("zui-quan_zui", me);
                tell_object(me, "你的罗汉醉酒运功完毕，将内力收回丹田。\n");
        }
}