
// Generated from ./gen/SensorLog.g4 by ANTLR 4.13.2


#include "SensorLogLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct SensorLogLexerStaticData final {
  SensorLogLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  SensorLogLexerStaticData(const SensorLogLexerStaticData&) = delete;
  SensorLogLexerStaticData(SensorLogLexerStaticData&&) = delete;
  SensorLogLexerStaticData& operator=(const SensorLogLexerStaticData&) = delete;
  SensorLogLexerStaticData& operator=(SensorLogLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag sensorloglexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<SensorLogLexerStaticData> sensorloglexerLexerStaticData = nullptr;

void sensorloglexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (sensorloglexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(sensorloglexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<SensorLogLexerStaticData>(
    std::vector<std::string>{
      "DOLLAR_SPACE", "PIPE", "LT", "GT", "COMMA", "BACKSLASH", "SLASH", 
      "U8_TYPE", "U16_TYPE", "U32_TYPE", "U64_TYPE", "S8_TYPE", "S16_TYPE", 
      "S32_TYPE", "S64_TYPE", "FLOAT_TYPE", "DOUBLE_TYPE", "DEVICE_ID_NUMBER", 
      "IDENTIFIER", "NUMBER", "LETTER", "DIGIT", "SPACE", "WS", "ANY"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'$ '", "'|'", "'<'", "'>'", "','", "'\\'", "'/'", "'u8'", "'u16'", 
      "'u32'", "'u64'", "'s8'", "'s16'", "'s32'", "'s64'", "'float'", "'double'", 
      "", "", "", "' '"
    },
    std::vector<std::string>{
      "", "DOLLAR_SPACE", "PIPE", "LT", "GT", "COMMA", "BACKSLASH", "SLASH", 
      "U8_TYPE", "U16_TYPE", "U32_TYPE", "U64_TYPE", "S8_TYPE", "S16_TYPE", 
      "S32_TYPE", "S64_TYPE", "FLOAT_TYPE", "DOUBLE_TYPE", "DEVICE_ID_NUMBER", 
      "IDENTIFIER", "NUMBER", "SPACE", "WS", "ANY"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,23,155,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,1,0,1,0,1,0,1,1,1,1,1,2,1,2,1,3,1,
  	3,1,4,1,4,1,5,1,5,1,6,1,6,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,9,1,9,1,9,1,9,
  	1,10,1,10,1,10,1,10,1,11,1,11,1,11,1,12,1,12,1,12,1,12,1,13,1,13,1,13,
  	1,13,1,14,1,14,1,14,1,14,1,15,1,15,1,15,1,15,1,15,1,15,1,16,1,16,1,16,
  	1,16,1,16,1,16,1,16,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,18,
  	1,18,1,18,1,18,5,18,123,8,18,10,18,12,18,126,9,18,1,19,4,19,129,8,19,
  	11,19,12,19,130,1,19,1,19,4,19,135,8,19,11,19,12,19,136,3,19,139,8,19,
  	1,20,1,20,1,21,1,21,1,22,1,22,1,23,4,23,148,8,23,11,23,12,23,149,1,23,
  	1,23,1,24,1,24,0,0,25,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,
  	11,23,12,25,13,27,14,29,15,31,16,33,17,35,18,37,19,39,20,41,0,43,0,45,
  	21,47,22,49,23,1,0,3,2,0,65,90,97,122,1,0,48,57,2,0,9,10,13,13,159,0,
  	1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,
  	0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,
  	23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,
  	0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,0,45,1,0,0,0,0,47,1,0,0,
  	0,0,49,1,0,0,0,1,51,1,0,0,0,3,54,1,0,0,0,5,56,1,0,0,0,7,58,1,0,0,0,9,
  	60,1,0,0,0,11,62,1,0,0,0,13,64,1,0,0,0,15,66,1,0,0,0,17,69,1,0,0,0,19,
  	73,1,0,0,0,21,77,1,0,0,0,23,81,1,0,0,0,25,84,1,0,0,0,27,88,1,0,0,0,29,
  	92,1,0,0,0,31,96,1,0,0,0,33,102,1,0,0,0,35,109,1,0,0,0,37,118,1,0,0,0,
  	39,128,1,0,0,0,41,140,1,0,0,0,43,142,1,0,0,0,45,144,1,0,0,0,47,147,1,
  	0,0,0,49,153,1,0,0,0,51,52,5,36,0,0,52,53,5,32,0,0,53,2,1,0,0,0,54,55,
  	5,124,0,0,55,4,1,0,0,0,56,57,5,60,0,0,57,6,1,0,0,0,58,59,5,62,0,0,59,
  	8,1,0,0,0,60,61,5,44,0,0,61,10,1,0,0,0,62,63,5,92,0,0,63,12,1,0,0,0,64,
  	65,5,47,0,0,65,14,1,0,0,0,66,67,5,117,0,0,67,68,5,56,0,0,68,16,1,0,0,
  	0,69,70,5,117,0,0,70,71,5,49,0,0,71,72,5,54,0,0,72,18,1,0,0,0,73,74,5,
  	117,0,0,74,75,5,51,0,0,75,76,5,50,0,0,76,20,1,0,0,0,77,78,5,117,0,0,78,
  	79,5,54,0,0,79,80,5,52,0,0,80,22,1,0,0,0,81,82,5,115,0,0,82,83,5,56,0,
  	0,83,24,1,0,0,0,84,85,5,115,0,0,85,86,5,49,0,0,86,87,5,54,0,0,87,26,1,
  	0,0,0,88,89,5,115,0,0,89,90,5,51,0,0,90,91,5,50,0,0,91,28,1,0,0,0,92,
  	93,5,115,0,0,93,94,5,54,0,0,94,95,5,52,0,0,95,30,1,0,0,0,96,97,5,102,
  	0,0,97,98,5,108,0,0,98,99,5,111,0,0,99,100,5,97,0,0,100,101,5,116,0,0,
  	101,32,1,0,0,0,102,103,5,100,0,0,103,104,5,111,0,0,104,105,5,117,0,0,
  	105,106,5,98,0,0,106,107,5,108,0,0,107,108,5,101,0,0,108,34,1,0,0,0,109,
  	110,3,43,21,0,110,111,3,43,21,0,111,112,3,43,21,0,112,113,3,43,21,0,113,
  	114,3,43,21,0,114,115,3,43,21,0,115,116,3,43,21,0,116,117,3,43,21,0,117,
  	36,1,0,0,0,118,124,3,41,20,0,119,123,3,41,20,0,120,123,3,43,21,0,121,
  	123,5,95,0,0,122,119,1,0,0,0,122,120,1,0,0,0,122,121,1,0,0,0,123,126,
  	1,0,0,0,124,122,1,0,0,0,124,125,1,0,0,0,125,38,1,0,0,0,126,124,1,0,0,
  	0,127,129,3,43,21,0,128,127,1,0,0,0,129,130,1,0,0,0,130,128,1,0,0,0,130,
  	131,1,0,0,0,131,138,1,0,0,0,132,134,5,46,0,0,133,135,3,43,21,0,134,133,
  	1,0,0,0,135,136,1,0,0,0,136,134,1,0,0,0,136,137,1,0,0,0,137,139,1,0,0,
  	0,138,132,1,0,0,0,138,139,1,0,0,0,139,40,1,0,0,0,140,141,7,0,0,0,141,
  	42,1,0,0,0,142,143,7,1,0,0,143,44,1,0,0,0,144,145,5,32,0,0,145,46,1,0,
  	0,0,146,148,7,2,0,0,147,146,1,0,0,0,148,149,1,0,0,0,149,147,1,0,0,0,149,
  	150,1,0,0,0,150,151,1,0,0,0,151,152,6,23,0,0,152,48,1,0,0,0,153,154,9,
  	0,0,0,154,50,1,0,0,0,7,0,122,124,130,136,138,149,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  sensorloglexerLexerStaticData = std::move(staticData);
}

}

SensorLogLexer::SensorLogLexer(CharStream *input) : Lexer(input) {
  SensorLogLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *sensorloglexerLexerStaticData->atn, sensorloglexerLexerStaticData->decisionToDFA, sensorloglexerLexerStaticData->sharedContextCache);
}

SensorLogLexer::~SensorLogLexer() {
  delete _interpreter;
}

std::string SensorLogLexer::getGrammarFileName() const {
  return "SensorLog.g4";
}

const std::vector<std::string>& SensorLogLexer::getRuleNames() const {
  return sensorloglexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& SensorLogLexer::getChannelNames() const {
  return sensorloglexerLexerStaticData->channelNames;
}

const std::vector<std::string>& SensorLogLexer::getModeNames() const {
  return sensorloglexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& SensorLogLexer::getVocabulary() const {
  return sensorloglexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView SensorLogLexer::getSerializedATN() const {
  return sensorloglexerLexerStaticData->serializedATN;
}

const atn::ATN& SensorLogLexer::getATN() const {
  return *sensorloglexerLexerStaticData->atn;
}




void SensorLogLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  sensorloglexerLexerInitialize();
#else
  ::antlr4::internal::call_once(sensorloglexerLexerOnceFlag, sensorloglexerLexerInitialize);
#endif
}
