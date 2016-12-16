// qishi-ji.c ʥ��ʿ�

inherit SKILL;

mapping *action = ({
([      "action": "$N˫Ŀŭ��������$w��Ȼ�̳�����������",
        "force" : 100,
        "attack": 35,
        "dodge" : 10,
        "parry" : 5,
        "lvl"   : 0,
        "damage": 85,
        "damage_type" : "����"
]),
([      "action": "$N˫�����ֵ�$wת�����ѣ��͵ļ�����$n��ȥ",
        "force" : 125,
        "attack": 42,
        "dodge" : 10,
        "parry" : 15,
        "damage": 100,
        "lvl"   : 10,
        "damage_type" : "����"
]),
([      "action": "$N���е�$w�����任�����������ͻȻֱ��$n��$l",
        "force" : 150,
        "attack": 45,
        "dodge" : 15,
        "parry" : 25,
        "damage": 100,
        "lvl"   : 30,
        "damage_type" : "����"
]),
([      "action": "$N���е�$w��Ȼ���أ��漴����$n��ȥ���쳣����",
        "force" : 160,
        "attack": 50,
        "dodge" : 25,
        "parry" : 29,
        "damage": 110,
        "lvl"   : 50,
        "damage_type" : "����"
]),
([      "action": "$N��ǰһ����˫�ֽ�$wһѹ��бб������$n��$l",
        "force" : 180,
        "attack": 48,
        "dodge" : 20,
        "parry" : 31,
        "damage": 115,
        "lvl"   : 80,
        "damage_type" : "����"
]),
([      "action": "$N���һ����$w���������̳���Я��һ���������$n",
        "force" : 240,
        "attack": 52,
        "dodge" : 25,
        "parry" : 37,
        "damage": 120,
        "lvl"   : 100,
        "damage_type" : "����"
]),
([      "action": "$N��ǰ������$w����ǰ�̣����޷��˵Ĺ���$n",
        "force" : 260,
        "attack": 55,
        "dodge" : 15,
        "parry" : 37,
        "damage": 125,
        "lvl"   : 120,
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "club" || usage == "parry"; } 

int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("����ڹ���򲻹���\n");

        if ((int)me->query_skill("club", 1) < (int)me->query_skill("qishi-ji", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷����������ʥ��ʿꪡ�\n");

        if ((int)me->query_skill("club", 1) < (int)me->query_skill("qishi-ji", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷����������ʥ��ʿꪡ�\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("qishi-ji", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "club" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("qi", me)<80 )
                return notify_fail("�������������ʥ��ʿꪡ�\n");

        if( query("neili", me)<50 )
                return notify_fail("�������������ʥ��ʿꪡ�\n");

        me->receive_damage("qi", 70);
        addn("neili", -40, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"qishi-ji/" + action;
}