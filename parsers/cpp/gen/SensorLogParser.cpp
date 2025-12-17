
// Generated from ./gen/SensorLog.g4 by ANTLR 4.13.2


#include "SensorLogListener.h"

#include "SensorLogParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct SensorLogParserStaticData final {
  SensorLogParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  SensorLogParserStaticData(const SensorLogParserStaticData&) = delete;
  SensorLogParserStaticData(SensorLogParserStaticData&&) = delete;
  SensorLogParserStaticData& operator=(const SensorLogParserStaticData&) = delete;
  SensorLogParserStaticData& operator=(SensorLogParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag sensorlogParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<SensorLogParserStaticData> sensorlogParserStaticData = nullptr;

void sensorlogParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (sensorlogParserStaticData != nullptr) {
    return;
  }
#else
  assert(sensorlogParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<SensorLogParserStaticData>(
    std::vector<std::string>{
      "file", "deviceDefinitions", "deviceDefinition", "deviceContent", 
      "deviceName", "sensorDefinition", "sensorName", "sensorNamePart", 
      "dataType", "unitOfMeasurement", "unitPart", "deviceId", "padding"
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
  	4,1,23,92,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,7,
  	7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,1,0,1,0,1,0,1,0,3,0,
  	31,8,0,1,0,1,0,1,1,1,1,1,1,5,1,38,8,1,10,1,12,1,41,9,1,1,2,1,2,1,2,1,
  	2,1,3,1,3,1,3,4,3,50,8,3,11,3,12,3,51,1,3,1,3,1,3,1,4,1,4,1,5,1,5,1,5,
  	1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,6,5,6,70,8,6,10,6,12,6,73,9,6,1,7,1,7,1,
  	8,1,8,1,9,1,9,1,9,3,9,82,8,9,1,10,1,10,1,11,1,11,1,11,1,11,1,12,1,12,
  	1,12,0,0,13,0,2,4,6,8,10,12,14,16,18,20,22,24,0,2,1,0,19,20,1,0,8,17,
  	83,0,26,1,0,0,0,2,34,1,0,0,0,4,42,1,0,0,0,6,46,1,0,0,0,8,56,1,0,0,0,10,
  	58,1,0,0,0,12,66,1,0,0,0,14,74,1,0,0,0,16,76,1,0,0,0,18,78,1,0,0,0,20,
  	83,1,0,0,0,22,85,1,0,0,0,24,89,1,0,0,0,26,27,5,1,0,0,27,28,3,2,1,0,28,
  	30,5,6,0,0,29,31,3,24,12,0,30,29,1,0,0,0,30,31,1,0,0,0,31,32,1,0,0,0,
  	32,33,5,0,0,1,33,1,1,0,0,0,34,39,3,4,2,0,35,36,5,21,0,0,36,38,3,4,2,0,
  	37,35,1,0,0,0,38,41,1,0,0,0,39,37,1,0,0,0,39,40,1,0,0,0,40,3,1,0,0,0,
  	41,39,1,0,0,0,42,43,5,2,0,0,43,44,3,6,3,0,44,45,5,2,0,0,45,5,1,0,0,0,
  	46,49,3,8,4,0,47,48,5,21,0,0,48,50,3,10,5,0,49,47,1,0,0,0,50,51,1,0,0,
  	0,51,49,1,0,0,0,51,52,1,0,0,0,52,53,1,0,0,0,53,54,5,21,0,0,54,55,3,22,
  	11,0,55,7,1,0,0,0,56,57,5,19,0,0,57,9,1,0,0,0,58,59,5,3,0,0,59,60,3,12,
  	6,0,60,61,5,5,0,0,61,62,3,16,8,0,62,63,5,5,0,0,63,64,3,18,9,0,64,65,5,
  	4,0,0,65,11,1,0,0,0,66,71,3,14,7,0,67,68,5,21,0,0,68,70,3,14,7,0,69,67,
  	1,0,0,0,70,73,1,0,0,0,71,69,1,0,0,0,71,72,1,0,0,0,72,13,1,0,0,0,73,71,
  	1,0,0,0,74,75,7,0,0,0,75,15,1,0,0,0,76,77,7,1,0,0,77,17,1,0,0,0,78,81,
  	3,20,10,0,79,80,5,7,0,0,80,82,3,20,10,0,81,79,1,0,0,0,81,82,1,0,0,0,82,
  	19,1,0,0,0,83,84,7,0,0,0,84,21,1,0,0,0,85,86,5,3,0,0,86,87,5,18,0,0,87,
  	88,5,4,0,0,88,23,1,0,0,0,89,90,9,0,0,0,90,25,1,0,0,0,5,30,39,51,71,81
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  sensorlogParserStaticData = std::move(staticData);
}

}

SensorLogParser::SensorLogParser(TokenStream *input) : SensorLogParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

SensorLogParser::SensorLogParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  SensorLogParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *sensorlogParserStaticData->atn, sensorlogParserStaticData->decisionToDFA, sensorlogParserStaticData->sharedContextCache, options);
}

SensorLogParser::~SensorLogParser() {
  delete _interpreter;
}

const atn::ATN& SensorLogParser::getATN() const {
  return *sensorlogParserStaticData->atn;
}

std::string SensorLogParser::getGrammarFileName() const {
  return "SensorLog.g4";
}

const std::vector<std::string>& SensorLogParser::getRuleNames() const {
  return sensorlogParserStaticData->ruleNames;
}

const dfa::Vocabulary& SensorLogParser::getVocabulary() const {
  return sensorlogParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView SensorLogParser::getSerializedATN() const {
  return sensorlogParserStaticData->serializedATN;
}


//----------------- FileContext ------------------------------------------------------------------

SensorLogParser::FileContext::FileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SensorLogParser::FileContext::DOLLAR_SPACE() {
  return getToken(SensorLogParser::DOLLAR_SPACE, 0);
}

SensorLogParser::DeviceDefinitionsContext* SensorLogParser::FileContext::deviceDefinitions() {
  return getRuleContext<SensorLogParser::DeviceDefinitionsContext>(0);
}

tree::TerminalNode* SensorLogParser::FileContext::BACKSLASH() {
  return getToken(SensorLogParser::BACKSLASH, 0);
}

tree::TerminalNode* SensorLogParser::FileContext::EOF() {
  return getToken(SensorLogParser::EOF, 0);
}

SensorLogParser::PaddingContext* SensorLogParser::FileContext::padding() {
  return getRuleContext<SensorLogParser::PaddingContext>(0);
}


size_t SensorLogParser::FileContext::getRuleIndex() const {
  return SensorLogParser::RuleFile;
}

void SensorLogParser::FileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SensorLogListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFile(this);
}

void SensorLogParser::FileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SensorLogListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFile(this);
}

SensorLogParser::FileContext* SensorLogParser::file() {
  FileContext *_localctx = _tracker.createInstance<FileContext>(_ctx, getState());
  enterRule(_localctx, 0, SensorLogParser::RuleFile);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(26);
    match(SensorLogParser::DOLLAR_SPACE);
    setState(27);
    deviceDefinitions();
    setState(28);
    match(SensorLogParser::BACKSLASH);
    setState(30);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 16777214) != 0)) {
      setState(29);
      padding();
    }
    setState(32);
    match(SensorLogParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeviceDefinitionsContext ------------------------------------------------------------------

SensorLogParser::DeviceDefinitionsContext::DeviceDefinitionsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SensorLogParser::DeviceDefinitionContext *> SensorLogParser::DeviceDefinitionsContext::deviceDefinition() {
  return getRuleContexts<SensorLogParser::DeviceDefinitionContext>();
}

SensorLogParser::DeviceDefinitionContext* SensorLogParser::DeviceDefinitionsContext::deviceDefinition(size_t i) {
  return getRuleContext<SensorLogParser::DeviceDefinitionContext>(i);
}

std::vector<tree::TerminalNode *> SensorLogParser::DeviceDefinitionsContext::SPACE() {
  return getTokens(SensorLogParser::SPACE);
}

tree::TerminalNode* SensorLogParser::DeviceDefinitionsContext::SPACE(size_t i) {
  return getToken(SensorLogParser::SPACE, i);
}


size_t SensorLogParser::DeviceDefinitionsContext::getRuleIndex() const {
  return SensorLogParser::RuleDeviceDefinitions;
}

void SensorLogParser::DeviceDefinitionsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SensorLogListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeviceDefinitions(this);
}

void SensorLogParser::DeviceDefinitionsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SensorLogListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeviceDefinitions(this);
}

SensorLogParser::DeviceDefinitionsContext* SensorLogParser::deviceDefinitions() {
  DeviceDefinitionsContext *_localctx = _tracker.createInstance<DeviceDefinitionsContext>(_ctx, getState());
  enterRule(_localctx, 2, SensorLogParser::RuleDeviceDefinitions);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(34);
    deviceDefinition();
    setState(39);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SensorLogParser::SPACE) {
      setState(35);
      match(SensorLogParser::SPACE);
      setState(36);
      deviceDefinition();
      setState(41);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeviceDefinitionContext ------------------------------------------------------------------

SensorLogParser::DeviceDefinitionContext::DeviceDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> SensorLogParser::DeviceDefinitionContext::PIPE() {
  return getTokens(SensorLogParser::PIPE);
}

tree::TerminalNode* SensorLogParser::DeviceDefinitionContext::PIPE(size_t i) {
  return getToken(SensorLogParser::PIPE, i);
}

SensorLogParser::DeviceContentContext* SensorLogParser::DeviceDefinitionContext::deviceContent() {
  return getRuleContext<SensorLogParser::DeviceContentContext>(0);
}


size_t SensorLogParser::DeviceDefinitionContext::getRuleIndex() const {
  return SensorLogParser::RuleDeviceDefinition;
}

void SensorLogParser::DeviceDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SensorLogListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeviceDefinition(this);
}

void SensorLogParser::DeviceDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SensorLogListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeviceDefinition(this);
}

SensorLogParser::DeviceDefinitionContext* SensorLogParser::deviceDefinition() {
  DeviceDefinitionContext *_localctx = _tracker.createInstance<DeviceDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 4, SensorLogParser::RuleDeviceDefinition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(42);
    match(SensorLogParser::PIPE);
    setState(43);
    deviceContent();
    setState(44);
    match(SensorLogParser::PIPE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeviceContentContext ------------------------------------------------------------------

SensorLogParser::DeviceContentContext::DeviceContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SensorLogParser::DeviceNameContext* SensorLogParser::DeviceContentContext::deviceName() {
  return getRuleContext<SensorLogParser::DeviceNameContext>(0);
}

std::vector<tree::TerminalNode *> SensorLogParser::DeviceContentContext::SPACE() {
  return getTokens(SensorLogParser::SPACE);
}

tree::TerminalNode* SensorLogParser::DeviceContentContext::SPACE(size_t i) {
  return getToken(SensorLogParser::SPACE, i);
}

SensorLogParser::DeviceIdContext* SensorLogParser::DeviceContentContext::deviceId() {
  return getRuleContext<SensorLogParser::DeviceIdContext>(0);
}

std::vector<SensorLogParser::SensorDefinitionContext *> SensorLogParser::DeviceContentContext::sensorDefinition() {
  return getRuleContexts<SensorLogParser::SensorDefinitionContext>();
}

SensorLogParser::SensorDefinitionContext* SensorLogParser::DeviceContentContext::sensorDefinition(size_t i) {
  return getRuleContext<SensorLogParser::SensorDefinitionContext>(i);
}


size_t SensorLogParser::DeviceContentContext::getRuleIndex() const {
  return SensorLogParser::RuleDeviceContent;
}

void SensorLogParser::DeviceContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SensorLogListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeviceContent(this);
}

void SensorLogParser::DeviceContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SensorLogListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeviceContent(this);
}

SensorLogParser::DeviceContentContext* SensorLogParser::deviceContent() {
  DeviceContentContext *_localctx = _tracker.createInstance<DeviceContentContext>(_ctx, getState());
  enterRule(_localctx, 6, SensorLogParser::RuleDeviceContent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(46);
    deviceName();
    setState(49); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(47);
              match(SensorLogParser::SPACE);
              setState(48);
              sensorDefinition();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(51); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
    setState(53);
    match(SensorLogParser::SPACE);
    setState(54);
    deviceId();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeviceNameContext ------------------------------------------------------------------

SensorLogParser::DeviceNameContext::DeviceNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SensorLogParser::DeviceNameContext::IDENTIFIER() {
  return getToken(SensorLogParser::IDENTIFIER, 0);
}


size_t SensorLogParser::DeviceNameContext::getRuleIndex() const {
  return SensorLogParser::RuleDeviceName;
}

void SensorLogParser::DeviceNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SensorLogListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeviceName(this);
}

void SensorLogParser::DeviceNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SensorLogListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeviceName(this);
}

SensorLogParser::DeviceNameContext* SensorLogParser::deviceName() {
  DeviceNameContext *_localctx = _tracker.createInstance<DeviceNameContext>(_ctx, getState());
  enterRule(_localctx, 8, SensorLogParser::RuleDeviceName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(56);
    match(SensorLogParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SensorDefinitionContext ------------------------------------------------------------------

SensorLogParser::SensorDefinitionContext::SensorDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SensorLogParser::SensorDefinitionContext::LT() {
  return getToken(SensorLogParser::LT, 0);
}

SensorLogParser::SensorNameContext* SensorLogParser::SensorDefinitionContext::sensorName() {
  return getRuleContext<SensorLogParser::SensorNameContext>(0);
}

std::vector<tree::TerminalNode *> SensorLogParser::SensorDefinitionContext::COMMA() {
  return getTokens(SensorLogParser::COMMA);
}

tree::TerminalNode* SensorLogParser::SensorDefinitionContext::COMMA(size_t i) {
  return getToken(SensorLogParser::COMMA, i);
}

SensorLogParser::DataTypeContext* SensorLogParser::SensorDefinitionContext::dataType() {
  return getRuleContext<SensorLogParser::DataTypeContext>(0);
}

SensorLogParser::UnitOfMeasurementContext* SensorLogParser::SensorDefinitionContext::unitOfMeasurement() {
  return getRuleContext<SensorLogParser::UnitOfMeasurementContext>(0);
}

tree::TerminalNode* SensorLogParser::SensorDefinitionContext::GT() {
  return getToken(SensorLogParser::GT, 0);
}


size_t SensorLogParser::SensorDefinitionContext::getRuleIndex() const {
  return SensorLogParser::RuleSensorDefinition;
}

void SensorLogParser::SensorDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SensorLogListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSensorDefinition(this);
}

void SensorLogParser::SensorDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SensorLogListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSensorDefinition(this);
}

SensorLogParser::SensorDefinitionContext* SensorLogParser::sensorDefinition() {
  SensorDefinitionContext *_localctx = _tracker.createInstance<SensorDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 10, SensorLogParser::RuleSensorDefinition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(58);
    match(SensorLogParser::LT);
    setState(59);
    sensorName();
    setState(60);
    match(SensorLogParser::COMMA);
    setState(61);
    dataType();
    setState(62);
    match(SensorLogParser::COMMA);
    setState(63);
    unitOfMeasurement();
    setState(64);
    match(SensorLogParser::GT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SensorNameContext ------------------------------------------------------------------

SensorLogParser::SensorNameContext::SensorNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SensorLogParser::SensorNamePartContext *> SensorLogParser::SensorNameContext::sensorNamePart() {
  return getRuleContexts<SensorLogParser::SensorNamePartContext>();
}

SensorLogParser::SensorNamePartContext* SensorLogParser::SensorNameContext::sensorNamePart(size_t i) {
  return getRuleContext<SensorLogParser::SensorNamePartContext>(i);
}

std::vector<tree::TerminalNode *> SensorLogParser::SensorNameContext::SPACE() {
  return getTokens(SensorLogParser::SPACE);
}

tree::TerminalNode* SensorLogParser::SensorNameContext::SPACE(size_t i) {
  return getToken(SensorLogParser::SPACE, i);
}


size_t SensorLogParser::SensorNameContext::getRuleIndex() const {
  return SensorLogParser::RuleSensorName;
}

void SensorLogParser::SensorNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SensorLogListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSensorName(this);
}

void SensorLogParser::SensorNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SensorLogListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSensorName(this);
}

SensorLogParser::SensorNameContext* SensorLogParser::sensorName() {
  SensorNameContext *_localctx = _tracker.createInstance<SensorNameContext>(_ctx, getState());
  enterRule(_localctx, 12, SensorLogParser::RuleSensorName);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(66);
    sensorNamePart();
    setState(71);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SensorLogParser::SPACE) {
      setState(67);
      match(SensorLogParser::SPACE);
      setState(68);
      sensorNamePart();
      setState(73);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SensorNamePartContext ------------------------------------------------------------------

SensorLogParser::SensorNamePartContext::SensorNamePartContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SensorLogParser::SensorNamePartContext::IDENTIFIER() {
  return getToken(SensorLogParser::IDENTIFIER, 0);
}

tree::TerminalNode* SensorLogParser::SensorNamePartContext::NUMBER() {
  return getToken(SensorLogParser::NUMBER, 0);
}


size_t SensorLogParser::SensorNamePartContext::getRuleIndex() const {
  return SensorLogParser::RuleSensorNamePart;
}

void SensorLogParser::SensorNamePartContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SensorLogListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSensorNamePart(this);
}

void SensorLogParser::SensorNamePartContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SensorLogListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSensorNamePart(this);
}

SensorLogParser::SensorNamePartContext* SensorLogParser::sensorNamePart() {
  SensorNamePartContext *_localctx = _tracker.createInstance<SensorNamePartContext>(_ctx, getState());
  enterRule(_localctx, 14, SensorLogParser::RuleSensorNamePart);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(74);
    _la = _input->LA(1);
    if (!(_la == SensorLogParser::IDENTIFIER

    || _la == SensorLogParser::NUMBER)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DataTypeContext ------------------------------------------------------------------

SensorLogParser::DataTypeContext::DataTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SensorLogParser::DataTypeContext::U8_TYPE() {
  return getToken(SensorLogParser::U8_TYPE, 0);
}

tree::TerminalNode* SensorLogParser::DataTypeContext::U16_TYPE() {
  return getToken(SensorLogParser::U16_TYPE, 0);
}

tree::TerminalNode* SensorLogParser::DataTypeContext::U32_TYPE() {
  return getToken(SensorLogParser::U32_TYPE, 0);
}

tree::TerminalNode* SensorLogParser::DataTypeContext::U64_TYPE() {
  return getToken(SensorLogParser::U64_TYPE, 0);
}

tree::TerminalNode* SensorLogParser::DataTypeContext::S8_TYPE() {
  return getToken(SensorLogParser::S8_TYPE, 0);
}

tree::TerminalNode* SensorLogParser::DataTypeContext::S16_TYPE() {
  return getToken(SensorLogParser::S16_TYPE, 0);
}

tree::TerminalNode* SensorLogParser::DataTypeContext::S32_TYPE() {
  return getToken(SensorLogParser::S32_TYPE, 0);
}

tree::TerminalNode* SensorLogParser::DataTypeContext::S64_TYPE() {
  return getToken(SensorLogParser::S64_TYPE, 0);
}

tree::TerminalNode* SensorLogParser::DataTypeContext::FLOAT_TYPE() {
  return getToken(SensorLogParser::FLOAT_TYPE, 0);
}

tree::TerminalNode* SensorLogParser::DataTypeContext::DOUBLE_TYPE() {
  return getToken(SensorLogParser::DOUBLE_TYPE, 0);
}


size_t SensorLogParser::DataTypeContext::getRuleIndex() const {
  return SensorLogParser::RuleDataType;
}

void SensorLogParser::DataTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SensorLogListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDataType(this);
}

void SensorLogParser::DataTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SensorLogListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDataType(this);
}

SensorLogParser::DataTypeContext* SensorLogParser::dataType() {
  DataTypeContext *_localctx = _tracker.createInstance<DataTypeContext>(_ctx, getState());
  enterRule(_localctx, 16, SensorLogParser::RuleDataType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(76);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 261888) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnitOfMeasurementContext ------------------------------------------------------------------

SensorLogParser::UnitOfMeasurementContext::UnitOfMeasurementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SensorLogParser::UnitPartContext *> SensorLogParser::UnitOfMeasurementContext::unitPart() {
  return getRuleContexts<SensorLogParser::UnitPartContext>();
}

SensorLogParser::UnitPartContext* SensorLogParser::UnitOfMeasurementContext::unitPart(size_t i) {
  return getRuleContext<SensorLogParser::UnitPartContext>(i);
}

tree::TerminalNode* SensorLogParser::UnitOfMeasurementContext::SLASH() {
  return getToken(SensorLogParser::SLASH, 0);
}


size_t SensorLogParser::UnitOfMeasurementContext::getRuleIndex() const {
  return SensorLogParser::RuleUnitOfMeasurement;
}

void SensorLogParser::UnitOfMeasurementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SensorLogListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnitOfMeasurement(this);
}

void SensorLogParser::UnitOfMeasurementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SensorLogListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnitOfMeasurement(this);
}

SensorLogParser::UnitOfMeasurementContext* SensorLogParser::unitOfMeasurement() {
  UnitOfMeasurementContext *_localctx = _tracker.createInstance<UnitOfMeasurementContext>(_ctx, getState());
  enterRule(_localctx, 18, SensorLogParser::RuleUnitOfMeasurement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(78);
    unitPart();
    setState(81);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SensorLogParser::SLASH) {
      setState(79);
      match(SensorLogParser::SLASH);
      setState(80);
      unitPart();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnitPartContext ------------------------------------------------------------------

SensorLogParser::UnitPartContext::UnitPartContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SensorLogParser::UnitPartContext::IDENTIFIER() {
  return getToken(SensorLogParser::IDENTIFIER, 0);
}

tree::TerminalNode* SensorLogParser::UnitPartContext::NUMBER() {
  return getToken(SensorLogParser::NUMBER, 0);
}


size_t SensorLogParser::UnitPartContext::getRuleIndex() const {
  return SensorLogParser::RuleUnitPart;
}

void SensorLogParser::UnitPartContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SensorLogListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnitPart(this);
}

void SensorLogParser::UnitPartContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SensorLogListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnitPart(this);
}

SensorLogParser::UnitPartContext* SensorLogParser::unitPart() {
  UnitPartContext *_localctx = _tracker.createInstance<UnitPartContext>(_ctx, getState());
  enterRule(_localctx, 20, SensorLogParser::RuleUnitPart);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(83);
    _la = _input->LA(1);
    if (!(_la == SensorLogParser::IDENTIFIER

    || _la == SensorLogParser::NUMBER)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeviceIdContext ------------------------------------------------------------------

SensorLogParser::DeviceIdContext::DeviceIdContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SensorLogParser::DeviceIdContext::LT() {
  return getToken(SensorLogParser::LT, 0);
}

tree::TerminalNode* SensorLogParser::DeviceIdContext::DEVICE_ID_NUMBER() {
  return getToken(SensorLogParser::DEVICE_ID_NUMBER, 0);
}

tree::TerminalNode* SensorLogParser::DeviceIdContext::GT() {
  return getToken(SensorLogParser::GT, 0);
}


size_t SensorLogParser::DeviceIdContext::getRuleIndex() const {
  return SensorLogParser::RuleDeviceId;
}

void SensorLogParser::DeviceIdContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SensorLogListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeviceId(this);
}

void SensorLogParser::DeviceIdContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SensorLogListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeviceId(this);
}

SensorLogParser::DeviceIdContext* SensorLogParser::deviceId() {
  DeviceIdContext *_localctx = _tracker.createInstance<DeviceIdContext>(_ctx, getState());
  enterRule(_localctx, 22, SensorLogParser::RuleDeviceId);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(85);
    match(SensorLogParser::LT);
    setState(86);
    match(SensorLogParser::DEVICE_ID_NUMBER);
    setState(87);
    match(SensorLogParser::GT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PaddingContext ------------------------------------------------------------------

SensorLogParser::PaddingContext::PaddingContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SensorLogParser::PaddingContext::getRuleIndex() const {
  return SensorLogParser::RulePadding;
}

void SensorLogParser::PaddingContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SensorLogListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPadding(this);
}

void SensorLogParser::PaddingContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SensorLogListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPadding(this);
}

SensorLogParser::PaddingContext* SensorLogParser::padding() {
  PaddingContext *_localctx = _tracker.createInstance<PaddingContext>(_ctx, getState());
  enterRule(_localctx, 24, SensorLogParser::RulePadding);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(89);
    matchWildcard();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void SensorLogParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  sensorlogParserInitialize();
#else
  ::antlr4::internal::call_once(sensorlogParserOnceFlag, sensorlogParserInitialize);
#endif
}
