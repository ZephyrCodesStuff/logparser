grammar SensorLog;

// Parser Rules

// Entry point - the entire file structure
file: DOLLAR_SPACE deviceDefinitions BACKSLASH padding? EOF;

// Multiple device definitions separated by spaces
deviceDefinitions: deviceDefinition (SPACE deviceDefinition)*;

// A single device definition enclosed in pipes
deviceDefinition: PIPE deviceContent PIPE;

// Device content: name followed by sensor definitions and device ID
deviceContent:
	deviceName (SPACE sensorDefinition)+ SPACE deviceId;

// Device name (IMU, GPS, ALT, MAG, PIT, PWR)
deviceName: IDENTIFIER;

// Sensor definition in angle brackets
sensorDefinition:
	LT sensorName COMMA dataType COMMA unitOfMeasurement GT;

// Sensor name - can contain multiple words separated by spaces
sensorName: sensorNamePart (SPACE sensorNamePart)*;

// Part of a sensor name (word or number)
sensorNamePart: IDENTIFIER | NUMBER;

// Data type specification
dataType:
	U8_TYPE
	| U16_TYPE
	| U32_TYPE
	| U64_TYPE
	| S8_TYPE
	| S16_TYPE
	| S32_TYPE
	| S64_TYPE
	| FLOAT_TYPE
	| DOUBLE_TYPE;

// Unit of measurement
unitOfMeasurement:
	unitPart (SLASH unitPart)?; // For compound units like m/s, mdeg/s

// Part of a unit (can be identifier or number)
unitPart: IDENTIFIER | NUMBER;

// 8-digit device ID in angle brackets
deviceId: LT DEVICE_ID_NUMBER GT;

// Optional padding at the end for 16-byte alignment
padding:
	.; // Match any remaining characters (control chars for padding)

// Lexer Rules

// Literals
DOLLAR_SPACE: '$ ';
PIPE: '|';
LT: '<';
GT: '>';
COMMA: ',';
BACKSLASH: '\\';
SLASH: '/';

// Data types
U8_TYPE: 'u8';
U16_TYPE: 'u16';
U32_TYPE: 'u32';
U64_TYPE: 'u64';
S8_TYPE: 's8';
S16_TYPE: 's16';
S32_TYPE: 's32';
S64_TYPE: 's64';
FLOAT_TYPE: 'float';
DOUBLE_TYPE: 'double';

// Device ID - exactly 8 digits
DEVICE_ID_NUMBER:
	DIGIT DIGIT DIGIT DIGIT DIGIT DIGIT DIGIT DIGIT;

// Basic identifiers and numbers
IDENTIFIER: LETTER (LETTER | DIGIT | '_')*;
NUMBER: DIGIT+ ('.' DIGIT+)?;

// Fragments for basic character classes
fragment LETTER: [a-zA-Z];
fragment DIGIT: [0-9];

// Single space (important: don't skip spaces as they're meaningful in sensor names)
SPACE: ' ';

// Skip other whitespace (newlines, tabs, carriage returns)
WS: [\t\r\n]+ -> skip;

// Catch any other characters (for padding at the end)
ANY: .;