// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return MAG "幽冥剑气" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        int i, level;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必须空手才能使用" + name() + "。\n");

        if ((int)me->query_skill("canhe-zhi", 1) < 120)
                return notify_fail("你的参合指修为有限，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("finger") != "canhe-zhi")
                return notify_fail("你没有激发参合指，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("finger") != "canhe-zhi")
                return notify_fail("你现在没有准备使用参合指，难以施展" + name() + "。\n");

        if( query("max_neili", me)<2500 )
                return notify_fail("你的内力修为不足，难以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "只见$N" HIW "身形一展，身法陡然变得诡异无比，聚力于指悄然点"
              "出，数股剑气直袭$n" HIW "要穴而去。\n" NOR;

        message_combatd(msg, me, target);

        me->start_busy(1 + random(3));
        addn("neili", -300, me);
        level = me->query_skill("canhe-zhi", 1);
        addn("apply/attack", level/2, me);
        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }
        addn("apply/attack", -level/2, me);

        return 1;
}