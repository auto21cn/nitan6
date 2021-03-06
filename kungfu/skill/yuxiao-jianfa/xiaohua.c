// xiaohua.c 箫花齐放
// Modified by whuan
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
int perform(object me, object target)
{
        string msg;
        object weapon;
        int i,j,k,damage;
        if( !target ) target = offensive_target(me);

        if (!objectp(weapon = me->query_temp("weapon")) 
         || (string)weapon->query("skill_type") != "sword")
        if (!objectp(weapon = me->query_temp("secondary_weapon"))
         || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你手中无剑，如何使得玉萧剑法的精妙绝招？\n");
    
        if( time() < 10+(int)me->query_temp("xiaohua") )        
                return notify_fail("你刚使「箫花齐放」攻敌，气血汹涌，无法出招！\n");    
    
        if ( (int)me->query("neili") <500)
                return notify_fail("你的内力不够，无法使出「箫花齐放」！\n");
        
        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("「箫花齐放」只能对战斗中的对手使用。\n");

        if( (int)me->query_skill("yuxiao-jian", 1) < 100 )
                return notify_fail("你的玉箫剑法不够娴熟，不会使用「箫花齐放」。\n");

        if( (int)me->query_skill("bibo-shengong", 1) < 100 ) 
                return notify_fail("你的碧波神功修为不够，无法运用「箫花齐放」攻敌。\n");

        me->set_temp("xiaohua",time());
       
        j=1+me->query_skill("sword")/50; 
        if (j>7) j=7; //计算剑数
        k=(int)me->query_skill("sword");
        damage = k+random(k/2) + me->query_temp("apply/damage");
        damage = damage*11/20;//计算伤害
        
        msg = CYN "$N使出玉箫剑法绝招「箫花齐放」，纵身一跃，连出"+chinese_number(j)+"剑，照向$n。\n";
        message_vision(msg, me, target);

        for (i=0;i<j;i++)
        {
		       if (random(me->query_skill("sword")+target->query_skill("dodge"))>target->query_skill("dodge")) 
		       {
			       message_vision(HIY"\n$n一个不慎，中了一剑！\n"NOR,me,target);
             target->receive_damage("qi",damage,me);
             target->receive_wound("qi",damage/6+random(damage/6),me); 
			       COMBAT_D->report_status(target);
            }
		       else
             message_vision(HIY"\n$n左跳右闪，好不容易才避开了这一剑！\n"NOR,me,target);
         }

        me->start_busy(1+random(2));
        me->add("neili",-30*j);
        return 1;
}
