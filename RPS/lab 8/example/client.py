import xmlrpc.client

server = xmlrpc.client.ServerProxy("http://localhost:9000/")
try:
    response = server.methods_for_string(
        "Hello, my name is Willy. I am from the USA. My profession is a programmer.", 'a'
    )
    print(f"String: {response['line']}\n"
          f"There are {response['words']} words\n"
          f"There are {response['symbols']} symbols\n"
          f"There are {response['universal_symbols']} universal symbols\n"
          f"There are {response['defined_symbols']} symbols '{response['symbol']}'\n")
except Exception as e:
    print("Error: ", e)