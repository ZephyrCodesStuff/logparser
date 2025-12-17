
// Generated from ./gen/SensorLog.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  SensorLogParser : public antlr4::Parser {
public:
  enum {
    DOLLAR_SPACE = 1, PIPE = 2, LT = 3, GT = 4, COMMA = 5, BACKSLASH = 6, 
    SLASH = 7, U8_TYPE = 8, U16_TYPE = 9, U32_TYPE = 10, U64_TYPE = 11, 
    S8_TYPE = 12, S16_TYPE = 13, S32_TYPE = 14, S64_TYPE = 15, FLOAT_TYPE = 16, 
    DOUBLE_TYPE = 17, DEVICE_ID_NUMBER = 18, IDENTIFIER = 19, NUMBER = 20, 
    SPACE = 21, WS = 22, ANY = 23
  };

  enum {
    RuleFile = 0, RuleDeviceDefinitions = 1, RuleDeviceDefinition = 2, RuleDeviceContent = 3, 
    RuleDeviceName = 4, RuleSensorDefinition = 5, RuleSensorName = 6, RuleSensorNamePart = 7, 
    RuleDataType = 8, RuleUnitOfMeasurement = 9, RuleUnitPart = 10, RuleDeviceId = 11, 
    RulePadding = 12
  };

  explicit SensorLogParser(antlr4::TokenStream *input);

  SensorLogParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~SensorLogParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class FileContext;
  class DeviceDefinitionsContext;
  class DeviceDefinitionContext;
  class DeviceContentContext;
  class DeviceNameContext;
  class SensorDefinitionContext;
  class SensorNameContext;
  class SensorNamePartContext;
  class DataTypeContext;
  class UnitOfMeasurementContext;
  class UnitPartContext;
  class DeviceIdContext;
  class PaddingContext; 

  class  FileContext : public antlr4::ParserRuleContext {
  public:
    FileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DOLLAR_SPACE();
    DeviceDefinitionsContext *deviceDefinitions();
    antlr4::tree::TerminalNode *BACKSLASH();
    antlr4::tree::TerminalNode *EOF();
    PaddingContext *padding();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FileContext* file();

  class  DeviceDefinitionsContext : public antlr4::ParserRuleContext {
  public:
    DeviceDefinitionsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<DeviceDefinitionContext *> deviceDefinition();
    DeviceDefinitionContext* deviceDefinition(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SPACE();
    antlr4::tree::TerminalNode* SPACE(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DeviceDefinitionsContext* deviceDefinitions();

  class  DeviceDefinitionContext : public antlr4::ParserRuleContext {
  public:
    DeviceDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> PIPE();
    antlr4::tree::TerminalNode* PIPE(size_t i);
    DeviceContentContext *deviceContent();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DeviceDefinitionContext* deviceDefinition();

  class  DeviceContentContext : public antlr4::ParserRuleContext {
  public:
    DeviceContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeviceNameContext *deviceName();
    std::vector<antlr4::tree::TerminalNode *> SPACE();
    antlr4::tree::TerminalNode* SPACE(size_t i);
    DeviceIdContext *deviceId();
    std::vector<SensorDefinitionContext *> sensorDefinition();
    SensorDefinitionContext* sensorDefinition(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DeviceContentContext* deviceContent();

  class  DeviceNameContext : public antlr4::ParserRuleContext {
  public:
    DeviceNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DeviceNameContext* deviceName();

  class  SensorDefinitionContext : public antlr4::ParserRuleContext {
  public:
    SensorDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LT();
    SensorNameContext *sensorName();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    DataTypeContext *dataType();
    UnitOfMeasurementContext *unitOfMeasurement();
    antlr4::tree::TerminalNode *GT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SensorDefinitionContext* sensorDefinition();

  class  SensorNameContext : public antlr4::ParserRuleContext {
  public:
    SensorNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<SensorNamePartContext *> sensorNamePart();
    SensorNamePartContext* sensorNamePart(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SPACE();
    antlr4::tree::TerminalNode* SPACE(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SensorNameContext* sensorName();

  class  SensorNamePartContext : public antlr4::ParserRuleContext {
  public:
    SensorNamePartContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *NUMBER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SensorNamePartContext* sensorNamePart();

  class  DataTypeContext : public antlr4::ParserRuleContext {
  public:
    DataTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *U8_TYPE();
    antlr4::tree::TerminalNode *U16_TYPE();
    antlr4::tree::TerminalNode *U32_TYPE();
    antlr4::tree::TerminalNode *U64_TYPE();
    antlr4::tree::TerminalNode *S8_TYPE();
    antlr4::tree::TerminalNode *S16_TYPE();
    antlr4::tree::TerminalNode *S32_TYPE();
    antlr4::tree::TerminalNode *S64_TYPE();
    antlr4::tree::TerminalNode *FLOAT_TYPE();
    antlr4::tree::TerminalNode *DOUBLE_TYPE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DataTypeContext* dataType();

  class  UnitOfMeasurementContext : public antlr4::ParserRuleContext {
  public:
    UnitOfMeasurementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<UnitPartContext *> unitPart();
    UnitPartContext* unitPart(size_t i);
    antlr4::tree::TerminalNode *SLASH();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  UnitOfMeasurementContext* unitOfMeasurement();

  class  UnitPartContext : public antlr4::ParserRuleContext {
  public:
    UnitPartContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *NUMBER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  UnitPartContext* unitPart();

  class  DeviceIdContext : public antlr4::ParserRuleContext {
  public:
    DeviceIdContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LT();
    antlr4::tree::TerminalNode *DEVICE_ID_NUMBER();
    antlr4::tree::TerminalNode *GT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DeviceIdContext* deviceId();

  class  PaddingContext : public antlr4::ParserRuleContext {
  public:
    PaddingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PaddingContext* padding();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

