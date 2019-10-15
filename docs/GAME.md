# Game Design Notes

This file contains all design choices for the game logic and gameplay portion of the project. Segments marked `DEV` are in development and are not finalized.

## Game Logic

### Entity-Component-System (ECS) `DEV`

ECS is a architectural pattern that follows a "composition over inheritance" principle.

#### Entity 

A general purpose object identified by a unique id. Every entity type should have its own set of unique identifiers.

#### Component

Raw data to describe an aspect of the object. Typically implemented using a struct or class.

#### System

Each system runs continuously and performs global actions on every entity that possesses a Component of the same type.

Note: Possibility of implementing multi-threading here.

## Gameplay

### Combat `DEV`

I'm feeling ARPG zelda style but with more combat options.

### Stats `DEV`

Each statistic should have equal beneficial impact on gameplay. There should not be a statistic that does not directly impact play style. My suggestion for stats:

`CON Constitution` -> Affects unit's total HP.
`DEF Defense` -> Affects damage calculation on incoming physical damage.
`STR Strength` -> Affects damage calculation on outoging physical damage. 
`MAG Magic` -> Affects damage calculation on outgoing magical damage.
`RES Resistance` -> Affects damage calculation on incoming magical damage.
`SPD Speed` -> Affects unit's avoidance and movement.
`LCK Luck` -> Affects unit's critical hit rate.

### Jobs and Classes `DEV`

~~The idea of classes should not be based around what weapons they use but rather their statistics and abilities. All classes should be able to wield all weapons but their statistics should force specific classes to benefit from the use of specific weapons.

Classes should be able to progress tiers based on stats not level. This should be achieved by using specific weapon types.

Notes:
- Classes should provide unique abilities
- There should also be some sort of multiclassing mechanic. A way of blending together abilities to create new and unique abilities/strategies.

Each tier of class should introduce an element of gameplay strategy. I propose the following idea for tiers (Come up with cool names later):

*Trainee*: There should only be one trainee class that has basic stats across the board. This should essentially be a blank slate for the player to project themselves onto.

*Novice*: There should be one novice class per stat type. This should be a class that is unlocked based on stat levels but gives some form of proficiency bonus for using that weapon.

*Advanced*: There should be 2 classes per novice class at this level, however novice classes within the same weapons triangle should share two classes to allow class mobility. The advanced class should not be weapons based but rather statistic or gameplay based.~~

#### Jobs

Jobs define what weapon a unit can use. A unit can only equip one primary job and one secondary job at a time to provide balanced and customizable choice of weapons.

Possible list of jobs:
- Swordmaster `SWORD`
- Lancer `LANCE`
- Axeman `AXE`
- Archer `BOW`
- Mage `ELEMENTAL`
- Priest `HOLY`
- Shaman `DARK`

#### Classes

Classes define what stats the unit gains benefits and detriments to. I want to build in some sort of "mix and match" functionslity into this system.

Possible list of classes:
- Warrior - A physical tank `+CON +DEF -RES`
- Knight - A one-man fortress `+CON +RES -ATK`
- Assasin - Fast and lethal `+ATK +SPD -DEF`
- Myrmidon - Strong and lucky `+ATK +LCK -CON`
- Fighter - Master of melee `+ATK +DEF -RES`
- Wizard - Master of magic `+MAG +RES -DEF`
- Sorcerer - Quick spellcaster `+MAG +SPD -CON`
- Mageknight - A spellsword `+MAG +ATK -SPD`
- Ranger - Speedy and evasive `+SPD +LCK -DEF`

### Weapons `DEV`

Weapon types are as follows:
- Sword - Balanced weapon speed and damage 
- Lance - Fast weapon speed
- Axe - High damage output
- Bow - Provides range, what else do you want?
- Elemental - Higher damage. Fire, Lightning, Ice
- Holy - Self-buffs, healing, etc
- Shadow - De-buffs, bleeding damage, etc

#### Weapon Triangles `DEV`

The basis of the type effectiveness is based around a needlessy complex triangle system that I think is really cool.

~~Essentially `Ranged` beats `Melee` beats `Magic`. But within those types:

`Sword` beats `Axe` beats `Lance`
`Elemental` beats `Holy` beats `Shadow`
`Bow` beats `Hand-Thrown` beats `Something`~~

The more I look at it the more Fire Emblem's weapon effectiveness choices make sense.

I think the `Melee` and `Magic` triangles make sense but `Bow` should be in their own category. Like an auxillary weapon that isn't a main focus.


