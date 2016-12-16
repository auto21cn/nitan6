// yong.c ����������

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        int count;
        int lvl;
        int i;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("����������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if( query("neili", me)<200 )
                return notify_fail("��������������޷�ʩչ���������ƣ�\n");

        if ((lvl = me->query_skill("bluesea-force", 1)) < 150)
                return notify_fail("����Ϻ�������򲻹����޷�ʩչ���������ƣ�\n");

        if (me->query_skill_mapped("strike") != "bluesea-force")
                return notify_fail("��û�м����Ϻ�����Ϊ�Ʒ����޷�ʩչ���������ƣ�\n");

        if (me->query_skill_prepared("strike") != "bluesea-force")
                return notify_fail("��û��׼����ʹ���Ϻ��������޷�ʩչ���������ƣ�\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "���Ữ�˸�Ȧ�ӣ����κ�Ȼ��죬������Ϊһ������$n"
              HIC "��\n" NOR;
        i = 5;
        if (lvl + random(lvl) > (int)target->query_skill("force") * 2 / 3)
        {
                msg += HIY "��������֮�£�$n" HIY "��ʱ���ú���"
                       "����������������ѹ��������ܣ�ֻ��$N"
                       HIY "һ�ƽ�һ�ƵĹ��������纣�ˡ�\n" NOR;
                count = me->query_skill("bluesea-force", 1) / 5;
                addn_temp("apply/attack", count, me);
                i += random(5);
        } else
        {
                msg += CYN "$n" CYN "��������죬ֻ���������������ֵ���\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn("neili", -i*20, me);

        while (i--)
        {
                if (! me->is_fighting(target))
                        break;
                if (i > 4 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(7));
        return 1;
}