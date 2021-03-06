
#include <ansi.h>

inherit F_SSERVER;

string name() { return HIW "参商剑气" NOR; }

int perform( object me, object target)
{
        int lvl, str, dex, skill;
        string weapon;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("参商剑气只能对战斗中的对手使用！\n");

        if( query_temp("canshang", me) )
                return notify_fail("你已经在使用参商剑气了！\n");

        if( objectp(query_temp("weapon", me)) )
                        return notify_fail("参商剑气需要你空手才能施展！\n");

        if( me->query_skill_mapped("finger") != "canhe-zhi" )
                return notify_fail("你所使用的并非参合指，不能施展参商剑气！\n");

        if( me->query_skill_prepared("finger") != "canhe-zhi" )
                return notify_fail("你所备的并非参合指，不能施展参商剑气！\n");

        if( me->query_skill_mapped("force") != "shenyuan-gong" )
                return notify_fail("你所激发的内功并非神元功，施展不出参商剑气！\n");

        if( me->query_skill("force") < 140 )
                return notify_fail("你的内功火候不到，无法施展慕容家传绝学！\n");

        if( me->query_int() < 22 )
                return notify_fail("你的悟性太差，不能施展姑苏慕容家传绝学！\n");

        if( (lvl=me->query_skill("finger")) < 100 )
                return notify_fail("参商剑气需要精深的指力方能奏效！\n");

        if( query("neili", me) <= lvl*3/2 )
                return notify_fail("你的内力不足以使用慕容绝学参商指法！\n");

        if( query("jingli", me)<lvl )
                return notify_fail("你的精力不足以使用慕容绝学参商指法！\n");

        message_combatd(HIM "$N" HIM "口中默念“动静如参商”，心随意转，劲跟力发。只听得内力破空之声呲呲作响！\n"
                        HIM "内力化作一股剑气直奔$n" HIM "射去！\n" NOR, me, target);
        str = me->query_str()/2;
        dex = me->query_dex()/3;
        addn_temp("apply/str", str, me);
        addn_temp("apply/dex", dex, me);
        set_temp("canshang", 1, me);

        skill = (me->query_skill("canhe-zhi",1)+me->query_skill("beidou-xianzong" ,1)) / 2;

        me->start_call_out( (: call_other, __FILE__, "end_perform", me, str, dex :),skill/8);

        addn("neili", -lvl, me);
        addn("jingli", -lvl, me);
        return 1;
}

void end_perform( object me, int str, int dex)
{
        addn_temp("apply/str", -str, me);
        addn_temp("apply/dex", -dex, me);
        delete_temp("canshang", me);

        tell_object(me, HIY "你缓缓收住身形，轻吁一口气，将内力收回丹田。\n" NOR);
}