import xmlrpc.client
from xmlrpc.server import SimpleXMLRPCServer
import example.string_methods as string_methods

def methods_for_string(line, symbol):
    words = string_methods.number_of_words(line)
    symbols = string_methods.number_of_symbols(line)
    universal_symbols = string_methods.number_of_universal_symbols(line)
    defined_symbols = string_methods.number_of_defined_characters(line, symbol)
    
    return {
        "line": line,
        "words": words,
        "symbols": symbols,
        "universal_symbols": universal_symbols,
        "defined_symbols": defined_symbols,
        "symbol": symbol
    }

# Запуск сервера
server = SimpleXMLRPCServer(("localhost", 9000))
print("Listening on port 9000...")
server.register_function(methods_for_string, "methods_for_string")
server.serve_forever()

