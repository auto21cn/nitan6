// jingang-chu.c ��ս�ħ��

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N�߾�����$w��ʹ��һ��"HIY"�����������"NOR"��ֱ��$n��$l",
        "skill_name" : "�������",
        "lvl" : 0
]),
([        "action" : "$Nʹ��"HIY"����շ�ħ��"NOR"�������趯$w��һ������$w��ɨ$n������",
        "skill_name" : "��շ�ħ",
        "lvl" : 8
]),
([        "action" : "$N�������棬ʹ��һʽ"HIY"�����������"NOR"��˫����$w��һ��ֱ��$n��$l",
        "skill_name" : "�������",
        "lvl" : 16
]),
([        "action" : "$Nʹ��һ��"HIY"����Ȥ������"NOR"��˫�־ٹ�����$n���ɲ�",
        "skill_name" : "��Ȥ����",
        "lvl" : 24
]),
([        "action" : "$N�趯����$w��ʹ��"HIY"���������ޡ�"NOR"����ʱ��ס$n��ȫ��",
        "skill_name" : "��������",
        "lvl" : 32
]),
([        "action" : "$Nʹ��һ��"HIY"������Ѫ����"NOR"��ȫ�����ض��ɣ�һ��ֱ��$n��$l",
        "skill_name" : "����Ѫ��",
        "lvl" : 40
]),
([        "action" : "$Nʹ��һʽ"HIY"��������ħ��"NOR"���Թ�֧�أ�˫��ɴ�$n������",
        "skill_name" : "������ħ",
        "lvl" : 48
]),
([        "action" : "$N�������ƣ�ʹ��"HIY"����ħ������"NOR"����������������$w��ɨ$n��$l",
        "skill_name" : "��ħ����",
        "lvl" : 56
]),
});

int valid_enable(string usage) { return usage == "staff" || usage == "parry"; }
int valid_learn(object me)
{
        if( query("max_neili", me)<800 )
                return notify_fail("���������Ϊ����������������ս�ħ�ơ�\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ����̫ǳ������������ս�ħ�ơ�\n");

        if ((int)me->query_skill("staff", 1) < 50)
                return notify_fail("��Ļ�����������������������ս�ħ�ơ�\n");

        if ((int)me->query_skill("staff", 1) < (int)me->query_skill("jingang-chu", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������Ľ�ս�ħ�ơ�\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "staff" )
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if( query("qi", me)<50 || query("neili", me)<30 )
                return notify_fail("����������������������˽�ս�ħ�ơ�\n");
        me->receive_damage("qi", 40);
        addn("neili", -20, me);
        return 1;
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -45;
        int d_e2 = -10;
        int p_e1 = 15;
        int p_e2 = 45;
        int f_e1 = 250;
        int f_e2 = 300;
        int m_e1 = 190;
        int m_e2 = 290;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("jingang-chu", 1);
        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* �������������� */
                        break;
                }
        seq = random(seq);       /* ѡ������������ */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage"      : m_e1 + (m_e2 - m_e1) * seq / ttl,
                "damage_type" : "����",
        ]);
}
int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
       return __DIR__"jingang-chu/" + action;
}

int help(object me)
{
        write(HIC"\n��ս�ħ�ƣ�"NOR"\n");
        write(@HELP

    ��ս�ħ��Ϊѩɽ����е�书��

        ѧϰҪ��
                �����������С���๦20��
                ����100
HELP
        );
        return 1;
}