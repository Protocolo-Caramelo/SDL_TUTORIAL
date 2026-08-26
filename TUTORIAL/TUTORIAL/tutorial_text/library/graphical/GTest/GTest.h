#ifdef COMPILATION_DEVQUOTE
#ifndef GTEST_H
#define GTEST_H

#include"GText/GTextCharFormat.h"
#include"GText/GTextCacheGlyph.h"
#include"GText/GTextCache.h"
#include"GText/GText.h"

#include"GInit.h"

#define GTEST_DELAY 16
#define FPS_DELAY 100

#define CHR_ROTATION_DELAY 10000
#define CHR_ROTATION_MAX 360.0
#define TXT_ROTATION_DELAY 10000
#define TXT_ROTATION_MAX 360.0

//
// Hardware test
//
void SimpleWindow();

//
// GText
//
void TextCG_Test();
void TextCache_Test(char*, unsigned);
void Text_Test(char*, unsigned, char*);

#endif
#endif
