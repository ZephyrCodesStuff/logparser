
// Generated from ./gen/SensorLog.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  SensorLogLexer : public antlr4::Lexer {
public:
  enum {
    DOLLAR_SPACE = 1, PIPE = 2, LT = 3, GT = 4, COMMA = 5, BACKSLASH = 6, 
    SLASH = 7, U8_TYPE = 8, U16_TYPE = 9, U32_TYPE = 10, U64_TYPE = 11, 
    S8_TYPE = 12, S16_TYPE = 13, S32_TYPE = 14, S64_TYPE = 15, FLOAT_TYPE = 16, 
    DOUBLE_TYPE = 17, DEVICE_ID_NUMBER = 18, IDENTIFIER = 19, NUMBER = 20, 
    SPACE = 21, WS = 22, ANY = 23
  };

  explicit SensorLogLexer(antlr4::CharStream *input);

  ~SensorLogLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

