//***************************************************************************************************
// Project:		SpongeBob Squarepants GBA.
// Source:		All Game Includes (Header).
// Author:		A.R.Cummings.
// (C) 2000/1:	Climax.
//***************************************************************************************************

#ifndef _INCLUDES_H
#define _INCLUDES_H

#include <Agb.h>
#include <stdio.h>

#include "Main.h"
#include "Game.h"

// compilier triggers
#define MUSIC_ON
#define BEANER

//sound
#include "../Sound/out/m4aLib.h"

//music
#define SBP_CHAP_1_LEVEL_1	(0)
#define SBP_CHAP_1_LEVEL_3	(1)
#define SBP_CHAP_1_LEVEL_4	(2)
#define SBP_CHAP_1_BOSS   	(3)
#define SBP_CHAP_2_LEVEL_1	(4)
#define SBP_CHAP_2_LEVEL_2	(5)
#define SBP_CHAP_2_LEVEL_4 	(6)
#define SBP_CHAP_2_BOSS         (7)
#define SBP_CHAP_3_LEVEL_1      (8)
#define SBP_CHAP_3_LEVEL_2      (9)
#define SBP_CHAP_3_LEVEL_4      (10)
#define SBP_CHAP_3_BOSS_1       (11)
#define SBP_CHAP_3_BOSS_2       (12)
#define SBP_CHAP_4_LEVEL_1      (13)
#define SBP_CHAP_4_LEVEL_2      (14)
#define SBP_CHAP_4_LEVEL_3      (15)
#define SBP_CHAP_4_BOSS         (16)
#define SBP_CHAP_5_LEVEL_1      (17)
#define SBP_CHAP_5_LEVEL_2      (18)
#define SBP_CHAP_5_LEVEL_4      (19)
#define SBP_CHAP_5_BOSS         (20)
#define SBP_CHAP_6_LEVEL_BT     (21)
#define SBP_CHAP_6_LEVEL_G      (22)
#define SBP_CHAP_6_LEVEL_RS     (23)
#define SBP_CHAP_6_LEVEL_TOP    (24)
#define SBP_GAMEOVER            (25)
#define SBP_OPTIONS             (26)
#define SBP_TITLEMUSIC          (27)

//sound effects
#define SFX_SPONGEBOB_WALK_1				(28)
#define SFX_SPONGEBOB_WALK_2                                        (29)
#define SFX_SPONGEBOB_SQUEAKY_SHOES_1                               (30)
#define SFX_SPONGEBOB_SQUEAKY_SHOES_2                               (31)
#define SFX_SPONGEBOB_JUMP                                          (32)
#define SFX_SPONGEBOB_BUTTBOUNCE                                  (33)
#define SFX_SPONGEBOB_BLINK                                         (34)
#define SFX_BUBBLE_WAND                                           (35)
#define SFX_SPONGEBOB_DEFEATED_JINGLE                               (36)
#define SFX_BALLOON_INFLATE                                         (37)
#define SFX_GLASSES_ON                                              (38)
#define SFX_JELLY_LAUNCHER                                          (39)
#define SFX_SPONGEBOB_KARATE                                        (40)
#define SFX_SPONGEBOB_ATTACK_IMPACT_WITH_ENEMY                     (41)
#define SFX_SPONGEBOB_LAND_AFTER_FALL                               (42)
#define SFX_SPONGEBOB_NET                                           (43)
#define SFX_ANEMONE_ATTACK_LEVEL1                                 (44)
#define SFX_ANEMONE_ATTACK_LEVEL3                                 (45)
#define SFX_ANEMONE_DEFEATED_BALLOON POP                 (46)
#define SFX_BALL_BLOB_MOVE                                          (47)
#define SFX_BALL_BLOB_ATTACK                                        (48)
#define SFX_BEANIE_FALL                                             (49)
#define SFX_BOOGER_APPEAR                                           (50)
#define SFX_CLAM_EAT_SOUND                           (51)
#define SFX_CLAM_DEFEATED                                           (52)
#define SFX_CLAM_MOVE                                               (53)
#define SFX_EYEBALL_SENTRY_ATTACK                                 (54)
#define SFX_FISH_HOOK_MOVE                                          (55)
#define SFX_FLAMING_SKULL_MOVE                                    (56)
#define SFX_FLAMING_SKULL_DEFEATED                                  (57)
#define SFX_ZOMBIE_FISH_FOLK                                        (58)
#define SFX_CANNING_MACHINE                                         (59)
#define SFX_LAVA                                                  (60)
#define SFX_ROLLING_ROCK                                            (61)
#define SFX_SAW                                                     (62)
#define SFX_WHIRLPOOL_DRAIN                                       (63)
#define SFX_WHIRLPOOL_WHIRL                                       (64)
#define SFX_HERMIT_CRAB_ATTACK                                      (65)
#define SFX_SPIDER_CRAB_MOVE                                        (66)
#define SFX_HERMIT_CRAB_MOVE                                        (67)
#define SFX_HAZARD_ACID_DROP                                    (68)
#define SFX_HAZARD_ACORN_LAND                                   (69)
#define SFX_HAZARD_BLADE_ATTACK_BABY_OCTOPUS_ATTACK		     (70)
#define SFX_HAZARD_BLADE_MOVE                      		     (71)
#define SFX_HAZARD_ROPE_MOVE                       		       (72)
#define SFX_HAZARD_ROPE_SNAP                       		     (73)
#define SFX_ANY_OBJECT_FALLING                     		         (74)
#define SFX_HAZARD_FIREBALL_LAND                   		     (75)
#define SFX_HAZARD_FIREBALL_LAUNCH                 		     (76)
#define SFX_HAZARD_FALLING_ROCK_FALL               		     (77)
#define SFX_HAZARD_FALLING_ROCK_LAND               		     (78)
#define SFX_HAZARD_MINE                            		       (79)
#define SFX_SPONGEBOB_SPLASH_INTO_WATER            		         (80)
#define SFX_SPONGEBOB_DIVING_HELMET                		         (81)
#define SFX_HAZARD_STALACTITE_LAND                 		       (82)
#define SFX_HAZARD_STALACTITE_RATTLE               		       (83)
#define SFX_HAZARD_STEAM                           		     (84)
#define SFX_BABY_OCTOPUS_APPEAR_DISAPPEAR          		         (85)
#define SFX_ITEM_CORAL_BLOWER                      		     (86)
#define SFX_ITEM_DISGUISE                          		       (87)
#define SFX_ITEM_JAMJAR_AMMO                       		       (88)
#define SFX_ITEM_LEVEL_ITEM                        		     (89)
#define SFX_ITEM_ANY_OTHER_ITEM                    		       (90)
#define SFX_ITEM_POWER_UP_ITEM                     		     (91)
#define SFX_ITEM_SKILL_ITEM                        		     (92)
#define SFX_JELLYFISH_MOVE                         		         (93)
#define SFX_GENERIC_ENEMY_DEFEATED                 		         (94)
#define SFX_JELLYFISH_ATTACK                       		       (95)
#define SFX_NAUTILUS_ATTACK							(96)
#define SFX_NAUTILUS_MOVE                          		         (97)
#define SFX_NINJASTARFISH_ATTACK_SQUIDDART_ATTACK  		       (98)
#define SFX_NINJASTARFISH_STICK_TO_PLAYER          		         (99)
#define SFX_PRICKLY_BUG_MOVE                       		        (100)
#define SFX_PUFFAFISH_MOVE_GENERIC_FISH_SWIM       		(101)
#define SFX_SKULL_ATTACK                           		      (102)
#define SFX_SEASNAKE_ATTACK                        		        (103)
#define SFX_SEASNAKE_MOVE                          		        (104)
#define SFX_TELEPHONE_BOX                          		        (105)
#define SFX_WORLD_OBJECT_BARRIER_SMASH             		      (106)
#define SFX_WORLD_OBJECT_BIG_WHEEL                 		    (107)
#define SFX_WORLD_OBJECT_GEYSER                    		    (108)
#define SFX_WORLD_OBJECT_GHOST_TRAIN_DOORS         		    (109)
#define SFX_WORLD_OBJECT_DISAPPEARING_PLATFORM     		      (110)
#define SFX_WORLD_OBJECT_RE_SPAWNING_PLATFORM      		      (111)
#define SFX_WORLD_OBJECT_ROTATING_PLATFORM         		      (112)
#define SFX_WORLD_OBJECT_SEESAW                    		      (113)
#define SFX_WORLD_OBJECT_TRAIN_TRACKS              		      (114)
#define SFX_WORLD_OBJECT_CURRENTS                  		      (115)
#define SFX_FRONT_END_MOVE CURSOR                  		      (116)
#define SFX_FRONT_END_SELECT                       		      (117)
#define SFX_FRONT_END_ERROR                        		      (118)
#define SFX_FRONT_END_OK                           		      (119)

extern SoundArea sound;
extern MusicPlayerArea music;
extern MusicPlayerArea phrase;
extern MusicPlayerTrack track[8];
extern int maxchn;
extern SongHeader *demosong[43];

#define SoundInit(P1)   SoundDriverInit(P1)
#define SoundMode(P1)   SoundDriverMode(P1)
#define SoundMain()     SoundDriverMain()
#define SoundVSync()    SoundDriverVSync()
#define SoundClearAll() SoundChannelClear()
#define MidiKey2fr(P1,P2,P3)    MidiKey2Freq(P1,P2,P3)

#define MPlayOpen(P1,P2,P3)     MusicPlayerOpen(P1,P2,P3)
#define MPlayStart(P1,P2)       MusicPlayerStart(P1,P2)
#define MPlayStop(P1)           MusicPlayerStop(P1)
#define MPlayContinue(P1)       MusicPlayerContinue(P1)
#define MPlayFadeOut(P1,P2)     MusicPlayerFadeOut(P1,P2)

//LANGUAGE VERSIONS

// note only uncomment one of these or it will be fucked...
#define ENGLISH
#define AMERICAN
//#define GERMAN
//#define FRENCH
//#define SPANISH							 

#endif

//***************************************************************************************************