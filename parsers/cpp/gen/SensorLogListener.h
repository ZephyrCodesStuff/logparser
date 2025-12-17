
// Generated from ./gen/SensorLog.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "SensorLogParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by SensorLogParser.
 */
class  SensorLogListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterFile(SensorLogParser::FileContext *ctx) = 0;
  virtual void exitFile(SensorLogParser::FileContext *ctx) = 0;

  virtual void enterDeviceDefinitions(SensorLogParser::DeviceDefinitionsContext *ctx) = 0;
  virtual void exitDeviceDefinitions(SensorLogParser::DeviceDefinitionsContext *ctx) = 0;

  virtual void enterDeviceDefinition(SensorLogParser::DeviceDefinitionContext *ctx) = 0;
  virtual void exitDeviceDefinition(SensorLogParser::DeviceDefinitionContext *ctx) = 0;

  virtual void enterDeviceContent(SensorLogParser::DeviceContentContext *ctx) = 0;
  virtual void exitDeviceContent(SensorLogParser::DeviceContentContext *ctx) = 0;

  virtual void enterDeviceName(SensorLogParser::DeviceNameContext *ctx) = 0;
  virtual void exitDeviceName(SensorLogParser::DeviceNameContext *ctx) = 0;

  virtual void enterSensorDefinition(SensorLogParser::SensorDefinitionContext *ctx) = 0;
  virtual void exitSensorDefinition(SensorLogParser::SensorDefinitionContext *ctx) = 0;

  virtual void enterSensorName(SensorLogParser::SensorNameContext *ctx) = 0;
  virtual void exitSensorName(SensorLogParser::SensorNameContext *ctx) = 0;

  virtual void enterSensorNamePart(SensorLogParser::SensorNamePartContext *ctx) = 0;
  virtual void exitSensorNamePart(SensorLogParser::SensorNamePartContext *ctx) = 0;

  virtual void enterDataType(SensorLogParser::DataTypeContext *ctx) = 0;
  virtual void exitDataType(SensorLogParser::DataTypeContext *ctx) = 0;

  virtual void enterUnitOfMeasurement(SensorLogParser::UnitOfMeasurementContext *ctx) = 0;
  virtual void exitUnitOfMeasurement(SensorLogParser::UnitOfMeasurementContext *ctx) = 0;

  virtual void enterUnitPart(SensorLogParser::UnitPartContext *ctx) = 0;
  virtual void exitUnitPart(SensorLogParser::UnitPartContext *ctx) = 0;

  virtual void enterDeviceId(SensorLogParser::DeviceIdContext *ctx) = 0;
  virtual void exitDeviceId(SensorLogParser::DeviceIdContext *ctx) = 0;

  virtual void enterPadding(SensorLogParser::PaddingContext *ctx) = 0;
  virtual void exitPadding(SensorLogParser::PaddingContext *ctx) = 0;


};

