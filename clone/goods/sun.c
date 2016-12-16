// This program is a part of NT MudLIB
// sun.c �ջ�

#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(RED "�ջ�" NOR, ({ "sun soul", "sun" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", RED "̫��������۶��ɣ��ڽ�ɫ������а��ħ��ǧ�����ס���\n" NOR);
                set("value", 50000);
                set("unit", "��");
                set("can_enchant", "weapon");
                set("auto_load", 1);
        }
        setup();
}

int do_extract(object obj)
{
        mapping enchase_prop;
        mapping applied_prop;
        mapping ins;
        string *apply, *key;
        string type, enc;
        object ob;
        mixed res;
        int i;

        ob = this_object();

        if( !obj ) return notify_fail("û�������Ʒ��\n");

        if( query("enchase", ob) )
                return notify_fail("�ջ��Ѿ���ħ�������ˡ�\n");

        if( !query("enchase", obj) || !(applied_prop=query("enchase/apply_prop", obj)) )
                return notify_fail("�����Ʒ����û�п�������ħ�����ԡ�\n");

        if( obj->is_item_make() || !(ins=copy(query("insert", obj))) )
                return notify_fail("�����Ʒ�޷�������ħ�����ԡ�\n");

        if( !query("skill_type", obj) && query("armor_type", obj) != "hands" && query("armor_type", obj) != "finger" )
                return notify_fail("�ջ�ֻ��������ħ��������Ʒ�����ԡ�\n");

        if( random(100) < 20 )
                return notify_fail("��ħʧ�ܡ�\n");
        
        key = keys(ins);
        enc = key[random(sizeof(key))];
        res = copy(ins[enc]);
        map_delete(ins, enc);

        enchase_prop = res["apply_prop"];
        if( !mapp(enchase_prop) )
                return notify_fail("��ħʧ�ܡ�\n");

        set("insert", ins, obj);
        apply = keys(enchase_prop);
        for( i=0; i<sizeof(apply); i++ )
        {
                if( undefinedp(applied_prop[apply[i]]) )
                        continue;
                else
                {
                        applied_prop[apply[i]] -= enchase_prop[apply[i]];
                        if( applied_prop[apply[i]] < 1 )
                                map_delete(applied_prop, apply[i]);
                }
        }

        if( !sizeof(applied_prop) )
                delete("enchase/apply_prop", obj);
        else
                set("enchase/apply_prop", applied_prop, obj);

        if( query("skill_type", obj))type=query("skill_type", obj);
        else type=query("armor_type", obj);

        set("enchase/weapon_prop", enchase_prop, ob);
        set("enchase/type", type, ob);
        set("enchase/SN", 1+random(9), ob);
        set("enchase/level",query("require/level",  obj), ob);
        set("enchant", 1, ob);
        set("set_data", 1, ob);

        return 1;
}