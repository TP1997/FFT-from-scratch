#include <math.h>
#include <iostream>
#include <algorithm>
#include "FFT.h"
#include "manip.h"

FFT::FFT(const std::string filename, int &bufferSize_){
    pos=0;
    soundBuffer.loadFromFile("files/"+filename);
    sampleRate=soundBuffer.getSampleRate()*soundBuffer.getChannelCount();
    std::cout << soundBuffer.getChannelCount() << std::endl;
    sampleCount=soundBuffer.getSampleCount();
    freqBinWidth=sampleRate/bufferSize_;

    //audioSamples=new sf::Int16[sampleCount];
    //audioSamples=soundBuffer.getSamples();

    minSampleVal=*(std::min_element(soundBuffer.getSamples(), soundBuffer.getSamples()+sampleCount));
    maxSampleVal=*(std::max_element(soundBuffer.getSamples(), soundBuffer.getSamples()+sampleCount));

    sound.setBuffer(soundBuffer);

    bufferSize=std::min(bufferSize_, sampleCount);

    samples.resize(bufferSize);
    freqBins.resize(bufferSize);
    freqMagn.resize(bufferSize);

    vtxA.setPrimitiveType(sf::LineStrip);
    vtxA.resize(bufferSize);
    vtxB.setPrimitiveType(sf::Lines);
    vtxC.setPrimitiveType(sf::Quads);

    window=new float[bufferSize];
    for(int n=0; n<bufferSize; n++){
        window[n]=0.54 - 0.46*std::cos(2*PI*n/(bufferSize-1))*1.0;
    }

    sound.play();

}
FFT::~FFT(){
    delete[] window;
}//timeDomainSamples[i-pos].real()*0.01+200
void FFT::hamming(){
    pos=sound.getPlayingOffset().asSeconds()*sampleRate;
    if(pos+bufferSize < sampleCount){
        for(int i=pos; i<pos+bufferSize; i++){
            //HAMMING
            samples[i-pos]=complex(soundBuffer.getSamples()[i]*window[i-pos],0);//muuta 0.3
            vtxA[i-pos]=sf::Vertex(sf::Vector2f(50,100)+sf::Vector2f((i-pos)*500/bufferSize, algorithms::scale(samples[i-pos].real(), minSampleVal, maxSampleVal)), sf::Color::Cyan);
        }
    }

}//algorithms::scale(timeDomainSamples[i-pos].real(), minSampleVal, maxSampleVal)+400
//timeDomainSamples[i-pos].real()+400
//vtxA[i-pos]=sf::Vertex(sf::Vector2f((i-pos)*0.03+200, timeDomainSamples[i-pos].real()*0.02+400), sf::Color::Cyan);
//vtxA[i-pos]=vtxA[i-pos]=sf::Vertex(sf::Vector2f((i-pos)*0.03+200, algorithms::scale(timeDomainSamples[i-pos].real(), minSampleVal, maxSampleVal)+400), sf::Color::Cyan);

void FFT::fft(std::valarray<complex>& curr){
    int N=curr.size();
    if(N==1) return;

    std::valarray<complex> even=curr[std::slice(0, N/2, 2)];
    std::valarray<complex> odd=curr[std::slice(1, N/2, 2)];

    fft(even);
    fft(odd);

    for(int k=0; k<N/2; k++){
        complex e=complex(std::cos(-2*PI*k/N), std::sin(-2*PI*k/N))*odd[k];
        curr[k]=even[k] + e;
        curr[k+N/2]=even[k] - e;
    }

}

void FFT::update(){
    hamming();
    freqBins=samples;//std::valarray<complex>(samples.data(), bufferSize);
    fft(freqBins);
    one_3rd_octave();
    updateVertexArray2();
    //updateVertexArray();


}

void FFT::one_3rd_octave(){
    octaveBins.clear();
    for(int n=0; n<bufferSize; n++){
        freqMagn[n]=std::abs(freqBins[n]);
    }
    const double factor=std::cbrt(2);
    double startFq=11.2f;
    double endFq=startFq*factor;
    while(endFq<=sampleRate/2){
        int strtIdx=startFq/freqBinWidth;
        int endIdx=endFq/freqBinWidth;

        double maxMagn=*(std::max_element(freqMagn.begin()+strtIdx, freqMagn.begin()+endIdx));
        //octaveBins.push_back(maxMagn);
        octaveBins.push_back(std::max(algorithms::exponential(maxMagn), 5.0));
        //octaveBins.push_back(std::sqrt(40*maxMagn));
        //octaveBins.push_back(algorithms::test(maxMagn));
        //octaveBins.push_back(maxMagn*std::log10(maxMagn));
        startFq*=factor;
        endFq*=factor;
    }
}
void FFT::updateVertexArray2(){
    vtxC.clear();

    double start_=500.0;
    double lowy=750.0;
    double wdth=20.0;
    for(int n=0; n<octaveBins.size(); n++){
        //double magn=octaveBins[n]*0.00001;
        double magn=octaveBins[n]*1;
        //double magn=octaveBins[n]*0.01;
        //double magn=octaveBins[n]*0.00001;
        sf::Color custom=algorithms::calcColor(magn);
        double pos=start_+20*n;
        vtxC.append(sf::Vertex(sf::Vector2f(pos, lowy), custom));
        vtxC.append(sf::Vertex(sf::Vector2f(pos, lowy-magn-5), custom));
        vtxC.append(sf::Vertex(sf::Vector2f(pos+wdth, lowy-magn-5), custom));
        vtxC.append(sf::Vertex(sf::Vector2f(pos+wdth, lowy), custom));
    }

}

void FFT::updateVertexArray(){
    vtxB.clear();


    int lins=bufferSize/2;
    double start_=-500;
    double end_=2048;
    double lowy=750.0;
    double dist=(end_-start_)/(lins);
    int hop=((bufferSize/2)/lins);
    double Fs=44100.0;

    for(float f=1; f<bufferSize/2; f*=1.01){//int k=0; k<bufferSize/2; k+=hop
        int k=(int)f;
        //double mag=20*std::log10(std::abs(freqBins[k])/(0.00001));//(bufferSize/2);*0.000005
        //double mag=std::abs(freqBins[k])*0.000005;
        double mag=std::max(algorithms::exponential(std::abs(freqBins[k])), 0.0);
        sf::Color custom=algorithms::calcColor(mag);
        //mag=std::log10(mag)*20;

        //double pos=Fs*std::sqrt(50*k)/(bufferSize);
        //double pos=50*std::log(std::pow((k+1), 3));
        //double pos=std::log(std::pow(k, 2))*std::pow(k, 0.8);
        double pos=start_+(std::log(k+20)/std::log(bufferSize))*end_;
        //double pos=(Fs*k)/bufferSize;

        vtxB.append(sf::Vertex(sf::Vector2f(pos, lowy), sf::Color::Green)); //alataso, älä muuta
        vtxB.append(sf::Vertex(sf::Vector2f(pos, lowy-mag), custom));//ylätaso
        //vtxB.append(sf::Vertex(sf::Vector2f(start_+(k+1)*dist, lowy-mag*16), sf::Color::Red));
        //vtxB.append(sf::Vertex(sf::Vector2f(start_+(k+1)*dist, lowy), sf::Color::Cyan));
    }
    //std::cout << vtxB.getVertexCount()/2 << " : " << bufferSize/2<< std::endl;
    //std::cout << dist<< std::endl;

}

void FFT::draw(sf::RenderWindow &rw){
    rw.draw(vtxA);
    //rw.draw(vtxB);
    rw.draw(vtxC);
}

double FFT::db(complex &c){
    return std::log10(std::sqrt(std::abs(c)))*20;
}

bool FFT::isPlaying(){
    return sound.getStatus()== sf::SoundSource::Status::Playing;
}
