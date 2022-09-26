//
// Created by Perfare on 2020/7/4.
//

#ifndef RIRU_IL2CPPDUMPER_GAME_H
#define RIRU_IL2CPPDUMPER_GAME_H

// Try increase sleep time if having issues with the game. Decrease sleep time if anti-cheat detection it earlier
#define Sleep 3

// Uncomment for fake lib mode
// It is to load our fake libunity.so and load game's real librealunity.so
#define UseFakeLib

// Target renamed lib
#define RealLibToLoad "librealmain.so"

#endif //RIRU_IL2CPPDUMPER_GAME_H
