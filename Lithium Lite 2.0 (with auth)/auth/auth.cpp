#define CURL_STATICLIB
#include "../main.h"
#include "crypto/sha256.h"
#include "crypto/sha512.h"
#include "json.h"
using json = nlohmann::json;

#define CURL_STATICLIB
#pragma comment (lib, "Normaliz.lib")
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Wldap32.lib")
#pragma comment (lib, "Crypt32.lib")
#pragma comment (lib, "advapi32.lib")
#pragma comment (lib, "../lib/curl/lib/libcurl_a.lib")
#include "../lib/curl/include/curl/curl.h"

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

std::vector<char>* v::auth::getreq(std::string* params, int extra)
{
    VM_FISH_BLACK_START
    std::vector<char>* buf = new std::vector<char>();
    std::string* response = new std::string();

    CURL* curl = curl_easy_init();
    CURLcode res;

    if (curl) {

        if (extra == 0)
            curl_easy_setopt(curl, CURLOPT_URL, lith_host);
        else if (extra == 1)
            curl_easy_setopt(curl, CURLOPT_URL, lith_security_host);
        if (md5(sha512(lith_host)) != xorstr("494d11d248abbbb952daa02162833191"))
            exit(0);
        if (md5(sha512(lith_security_host)) != xorstr("6d8423a62eb5dd7e84d8e8f252b9fdf0"))
            exit(0);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params->c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)params->length());
        curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_DEFAULT);

        res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            for (const auto& i : *response)
                buf->push_back(i);

            delete response;
        }

        curl_easy_cleanup(curl);
    }
    VM_FISH_BLACK_END
    return buf;
}

int v::auth::authenticate(std::string hwid, std::string token)
{
    VM_FISH_BLACK_START
    char path[MAX_PATH];
    GetModuleFileName(0, path, MAX_PATH);

    std::ifstream file(path, std::ios::binary | std::ios::in | std::ios::ate);
    uint64_t uid = 0;
    if (file.is_open() && file.good()) {

        size_t size = file.tellg();
        char* memblock = new char[size];
        file.seekg(0, std::ios::beg);
        file.read(memblock, size);
        file.close();

        uint8_t out[8];

        unsigned int pos = 0;
        for (unsigned int i = size - 8; i < size; i++) {

            out[pos] = (uint8_t)memblock[i];
            pos++;
        }
        delete[] memblock;

        const auto u8tou64 = [](uint8_t const u8[8]) {

            uint64_t u64;
            memcpy(&u64, u8, sizeof u64);
            return u64;
        };

        uid = u8tou64(out);
    }

    std::string response;
    std::string* params = new std::string(xorstr("ver=") + (std::string)v::info::version + xorstr("&hwid=") + hwid + xorstr("&token=") + token + xorstr("&alts=") + get_alts_str() + xorstr("&exe=") + std::to_string(uid));

    std::vector<char>* buf = getreq(params, 0);

    delete params;

    if (buf->size() != 128) {
        delete buf;
        return v::auth::error;
    }

    for (const auto& i : *buf)
        response.push_back(i);
    delete buf;

    if (response.empty() || response.size() != 128) {
        return v::auth::error;
    }
    else if (response == sha512(picosha2::hash256_hex_string(sha512(xorstr("thankyou")) + sha512(v::info::version) + sha512(hwid) + sha512(token)))) {

        if (strcmp(response.c_str(), sha512(picosha2::hash256_hex_string(sha512(xorstr("thankyou")) + sha512(v::info::version) + sha512(hwid) + sha512(token))).c_str()) == 0) {

            if (response.find(sha512(picosha2::hash256_hex_string(sha512(xorstr("thankyou")) + sha512(v::info::version) + sha512(hwid) + sha512(token)))) != std::string::npos) {

                return v::auth::authenticated;
            }
        }
    }
    else if (response == sha512(picosha2::hash256_hex_string(sha512(xorstr("nothanks")) + sha512(v::info::version) + sha512(token)))) {

        if (strcmp(response.c_str(), sha512(picosha2::hash256_hex_string(sha512(xorstr("nothanks")) + sha512(v::info::version) + sha512(token))).c_str()) == 0) {

            if (response.find(sha512(picosha2::hash256_hex_string(sha512(xorstr("nothanks")) + sha512(v::info::version) + sha512(token)))) != std::string::npos) {

                return v::auth::not_authorized;
            }
        }
    }
    else if (response == sha512(picosha2::hash256_hex_string(sha512(xorstr("outdated")) + sha512(v::info::version) + sha512(token)))) {

        if (strcmp(response.c_str(), sha512(picosha2::hash256_hex_string(sha512(xorstr("outdated")) + sha512(v::info::version) + sha512(token))).c_str()) == 0) {

            if (response.find(sha512(picosha2::hash256_hex_string(sha512(xorstr("outdated")) + sha512(v::info::version) + sha512(token)))) != std::string::npos) {

                return v::auth::outdated;
            }
        }
    }
    VM_FISH_BLACK_END
    return v::auth::error;
}