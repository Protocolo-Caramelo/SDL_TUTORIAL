#ifdef COMPILATION_DEVQUOTE
#ifndef GTEST_H
#define GTEST_H

#include"GText/GTextCharFormat.h"
#include"GText/GTextCacheGlyph.h"
#include"GText/GTextCache.h"
#include"GText/GText.h"

#include"GInit.h"

#define GTEST_DELAY 1000
#define FPS_DELAY 100
#define ROTATION_DELAY 10000

//
// GText
//
void TextCG_Test();
void TextCache_Test(char*, unsigned);
void Text_Test(char*, unsigned, char*);

#endif
#endif
