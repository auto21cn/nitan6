#include <ansi.h>

#define DIAN "��" HIW "���쾢����Ծ��" NOR "��"

int exert(object me, object target)
{
        if( userp(me) && !query("can_perform/taiji-shengong/dian", me) )
                return notify_fail("�㻹û����������˹����ϣ��޷�ʩչ" DIAN "��\n"); 

        if (! target)
                return notify_fail("��Ҫ������Ϊ˭���ˣ�\n");

        if (target == me)
                return notify_fail(DIAN "ֻ�ܶԱ���ʩչ��\n");

        if (me->is_fighting() || target->is_fighting())
                return notify_fail("ս�����޷��˹����ˡ�\n");

        if( query("not_living", target) )
                return notify_fail("���޷���" + target->name() + "���ˡ�\n");

        if ((int)me->query_skill("taiji-shengong", 1) < 100)
                return notify_fail("���̫���񹦲�����죬����ʩչ" DIAN "��\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("���������Ϊ̫ǳ������ʩչ" DIAN "��\n");

        if( query("neili", me)<1000 )
                return notify_fail("�����ڵ��������㣬����ʩչ" DIAN "��\n");

        if( query("jing", me)<100 )
                return notify_fail("�����ھ���״̬���ѣ�����ʩչ" DIAN "��\n");

        if( query("eff_qi", target) >= query("max_qi", target) && 
            query("eff_jing", target) >= query("max_jing", target) )
                return notify_fail("�Է�û�����ˣ�����Ҫ�������ơ�\n");

        message_sort(HIW "\nֻ��$N" HIW "˫��ʳָ��Ĵָ���ã��ɺ��쾢"
                     "�ƣ���ʳָָ�����$n" HIW "�������ִ�����Ծ�ϣ�"
                     "�����ڹ���΢΢�ڶ������к��쾢����Ծ��ʹ��������"
                     "�����¶���֮��Ҳ�ܻ���Ƭ�̡�����һ������$p��ͷ"
                     "��ð�������飬ͷ��ð�������������۵�һ���³���"
                     "Ѫ����ɫ��ʱ������������ˡ�\n" NOR, me, target);

        addn("neili", -800, me);
        me->receive_damage("qi", 100);
        me->receive_damage("jing", 50);

        target->receive_curing("qi", 100 + (int)me->query_skill("force") +
                                     (int)me->query_skill("taiji-shengong", 1) * 3);

        if( query("qi", target) <= 0 )
                set("qi", 1, target);

        target->receive_curing("jing", 100 + (int)me->query_skill("force") / 3 +
                                       (int)me->query_skill("taiji-shengong", 1));

        if( query("jing", target) <= 0 )
                set("jing", 1, target);

        if (! living(target))
                target->revive();

        if (! target->is_busy())
                target->stary_busy(2);

        message_vision("\n$N��Ŀڤ������ʼ�˹���Ϣ��\n", me);
        me->start_busy(10);
        return 1;
}