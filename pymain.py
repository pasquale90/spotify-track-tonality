from sp_key_mapping import keys,modes
import spotipy
from spotipy.oauth2 import SpotifyOAuth

class Spotifeye:
    # Constructor
    def __init__(self,client_id,secret_id,redirect_uri):
        self.client_id=client_id
        self.secret_id=secret_id
        self.redirect_uri=redirect_uri
        my_scopes = 'user-read-playback-state'
        
        self.sp = spotipy.Spotify(auth_manager=SpotifyOAuth(client_id=client_id,
                                            client_secret=secret_id,
                                            redirect_uri=redirect_uri,
                                            scope=my_scopes,open_browser=False))
    # Operate
    def update_result(self):

        res = self.sp.current_playback()
        if res!=None:
            track = res["item"]["name"]
            artist = [art["name"] if i==0 else ","+art["name"] for i,art in enumerate(res["item"]["artists"])][0]
            features = self.sp.audio_features(res["item"]["uri"])
            key = features[0]["key"]
            mode = features[0]["mode"]
            final_result = f"Artist:{artist}\nTrack:{track}\nkey:{keys[key]}-{modes[mode]}\n"
        else:
            final_result = "No track is currently playing" 

        print(f"Result (Python) :\n{final_result}")    
        return final_result


def main(client_id,secret_id,redirect_uri):

    service = Spotifeye(client_id,secret_id,redirect_uri)

    return service.update_result()

if __name__=="__main__":
    main()