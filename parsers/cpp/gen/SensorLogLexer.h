
// Generated from ./gen/SensorLog.g4 by ANTLR 4.13.2

#pragma once

#include "antlr4-runtime.h"

class SensorLogLexer : public antlr4::Lexer {
public:
  enum {
    DOLLAR_SPACE = 1,
    PIPE = 2,
    LT = 3,
    GT = 4,
    COMMA = 5,
    BACKSLASH = 6,
    SLASH = 7,
    FLOAT_TYPE = 8,
    U32_TYPE = 9,
    U8_TYPE = 10,
    U16_TYPE = 11,
    DEVICE_ID_NUMBER = 12,
    IDENTIFIER = 13,
    NUMBER = 14,
    SPACE = 15,
    WS = 16,
    ANY = 17
  };

  explicit SensorLogLexer(antlr4::CharStream *input);

  ~SensorLogLexer() override;

  std::string getGrammarFileName() const override;

  const std::vector<std::string> &getRuleNames() const override;

  const std::vector<std::string> &getChannelNames() const override;

  const std::vector<std::string> &getModeNames() const override;

  const antlr4::dfa::Vocabulary &getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN &getATN() const override;

  // By default the static state used to implement the lexer is lazily
  // initialized during the first call to the constructor. You can call this
  // function if you wish to initialize the static state ahead of time.
  static void initialize();

private:
  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.
};
