#include <ansi.h>

inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "������"; }

int valid_learn(object me)
{        
        if (me->query_skill("qiankun-jian", 1) < 120)
                return notify_fail("��Ǭ���񽣻���㣬�޷���ϰ�����޼���\n");        

        if( query("family/family_name", me) != family_name() )
                return notify_fail("�����޼�ֻ�������ɵ��ӷ�����ϰ��\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}