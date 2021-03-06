// Written by Lonely@nitan.org
// 凤凰涅磐 转世技能

#include <ansi.h>
inherit F_CLEAN_UP;

void remove_effect(object me);

int exert(object me, object target)
{
        int skill;

        /*
        if( userp(me) && !query("can_exert/linji-zhuang/niepan", me) ) 
                return notify_fail("你未得高人指点，不知该如何施展凤凰涅磐。\n");  

        if( query("family/family_name", me) != "峨嵋派" )
                return notify_fail("你不是少林弟子，无法使用凤凰涅磐。\n");
        */

        if( !query("reborn/times", me) )
                return notify_fail("你尚未转世重生，无法使用凤凰涅磐！\n");

        skill = me->query_skill("linji-zhuang", 1);
        if( skill < 1000 )
                return notify_fail("你的临济十二庄修为还不够，无法使用凤凰涅磐！\n");

        if( query("jingli", me)<1000 )
                return notify_fail("你的真气不够。\n");

        if( query("neili", me)<2000 )
                return notify_fail("你的内力不够。\n");

        if( objectp(target) && target != me ) {
                if( !target->query_weak() )
                        return notify_fail(target->name() + "并没有处于虚弱状态。\n");

                addn("neili", -1000, me);
                me->receive_damage("qi", 0);
                target->clear_weak();
                message_combatd(HIY "只见$N" HIY "屏息静气，双掌贴在"+target->name()+"背后，交错运行大小二庄，只见"+target->name()+"全身被紫芒笼罩。\n" NOR, me);
                tell_object(target, HIG"\n你感觉身体状态慢慢的复原了。。。\n\n" NOR);
                tell_object(me, HIG"\n你替"+target->name()+"消除了虚弱状态。。。\n\n" NOR);
                if( me->is_fighting() ) me->start_busy(3);
                return 1;
        }

        if( query_temp("niepan", me) )
                return notify_fail("你已经在运起凤凰涅磐了。\n");

        addn("neili", -1000, me);
        me->receive_damage("qi", 0);

        message_combatd(HIY "$N" HIY "神色忽而欢叹、忽而忧心、转瞬间又化做不喜不悲之状，\n随著$N" HIY "张开眼神，一屡精光乍现及逝，$N"HIY"的气习却已全然不同。\n" NOR, me);

        addn_temp("apply/avoid_busy", 100, me);
        addn_temp("apply/avoid_weak", 100, me);
        addn_temp("apply/reduce_damage", 70, me);
        set_temp("niepan", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), skill/2);

        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}

void remove_effect(object me)
{
        if( query_temp("niepan", me)){
                addn_temp("apply/avoid_busy", -100, me);
                addn_temp("apply/avoid_weak", -100, me);
                addn_temp("apply/reduce_damage", -70, me);
                delete_temp("niepan", me);
                tell_object(me, "你的临济庄运行完毕，将内力收回丹田。\n");
        }
}
