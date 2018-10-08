class GameVolume{
  private:
    int music_volume;
    int sfx_volume;
  public:
    void set_volumes(){
      music_volume = 50;
      sfx_volume = 50;
    }

    int get_music_volume(){
      return music_volume;
    }

    int get_sfx_volume(){
      return sfx_volume;
    }

    void music_volume_up(){
      music_volume = music_volume + 5;
      if(music_volume > 100){
        music_volume = 100;
      }
    }

    void music_volume_down(){
      music_volume = music_volume - 5;
      if(music_volume < 0){
        music_volume = 0;
      }
    }

    void sfx_volume_up(){
      sfx_volume = sfx_volume + 5;
      if(sfx_volume > 100){
        sfx_volume = 100;
      }
    }

    void sfx_volume_down(){
      sfx_volume = sfx_volume - 5;
      if(sfx_volume > 50){
        sfx_volume = 0;
      }
    }
};