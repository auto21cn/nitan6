// This program is a part of NITAN MudLIB
// zuida.c 少林醉棍 八仙醉打

#include <ansi.h>

inherit F_SSERVER;

string name() { return "八仙醉打"; }
void remove_effect(object me, int amount, int amount1);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int count, count1, cnt, skill;

        if (! me->is_fighting())
                return notify_fail("「八仙醉打」只能在战斗中使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "club" )
                return notify_fail("你使用的武器不对。\n");

        if( query_temp("zg_zuida", me) )
                return notify_fail("你已经在运功中了。\n");

        if( query_temp("powerup", me) )
                return notify_fail("你已经运起内功加力了，没有更多的内力使用八仙醉打。\n");

        if ((int)me->query_str() < 25)
                return notify_fail("你现在的臂力不够，目前不能使用此绝技！\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的内功火候不够，难以施展此项绝技！\n");

        if ((int)me->query_skill("club") < 100)
                return notify_fail("你的棍法修为不够，不会使用此项绝技！\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真气不足！\n");

        msg = HIY "$N" HIY "使出少林醉棍的绝技「八仙醉打」，臂"
              "力陡然增加, 身法陡然加快！\n" NOR;

        message_combatd(msg, me, target);
        skill = me->query_skill("zui-gun",1);
        cnt =(int)( (int)me->query_condition("drunk") / 30);
        if( cnt > 50 ) cnt = 50;
        count=query("str", me)*random(cnt+2);
        count1=query("dex", me)*random(cnt+2);

        addn_temp("apply/str", count, me);
        addn_temp("apply/dex", count1, me);
        set_temp("zg_zuida", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                           me, count, count1 :), skill / 3);
        me->start_busy(2);

        addn("neili", -150, me);
        return 1;
}

void remove_effect(object me, int amount, int amount1)
{
        if( query_temp("zg_zuida", me) )
        {
                addn_temp("apply/str", -amount, me);
                addn_temp("apply/dex", -amount1, me);
                delete_temp("zg_zuida", me);
                tell_object(me, "你的八仙醉打运功完毕，将内力收回丹田。\n");
        }
}
