#include "NoiseEffect.h"

NoiseEffect::NoiseEffect()
{
    name = "Noise";
    parameters.setName(name + baseName);
    parameters.add(resolution.set( "Resolution", 512, 2, 64 ));
    parameters.add(noiseFrequency.set( "Noise Frequency", 20.0f, 0.00001f, 4096.0f ));
    parameters.add(animate.set( "Animate", true ));
    parameters.add(doThreshold.set( "Threshold", false ));
    parameters.add(thresholdLow.set( "Treshold Low", 0, 0, 255 ));
    parameters.add(thresholdHigh.set( "Treshold High", 127, 0, 255 ));
    parameters.add(invert.set( "Invert Threshold", false ));

    noiseStartX = 0;
    noiseStartY = 0;
}

NoiseEffect::~NoiseEffect()
{

}

void NoiseEffect::setup()
{
    noiseImage.allocate( resx, resy, OF_IMAGE_GRAYSCALE);

}

void NoiseEffect::begin()
{
    if(!bEnabled) return;
}

void NoiseEffect::update(float curTime)
{
    if(!bEnabled) return;

    BaseEffect::update(curTime);

    float time = 0.0f;
    if( animate ) time = ofGetElapsedTimef()/1.0f;

    ofPixelsRef pixels = noiseImage.getPixels();

    int tmpIndex = 0;
    for( int y = 0; y < noiseImage.getHeight(); y++ )
    {
        for( int x = 0; x < noiseImage.getWidth(); x++ )
        {
            // We're grabbing a single reading from the noise function here, but we can also add together more
            // readings at different frequencies to make more complex patterns

            float tmpNoise = ofNoise( (noiseStartX + x) / noiseFrequency, (noiseStartY + y) / noiseFrequency, time );

            pixels[tmpIndex] = tmpNoise * 255.0f;
            tmpIndex++;
        }
    }

    if( doThreshold)
    {
        threshold( false );
    }

    noiseImage.update(); // uploads the new pixels to the gfx card
}

//--------------------------------------------------------------
void NoiseEffect::threshold( bool _upload )
{
    ofPixelsRef pixels = noiseImage.getPixels();

    int tmpIndex = 0;
    for( int y = 0; y < noiseImage.getHeight(); y++ )
    {
        for( int x = 0; x < noiseImage.getWidth(); x++ )
        {
            if( pixels[tmpIndex] >= thresholdLow && pixels[tmpIndex] <= thresholdHigh )
            {
                pixels[tmpIndex] = 255;
            }
            else
            {
                pixels[tmpIndex] = 0;
            }

            if( invert )
            {
                pixels[tmpIndex] = 255 - pixels[tmpIndex];
            }

            tmpIndex++;
        }
    }


    if( _upload )
    {
        noiseImage.update();
    }
}


void NoiseEffect::draw(float x, float y, float w, float h)
{
    if(!bEnabled) return;

    ofPushStyle();
    ofSetColor(255,0,255);
    noiseImage.draw( x, y, w, h );
    ofPopStyle();

}
