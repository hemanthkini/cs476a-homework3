//
//  TronLookAndFeel.h
//  Homework3
//
//  Created by Hemanth Kini on 10/19/16.
//
//

#ifndef TronLookAndFeel_h
#define TronLookAndFeel_h

class TronLookAndFeel : public LookAndFeel_V3
{
public:
    TronLookAndFeel()
    {
        
    }
    // Make a TRON slider.
    void drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos,
                          const Slider::SliderStyle style, Slider &s) override {
        // Outline
        g.setColour(Colours::limegreen);
        float centery = y + ((float)height / 2.0);
        float height_of_slider_index = 0.8; //Fill up 0.3 of our available height space for the slider.
        float top_left = centery - (((float)height / 2.0) * height_of_slider_index);
        float height_of_slider = height_of_slider_index * height;
        g.drawRect((float)x, top_left, (float)width, height_of_slider);
        
        // Fill in the slider.
        g.fillRect((float)x, top_left, sliderPos - minSliderPos, height_of_slider);
        
        s.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    }
    
    // Make a TRON button
    void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
                              bool isMouseOverButton, bool isButtonDown) override {
        Rectangle<int> buttonArea = button.getLocalBounds();
        g.setColour(Colours::limegreen);
        g.drawRect(buttonArea);
        
        // Fill the button in when pressed.
        if (isButtonDown) {
            g.fillRect(buttonArea);
        }
    }
    
    // Make a TRON toggle button.
    void drawToggleButton(Graphics& g, ToggleButton& button, bool isMouseOverButton, bool isButtonDown) override {
        Rectangle<int> buttonArea = button.getLocalBounds();
        g.setColour(Colours::limegreen);
        g.drawRect(buttonArea);
        
        // Fill the button in when pressed.
        if (button.getToggleState()) {
            g.fillRect(buttonArea);
        }
    }
    
};


#endif /* TronLookAndFeel_h */
