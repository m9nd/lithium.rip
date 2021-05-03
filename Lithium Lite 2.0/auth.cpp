/*
#define CURL_STATICLIB
#include "../main.h"
#include "crypto/sha256.h"
#include "crypto/sha512.h"
#include "json.h"

#define CURL_STATICLIB
#pragma comment (lib, "Normaliz.lib")
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Wldap32.lib")
#pragma comment (lib, "Crypt32.lib")
#pragma comment (lib, "advapi32.lib")
#pragma comment (lib, "../lib/curl/lib/libcurl_a.lib")
#include "../../../../../../curl/include/curl/curl.h"

std::vector<std::string> get_alts()
{
    std::vector<std::string> alts;

    std::string path = getenv(xorstr("APPDATA"));
    path.append(xorstr("\\.minecraft\\launcher_accounts.json"));

    std::ifstream stream(path.c_str());
    if (!stream.is_open() || !stream.good()) {
        alts.push_back(xorstr("Failed"));
        return alts;
    }
    else {

        json j;
        stream >> j;

        for (const auto& element : j[xorstr("accounts")]) {

            for (const auto& element2 : element[xorstr("minecraftProfile")]) {

                static int counter = 0;
                counter++;
                if (counter == 2) {

                    counter = 0;
                    if (std::find(alts.begin(), alts.end(), element2) == alts.end())
                        alts.push_back(element2);
                }
            }
        }
    }

    if (alts.size() == 0)
        alts.push_back(xorstr("Failed"));

    return alts;
}

std::string get_alts_str()
{
    std::string alts_str;

    for (const auto& i : get_alts())
        alts_str.append(i + xorstr(","));

    alts_str.erase(alts_str.size() - 1);

    return alts_str;
}

size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
*/