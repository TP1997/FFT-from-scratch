#ifndef FFT_H_INCLUDED
#define FFT_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <valarray>
#include <complex>

#define PI 3.141592653589793238460
using complex=std::complex<double>;

class FFT{
    int bufferSize;
    float *window;
    int sampleRate;     //Samples per second
    int sampleCount;    //Total samples in wav-file
    int pos;
    double freqBinWidth;
    //const sf::Int16* audioSamples;
    sf::Int16 minSampleVal;
    sf::Int16 maxSampleVal;
    sf::SoundBuffer soundBuffer;
    sf::Sound sound;

    sf::VertexArray vtxA;
    sf::VertexArray vtxB;
    sf::VertexArray vtxC;
    std::valarray<complex> samples;
    std::valarray<complex> freqBins;
    std::vector<double> freqMagn;
    std::vector<double> octaveBins; //Magnitude per 1/3 octave
    public:
    FFT(const std::string, int&);
    ~FFT();
    void hamming();
    void fft(std::valarray<complex>&);
    void one_3rd_octave();
    void update();
    double db(complex&);
    void updateVertexArray();
    void updateVertexArray2();
    void draw(sf::RenderWindow &);
    bool isPlaying();
};

#endif // FFT_H_INCLUDED
