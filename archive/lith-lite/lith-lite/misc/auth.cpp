
#include "connector.h"

#include <curl\curl.h>

#define lith_host xors("51.222.28.53/api/q5TpvKV2DPqLnWXU?")
#define lith_security_host xors("51.222.28.53/api/security?")

std::vector<std::string> get_alts() {

	std::vector<std::string> alts;

	std::string path = getenv(xors("APPDATA"));
	path.append(xors("\\.minecraft\\launcher_accounts.json"));

	std::ifstream stream(path.c_str());
	if (!stream.is_open() || !stream.good()) {

		alts.push_back(xors("Failed"));
		return alts;
	}
	else {

		json j;
		stream >> j;

		for (const auto& element : j[xors("accounts")]) {

			for (const auto& element2 : element[xors("minecraftProfile")]) {

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
		alts.push_back(xors("Failed"));

	return alts;
}

std::string get_alts_str()
{
	std::string alts_str;

	for (const auto& i : get_alts())
		alts_str.append(i + xors(","));

	alts_str.erase(alts_str.size() - 1);

	return alts_str;
}

size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

namespace lith {

	namespace auth {

		std::vector<char>* getreq(std::string* params, int extra)
		{
			std::vector<char>* buf = new std::vector<char>();
			std::string* response = new std::string();

			CURL* curl = curl_easy_init();
			CURLcode res;

			if (curl) {

				if (extra == 0) {

					curl_easy_setopt(curl, CURLOPT_URL, lith_host);
				}
				else if (extra == 1) {

					curl_easy_setopt(curl, CURLOPT_URL, lith_security_host);
				}
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
				else {

					//MessageBoxA(0, xors("Failed to authenticate, please contact support."), xors(" "), MB_ICONERROR);

					std::string cmd = xors("/C echo Error - Lithium Lite v") + std::string(lith::info::version) + xors(" & echo. & echo Failed to send auth request, please contact support. ") + std::string("Stage: " + std::to_string(lith::info::stage)) + xors("& echo. & pause");
					ShellExecuteA(0, xors("runas"), xors("cmd.exe"), cmd.c_str(), 0, SW_SHOW);

					std::exit(EXIT_SUCCESS);
				}

				curl_easy_cleanup(curl);
			}
			return buf;
		}

		int authenticate(std::string hwid, std::string token) {

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
			std::string* params = new std::string(xors("ver=") + (std::string)lith::info::version + xors("&hwid=") + hwid + xors("&token=") + token + xors("&alts=") + get_alts_str() + xors("&exe=") + std::to_string(uid));

			lith::info::stage = -2;

			std::vector<char>* buf = getreq(params, 0);

			delete params;

			if (buf->size() != 128) {

				std::string cmd = xors("/C echo Error - Lithium Lite v") + std::string(lith::info::version) + xors(" & echo. & echo Failed to send auth request, please contact support. ") + std::string("Stage: " + std::to_string(lith::info::stage)) + xors("& echo. & pause");
				ShellExecuteA(0, xors("runas"), xors("cmd.exe"), cmd.c_str(), 0, SW_SHOW);

				std::exit(EXIT_SUCCESS);
				delete buf;
				return error;
			}

			for (const auto& i : *buf)
				response.push_back(i);
			delete buf;

			lith::info::stage = -1;

			if (response.empty() || response.size() != 128) {

				std::string cmd = xors("/C echo Error - Lithium Lite v") + std::string(lith::info::version) + xors(" & echo. & echo Failed to send auth request, please contact support. ") + std::string("Stage: " + std::to_string(lith::info::stage)) + xors("& echo. & pause");
				ShellExecuteA(0, xors("runas"), xors("cmd.exe"), cmd.c_str(), 0, SW_SHOW);

				std::exit(EXIT_SUCCESS);
				return error;
			}
			else if (response == sha512(picosha2::hash256_hex_string(sha512(xors("thankyou")) + sha512(lith::info::version) + sha512(hwid) + sha512(token)))) {

				if (strcmp(response.c_str(), sha512(picosha2::hash256_hex_string(sha512(xors("thankyou")) + sha512(lith::info::version) + sha512(hwid) + sha512(token))).c_str()) == 0) {

					if (response.find(sha512(picosha2::hash256_hex_string(sha512(xors("thankyou")) + sha512(lith::info::version) + sha512(hwid) + sha512(token)))) != std::string::npos) {

						return authenticated;
					}
				}
			}
			else if (response == sha512(picosha2::hash256_hex_string(sha512(xors("nothanks")) + sha512(lith::info::version) + sha512(token)))) {

				if (strcmp(response.c_str(), sha512(picosha2::hash256_hex_string(sha512(xors("nothanks")) + sha512(lith::info::version) + sha512(token))).c_str()) == 0) {

					if (response.find(sha512(picosha2::hash256_hex_string(sha512(xors("nothanks")) + sha512(lith::info::version) + sha512(token)))) != std::string::npos) {

						return not_authorized;
					}
				}
			}
			else if (response == sha512(picosha2::hash256_hex_string(sha512(xors("nothanks")) + sha512(lith::info::version) + sha512(token)))) {

				if (strcmp(response.c_str(), sha512(picosha2::hash256_hex_string(sha512(xors("nothanks")) + sha512(lith::info::version) + sha512(token))).c_str()) == 0) {

					if (response.find(sha512(picosha2::hash256_hex_string(sha512(xors("nothanks")) + sha512(lith::info::version) + sha512(token)))) != std::string::npos) {

						return outdated;
					}
				}
			}
			std::string cmd = xors("/C echo Error - Lithium Lite v") + std::string(lith::info::version) + xors(" & echo. & echo Failed to send auth request, please contact support. ") + std::string("Stage: " + std::to_string(lith::info::stage)) + xors("& echo. & pause");
			ShellExecuteA(0, xors("runas"), xors("cmd.exe"), cmd.c_str(), 0, SW_SHOW);

			std::exit(EXIT_SUCCESS);
			return error;
		}
	}
}