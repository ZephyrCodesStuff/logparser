"""Wrapper class around the generated ANTLR lexer/parser for SensorLog.

Provides convenient methods to parse from a file or from a string and
optionally walk the parse tree with a provided listener. By default it
uses the `SensorLogCollector` to return a Python structure of the parsed
data which is convenient to convert to JSON.
"""
from typing import Optional, Tuple


class SensorLogParserWrapper:
    """Encapsulate the creation and use of the generated lexer/parser.

    Methods:
        parse_file(path) -> (tree, parser, result)
        parse_string(text) -> (tree, parser, result)

    If `result` is not None it contains a Python structure produced by
    the listener (e.g. `SensorLogCollector.get_result()`).
    """

    def __init__(self, listener: Optional[object] = None):
        # default listener builds a Python structure of the parsed data
        if listener is None:
            try:
                from sensorlog_collector import SensorLogCollector
            except Exception:
                # lazy import fallback in case module path differs
                from SensorLogCollector import SensorLogCollector
            listener = SensorLogCollector()
        self.listener = listener

    def parse_file(self, path: str) -> Tuple[object, object, object]:
        from antlr4 import FileStream, CommonTokenStream, ParseTreeWalker
        from gen.SensorLogLexer import SensorLogLexer
        from gen.SensorLogParser import SensorLogParser

        input_stream = FileStream(path, encoding='utf-8')
        lexer = SensorLogLexer(input_stream)
        stream = CommonTokenStream(lexer)
        parser = SensorLogParser(stream)

        tree = parser.file_()

        if self.listener is not None:
            walker = ParseTreeWalker()
            walker.walk(self.listener, tree)

        result = None
        if hasattr(self.listener, 'get_result'):
            result = self.listener.get_result()

        return tree, parser, result

    def parse_string(self, text: str) -> Tuple[object, object, object]:
        from antlr4 import InputStream, CommonTokenStream, ParseTreeWalker
        from gen.SensorLogLexer import SensorLogLexer
        from gen.SensorLogParser import SensorLogParser

        input_stream = InputStream(text)
        lexer = SensorLogLexer(input_stream)
        stream = CommonTokenStream(lexer)
        parser = SensorLogParser(stream)

        tree = parser.file_()

        if self.listener is not None:
            walker = ParseTreeWalker()
            walker.walk(self.listener, tree)

        result = None
        if hasattr(self.listener, 'get_result'):
            result = self.listener.get_result()

        return tree, parser, result
