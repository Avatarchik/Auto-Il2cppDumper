//
// Created by Perfare on 2020/7/4.
//

#ifndef RIRU_IL2CPPDUMPER_GAME_H
#define RIRU_IL2CPPDUMPER_GAME_H

// Uncomment for root mode
// Root mode is to load our fake libunity.so and load game's real librealunity.so
#define RootMode

// Increase sleep in seconds if getting issue with dumper, like if not fully dumped or crashes
#define Sleep 15

// Target renamed lib
#define RealLibToLoad "librealunity.so"

#endif //RIRU_IL2CPPDUMPER_GAME_H
