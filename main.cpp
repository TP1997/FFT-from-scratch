#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <valarray>

#include "FFT.h"


using namespace std;
using namespace sf;
void fills_curve(){
    for(int n=0; n<1000; n++){
        //test.s_curve[n]=n;
    }

}
int main()
{

    //RenderWindow window(VideoMode(400, 400), "SFML works!");
    /*
    SoundBuffer sb;
    if(!sb.loadFromFile("Rammstein - Feuer frei!.wav")){
        cout << "Virhe" << endl;
        return -1;
    }
    Sound sound;
    sound.setBuffer(sb);
    sound.play();
    while(sound.getStatus()!= sf::SoundSource::Status::Stopped){


    }
    /*
    //cout << "Total samples2: " << sb.getSampleRate()*sb.getDuration().asSeconds() << endl;

    int totSamples=sb.getSampleCount();
    int sampleRate=sb.getSampleRate();
    float totDuration=sb.getDuration().asSeconds();
    int bufferSize=2048;
    Sound sound;
    sound.setBuffer(sb);
    sound.play();
    int pos,prevpos,n=0;
    while(sound.getStatus()!= sf::SoundSource::Status::Stopped){
        prevpos=pos;
        sf::Time t=sound.getPlayingOffset();
        pos=t.asSeconds()*sampleRate;
        if(pos!=prevpos){
            int endPos=(pos+bufferSize < totSamples)?pos+bufferSize:totSamples;
            cout << "time elapsed (sec): " << t.asSeconds() << endl;
            cout << "pos: " << pos << endl;
            cout << "prevpos: " << prevpos << endl;
            cout << "chunk size: " << bufferSize << endl;
            cout << "chunk interval: [" << pos << "," << endPos << "]" << endl;
            cout << endl;
        }

    }
    cout << "Total samples: " << totSamples << endl;
    cout << "Samples per sec: " << sampleRate << endl;
    cout << "Total duration: " << totDuration << endl;

    const sf::Int16* audioSamples=sb.getSamples();
    valarray<Int16> va(audioSamples, totSamples);
    Int16 max_=va.max();
    Int16 min_=va.min();
    cout << "Max value: " << max_ << endl;
    cout << "Min value: " << min_ << endl;
    cout << endl;
    for(int n=0; n<totSamples; n++){
        if(va[n]==max_)
            cout << "max found in idx[" << n << "]" <<  endl;
        if(va[n]==min_)
            cout << "min found in idx[" << n << "]" <<  endl;
Rammstein - Feuer frei!.wav
100hz.wav
chameleon.wav
ass.wav
saeed.wav
bliz.wav
sifflet.wav
funk.wav
once.wav
du.wav
arrietty.wav
nuc.wav
lunatic.wav
sauce.wav
spoken.wav
owen.wav
whisp.wav
bc3.wav
radio.wav
idiot.wav
slip.wav
up.wav
slayer.wav
kids.wav
vege.wav
5cm.wav
Nutmeg.wav
bay.wav
splinter.wav
strobe.wav
strobe2.wav
    }*/
    string fname="gotye.wav";
    //16384
    int bfsize=16384;
    RenderWindow window(VideoMode(2048, 800), "SFML works!");
    //window.setFramerateLimit(60);
    FFT fft(fname, bfsize);
    while (window.isOpen() && fft.isPlaying())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear();
        fft.update();
        fft.draw(window);
        window.display();

    }

    return 0;
}
