
#include <armor.h>
#include <self.h>

inherit ARMOR;

void create(class data)
{
        set_name("甲", ({ "armor", }));

        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", "这是一件普通的护甲。\n");
                set("unit", "件");
                set("value", 200);
                set("material", "cloth");
                set("armor_prop/armor", query("point")*2);
        }

        set_weight(500);
        setup();
}

// 武器装备的伤害值
int apply_damage()
{
        int d;
        int p;

        attack_lvl = weapon_level();
        p = query("point");
        d = attack_lvl * p / MAX_LEVEL + query("bless") * 10; // 乾坤圣水圣化一次增加十点攻击
        return d + p;
}

// 防御装备的有效值
int apply_armor()
{
        int d;
        int p;

        defense_lvl = armor_level();
        p = query("point");
        // if( d > p * 3 / 2) d = p * 3 / 2 + query("bless") * 10;// 乾坤圣水圣化一次增加10点防御
        d = p * 3 / 2 + query("bless") * 2;// 乾坤圣水圣化一次增加2点防御
        return d + p;
}

#include <ansi.h>
#include <armor.h>

inherit ARMOR;

void create()
{
        set_name("金丝甲", ({ "aarmor" }));
        set_weight(9000);
        set("item_make", 1);
        set("unit", "张");
        set("long", "这是由神铁炼制而成的一张护甲。
护甲缘上刻着一行小字：胡大一(adami)
");
        set("value", 2100000);
        set("point", 152);
        set("material", "magic stone");
        set("material_file", "ddd");
        set("wear_msg", "$N装备金丝甲。\n");
        set("remove_msg", "$N脱下了金丝甲。\n");
        set("armor_prop/armor", apply_armor());

        setup();
}

string long() { return query("long") + item_long(); }


#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
        set_name("白虹剑", ({ "asword" }));
        set_weight(9000);
        set("item_make", 1);
        set("unit", "柄");
        set("long", "这是由神铁炼制而成的一柄剑。
剑柄上刻着一行小字：胡大一(adami)
");
        set("value", 2100000);
        set("point", 190);
        set("material", "magic stone");
        set("wield_msg", "$N「唰」的一声抽出一柄寒光闪闪的$n握在手中。\n");
        set("unwield_msg", "$N将手中的$n插回剑鞘。\n");

        init_sword(apply_damage());

        setup();
}

string long() { return query("long") + item_long(); }
