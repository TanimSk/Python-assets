from soundplayer import SoundPlayer

p = SoundPlayer("/home/pi/songs/song" + str(songID) + ".mp3", 1)        
p.play()
p.pause()
p.resume()
p.stop()