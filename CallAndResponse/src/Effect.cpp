#include "Effect.h"

Effect::Effect()
{

    noiseStartX = 0;
    noiseStartY = 0;

    resolution.set( "Resolution", 512, 2, 64 );
    noiseFrequency.set( "Noise Frequency", 80.0f, 0.00001f, 4096.0f );
    animate.set( "Animate", true );
    doThreshold.set( "Threshold", false );
    thresholdLow.set( "Treshold Low", 0, 0, 255 );
    thresholdHigh.set( "Treshold High", 127, 0, 255 );
    invert.set( "Invert Threshold", false );
}

Effect::~Effect()
{

}

void Effect::setup()
{
    noiseImage.allocate( resx, resy, OF_IMAGE_COLOR );

}

void Effect::update()
{
    float time = 0.0f;
    if( animate ) time = ofGetElapsedTimef();

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
void Effect::threshold( bool _upload )
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

void Effect::draw()
{
    noiseImage.draw( 0,0, noiseImage.getWidth(), noiseImage.getHeight() );
}

void Effect::draw(float x, float y, float w, float h)
{
    noiseImage.draw( x, y, w, h );
}
