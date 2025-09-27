# Parse a test file
SAMPLE_FILE = "../../samples/example_header.log"

def main():
    from sensorlog_wrapper import SensorLogParserWrapper
    import json

    wrapper = SensorLogParserWrapper()
    tree, parser, result = wrapper.parse_file(SAMPLE_FILE)

    if result is not None:
        print(json.dumps(result, indent=2))
    else:
        # fallback: print the parse tree
        print(tree.toStringTree(recog=parser))


if __name__ == '__main__':
    main()