#include<FastLED.h>
#include <cstdint>

#define NUM_LEDS 1
#define DATA_PIN LED_RGB
#define LED_TYPE WS2812
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

#define BRIGHTNESS 30
#define FRAMES_PER_SECOND 120

_FL_DEFPIN( DATA_PIN, BSP_IO_PORT_01_PIN_05, R_PORT1_BASE );

void setup() {
  Serial.begin(115200);
  while (!Serial){delay(100);}; // wait for serial attach

  Serial.println("Initializing RGB test.");

  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);

  FastLED.setBrightness(BRIGHTNESS);

  Serial.println("Initialized.");
}

typedef void (*SimplePatternList[])();
SimplePatternList patterns = { rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };

uint8_t currentPattern = 0; // Index of the current pattern
uint8_t hue = 0; // rotating "base color" used by many of the patterns

void loop()
{
  patterns[currentPattern]();

  FastLED.show();

  FastLED.delay(1000/FRAMES_PER_SECOND);

  EVERY_N_MILLISECONDS( 20 ) { hue++; }
  EVERY_N_SECONDS( 10 ) { nextPattern(); }
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  currentPattern = (currentPattern + 1) % ARRAY_SIZE(patterns);
}

void rainbow()
{
  fill_rainbow( leds, NUM_LEDS, hue, 7);
}

void rainbowWithGlitter()
{
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter )
{
  if (random8() < chanceOfGlitter ) 
  {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti()
{
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( hue + random8(64), 200, 255);
}

void sinelon()
{
  fadeToBlackBy(leds, NUM_LEDS, 20);
  int pos = beatsin16(13,0,NUM_LEDS-1);
  leds[pos] += CHSV(hue, 255, 192);
}

void bpm()
{
  uint8_t beatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( beatsPerMinute, 64, 255);
  for(int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = ColorFromPalette(palette, hue+(i*2), beat-hue+(i*10));
  }
}

void juggle()
{
  fadeToBlackBy(leds, NUM_LEDS, 20);
  uint8_t dothue = 0;
  for( int i = 0; i < 8; i++)
  {
    leds[beatsin16(i+7, 0, NUM_LEDS-1)] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}
