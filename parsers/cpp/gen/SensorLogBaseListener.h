
// Generated from ./gen/SensorLog.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "SensorLogListener.h"


/**
 * This class provides an empty implementation of SensorLogListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  SensorLogBaseListener : public SensorLogListener {
public:

  virtual void enterFile(SensorLogParser::FileContext * /*ctx*/) override { }
  virtual void exitFile(SensorLogParser::FileContext * /*ctx*/) override { }

  virtual void enterDeviceDefinitions(SensorLogParser::DeviceDefinitionsContext * /*ctx*/) override { }
  virtual void exitDeviceDefinitions(SensorLogParser::DeviceDefinitionsContext * /*ctx*/) override { }

  virtual void enterDeviceDefinition(SensorLogParser::DeviceDefinitionContext * /*ctx*/) override { }
  virtual void exitDeviceDefinition(SensorLogParser::DeviceDefinitionContext * /*ctx*/) override { }

  virtual void enterDeviceContent(SensorLogParser::DeviceContentContext * /*ctx*/) override { }
  virtual void exitDeviceContent(SensorLogParser::DeviceContentContext * /*ctx*/) override { }

  virtual void enterDeviceName(SensorLogParser::DeviceNameContext * /*ctx*/) override { }
  virtual void exitDeviceName(SensorLogParser::DeviceNameContext * /*ctx*/) override { }

  virtual void enterSensorDefinition(SensorLogParser::SensorDefinitionContext * /*ctx*/) override { }
  virtual void exitSensorDefinition(SensorLogParser::SensorDefinitionContext * /*ctx*/) override { }

  virtual void enterSensorName(SensorLogParser::SensorNameContext * /*ctx*/) override { }
  virtual void exitSensorName(SensorLogParser::SensorNameContext * /*ctx*/) override { }

  virtual void enterSensorNamePart(SensorLogParser::SensorNamePartContext * /*ctx*/) override { }
  virtual void exitSensorNamePart(SensorLogParser::SensorNamePartContext * /*ctx*/) override { }

  virtual void enterDataType(SensorLogParser::DataTypeContext * /*ctx*/) override { }
  virtual void exitDataType(SensorLogParser::DataTypeContext * /*ctx*/) override { }

  virtual void enterUnitOfMeasurement(SensorLogParser::UnitOfMeasurementContext * /*ctx*/) override { }
  virtual void exitUnitOfMeasurement(SensorLogParser::UnitOfMeasurementContext * /*ctx*/) override { }

  virtual void enterUnitPart(SensorLogParser::UnitPartContext * /*ctx*/) override { }
  virtual void exitUnitPart(SensorLogParser::UnitPartContext * /*ctx*/) override { }

  virtual void enterDeviceId(SensorLogParser::DeviceIdContext * /*ctx*/) override { }
  virtual void exitDeviceId(SensorLogParser::DeviceIdContext * /*ctx*/) override { }

  virtual void enterPadding(SensorLogParser::PaddingContext * /*ctx*/) override { }
  virtual void exitPadding(SensorLogParser::PaddingContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

