
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
      "FLOAT_TYPE", "U32_TYPE", "U8_TYPE", "U16_TYPE", "DEVICE_ID_NUMBER", 
      "IDENTIFIER", "NUMBER", "LETTER", "DIGIT", "SPACE", "WS", "ANY"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'$ '", "'|'", "'<'", "'>'", "','", "'\\'", "'/'", "'float'", 
      "'u32'", "'u8'", "'u16'", "", "", "", "' '"
    },
    std::vector<std::string>{
      "", "DOLLAR_SPACE", "PIPE", "LT", "GT", "COMMA", "BACKSLASH", "SLASH", 
      "FLOAT_TYPE", "U32_TYPE", "U8_TYPE", "U16_TYPE", "DEVICE_ID_NUMBER", 
      "IDENTIFIER", "NUMBER", "SPACE", "WS", "ANY"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,17,117,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,1,0,1,0,1,0,1,1,1,1,1,2,
  	1,2,1,3,1,3,1,4,1,4,1,5,1,5,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,1,8,1,8,1,
  	8,1,8,1,9,1,9,1,9,1,10,1,10,1,10,1,10,1,11,1,11,1,11,1,11,1,11,1,11,1,
  	11,1,11,1,11,1,12,1,12,1,12,1,12,5,12,85,8,12,10,12,12,12,88,9,12,1,13,
  	4,13,91,8,13,11,13,12,13,92,1,13,1,13,4,13,97,8,13,11,13,12,13,98,3,13,
  	101,8,13,1,14,1,14,1,15,1,15,1,16,1,16,1,17,4,17,110,8,17,11,17,12,17,
  	111,1,17,1,17,1,18,1,18,0,0,19,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,
  	9,19,10,21,11,23,12,25,13,27,14,29,0,31,0,33,15,35,16,37,17,1,0,3,2,0,
  	65,90,97,122,1,0,48,57,2,0,9,10,13,13,121,0,1,1,0,0,0,0,3,1,0,0,0,0,5,
  	1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,
  	0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,
  	27,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,1,39,1,0,0,0,3,42,1,
  	0,0,0,5,44,1,0,0,0,7,46,1,0,0,0,9,48,1,0,0,0,11,50,1,0,0,0,13,52,1,0,
  	0,0,15,54,1,0,0,0,17,60,1,0,0,0,19,64,1,0,0,0,21,67,1,0,0,0,23,71,1,0,
  	0,0,25,80,1,0,0,0,27,90,1,0,0,0,29,102,1,0,0,0,31,104,1,0,0,0,33,106,
  	1,0,0,0,35,109,1,0,0,0,37,115,1,0,0,0,39,40,5,36,0,0,40,41,5,32,0,0,41,
  	2,1,0,0,0,42,43,5,124,0,0,43,4,1,0,0,0,44,45,5,60,0,0,45,6,1,0,0,0,46,
  	47,5,62,0,0,47,8,1,0,0,0,48,49,5,44,0,0,49,10,1,0,0,0,50,51,5,92,0,0,
  	51,12,1,0,0,0,52,53,5,47,0,0,53,14,1,0,0,0,54,55,5,102,0,0,55,56,5,108,
  	0,0,56,57,5,111,0,0,57,58,5,97,0,0,58,59,5,116,0,0,59,16,1,0,0,0,60,61,
  	5,117,0,0,61,62,5,51,0,0,62,63,5,50,0,0,63,18,1,0,0,0,64,65,5,117,0,0,
  	65,66,5,56,0,0,66,20,1,0,0,0,67,68,5,117,0,0,68,69,5,49,0,0,69,70,5,54,
  	0,0,70,22,1,0,0,0,71,72,3,31,15,0,72,73,3,31,15,0,73,74,3,31,15,0,74,
  	75,3,31,15,0,75,76,3,31,15,0,76,77,3,31,15,0,77,78,3,31,15,0,78,79,3,
  	31,15,0,79,24,1,0,0,0,80,86,3,29,14,0,81,85,3,29,14,0,82,85,3,31,15,0,
  	83,85,5,95,0,0,84,81,1,0,0,0,84,82,1,0,0,0,84,83,1,0,0,0,85,88,1,0,0,
  	0,86,84,1,0,0,0,86,87,1,0,0,0,87,26,1,0,0,0,88,86,1,0,0,0,89,91,3,31,
  	15,0,90,89,1,0,0,0,91,92,1,0,0,0,92,90,1,0,0,0,92,93,1,0,0,0,93,100,1,
  	0,0,0,94,96,5,46,0,0,95,97,3,31,15,0,96,95,1,0,0,0,97,98,1,0,0,0,98,96,
  	1,0,0,0,98,99,1,0,0,0,99,101,1,0,0,0,100,94,1,0,0,0,100,101,1,0,0,0,101,
  	28,1,0,0,0,102,103,7,0,0,0,103,30,1,0,0,0,104,105,7,1,0,0,105,32,1,0,
  	0,0,106,107,5,32,0,0,107,34,1,0,0,0,108,110,7,2,0,0,109,108,1,0,0,0,110,
  	111,1,0,0,0,111,109,1,0,0,0,111,112,1,0,0,0,112,113,1,0,0,0,113,114,6,
  	17,0,0,114,36,1,0,0,0,115,116,9,0,0,0,116,38,1,0,0,0,7,0,84,86,92,98,
  	100,111,1,6,0,0
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
