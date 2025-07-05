#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include "Button.h"
#include "Input.h"
using namespace std;

int main() {
    Input inputDisplay(10.f, 10.f);  
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Neural Network Visualizer"); 
    Button addLayerButton(30, 500, 150, 50, "ADD LAYER", Button::addLayer);
    Button addNeuronButton(230, 500, 150, 50, "ADD NEURON", Button::addNeuron);
    Network layerList;
    Button buildButton(430, 500, 150, 50, "BUILD", Button::build);
    Button trainButton(630, 500, 150, 50, "TRAIN", Button::train);
    Button testButton(830, 500, 150, 50, "TEST", Button::test);

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (addLayerButton.isMouseOver(window))
                {
                    addLayerButton.onPressed(layerList);
                }

                if (addNeuronButton.isMouseOver(window))
                {
                    if (!layerList.isEmpty())
                    {
                        for (int i = 0; i < layerList.size(); i++)
                        {
                            if (layerList[i].getSelection())
                            {
                                addNeuronButton.onPressed(layerList[i]);
                            }
                        }
                    }
                    else{}
                }

                //only added selection checks for a non-empty network which prevents redundant operations on empty network(has no layers)
                if (!layerList.isEmpty())
                {
                    for (int i = 0; i < layerList.size(); i++)
                    {
                        if (layerList[i].isMouseOver(window))
                        {
                            layerList[i].toggleSelection();
                        }
                    }
                }

                if (buildButton.isMouseOver(window))
                {
                    layerList.buildConnections();
                }

                if (trainButton.isMouseOver(window))
                {
                    layerList.trainNetwork(inputDisplay, window);
                }

                if (testButton.isMouseOver(window))
                {
                    layerList.testNetwork();
                }


            }


        }

        // clear the window with black color
        window.clear(sf::Color::White);
        inputDisplay.draw(window);
        addLayerButton.draw(window);
        addNeuronButton.draw(window);
        buildButton.draw(window);
        trainButton.draw(window);
        testButton.draw(window);

        layerList.draw(window);

        // end the current frame
        window.display();
    }
    return 0;
}
