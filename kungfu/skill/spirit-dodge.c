inherit SKILL;

string *dodge_msg = ({
        "$n�������Ʈ��һ�㣬�պñܹ�$N���������ơ�\n",
        "����$n�ڿ���һ�����ڣ������$N��һ�С�\n"
});

int valid_enable(string usage) { return (usage == "dodge") || (usage == "move"); }

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( query("qi", me)<40 )
                return notify_fail("�������̫���ˣ���ô������һ���ڿ��з��أ�\n");
        me->receive_damage("qi", 30);
        return 1;
}
