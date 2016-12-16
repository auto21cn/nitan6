// powerup.c 

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("��ֻ������ȿ�ս���������Լ���ս������\n");

        if( query("neili", me)<150 )
                return notify_fail("�������������\n");

        if( query_temp("powerup", me) )
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);
        
        message_combatd(HIY "$N" HIY "����һ��������������֮ʱ��˫Ŀ�Ѿ�������Ĺ�â����Χ�Ŀ����������������ս�⣡\n" NOR, me);
        addn_temp("apply/attack", skill/2, me);
        addn_temp("apply/defense", skill/2, me);
        set_temp("powerup", 1, me);

        me->start_call_out((:call_other, __FILE__, "remove_effect", me,
                           skill / 2:), skill);
        if (me->is_fighting()) me->start_busy(3);
        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/defense", -amount, me);
                delete_temp("powerup", me);
                tell_object(me, "�����ȿ�ս��������ϣ��������ջص��\n");
        }
}