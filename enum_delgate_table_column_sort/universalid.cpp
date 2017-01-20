#include "universalid.hpp"

#include <ostream>
#include <stdexcept>
#include <sstream>
#include <iostream>

namespace
{
    struct TypeData
    {
            UniversalId::Class mClass;
            UniversalId::Type mType;
            const char *mName;
            const char *mIcon;
    };

    static const TypeData sNoArg[] = {
        {UniversalId::Class_None, UniversalId::Type_None, "-", NULL},
        {UniversalId::Class_RecordList, UniversalId::Type_Globals, "Global Variables",
         NULL},
        {UniversalId::Class_RecordList, UniversalId::Type_Gmsts, "Game Settings", NULL},
        {UniversalId::Class_RecordList, UniversalId::Type_Skills, "Skills", NULL},
        {UniversalId::Class_RecordList, UniversalId::Type_Classes, "Classes", NULL},
        {UniversalId::Class_RecordList, UniversalId::Type_Factions, "Factions", NULL},
        {UniversalId::Class_RecordList, UniversalId::Type_Races, "Races", NULL},
        {UniversalId::Class_RecordList, UniversalId::Type_Sounds, "Sounds", NULL},
        {UniversalId::Class_RecordList, UniversalId::Type_Scripts, "Scripts", NULL},
        {UniversalId::Class_RecordList, UniversalId::Type_Regions, "Regions", NULL},
        {UniversalId::Class_RecordList, UniversalId::Type_Birthsigns, "Birthsigns", NULL},
        {UniversalId::Class_RecordList, UniversalId::Type_Spells, "Spells", NULL},
        {UniversalId::Class_RecordList, UniversalId::Type_Topics, "Topics", NULL},
        {UniversalId::Class_RecordList, UniversalId::Type_Journals, "Journals", NULL},
        {UniversalId::Class_RecordList, UniversalId::Type_TopicInfos, "Topic Infos",
         NULL},
        {UniversalId::Class_RecordList, UniversalId::Type_JournalInfos, "Journal Infos",
         NULL},
        {UniversalId::Class_RecordList, UniversalId::Type_Cells, "Cells", NULL},
        {UniversalId::Class_RecordList, UniversalId::Type_Enchantments, "Enchantments",
         NULL},
        {UniversalId::Class_RecordList, UniversalId::Type_BodyParts, "Body Parts", NULL},
        {UniversalId::Class_RecordList, UniversalId::Type_Referenceables, "Objects",
         NULL},
        {UniversalId::Class_RecordList, UniversalId::Type_References, "Instances", NULL},
        {UniversalId::Class_NonRecord, UniversalId::Type_RegionMap, "Region Map", NULL},
        {UniversalId::Class_RecordList, UniversalId::Type_Filters, "Filters", NULL},
        {UniversalId::Class_ResourceList, UniversalId::Type_Meshes, "Meshes", NULL},
        {UniversalId::Class_ResourceList, UniversalId::Type_Icons, "Icons", NULL},
        {UniversalId::Class_ResourceList, UniversalId::Type_Musics, "Music Files", NULL},
        {UniversalId::Class_ResourceList, UniversalId::Type_SoundsRes, "Sound Files",
         NULL},
        {UniversalId::Class_ResourceList, UniversalId::Type_Textures, "Textures", NULL},
        {UniversalId::Class_ResourceList, UniversalId::Type_Videos, "Videos", NULL},
        {UniversalId::Class_RecordList, UniversalId::Type_DebugProfiles, "Debug Profiles",
         NULL},
        {UniversalId::Class_Transient, UniversalId::Type_RunLog, "Run Log", NULL},
        {UniversalId::Class_RecordList, UniversalId::Type_SoundGens, "Sound Generators",
         NULL},
        {UniversalId::Class_RecordList, UniversalId::Type_MagicEffects, "Magic Effects",
         NULL},
        {UniversalId::Class_RecordList, UniversalId::Type_Pathgrids, "Pathgrids", NULL},
        {UniversalId::Class_RecordList, UniversalId::Type_StartScripts, "Start Scripts",
         NULL},
        {UniversalId::Class_RecordList, UniversalId::Type_MetaDatas, "Meta Data Table",
         NULL},

        {UniversalId::Class_None, UniversalId::Type_None, NULL, NULL}  // end marker
    };

    static const TypeData sIdArg[] = {
        {UniversalId::Class_Record, UniversalId::Type_Global, "Global Variable",
         ":./globvar.png"},
        {UniversalId::Class_Record, UniversalId::Type_Gmst, "Game Setting",
         ":./GMST.png"},
        {UniversalId::Class_Record, UniversalId::Type_Skill, "Skill", ":./skill.png"},
        {UniversalId::Class_Record, UniversalId::Type_Class, "Class", ":./class.png"},
        {UniversalId::Class_Record, UniversalId::Type_Faction, "Faction",
         ":./faction.png"},
        {UniversalId::Class_Record, UniversalId::Type_Race, "Race", ":./race.png"},
        {UniversalId::Class_Record, UniversalId::Type_Sound, "Sound", ":./sound.png"},
        {UniversalId::Class_Record, UniversalId::Type_Script, "Script", ":./script.png"},
        {UniversalId::Class_Record, UniversalId::Type_Region, "Region", ":./land.png"},
        {UniversalId::Class_Record, UniversalId::Type_Birthsign, "Birthsign",
         ":./birthsign.png"},
        {UniversalId::Class_Record, UniversalId::Type_Spell, "Spell", ":./spell.png"},
        {UniversalId::Class_Record, UniversalId::Type_Topic, "Topic", NULL},
        {UniversalId::Class_Record, UniversalId::Type_Journal, "Journal", NULL},
        {UniversalId::Class_SubRecord, UniversalId::Type_TopicInfo, "TopicInfo", NULL},
        {UniversalId::Class_SubRecord, UniversalId::Type_JournalInfo, "JournalInfo",
         NULL},
        {UniversalId::Class_Record, UniversalId::Type_Cell, "Cell", ":./cell.png"},
        {UniversalId::Class_Record, UniversalId::Type_Cell_Missing, "Cell",
         ":./cell.png"},
        {UniversalId::Class_Record, UniversalId::Type_Referenceable, "Object", NULL},
        {UniversalId::Class_RefRecord, UniversalId::Type_Activator, "Activator",
         ":./activator.png"},
        {UniversalId::Class_RefRecord, UniversalId::Type_Potion, "Potion",
         ":./potion.png"},
        {UniversalId::Class_RefRecord, UniversalId::Type_Apparatus, "Apparatus",
         ":./apparatus.png"},
        {UniversalId::Class_RefRecord, UniversalId::Type_Armor, "Armor", ":./armor.png"},
        {UniversalId::Class_RefRecord, UniversalId::Type_Book, "Book", ":./book.png"},
        {UniversalId::Class_RefRecord, UniversalId::Type_Clothing, "Clothing",
         ":./clothing.png"},
        {UniversalId::Class_RefRecord, UniversalId::Type_Container, "Container",
         ":./container.png"},
        {UniversalId::Class_RefRecord, UniversalId::Type_Creature, "Creature",
         ":./creature.png"},
        {UniversalId::Class_RefRecord, UniversalId::Type_Door, "Door", ":./door.png"},
        {UniversalId::Class_RefRecord, UniversalId::Type_Ingredient, "Ingredient",
         ":./ingredient.png"},
        {UniversalId::Class_RefRecord, UniversalId::Type_CreatureLevelledList,
         "Creature Levelled List", ":./creature.png"},
        {UniversalId::Class_RefRecord, UniversalId::Type_ItemLevelledList,
         "Item Levelled List", ":./leveled-item.png"},
        {UniversalId::Class_RefRecord, UniversalId::Type_Light, "Light", ":./light.png"},
        {UniversalId::Class_RefRecord, UniversalId::Type_Lockpick, "Lockpick",
         ":./lockpick.png"},
        {UniversalId::Class_RefRecord, UniversalId::Type_Miscellaneous, "Miscellaneous",
         ":./miscellaneous.png"},
        {UniversalId::Class_RefRecord, UniversalId::Type_Npc, "NPC", ":./npc.png"},
        {UniversalId::Class_RefRecord, UniversalId::Type_Probe, "Probe", ":./probe.png"},
        {UniversalId::Class_RefRecord, UniversalId::Type_Repair, "Repair",
         ":./repair.png"},
        {UniversalId::Class_RefRecord, UniversalId::Type_Static, "Static",
         ":./static.png"},
        {UniversalId::Class_RefRecord, UniversalId::Type_Weapon, "Weapon",
         ":./weapon.png"},
        {UniversalId::Class_SubRecord, UniversalId::Type_Reference, "Instance", NULL},
        {UniversalId::Class_Record, UniversalId::Type_Filter, "Filter", ":./filter.png"},
        {UniversalId::Class_Collection, UniversalId::Type_Scene, "Scene", NULL},
        {UniversalId::Class_Collection, UniversalId::Type_Preview, "Preview", NULL},
        {UniversalId::Class_Record, UniversalId::Type_Enchantment, "Enchantment", NULL},
        {UniversalId::Class_Record, UniversalId::Type_BodyPart, "Body Part", NULL},
        {UniversalId::Class_Resource, UniversalId::Type_Mesh, "Mesh", NULL},
        {UniversalId::Class_Resource, UniversalId::Type_Icon, "Icon", NULL},
        {UniversalId::Class_Resource, UniversalId::Type_Music, "Music", NULL},
        {UniversalId::Class_Resource, UniversalId::Type_SoundRes, "Sound File", NULL},
        {UniversalId::Class_Resource, UniversalId::Type_Texture, "Texture", NULL},
        {UniversalId::Class_Resource, UniversalId::Type_Video, "Video", NULL},
        {UniversalId::Class_Record, UniversalId::Type_DebugProfile, "Debug Profile",
         NULL},
        {UniversalId::Class_Record, UniversalId::Type_SoundGen, "Sound Generator", NULL},
        {UniversalId::Class_Record, UniversalId::Type_MagicEffect, "Magic Effect", NULL},
        {UniversalId::Class_Record, UniversalId::Type_Pathgrid, "Pathgrid", NULL},
        {UniversalId::Class_Record, UniversalId::Type_StartScript, "Start Script", NULL},
        {UniversalId::Class_Record, UniversalId::Type_MetaData, "Meta Data", NULL},

        {UniversalId::Class_None, UniversalId::Type_None, NULL, NULL}  // end marker
    };

    static const TypeData sIndexArg[] = {
        {UniversalId::Class_Transient, UniversalId::Type_VerificationResults,
         "Verification Results", NULL},
        {UniversalId::Class_Transient, UniversalId::Type_LoadErrorLog, "Load Error Log",
         NULL},
        {UniversalId::Class_Transient, UniversalId::Type_Search, "Global Search", NULL},
        {UniversalId::Class_None, UniversalId::Type_None, NULL, NULL}  // end marker
    };
}

UniversalId::UniversalId (const std::string& universalId)
: mIndex(0)
{
    std::string::size_type index = universalId.find (':');

    if (index!=std::string::npos)
    {
        std::string type = universalId.substr (0, index);

        for (int i=0; sIdArg[i].mName; ++i)
            if (type==sIdArg[i].mName)
            {
                mArgumentType = ArgumentType_Id;
                mType = sIdArg[i].mType;
                mClass = sIdArg[i].mClass;
                mId = universalId.substr (index+2);
                return;
            }

        for (int i=0; sIndexArg[i].mName; ++i)
            if (type==sIndexArg[i].mName)
            {
                mArgumentType = ArgumentType_Index;
                mType = sIndexArg[i].mType;
                mClass = sIndexArg[i].mClass;

                std::istringstream stream (universalId.substr (index+2));

                if (stream >> mIndex)
                    return;

                break;
            }
    }
    else
    {
        for (int i=0; sNoArg[i].mName; ++i)
            if (universalId==sNoArg[i].mName)
            {
                mArgumentType = ArgumentType_None;
                mType = sNoArg[i].mType;
                mClass = sNoArg[i].mClass;
                return;
            }
    }

    throw std::runtime_error ("invalid UniversalId: " + universalId);
}

UniversalId::UniversalId (Type type) : mArgumentType (ArgumentType_None), mType (type), mIndex (0)
{
    for (int i=0; sNoArg[i].mName; ++i)
        if (type==sNoArg[i].mType)
        {
            mClass = sNoArg[i].mClass;
            return;
        }

    for (int i=0; sIdArg[i].mName; ++i)
        if (type==sIdArg[i].mType)
        {
            mArgumentType = ArgumentType_Id;
            mClass = sIdArg[i].mClass;
            return;
        }

    for (int i=0; sIndexArg[i].mName; ++i)
        if (type==sIndexArg[i].mType)
        {
            mArgumentType = ArgumentType_Index;
            mClass = sIndexArg[i].mClass;
            return;
        }

    throw std::logic_error ("invalid argument-less UniversalId type");
}

UniversalId::UniversalId (Type type, const std::string& id)
: mArgumentType (ArgumentType_Id), mType (type), mId (id), mIndex (0)
{
    for (int i=0; sIdArg[i].mName; ++i)
        if (type==sIdArg[i].mType)
        {
            mClass = sIdArg[i].mClass;
            return;
        }
    throw std::logic_error ("invalid ID argument UniversalId type");
}

UniversalId::UniversalId (Type type, int index)
: mArgumentType (ArgumentType_Index), mType (type), mIndex (index)
{
    for (int i=0; sIndexArg[i].mName; ++i)
        if (type==sIndexArg[i].mType)
        {
            mClass = sIndexArg[i].mClass;
            return;
        }

    throw std::logic_error ("invalid index argument UniversalId type");
}

UniversalId::Class UniversalId::getClass() const
{
    return mClass;
}

UniversalId::ArgumentType UniversalId::getArgumentType() const
{
    return mArgumentType;
}

UniversalId::Type UniversalId::getType() const
{
    return mType;
}

const std::string& UniversalId::getId() const
{
    if (mArgumentType!=ArgumentType_Id)
        throw std::logic_error ("invalid access to ID of non-ID UniversalId");

    return mId;
}

int UniversalId::getIndex() const
{
    if (mArgumentType!=ArgumentType_Index)
        throw std::logic_error ("invalid access to index of non-index UniversalId");

    return mIndex;
}

bool UniversalId::isEqual (const UniversalId& universalId) const
{
    if (mClass!=universalId.mClass || mArgumentType!=universalId.mArgumentType || mType!=universalId.mType)
            return false;

    switch (mArgumentType)
    {
        case ArgumentType_Id: return mId==universalId.mId;
        case ArgumentType_Index: return mIndex==universalId.mIndex;

        default: return true;
    }
}

bool UniversalId::isLess (const UniversalId& universalId) const
{
    if (mType<universalId.mType)
        return true;

    if (mType>universalId.mType)
        return false;

    switch (mArgumentType)
    {
        case ArgumentType_Id: return mId<universalId.mId;
        case ArgumentType_Index: return mIndex<universalId.mIndex;

        default: return false;
    }
}

std::string UniversalId::getTypeName() const
{
    const TypeData *typeData = mArgumentType==ArgumentType_None ? sNoArg :
        (mArgumentType==ArgumentType_Id ? sIdArg : sIndexArg);

    for (int i=0; typeData[i].mName; ++i)
        if (typeData[i].mType==mType)
            return typeData[i].mName;

    throw std::logic_error ("failed to retrieve UniversalId type name");
}

std::string UniversalId::toString() const
{
    std::ostringstream stream;

    stream << getTypeName();

    switch (mArgumentType)
    {
        case ArgumentType_None: break;
        case ArgumentType_Id: stream << ": " << mId; break;
        case ArgumentType_Index: stream << ": " << mIndex; break;
    }

    return stream.str();
}

std::string UniversalId::getIcon() const
{
    const TypeData *typeData = mArgumentType==ArgumentType_None ? sNoArg :
        (mArgumentType==ArgumentType_Id ? sIdArg : sIndexArg);

    for (int i=0; typeData[i].mName; ++i)
        if (typeData[i].mType==mType)
            return typeData[i].mIcon ? typeData[i].mIcon : ":placeholder";

    throw std::logic_error ("failed to retrieve UniversalId type icon");
}

std::vector<UniversalId::Type> UniversalId::listReferenceableTypes()
{
    std::vector<UniversalId::Type> list;

    for (int i=0; sIdArg[i].mName; ++i)
        if (sIdArg[i].mClass==Class_RefRecord)
            list.push_back (sIdArg[i].mType);

    return list;
}

std::vector<UniversalId::Type> UniversalId::listTypes (int classes)
{
    std::vector<UniversalId::Type> list;

    for (int i=0; sNoArg[i].mName; ++i)
        if (sNoArg[i].mClass & classes)
            list.push_back (sNoArg[i].mType);

    for (int i=0; sIdArg[i].mName; ++i)
        if (sIdArg[i].mClass & classes)
            list.push_back (sIdArg[i].mType);

    for (int i=0; sIndexArg[i].mName; ++i)
        if (sIndexArg[i].mClass & classes)
            list.push_back (sIndexArg[i].mType);
            
    return list;    
}

UniversalId::Type UniversalId::getParentType (Type type)
{
    for (int i=0; sIdArg[i].mType; ++i)
        if (type==sIdArg[i].mType)
        {
            if (sIdArg[i].mClass==Class_RefRecord)
                return Type_Referenceables;

            if (sIdArg[i].mClass==Class_SubRecord || sIdArg[i].mClass==Class_Record ||
                sIdArg[i].mClass==Class_Resource)
            {
                if (type==Type_Cell_Missing)
                    return Type_Cells;

                return static_cast<Type> (type-1);
            }

            break;
        }

    return Type_None;
}

UniversalId::operator std::string() const { return getTypeName(); }

bool operator== (const UniversalId& left, const UniversalId& right)
{
    return left.isEqual (right);
}

bool operator!= (const UniversalId& left, const UniversalId& right)
{
    return !left.isEqual (right);
}

bool operator< (const UniversalId& left, const UniversalId& right)
{
    return left.isLess (right);
}

std::ostream& operator<< (std::ostream& stream, const UniversalId& universalId)
{
    return stream << universalId.toString();
}
