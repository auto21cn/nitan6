#include <ansi.h>
#include <combat.h>

#define SHEN "「" HIM "五神朝元势" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg, wn;
        object weapon;
        int ap, dp;
        me = this_player();

        if( userp(me) && !query("can_perform/wushen-jian/shen", me) )
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(SHEN "只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，难以施展" SHEN "。\n");

        if ((int)me->query_skill("wushen-jian", 1) < 240)
                return notify_fail("你衡山五神剑不够娴熟，难以施展" SHEN "。\n");

        if (me->query_skill_mapped("sword") != "wushen-jian")
                return notify_fail("你没有激发衡山五神剑，难以施展" SHEN "。\n");

        if ((int)me->query_skill("force", 1) < 220)
                return notify_fail("你的内功火候不够，难以施展" SHEN "。\n");

        if ((int)me->query_skill("dodge", 1) < 200)
                return notify_fail("你的轻功火候不够，难以施展" SHEN "。\n");  

        if( query("max_neili", me)<5500 )
                return notify_fail("你的内力修为不足，难以施展" SHEN "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你现在的真气不够，难以施展" SHEN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        wn = weapon->name();

        msg = HIM "\n$N" HIM "一声怒喝，内劲暴涨，手中" + wn +
              HIM "变幻万千，霎那间化作红黄蓝绿白五道剑光，纵"
              "横飞扬。$P身法蓦地变快，随着剑光同时将『" HIR
              "祝融" HIM "』、『" HIY "紫盖" HIM "』、『" NOR
              WHT "石廪" HIM "』、『" HIG "芙蓉" HIM "』、『"
              HIW "天柱" HIM "』五套剑法交替使出，电光火石间"
              "已袭向$n" HIM "全身。" NOR;

        message_sort(msg, me, target);
        
        ap = attack_power(me, "sword");

        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");

                // 五分之一的几率可被招架
                if (random(10) <= 1 && ap / 2 < dp)
                {
                        damage = damage / 3;

                        msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                                  HIG "\n$n" HIG "见$N" HIG "五道剑光剑势"
                                                  "惊人，急忙收敛心神奋力招架。哪知$P这"
                                                  "招力道非凡，$p一声闷哼，连退几步，喷"
                                                  "出一口鲜血。\n" NOR);
                        addn("neili", -200, me);
                        me->start_busy(3 + random(2));
                } else 
                {
                        msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80 + random(10),
                                                  HIR "\n$n" HIR "见$N" HIR "五道剑光缤纷"
                                                  "洒落，交错纵横，呼啸着向自己袭来。心"
                                                  "底不由大惊，登时听得“噗嗤”一声，剑"
                                                  "气透体而过。\n" NOR);
                        addn("neili", -300, me);
                        me->start_busy(3 + random(3));
                }
        } else
        {
                msg = CYN "\n然而$n" CYN "以快对快，飞身一跳"
                      "已然躲过$N" CYN "这一招。\n" NOR;
                addn("neili", -150, me);
                me->start_busy(3);
        }
        message_sort(msg, me, target);
        return 1;
}