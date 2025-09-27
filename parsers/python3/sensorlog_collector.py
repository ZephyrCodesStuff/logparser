from typing import List, Dict
from gen.SensorLogListener import SensorLogListener
from gen.SensorLogParser import SensorLogParser


class SensorLogCollector(SensorLogListener):
    """Listener that builds a nested Python structure from the parse tree.

    Result format:
        { 'devices': [ { 'name': str, 'id': str, 'sensors': [ { 'name': str, 'data_type': str, 'unit': str }, ... ] }, ... ] }
    """

    def __init__(self):
        self.devices: List[Dict] = []
        self._current_device: Dict = None

    def enterFile(self, ctx:SensorLogParser.FileContext):
        self.devices = []

    def enterDeviceContent(self, ctx:SensorLogParser.DeviceContentContext):
        # start a new device record
        self._current_device = { 'name': None, 'id': None, 'sensors': [] }

    def exitDeviceName(self, ctx:SensorLogParser.DeviceNameContext):
        # deviceName is a single IDENTIFIER
        ident = ctx.IDENTIFIER()
        if ident is not None:
            self._current_device['name'] = ident.getText()

    def exitDeviceId(self, ctx:SensorLogParser.DeviceIdContext):
        # DEVICE_ID_NUMBER is the numeric id token
        token = ctx.DEVICE_ID_NUMBER()
        if token is not None:
            self._current_device['id'] = token.getText()

    def exitSensorDefinition(self, ctx:SensorLogParser.SensorDefinitionContext):
        # Build sensor dict from child contexts
        # sensor name: join sensorNamePart tokens with spaces
        name_ctx = ctx.sensorName()
        parts = []
        if name_ctx is not None:
            for p in name_ctx.sensorNamePart():
                parts.append(p.getText())
        name = ' '.join(parts)

        data_type = None
        dt = ctx.dataType()
        if dt is not None:
            data_type = dt.getText()

        unit = None
        uom = ctx.unitOfMeasurement()
        if uom is not None:
            unit_parts = [p.getText() for p in uom.unitPart()]
            unit = '/'.join(unit_parts)

        sensor = { 'name': name, 'data_type': data_type, 'unit': unit }
        self._current_device['sensors'].append(sensor)

    def exitDeviceContent(self, ctx:SensorLogParser.DeviceContentContext):
        # device complete, append to devices
        if self._current_device is not None:
            self.devices.append(self._current_device)
            self._current_device = None

    def get_result(self):
        return { 'devices': self.devices }
