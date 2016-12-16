// exercise.c
// Updated by Lonely

#include <skill.h>

inherit F_CLEAN_UP;

int exercising(object me);
int halt_exercise(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        mapping msg;
        int exercise_cost;
        string force;
        object where;
        int n;

        seteuid(getuid());
        where = environment(me);

        if( query("pigging", where) )
                return notify_fail("�㻹��ר�Ĺ����ɣ�\n");

        if( me->is_busy() || query_temp("pending/exercising", me) )
                return notify_fail("��������æ���ء�\n");

        if (me->is_fighting())
                return notify_fail("ս���в������ڹ������߻���ħ��\n");

        if (! stringp(force = me->query_skill_mapped("force")))
                return notify_fail("��������� enable ѡ����Ҫ�õ��ڹ��ķ���\n");

        if (! arg || ! sscanf(arg, "%d", exercise_cost))
                return notify_fail("��Ҫ��������������\n");

        if (exercise_cost < 10)
                return notify_fail("����ڹ���û�дﵽ�Ǹ����磡\n");

        if( query("qi", me)<exercise_cost )
                return notify_fail("�����ڵ���̫���ˣ��޷�������Ϣ����ȫ��������\n");

        if( query("jing", me)*100/query("max_jing", me)<70 )
                return notify_fail("�����ھ��������޷�������Ϣ��������\n");

        if( query("no_fight", environment(me)) && 
            //(query("doing", me) != "scheme" || this_player(1)) )
            (query("doing", me) != "scheme") )
                return notify_fail("���޷�������ط����Ĵ�����\n");

        notify_fail("���޷�˳������ת��Ϣ��\n");
        if (SKILL_D(force)->do_effect(me))
                return 0;
        
        msg = SKILL_D(force)->exercise_msg(me);
        
        if (! msg || undefinedp(msg["start_self"]))
                write("�������������ù���һ����Ϣ��ʼ������������\n");
        else 
                write(msg["start_self"]);

        set_temp("pending/exercise", 1, me);
        set_temp("exercise_cost", exercise_cost, me);
        
        if (! msg || undefinedp(msg["apply_short"]))        
                me->set_short_desc("�����ڵ�������������");
        else
                me->set_short_desc(msg["apply_short"]);

        if (! msg || undefinedp(msg["start_other"]))
                tell_room(environment(me), me->name() + "��ϥ���£���ʼ����������\n", me);
        else
                tell_room(environment(me), msg["start_other"], me); 
                                            
        me->start_busy(bind((:call_other, __FILE__, "exercising" :), me),
                       bind((:call_other, __FILE__, "halt_exercise" :), me));
        return 1;
}

int exercising(object me)
{
        mapping msg;
        string force;
        int exercise_cost=query_temp("exercise_cost", me);
/*
        int neili_gain = (int)me->query_skill("force") / 2;

        neili_gain = 1 + neili_gain / 2 + random(neili_gain) +
                     query("exercise_improve", environment(me));
*/
        int neili_gain = (int)me->query_skill("force") * 2;
        if (neili_gain < 0) neili_gain = 1;
        if (exercise_cost > 2*neili_gain) neili_gain = exercise_cost/2;

        if (stringp(force = me->query_skill_mapped("force")))
                msg = SKILL_D(force)->exercise_msg(me);
        
        if (exercise_cost > 0)
        {
                if (neili_gain > exercise_cost)
                        neili_gain = exercise_cost;
                
                if( neili_gain>query("qi", me) )
                {
                        neili_gain=query("qi", me);
                        set_temp("exercise_cost", 0, me);
                        me->set_short_desc(0);
                        exercise_cost = 0;
                } else
                {
                        set_temp("exercise_cost", exercise_cost-=neili_gain, me);
                }
                addn("neili", neili_gain, me);
                addn("qi", -neili_gain, me);
                
                if (exercise_cost > 0)
                {
                        if (! random(3) && mapp(msg) && ! undefinedp(msg["exercise_msg"]))
                                tell_object(me, msg["exercise_msg"]);
                        return 1;
                }
        }

        set_temp("pending/exercise", 0, me);
        me->set_short_desc(0);
        
        if (! msg || undefinedp(msg["finish_self"]))
                tell_object(me, "��ֻ����Ϣ��ת˳�������������ϵ��վ��������\n");
        else
                tell_object(me, msg["finish_self"]);
        
        if (! msg || undefinedp(msg["finish_other"]))
                tell_room(environment(me), me->name() + "�˹���ϣ��������˿�����վ��������\n", me);
        else
                tell_room(environment(me), msg["finish_other"], me);
                                        
        if( query("neili", me)<query("max_neili", me)*2 )
                return 0;
        else
        {
                if( query("max_neili", me) >= me->query_current_neili_limit() )
                {
                        write("���������Ϊ�ƺ��Ѿ��ﵽ��ƿ����\n");
                        set("neili",query("max_neili",  me), me);
                        return 0;
                } else
                {
                        addn("max_neili", 1, me);
                        set("neili",query("max_neili",  me), me);
                        write("������������ˣ���\n");
                        return 0;
                }
        }
}

int halt_exercise(object me)
{
             mapping msg;
        string force;

        if (stringp(force = me->query_skill_mapped("force")))
                msg = SKILL_D(force)->exercise_msg(me);

        if (! msg || undefinedp(msg["halt_self"]))                        
                tell_object(me, "�㽫����ѹ�ص��վ��������\n");
        else 
                tell_object(me, msg["halt_self"]);
                
        if (! msg || undefinedp(msg["halt_other"]))                  
                tell_room(environment(me), me->name() + "����һ������վ��������\n", me);
        else
                tell_room(environment(me), msg["halt_other"], me);                        
         
        if( query("neili", me)>query("max_neili", me)*2 )
                set("neili",query("max_neili",  me)*2, me);
        set_temp("pending/exercise", 0, me);
        me->set_short_desc(0);
        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : exercise|dazuo [<�ķѡ���������> ������� 10]

�����������������ڵ����ڸ�����������������ѵ�����弡���������
��������������������������ʽ����������������ע�⣺�㲻���ڲ���
ս���ĵط�������

HELP );
        return 1;
}