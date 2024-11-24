#ifndef SPOTIFEYE_H
#define SPOTIFEYE_H

#include <fstream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
// #include "Error.h"
// #include "json.h"
#include "curlException.h"

class Spotifeye{
public:
    /*! @brief Class constructor. 
     * Initializes curl. 
     * Initializes member variables {client_id,client_secret,redirect_uri,refresh_token} from the values stored within the credentials/spotify.json 
     * @param string jsonPath - the absolute path of credentials/spotify.json 
     */
    Spotifeye(const std::string&);

    /*! @brief Function used to authenticate user for the first time, and to set the values for {refresh_token} + {authToken}.
     * @HINT:The {authToken} is a temporary token, refreshed when expired using the {refresh_token}.
     * @return bool - True if the User authentication was successful. Otherwise, false.
     */    
    bool setup_user();

    /*! @brief Function used to retrieve the current playback from the user's Spotify account.
     * @param vector<string>(4) - 4 positions for storing the current playback. 
     * Position 1 stores the list of artists
     * Position 2 stores the track name
     * Position 3 stores the tonality key
     * Position 4 stores the key's mode (minor/major)
     * @return bool - True for a successful retrieval. Otherwise, false.
     */
    bool update_result(std::vector<std::string> &);

private:

    std::string client_id,client_secret,redirect_uri,refresh_token;
    std::string jsonFile;
    const std::string scope {"user-read-playback-state"};


    /*! @brief General function used to formulate the http requests towards the Spotify API, using the libcurl library.
     * @param string url - the Spotify's server's URL
     * @param string header - the http headers appended to the request
     * @param string postFields - data used when making the POST request.
     * @return json data - the response to the API request
     */
    nlohmann::json curlUtils(std::string, std::string, std::string);
    

    /*! @brief Function used to read the User's credentials from a json file.
     * @return void 
     */
    void readCredentials();

    /*! @brief Function which is passed to the ui thread for receiving the input signal from the user and notifying the rest of the program.
     * @param Trigger - the control message that received from the corresponding ui method.
     * @return void 
     */
    void storeCredentials(const std::string&);
    

    /*! @brief Function used to form the authorization URL. This URL is used to redirect the user to authenticate himself via a browser window.
     * @HINT : The authorization is done only once upon the first time of usage. 
     * @HINT 2: After that, the user is redirected to a different URL. 
     * This URL contains the authorization code, and has to be pasted back into the console for further processing.
     * @param Trigger - the control message that received from the corresponding ui method.
     * @return void 
     */
    std::string getAuthorizationURL();

    /*! @brief Function to process the authorization code. This function is responsible for creating the accessToken and the refresh_token.
     * @param const string urlResponse - the URL pasted back into the console from the user
     * @param string &accessToken - the accessToken passed by reference so as to be set. 
     * @param string const& identifier - string that is used to parse the urlResponse.
     * @return bool - indicates whether the accessToken is set succesfully.
     */
    bool requestAccessToken(const std::string, std::string&, const std::string& identifier="code=");

    /*! @brief Function used to refresh the accessToken. The accessToken has a limited durability, thus, has to be occasionally refreshed.
     * @param string& accessToken - - the accessToken passed by reference so as to be updated. 
     * @return bool - indicates whether the accessToken is updated succesfully.
     */
    bool refreshAccessToken(std::string&);


    /*! @brief Function used to test the accessToken and to print hello to the user.
     * @param const string& accessToken - the accessToken used to apply the POST request.
     * @return bool - True if test is succeeded, otherwise false.
     */
    bool testAccessToken(const std::string&);    

    /*! @brief Function used to retrieve the current playback. This function is responsible for setting the first two positions of the resulted vector.
     * @param const std::string&
     * @param vector<std::string>(4) - 4 positions for storing the current playback. 
     * sets the Position 1 with the list of artists
     * sets the Position 2 with the track name
     * @return bool - True for a successful retrieval. Otherwise, false.
     */
    bool getCurrentPlayback(const std::string&, std::vector<std::string> &);
    
    /*! @brief Function used to retrieve the current playback. This function is responsible for setting the last two positions of the resulted vector.
     * @param vector<std::string>(4) - 4 positions for storing the current playback. 
     * sets the Position 3 with the tonality key
     * sets the Position 4 with the key's mode (minor/major)
     * @return bool - True for a successful retrieval. Otherwise, false.
     */
    bool getAudioFeatures(const std::string&, const std::string&, std::vector<std::string>&);

};  
#endif