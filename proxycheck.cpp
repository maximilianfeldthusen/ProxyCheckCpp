#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <curl/curl.h>

class ProxyChecker {
private:
    std::vector<std::string> proxyList;

    void loadProxyList(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;
        while (std::getline(file, line)) {
            proxyList.push_back(line);
        }
    }

    bool isInProxyList(const std::string& ip) {
        return std::find(proxyList.begin(), proxyList.end(), ip) != proxyList.end();
    }

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
        size_t totalSize = size * nmemb;
        userp->append(static_cast<char*>(contents), totalSize);
        return totalSize;
    }

    bool checkWithExternalService(const std::string& ip) {
        CURL* curl;
        CURLcode res;
        std::string readBuffer;

        curl = curl_easy_init();
        if(curl) {
            std::string url = "http://api.proxycheck.io/v2/" + ip + "?key=YOUR_API_KEY"; // Replace with your actual API key
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            }

            curl_easy_cleanup(curl);
        } else {
            std::cerr << "Failed to initialize CURL." << std::endl;
        }

        return readBuffer.find("\"proxy\": true") != std::string::npos;
    }

public:
    ProxyChecker(const std::string& filename) {
        loadProxyList(filename);
    }

    bool isProxy(const std::string& ip) {
        if (isInProxyList(ip)) {
            return true;
        }
        return checkWithExternalService(ip);
    }
};

int main() {
    ProxyChecker checker("proxies.txt");
    std::string ip;

    std::cout << "Enter IP address to check: ";
    std::cin >> ip;

    if (checker.isProxy(ip)) {
        std::cout << ip << " is a proxy." << std::endl;
    } else {
        std::cout << ip << " is not a proxy." << std::endl;
    }

    return 0;
}
