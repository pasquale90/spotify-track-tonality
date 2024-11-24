#include "spotifeye.h"
#include <cstddef>
#include <iostream>


/*
TODOS:
check if credentials are already set
implement 
    readEncryptedCredentials
    storeEncryptedCredentials
*/

namespace sp_key_mappings {
    std::vector<std::string> keys = {"C","C#/Db","D","D#/Eb","E","F","F#/Gb","G","G#/Ab","A","A#/Bb","B"};
    std::vector<std::string> modes = {"minor","major"};
}

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

Spotifeye::Spotifeye(const std::string& filePath) : jsonFile(filePath){
    curl_global_init( CURL_GLOBAL_ALL );
    readCredentials();
}

bool Spotifeye::setup_user(){
#ifdef ENCRYPTION
    std::cout<<
#else
    // Get authorization URL
    std::string authURL = getAuthorizationURL();
    
    // Prompt user to paste the authorization code
    std::cout << "\nPlease visit the following URL to authorize the application:\n" << authURL << "\n"<<std::endl;
    std::cout << "After authorization, you will be redirected to a URL. \nTo verify your account, please enter that URL here and press ENTER:\n\tURL:";
    std::string code;
    std::cin >> code;
    std::cout<<std::endl;

    // Exchange code for tokens
    std::string accessToken;
    if (!requestAccessToken(code,accessToken,"code=")){
        if (!refreshAccessToken(accessToken))
            return false;
    }

    // Make a test API request --> get current user's profile.
    testAccessToken(accessToken);

    storeCredentials(accessToken);

    return true;
#endif
}


bool Spotifeye::update_result(std::vector<std::string> &result ){

       // Exchange code for tokens
    std::string accessToken;
    
    // refresh accessToken in each call
    if (!refreshAccessToken(accessToken))
        return false;
    
    return getCurrentPlayback(accessToken, result);

}

nlohmann::json Spotifeye::curlUtils(std::string url, std::string header, std::string postFields=""){
    CURL* curl;
    nlohmann::json jsonResponse;

    curl = curl_easy_init();
    if(curl) {

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, header.c_str());

        std::string readBuffer;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        if(!postFields.empty())
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());
        
        int rc = curl_easy_perform(curl);
        if (rc != CURLE_OK)
            throw CurlException(rc);

        long statusCode = 0;
        curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &statusCode);
        if(statusCode < 200 || statusCode > 204)
// HINT : Disabled SpotifyException
            // throw SpotifyException(Error(nlohmann::json::parse(readBuffer)["error"]));
            std::cout<<"SpotifyException with status code "<<statusCode<<std::endl;

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
        if(readBuffer.empty())
            return nlohmann::json();
        return nlohmann::json::parse(readBuffer);
    }
    return nlohmann::json();

}

// Function to read a JSON file and return a `json` object
void Spotifeye::readCredentials() {
    std::ifstream inputFile(jsonFile); 
    if (!inputFile.is_open()) {
        throw std::runtime_error("Could not open file for reading: " + jsonFile);
    }
    nlohmann::json data;
    inputFile >> data;
    inputFile.close();

    client_id = data["client_id"];
    client_secret = data["client_secret"];
    redirect_uri = data["redirect_uri"];

    if (data.contains("refresh_token")){
        refresh_token = data["refresh_token"];
    }
}

// Function to save a `json` object to a file
void Spotifeye::storeCredentials(std::string const& access_token) {
    
    std::ofstream outputFile(jsonFile);
    if (!outputFile.is_open()) {
        throw std::runtime_error("Could not open file for writing: " + jsonFile);
    }

    nlohmann::json jsonData;
    jsonData["client_id"] = client_id;
    jsonData["client_secret"] = client_secret;
    jsonData["redirect_uri"] = redirect_uri;
    jsonData["refresh_token"] = refresh_token;
    jsonData["access_token"] = access_token;

    outputFile << jsonData.dump(4); // Write the JSON data with an indentation of 4 spaces
    outputFile.close();
}

// Function to get authorization URL
std::string Spotifeye::getAuthorizationURL() {
    std::string url = "https://accounts.spotify.com/authorize?";
    url += "response_type=code";
    url += "&client_id=" + client_id;
    url += "&redirect_uri=" + std::string(curl_easy_escape(NULL, redirect_uri.c_str(), redirect_uri.length()));
    url += "&scope=" + std::string(curl_easy_escape(NULL, scope.c_str(), scope.length()));
    return url;
}

// Function to request tokens
bool Spotifeye::requestAccessToken(const std::string urlResponse, std::string &accessToken, std::string const& identifier) {

    // parse code from the url
    std::string code = urlResponse.substr( urlResponse.find(identifier) + identifier.length() );

    std::string url = "https://accounts.spotify.com/api/token";
    std::string header = "Content-Type: application/x-www-form-urlencoded";
    std::string postFields = "grant_type=authorization_code";
    postFields += "&code=" + code;
    postFields += "&redirect_uri=" + std::string(curl_easy_escape(NULL, redirect_uri.c_str(), redirect_uri.length()));
    postFields += "&client_id=" + client_id;
    postFields += "&client_secret=" + client_secret;
    
    nlohmann::json response = curlUtils( url, header ,postFields);

    // std::string ;
    if(response.find("access_token") == response.end()) {
        std::cerr << "Failed to obtain access token. Response:\n" << response.dump(4) << "\n";
        return false;
    } 

    accessToken = response["access_token"];
    refresh_token = response["refresh_token"];
    std::cout<<"Access Token is set succesfully!"<<std::endl;
    std::cout << "Refresh Token is set succesfully!"<<std::endl;
    return true;
}

bool Spotifeye::refreshAccessToken(std::string& accessToken) {

    std::string url = "https://accounts.spotify.com/api/token";
    std::string header = "Content-Type: application/x-www-form-urlencoded";
    std::string postFields = "grant_type=refresh_token";
    postFields += "&refresh_token=" + refresh_token;
    postFields += "&client_id=" + client_id;
    postFields += "&client_secret=" + client_secret;
    nlohmann::json newTokens = curlUtils( url, header ,postFields);

    if(newTokens.find("access_token") != newTokens.end()) {

        // assign a new access Token. 
        // These are expired after a short period. `newTokens["expires_in"]` returns the time they remain valid in seconds.
        accessToken = newTokens["access_token"];

        // check if refresh_token is also updated
        if(newTokens.find("refresh_token") != newTokens.end()) {
            refresh_token = newTokens["refresh_token"];
            std::cout << "New Refresh Token: " << refresh_token << "\n";
        }
        return true;
    } 
    std::cerr << "Failed to refresh access token. Response:\n" << newTokens.dump(4) << "\n";
    return false;
}

bool Spotifeye::testAccessToken(const std::string& accessToken) {
    
    std::string url = "https://api.spotify.com/v1/me";
    std::string header = "Authorization: Bearer " + accessToken;

    nlohmann::json userInfo = curlUtils( url, header);

    if(userInfo.find("display_name") == userInfo.end()) {
        std::cout << "TEST FAILED : Failed to obtain account name. Response:\n" << userInfo.dump(4) << "\n";
        return false;
    } else {
        // std::cout << "User Profile:\n" << jsonResponse.dump(4) << "\n";
        std::cout<<userInfo["display_name"]<<" has authorized Eyeharp 's spotify API succesfully!"<<std::endl;
        return true;
    }

}

bool Spotifeye::getCurrentPlayback(const std::string& accessToken, std::vector<std::string> &playback) {

    std::string url = "https://api.spotify.com/v1/me/player/currently-playing";
    std::string header = "Authorization: Bearer " + accessToken;
    
    nlohmann::json playbackInfo = curlUtils( url, header);


    if (!playbackInfo.is_null()) {

        if (playbackInfo.contains("item") && playbackInfo["item"].is_object()) {
            
            nlohmann::json track = playbackInfo["item"];
            
            // playback[0] = track["artists"][0]["name"];
            auto artists = track["artists"];
            if (artists.size()==1)
                playback[0] = artists[0]["name"];
            else{
                playback[0]="[";
                for (size_t i = 0; i< artists.size(); ++i){
                    playback[0]+=artists[i]["name"];
                    playback[0]+=',';
                }
                playback[0][playback[0].size()-1] = ']';
            }
            
            playback[1] = track["name"];
            
            // ... (Extract other features)
            return getAudioFeatures(accessToken, track["id"], playback);
        }    
    }
    
    // "No playback information available
    return false;

}

bool Spotifeye::getAudioFeatures(const std::string& accessToken, const std::string& trackId, std::vector<std::string> &playback) {
    
    std::string url = "https://api.spotify.com/v1/audio-features/" + trackId;
    std::string header = "Authorization: Bearer " + accessToken;
    
    nlohmann::json audioFeatures = curlUtils( url, header);

    if (!audioFeatures.is_null()) {    
        int key = audioFeatures["key"]; // track's key
        int mode = audioFeatures["mode"]; // 0 = minor, 1 = major
        playback[2]=sp_key_mappings::keys[key];
        playback[3] = sp_key_mappings::modes[mode];
        return true;
    }   
    return false;     
}