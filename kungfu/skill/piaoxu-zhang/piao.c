#include <ansi.h>

string name() { return HIW "����Ʈ��" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int count;
        int lvl;
        int i;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if ((lvl = (int)me->query_skill("piaoxu-zhang", 1)) < 80)
                return notify_fail("��Ʈ���Ʒ�������죬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("strike") != "piaoxu-zhang")
                return notify_fail("��û�м���Ʈ���Ʒ�������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("strike") != "piaoxu-zhang")
                return notify_fail("��û��׼��Ʈ���Ʒ�������ʩչ" + name() + "��\n");

        if( query("neili", me)<100 )
                return notify_fail("�������������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "΢΢һЦ������ʩ��Ʈ���Ʒ�����������Ʈ�㡹����ʱ��"
              "Ӱ���أ���ʵ�ѱ棬ȫȫ����$n" HIW "��ȥ��\n" NOR;
        addn("neili", -50, me);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "��ʱ�����ۻ����ң�ȫȻ�ֱ�"
                       "������α��ֻ��ƴ���˶��ֵ���\n" NOR;
                count = ap / 10;
                addn_temp("apply/attack", count, me);
        } else
        {
                msg += HIC "����$n" HIC "��������������ֵ���˿"
                       "��������Ӱ�ĸ��ţ���\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        for (i = 0; i < 3; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }
        me->start_busy(1+random(2));
        addn_temp("apply/attack", -count, me);
        return 1;
}