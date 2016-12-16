// /kungfu/skill/beidou-zhenfa.c

#include <ansi.h>

inherit SKILL;

int valid_enable(string usage) { return usage=="array"; }

string *position = ({
        "��Ȩ","����","���","����","���","����","ҡ��"
});

string *sword = ({
        "̤���ţ���ƫ�棬������˼�����һ�������ޱȵġ��ֻ�������������ʵ�������д�ȥ��",
        "ʹһ�С���������������������Ʈ�����н�����ʵʵ�ó����㺮��������С�",
        "����һת����Ȼһʽ���ɨҶ����������콣Ӱ��Ю�ž�����ǰɨȥ��",
        "���쳤Ц������ƮȻ�����ڰ��������һ����һʽ�����ʹ��������ػ�����С�",
        "�������Ž���������̤��һ�С������롱����б�̡�",
        "��ǰ��ȥһ�󲽣�ʹ����̽�������������н����һ������Ѹ�����׻�����",
        "����һ������һʱ�������仨�������ó���㽣����ƮȻ�̳���",
        "���н�һָ���������࣬һʱ������Į�����������������",
        "��������Ʈ��ͻȻһת����ͷ�½��ϣ����ս���һ�С���׹��������������Ϣ�ع�����",
        "���һ����һ�С��׺羭�졹��������㻮��һ����Բ�����¡�",
        "��Ȼ���θ߸�Ծ��ʹ�����˼����ġ������н��ó����컨�꣬Ѹ�����������"
});

string *zhen =  ({
        "������󷨹����ƶ����������಻����˲�佫����Χ�����ġ�",
        "����������ƺ��ǰ�������������ӣ������ۻ����ң������ʧ��",
        "ֻ��������󰵺����а���֮���������˲������������ϵ������޷졣",
        "�������Խ��ԽС�����ν������˳�һ��������룬��������Ϣ֮�С�"
});


void start_beidouzhen(object ob, int mypos,int beidou_time,int bd_power );
int beidouzhen(object me);
int halt_beidou(object me);
void out_beidou(object me);

int valid_learn(object me)
{
        if( query("gender", me) == "����" && 
        (int)me->query_skill("beidou-zhenfa", 1) > 49)
                return notify_fail("���޸����ԣ����������������������������󷨡�\n");

        if ((int)me->query_skill("array", 1) <= (int)me->query_skill("beidou-zhenfa",1))
                return notify_fail("��Ļ����󷨻�򻹲�����\n");

            return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("�������ֻ����ѧ(learn)�������������ȡ�\n");
}

int form_array(object me,string arg)
{
        object enemy,*member;
        int beidou_time,i,mypos=0,power,bd_power,level;
        object here;
        string msg;
        float exp_diff;

        here = environment( me );

        if( me->is_busy() )
        {
                return notify_fail("����æ���أ�\n");
        }

        if( me->query_skill_mapped("array") != "beidou-zhenfa")
                return notify_fail("�㻹û�м�����������󷨣�\n");

        member = me->query_team();
        level = sizeof(member) *20;

        if (sizeof(member) < 3 || sizeof(member) > 7)
                return notify_fail("����������������ˣ�����߸��ˡ�\n");

        if( me->query_skill("beidou-zhenfa",1) < level)
                return notify_fail("���������󷨵ȼ�̫�ͣ�\n");

        if (!arg)
                return notify_fail("ָ���ʽ��team form beidou-zhenfa Ŀ��ID \n");

        if (!enemy = present(arg,here))
                return notify_fail("��Ҫ���󹥻���"+arg+"�������ﰡ��\n");

        if( query("family/family_name", enemy) == "ȫ���" )
                return notify_fail("��ô������Ҫͬ�Ų�ɱô��\n");

        if( query("race", enemy) != "����" )
                return notify_fail("��ô��ɱ������ţ��ô��\n");

        for( i = 0; i < sizeof(member); i++ )
        {
           if (!objectp(member[i]))
                return notify_fail("��Ķ����е����⣬��Ҫ������϶��顣\n");

           if (environment(member[i]) != here)
                return notify_fail("������е�" + member[i]->name() + "���ڲ������ﰡ��\n");

           if( query("family/family_name", member[i]) != "ȫ���" )
                return notify_fail("������е�" + member[i]->name() + "����ȫ��̵��ӡ�\n");

           if (member[i]->is_busy())
                return notify_fail("������е�" + member[i]->name() + "��æ���أ�\n");

           if (member[i]->query_skill_mapped("array") != "beidou-zhenfa")
                return notify_fail("������е�" + member[i]->name() + "û�м�����������󷨡�\n");

           if (member[i]->query_skill("beidou-zhenfa",1) < level )
                return notify_fail("������е�" + member[i]->name() + "������󷨵ȼ�������\n");

           if ( member[i]->query_skill("quanzhen-jian",1) <60 ||
                query("combat_exp", member[i])<50000 || 
                member[i]->query_skill("dodge") <60)
                return notify_fail("������е�" + member[i]->name() + "�书̫����ܲμӡ�������󡹡�\n");

           if( query("neili", member[i])<500 )
                return notify_fail("������е�" + member[i]->name() + "����̫����ܲμӡ�������󡹡�\n");

           if( query("jingli", member[i])<300 )
                return notify_fail("������е�" + member[i]->name() + "����̫����ܲμӡ�������󡹡�\n");

           exp_diff=to_float(query("combat_exp", member[i])-query("combat_exp", me));
           exp_diff/=to_float(query("combat_exp", me));

           if( exp_diff > 0.4 || exp_diff < -0.4 )
                return notify_fail("������е�" + member[i]->name() + "�书������̫�󣬲��ܹ��ڡ�������󡹡�\n");
        }

        power = me->query_skill("force");
        power += me->query_skill("sword");
        power+=query("str", me)*10;
        power += me->queyr("dex")*10;

        bd_power = me->query_skill("beidou-zhenfa",1);

        for (i = 0;i < sizeof(member); i++)
        {
                power += member[i]->query_skill("force");
                power += member[i]->query_skill("sword");
                power+=query("str", member[i])*10;
                power += member[i]->queyr("dex")*10;

                bd_power += member[i]->query_skill("beidou-zhenfa",1);
        }

        power /= 70;
        bd_power /= 35;
        power += bd_power;

        if(power>300)power=300;
        if(power<30)power=30;

        msg = "";

        for (i = 0;i < sizeof(member); i++)
        {
                start_beidouzhen(member[i],0,power/2,power);
                if (member[i] != me)
                {
                        msg += member[i]->name();
                        if (i != sizeof(member) -1)
                                msg += "��";
                }
        }

        message_vision(HIM"$NͻȻ�����ƶ�������" + msg +
                        "��" + enemy->name() + "Χ���м䣬���ǰڵġ���������󷨡�\n\n"NOR, me);

        message_vision(HIR"\n$N��$n�ȵ���" + RANK_D->query_rude(enemy) +
                        "��һ��Ϊ�����������챾��Ҫ�����е�����������\n\n"NOR, me, enemy);

        for (i = 0;i < sizeof(member); i++)
        {
                member[i]->kill_ob(enemy);
                enemy->kill_ob(member[i]);
        }

        return 1;
}

void start_beidouzhen(object ob, int mypos,int beidou_time,int bd_power )
{
        set_temp("pending/beidou", 1, ob);
        set_temp("beidou_time", beidou_time, ob);
        set_temp("bd_pos", mypos, ob);
        set_temp("bd_power", bd_power, ob);
        addn_temp("apply/defense", bd_power, ob);
        addn_temp("apply/parry", bd_power/3, ob);
        addn_temp("apply/dodge", bd_power/3, ob);
        ob->start_busy((: beidouzhen :), (:halt_beidou:));
}

void check_leaving(object me)
{
        string name=query("id", me);

        if( !userp(me) )
                {
                 object enemy = offensive_target(me);
                 if( !objectp(enemy) && !me->is_busy() && !me->is_fighting() )
                 {
                         message_vision(HIY"\n$N���˸�鮵���ƶ���ȸ����ˣ�˵��Ϳ첽�뿪�ˡ�\n"NOR, me);
                         call_out("destruct_me",10,me);
                         return;
                  }

                  call_out("check_leaving",5,me);
          }
}

int beidouzhen(object me)
{
        object *member,ob,where;
        int beidou_time,i,power,ok,mypos;
        object room, obj,enemy,weapon;

        enemy = offensive_target(me);
        beidou_time=query_temp("beidou_time", me);
        where = environment(me);
        mypos=query_temp("bd_pos", me);

        if (beidou_time < 1)
        {
                out_beidou(me);
                return 0;
        }

        if (!objectp(enemy) || environment(enemy) != where)
        {
                out_beidou(me);
                return 0;
        }

        if( query("neili", me)<300 || query("jingli", me)<100 )
        {
                out_beidou(me);
                return 0;
        }

        member = me->query_team();

        if (!member || sizeof(member) < 3 || sizeof(member) > 7)
        {
                out_beidou(me);
                return 0;
        }

        ok = 1;

        for ( i = 0;i < sizeof(member);i++)
        {
                if (environment(member[i]) != where)
                {
                        ok = 0;
                        break;
                }

                if( !query_temp("pending/beidou", member[i]) )
                {
                        ok = 0;
                        break;
                }
        }

        if (!ok)
        {
                out_beidou(me);
                return 0;
        }


        beidou_time = beidou_time-1;
        set_temp("beidou_time", beidou_time, me);

        power=query_temp("bd_power", me);

        if( random(6)==1 )
        {
                tell_room(environment(me), HIR"\n" + zhen[(int)random(4)] +"\n"NOR, this_object());
                if( objectp(enemy) &&
                    objectp(present(query("id", enemy),environment(me))) )
                        enemy->start_busy( random(2) );
        }

        if( random(2)==1 )
        {
                if(random(2)==0)
                        message_vision(WHT"\n" + position[mypos] + "λ�ϵ�$N������������񹦣���Ȼ����������������ǰһ�ݡ�\n"NOR, me);
                else
                        message_vision(WHT"\n" + position[mypos] + "λ�ϵ�$Nͦ�������������������ƮƮ��������硣\n"NOR, me);

                addn_temp("apply/damage", power, me);
                addn_temp("apply/sword", power/2, me);
                addn_temp("apply/attack", power, me);
                addn("jiali", power, me);
                COMBAT_D->do_attack(me,enemy,query_temp("weapon", me));
                addn_temp("apply/damage", -power, me);
                addn_temp("apply/sword", -power/2, me);
                addn_temp("apply/attack", -power, me);
                addn("jiali", -power, me);
                addn("jingli", -15-random(15), me);
                addn("neili", -20-random(20), me);
        }

        return 1;
}

void restart (object me)
{
        start_beidouzhen(me,query_temp("bd_pos", me),query_temp("beidou_time", me),query_temp("bd_power", me));
}

int halt_beidou(object me)
{
        object weapon;
        int beidou_time=query_temp("beidou_time", me);
        if (beidou_time > 0)
        {
                if( !living(me) ) return 1;

                if(random(2)==1)
                {
                        message_vision(HIG"\n$N������һ�������ˤ��������\n"NOR, me);
                }
                else message_vision(HIG"\n$N����Ļ��˼��Σ�������վ���˲��ӡ�\n"NOR, me);
                call_out("restart",4,me);
                return 1;
        }

        out_beidou(me);
        return 1;
}

void out_beidou(object me)
{
        object weapon;
        int bd_power;

        bd_power=query_temp("bd_power", me);

        if( !objectp(weapon=query_temp("weapon", me)) || 
           query("skill_type", weapon) != "sword" )
                message_vision(HIG"\n$N�������һ�ݣ�ʹһ�С���ɽʽ������ȭ����һȦ������������һ�����˳���������󡹡�\n"NOR, me);
        else
                message_vision(HIG"\n$N�������һ�ݣ�ʹһ�С��ս�ʽ������������һ��������������һ�����˳���������󡹡�\n"NOR, me);

        addn_temp("apply/defense", -bd_power, me);
        addn_temp("apply/parry", -bd_power/3, me);
        addn_temp("apply/dodge", -bd_power/3, me);
        delete_temp("pending/beidou", me);
        delete_temp("beidou_time", me);
        delete_temp("bd_pos", me);
        delete_temp("bd_power", me);
        return;
}