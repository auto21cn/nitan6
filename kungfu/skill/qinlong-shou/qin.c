//edit by gladiator ������

#include <ansi.h>
#include <combat.h>

#define QIN "��" HIR "������" NOR "��"

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string wn, msg;

        if (! target) target = offensive_target(me);

        if( userp(me) && me->query_skill("qinlong-shou",1)<120 && !query("can_perform/qinlong-shou/qin", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(QIN "ֻ����ս���жԶ���ʹ�á�\n");

        if( query_temp("weapon", me) )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" QIN "��\n");

        if (me->query_skill("force") < 100)
                return notify_fail("����ڹ�����Ϊ����������ʩչ" QIN "��\n");

        if (me->query_skill("qinlong-shou", 1) < 100)
                return notify_fail("�����������Ϊ����������ʩչ" QIN "��\n");

        if (me->query_skill_mapped("hand") != "qinlong-shou")
                return notify_fail("��û�м��������֣�����ʩչ" QIN "��\n");

        if( query("neili", me)<250 )
                return notify_fail("��������������������ʩչ" QIN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        wn = weapon->name();

        msg = HIC "$N" HIC "ʩ����" HIR QIN HIC "��������" +
              HIC "΢��������˫������צץ��$n" HIC "��\n" NOR;

        ap = me->query_skill("hand");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap * 2 / 3);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
                                           (: final, me, target, damage :));
                me->start_busy(2);
                addn("neili", -150, me);
        } else
        {
                msg += CYN "����$p" CYN "�������ң�������������񵲿���$P"
                       CYN "�Ľ��С�\n"NOR;
                me->start_busy(3);
                addn("neili", -60, me);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        addn("neili", -damage, target);

        if( query("neili", target)<0 )
                set("neili", 0, target);

        return  HIR "���$n" HIR "������$N" HIR "��ָ�����"
                "ָ��צ���͹�Ѩ��ȫ������������й������\n" NOR;
}