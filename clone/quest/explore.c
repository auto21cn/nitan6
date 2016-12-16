// �������explore.c

#include <ansi.h>
#include <quest.h>
#include <command.h>

inherit QUEST_OB;

#define NPC_OB          my["npc"]       // ���ձ����NPC����
#define NPC_NAME        my["npc_name"]  // ���ձ����NPC������
#define NPC_ID          my["npc_id"]    // ���ձ����NPC��ID
#define ENV_OB          my["env_ob"]    // �������صĵص�
#define QOB             my["qob"]       // ���ձ�����ļ�����
#define QOB_NAME        my["qob_name"]  // ���ձ��������
#define ZONE            my["zone"]      // ���ն�������������

object search_qob(object me);
int    npc_accept_object(object me, object who, object ob);
void   npc_destructed();

// ������󴴽�
void create()
{
        seteuid(getuid());
        setup();
}

// ����һ������
// ����һ����Ʒ����Ѱ�ң��Զ�������������������ص㣬����ɱ
// �˵�һ���˼��ɻ�ø���Ʒ��Ȼ�󽻸��ڶ�������ȡ������
void init_quest(object npc_ob, string qob_name, string zone, string *files)
{
        mapping my;
        string room;
        object env;
        object qob;

        my = query_entire_dbase();

        // �������������
        set_name(npc_ob->name() + "����");

        if( query_temp("quest_ob", npc_ob) )
        {
                // ���NPC�Ѿ���������������ֹ����
                destruct(this_object());
                return;
        }

        if (objectp(qob = find_object(qob_name)))
        {
                if( objectp(query_temp("quest_ob", qob)) )
                {
                        // ����Ʒ�Ѿ����ڲ���������������������ܽ���
                        destruct(this_object());
                        return;
                }
        } else
                // ����������Ʒ
                qob = load_object(qob_name);

        // ��¼����Ʒ����������
        set_temp("quest_ob", this_object(), qob);

        NPC_OB = npc_ob;
        NPC_NAME = npc_ob->name();
        NPC_ID=query("id", npc_ob);
        QOB    = qob;
        QOB_NAME = qob->name();
        ZONE = zone;

        // ���ѡ��һ���ص�
        for (;;)
        {
                call_other(room = zone + files[random(sizeof(files))], "???");
                if (! objectp(env = find_object(room)))
                {
                        // �޷�ȡ���������
                        cancel_quest();
                        return;
                }

                if( mapp(query("exits", env)) )
                        // �ҵ����г��ڵķ���
                        break;
        }

        // �ڷ����з��ÿ������Ķ��󣬲�ȥ���÷�������ҵ���
        // ������ͭ��
        env->set_temp("no_search",(["/clone/money/coin":0,
                                      "/clone/money/silver" : 0, ]));
        set_temp("search_objects", ([(:search_qob:):10000]), env);
        set_temp("been/searched", -150, env);
        ENV_OB = env;

        // ����NPC�ĶԻ���Ϣ
        set("inquiry/"+NPC_NAME, "�����������£�", npc_ob);
        set("inquiry/"+NPC_ID, "���Ұ������Ҷ����ˣ�", npc_ob);
        set("inquiry/"+QOB_NAME, "������...��֪��ô������ң�", npc_ob);
        set_temp("quest_ob", this_object(), npc_ob);

        // ���ý�����Ʒ����Ϣ������NPC���ڵ�ʱ�����������
        // ������ڣ���Ϊ����������ʱ������NPC�������Կ���
        // ��NPC���ñ��ص�"npc_accept_object"������
        set_temp("override/accept_object", (:npc_accept_object:), npc_ob);

        // ����������Ϣ��NPC���������Ժ��Զ��������
        set_temp("override/destruct", (:npc_destructed:), npc_ob);

        // �л�������״̬
        change_status(QUEST_READY);

        // ������������ʱ�䣺30����
        set("live_time", 1200);

        // �Ǽ�ҥ����Ϣ
        register_information();
}

// �ָ�NPC�����������ʱ�����ָ�������NPC
void restore_npc()
{
        mapping my = query_entire_dbase();
        object npc_ob;

        if (! objectp(npc_ob = NPC_OB))
                return;

        delete_temp("override/accept_object", npc_ob);
        delete_temp("override/destruct", npc_ob);
        delete("inquiry/"+NPC_NAME, npc_ob);
        delete("inquiry/"+NPC_ID, npc_ob);
        delete("inquiry/"+QOB_NAME, npc_ob);
        NPC_OB = 0;
}

// �ָ�ENV�����������ʱ�����ָ������Ļ���
void restore_env()
{
        mapping my = query_entire_dbase();
        object env;

        if (! objectp(env = ENV_OB))
                return;

        // ȥ����ʱ��������Ʒ��Ϣ
        delete_temp("search_objects", env);
        delete_temp("no_search", env);
        set_temp("been/searched", 30, env);
        ENV_OB = 0;
}

// ��������
void cancel_quest()
{
        mapping my = query_entire_dbase();

        // �ָ�NPC��Ȼ���������
        restore_npc();
        restore_env();

        if (objectp(QOB) && ! environment(QOB))
                destruct(QOB);

        ::cancel_quest();
}

// ����NPC����
void npc_destructed()
{
        call_out("cancel_quest", 0);
}

// �ڷ���������Ʒ
object search_qob(object me)
{
        mapping my = query_entire_dbase();
        mapping dq;
        int i, exp2, pot2, exc2;      // ǿ��freequest����õĶ��⽱��
        object ob, gift;
        string msg;

        if( query("score", me)<2000 )
                // ������2000�Ľ����������ܹ��ҵ�
                return 0;

        if (! objectp(QOB))
                // �����Ʒ�Ѿ�û���ˣ��޷�����
                return 0;

        if (objectp(environment(QOB)))
                // ����Ʒ�Ѿ��������޷�����
                return 0;

        if( !query("no_fight", environment(me)) && random(100)<10 )
        {
                // �ҵ�ɱ��һ����
                ob = new("/clone/npc/killer");
                ob->move(environment(me));
                message_vision(HIW "\nͻȻ�ܳ�һ����Ӱ����ݺݵĶ�$N"
                               HIW "�����" + RANK_D->query_rude(me)
                               + "�����������ɶ��\n" NOR, me);
                ob->kill_ob(me);
                return 0;
        }

        if( mapp(dq=query_temp("freequest", me)) && 
            dq[this_object()])
        {
                // �����ѯ�ʹ�������񣬴�ʱ�Ϳ��Ի�ý���
                map_delete(dq, this_object());

                GIFT_D->delay_bonus(me, ([ "exp"   : 100 + random(20),
                                           "pot"   : 30 + random(20),
                                           "score" : 5 + random(4),
                                           "prompt": "����Ѱ��" + QOB_NAME +
                                                     HIC "�Ĺ�����" ]));

                // ����Ϊ�����жϵ���������
                if( query("quest/freequest", me)>0 )
                        GIFT_D->delay_freequest_bonus(me);
        }
        return QOB;
}

// ѯ��NPC - ��Ҫ�ṩ��Ʒ����
string ask_npc(object knower, object me)
{
        mapping my = query_entire_dbase();

        if (! objectp(NPC_OB))
                return CYN "Ŷ����˵" HIY + NPC_NAME + NOR CYN
                       "��֪��ȥ�Ķ�ȥ�ˣ����ص�ʧ���ˡ�" NOR;

        return "��˵" + NPC_NAME + "�����һ�����������أ�";
}

// ѯ��QOB - �ṩ����Ʒ����Ϣ
string ask_qob(object knower, object me)
{
        mapping my = query_entire_dbase();
        mapping dq;
        object env;
        string exits;
        string *str;

        if (! objectp(QOB) || ! objectp(env = ENV_OB) && ! environment(QOB))
                return CYN "�ݿɿ�����Ϣ˵��" + QOB_NAME + CYN "��"
                       "��Ҳ�Ҳ����ˣ�����ôҲ�ǰ�æ���ˡ�" NOR;

        if (environment(QOB))
                return CYN "����˵�������Ѿ��ҵ�" + QOB_NAME +
                       CYN "�ˣ���������ô�Ͳ������أ�" NOR;

        if( query("score", me) >= 2000 )
        {
                if( !mapp(query("exits", env)) )
                        exits = "û�г���";
                else
                {
                        str=keys(query("exits", env));
                        str = map_array(str, (: GO_CMD->query_chinese_dir($1) :));
                        str -= ({ 0 });
                        exits = "��ž���" + implode(str, "��") + "����";
                }

                message("vision", WHT + knower->name() + "���˿����ܣ���������"
                                  "����" + me->name() + WHT "����˵��Щʲô��\n"
                                  NOR, environment(me), ({ me }));

                tell_object(me, sort_msg(knower->name() + "���˿���"
                            "�ܣ�����������������˵���������ǧ��"
                            "����߱���ѽ��������������������鱨��"
                            "�����Ҳ�ҪǮ�͸������ˣ���˵�Ǹ�������һ��" +
                            exits + "�ĵط�������������Ҳ����̫Զ�ء���"
                            "��������ϸ����û׼���з����أ���\n"));

                if( !mapp(dq=query_temp("freequest", me)) )
                        dq = ([ this_object() : 1 ]);
                else
                        dq[this_object()] = 1;

                set_temp("freequest", dq, me);
        } else
                message_vision(CYN "$N" CYN "�������µĴ�����$n" CYN "һ������"
                               "��¶��һ˿��м����̬��\n" NOR, knower, me);

        return CYN "��ʵ��˵��" HIY + QOB_NAME + NOR CYN
               "������ɶ���أ��ܱȵ��ϼ��Ⱥ;ƴ�ô��" NOR;
}

// �������
string query_introduce(object knower)
{
        mapping my = query_entire_dbase();

        if (! objectp(NPC))
        {
                remove_call_out("do_say");
                call_out("do_say", 1);
        }

        return CYN "��˵" + HIY + NPC_NAME + NOR CYN "��������Ѱ��" +
               HIY + QOB_NAME + NOR CYN "����������ϧ��Ҫ���ꡣ" NOR;
}

// ������ʾ
string query_prompt()
{
        switch (random(3))
        {
        case 0:
                return CYN "����������Ŀ���̸�����" HIY + name() +
                       NOR CYN "������";
        case 1:
                return "�ޣ�¥��ס����Ǽ������˸ղ�˵ʲô��" HIY + name() +
                       NOR CYN "���ء�";
        default:
                return "ǰ������������������ʿ��һ�����Ǹ��֣�"
                       "���ǻ�˵�����" HIY + name() + NOR CYN "���ء�";
        }
}

void do_say(object knower)
{
        if (! objectp(knower) || ! living(knower))
                return 0;

        message_vision(CYN "$N" CYN "���ʼ����������ͷ��¶�Ʋ��Ǻ��¡�"
                       "�㿴���ⲻ�����˰ɣ���\n" NOR, knower);
}

int npc_accept_object(object me, object who, object ob)
{
        mapping my = query_entire_dbase();
        mapping b;
        object reward;

        int exp;
        int pot;
        int score;
        int weiwang;

        if (ob->is_character() || ob->is_item_make())
                // ���������������ı���
                return 0;

        if (ob != QOB)
                return 0;

        if (me->is_fighting())
                return 0;

        if( base_name(environment(me)) != query("startroom", me) )
        {
                message_vision("$N����$n��һ���׳�ģ����\n", me, who);
                return -1;
        }

        message_sort(HIY "\n$N" HIY "�ӹ�" + ob->name() + HIY "��������ȥ��"
                     "�˿���ϲ����ʤ��һʱ���Ǽ�����֡����βŶ�$n" HIY "��"
                     "����λ" + RANK_D->query_respect(who) + "��ʵ���Ǹм�"
                     "���������С��˼�����Ц�ɣ�\n" NOR, me, who);

        message_vision(HIC "$N" HIC "����$n" HIC "һЩ" NOR + YEL "�ƽ�"
                       HIC "��Ϊ���ꡣ\n" NOR, me, who);

        reward = new("/clone/money/gold");
        reward->set_amount(1);
        reward->move(who, 1);

        // ����
        exp = 200 + random(200);
        pot = 150 + random(150);
        score = 15 + random(15);
        weiwang = 5 + random(5);

        b = ([ "exp"     : exp,
               "pot"     : pot,
               "score"   : score,
               "weiwang" : weiwang,
               "prompt"  : "��Ѱ��" + QOB_NAME + HIC
                           "�Ĺ����У���������" ]);
        GIFT_D->delay_bonus(who, b);

/*
        CHANNEL_D->do_channel(this_object(), "rumor",
                              "��˵" + who->name(1) +
                              "("+query("id", who)+
                              ")��" + me->name() + HIM +
                              "�ҵ���" + QOB_NAME + HIM
                              "���쵽��������" NOR);
*/

        destruct(ob);
        call_out("cancel_quest", 0);
        return -1;
}

// �ǼǸ��������Ϣ
void register_information()
{
        mapping my = query_entire_dbase();

        if (! clonep() || ! mapp(my))
                // �����������Բ��Ǽ�
                return;

        set_information(NPC_NAME, (: ask_npc :));
        set_information(NPC_ID,   (: ask_npc :));
        set_information(QOB_NAME, (: ask_qob :));
}

// ���������Ա�ĳ��ɢ����
int can_know_by(object knower)
{
        mapping my = query_entire_dbase();
        string fname;

        fname = file_name(environment(knower));
        if (! stringp(ZONE) || strlen(ZONE) < 1 ||
            ZONE == fname[0..strlen(ZONE) - 1])
                // ��С����ͬһ������
                return 1;

        return 0;
}