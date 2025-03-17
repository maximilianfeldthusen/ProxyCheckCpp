
## Documentation

### ProxyCheckCpp

This C++ program is designed to check whether a given IP address is a proxy by using a local list of proxies and an external web service. Let's break down the code step by step:

### Libraries Included
- `#include <iostream>`: This library is used for input and output operations.
- `#include <vector>`: This library provides the `std::vector` container which is used to store the list of proxies.
- `#include <string>`: This library allows the use of the `std::string` class for string manipulation.
- `#include <fstream>`: This library is used for file input and output, allowing the program to read the proxy list from a file.
- `#include <algorithm>`: This library provides algorithms like `std::find` used for searching in the vector.
- `#include <curl/curl.h>`: This library is used for making HTTP requests. It provides the capability to query the external proxy-checking service.

### ProxyChecker Class
The `ProxyChecker` class encapsulates the functionality for checking whether an IP address is a proxy.

#### Private Members
- **proxyList**: A vector of strings that holds the list of proxy IPs.

#### Private Methods
1. **loadProxyList**: 
   - Takes a filename as input.
   - Reads the file line by line and populates the `proxyList` vector with the IPs.

2. **isInProxyList**: 
   - Checks if a given IP is present in the `proxyList`. It returns `true` if found, otherwise `false`.

3. **WriteCallback**: 
   - A static method used as a callback for the `libcurl` library. It appends the data received from the HTTP request to a string.

4. **checkWithExternalService**: 
   - Uses `libcurl` to send a GET request to an external proxy-checking API.
   - Constructs the URL using the provided IP and an API key (placeholder `YOUR_API_KEY` should be replaced with an actual key).
   - If the request is successful, it checks the response for the presence of `"proxy": true`, indicating that the IP is a proxy.

#### Public Methods
1. **ProxyChecker Constructor**: 
   - Takes a filename as input and loads the proxy list from that file by calling `loadProxyList`.

2. **isProxy**: 
   - Checks if the given IP is in the local proxy list. If not, it calls `checkWithExternalService` to check against the external service.

### Main Function
The `main` function is the entry point of the program.
- It creates an instance of `ProxyChecker`, loading proxies from a file named "proxies.txt".
- It prompts the user to enter an IP address to check.
- It calls the `isProxy` method of the `ProxyChecker` instance with the provided IP and prints whether the IP is a proxy or not.

### Summary
In summary, this program provides a way to check if an IP address is a proxy by:
1. Checking a local list of proxies.
2. Making an HTTP request to an external service if the IP is not found in the local list. 

Make sure to replace `YOUR_API_KEY` with an actual API key for the external service to use the program successfully.

